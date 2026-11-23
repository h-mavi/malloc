# include "malloc_bonus.h"

meta info = {NULL, NULL, NULL};

void	*ft_malloc(size_t req)
{
	zone	**zone = NULL;

	if (!req)					{ req = 16; }
	if (req > SIZE_MAX - 15)	{ return NULL; }
	size_t	size = ALIGN16(req);

	// pthread_mutex_lock(&info.mutex_i);
	if (size <= N_TINY)			{ zone = &info.tiny; }
	else if (size <= M_SMALL)	{ zone = &info.small; }
	else {
		// pthread_mutex_unlock(&info.mutex_i);
		return (AddLargeBlock(size));
	}
	// pthread_mutex_unlock(&info.mutex_i);

	// pthread_mutex_lock(&(*zone)->mutex_z);
	if (!(*zone)->lst)
	{
		(*zone)->lst = AddBlock(size, *zone);
		// pthread_mutex_unlock(&(*zone)->mutex_z);
		return ((void *)(*zone)->lst->mem);
	}
	// pthread_mutex_unlock(&(*zone)->mutex_z);
	return (FindFreeBlock(size, *zone));
}

void	ft_free(void *ptr)
{
	zone	*zone = FindBlockZone(ptr);
	block	*chunk = FindBlock(ptr);

	// pthread_mutex_lock(&zone->mutex_z);
	if (!chunk) { /*pthread_mutex_unlock(&zone->mutex_z);*/ return ; }
	chunk->free = true;
	if (chunk->f_zone == LARGE)
		FreeLargeBlock(chunk);
	// pthread_mutex_unlock(&zone->mutex_z);
	CheckForCoalesce();
}

void	*ft_realloc(void *ptr, size_t req)
{
	block	*new = NULL,	*chunk = FindBlock(ptr);
	zone	*new_z = NULL,	*chunk_z = FindBlockZone(ptr);

	if (!ptr)			{ return (ft_malloc(req)); }
	// pthread_mutex_lock(&chunk_z->mutex_z);
	if (ptr && !req)	{ ft_free(ptr); }
	if (!req || !chunk || req > SIZE_MAX - 15) {
		// pthread_mutex_unlock(&chunk_z->mutex_z);
		return (NULL);
	}
	size_t	size = ALIGN16(req);

	if (size + sizeof(struct blockdata) == chunk->size) {
		// pthread_mutex_unlock(&chunk_z->mutex_z);
		return ((void *)chunk->mem);
	}

	if		(size <= N_TINY)	{ new = FindBlock(FindFreeBlock(size, info.tiny)); }
	else if (size <= M_SMALL)	{ new = FindBlock(FindFreeBlock(size, info.small)); }
	else						{ new = FindBlock(AddLargeBlock(size)); }

	if (!new) {
		// pthread_mutex_unlock(&chunk_z->mutex_z);
		return (NULL);
	}
	new_z = FindBlockZone(new);
	// if (new->f_zone != chunk->f_zone)	pthread_mutex_lock(&new_z->mutex_z);
	ft_memcpy(new->mem, chunk->mem, size);
	// if (new->f_zone != chunk->f_zone)	pthread_mutex_unlock(&new_z->mutex_z);

	chunk->free = true;
	if (chunk->f_zone == LARGE)
		FreeLargeBlock(chunk);
	// pthread_mutex_unlock(&chunk_z->mutex_z);

	CheckForCoalesce();
	return ((void *)new->mem);
}

void    show_alloc_mem()
{
	block   *chunk;
	zone    *zone = FindFirstZone();
	long     r_size, tot = 0, r_tot = 0;

	if (DEBUG) { ft_printf("[ DEBUG MODE : %sON%s ]\n", B_GREEN, RESET); }
	while (zone)
	{
		// pthread_mutex_lock(&info.mutex_i);
		if (zone == info.tiny)			{ ft_printf("TINY : %p\n", zone->beg); }
		else if (zone == info.small)	{ ft_printf("SMALL : %p\n", zone->beg); }
		else if (zone == info.large)	{ ft_printf("LARGE : %p\n", zone->beg); }
		// pthread_mutex_unlock(&info.mutex_i);
		if (DEBUG) { ft_printf("~   %sZONE%s  struct %p : %d bytes\n", B_BLUE, RESET, zone, sizeof(struct zonedata)); }

		r_tot += sizeof(struct zonedata);
		chunk = zone->lst;
		while(chunk)
		{
			// pthread_mutex_lock(&zone->mutex_z);
			r_size = chunk->size - sizeof(struct blockdata);
			if (DEBUG) { ft_printf("~   %sBLOCK%s struct %p : %d bytes\n", B_RED, RESET, chunk, sizeof(struct blockdata)); }
			if (!chunk->free)
			{
				tot += r_size;
				r_tot += chunk->size;
				ft_printf("%p - %p : %d bytes\n", chunk->mem, chunk->mem + r_size, r_size);
			}
			if (DEBUG && chunk->free)
			{
				r_tot += chunk->size;
				ft_printf("%p - %p : %d bytes <- FREED\n", chunk->mem, chunk->mem + r_size, r_size);
			}
			chunk = chunk->next;
		}
		// pthread_mutex_unlock(&zone->mutex_z);
		zone = FindNextZone(zone);
	}
	ft_printf("Total : %d bytes\n", tot);
	if (DEBUG) { ft_printf("~   %sREAL%s Total : %d bytes\n", B_GREEN, RESET, r_tot); } 
}

// idee su come sistemare i mutex:
/*
	Il problema però resta, perché avviene dopo un lock su un puntatore che può già essere diventato non valido.

	Critico: race TOCTOU tra FindBlock/FindBlockZone e uso successivo.
	FindBlock e FindBlockZone cercano sotto lock locale ma rilasciano lock prima di ritornare il puntatore in find_bonus.c:72 e find_bonus.c:96.
	Il chiamante poi usa quel puntatore dopo, ad esempio in malloc_bonus.c:38 o malloc_bonus.c:54.
	Tra “find” e “use”, un altro thread può modificare/coalescare/unmap.

	Alta: show_alloc_mem ha lock nel punto sbagliato nel loop.
	Dentro il while fai lock a ogni iterazione in malloc_bonus.c:108, ma l’unlock è uno solo fuori dal while in malloc_bonus.c:124.
	Questo porta a deadlock al secondo giro (mutex non ricorsivo) o comunque a comportamento non corretto.

	Alta: possibile crash in free su ptr invalido.
	Prendi la zona in malloc_bonus.c:35, ma fai lock in malloc_bonus.c:38 prima di verificare se zone è NULL.
	Se ptr non è tuo, FindBlockZone può tornare NULL e il lock crasha.

	Media: FindFreeBlock non riusa blocchi più grandi non splittabili.
	In find_bonus.c:19 accetti solo il caso “esattamente uguale” quando non splitti.
	Se il blocco è più grande ma il resto è troppo piccolo per creare un nuovo header, dovresti comunque allocarlo (pres->free = false), altrimenti frammenti e allochi nuovo blocco inutilmente.

	Media: lettura info.large senza lock metadata in coalesce.
	Il while in check_bonus.c:9 confronta zone != info.large senza proteggere quella lettura con info.mutex_i.
	Con aggiornamenti concorrenti del metadata è una race.

	Media: FreeLargeBlock non protegge metadata/large list al suo interno.
	In utils_bonus.c:129 e utils_bonus.c:138 manipoli info.large e la lista senza lock locale della funzione.
	Se la chiami da percorsi non perfettamente serializzati, può rompersi facilmente.

	Build blocker: MAP_ANON non definito nel tuo ambiente.
	Errori di compilazione su utils_bonus.c:7, utils_bonus.c:15, utils_bonus.c:56, utils_bonus.c:83.
	Serve MAP_ANONYMOUS o macro compatibile.

	In sintesi: hai corretto varie cose, ma restano soprattutto problemi di ordine temporale find/use e lock placement.
	Il fix più robusto è evitare funzioni “find che sbloccano e ritornano raw pointer”, e far sì che il lock della zona copra ricerca + uso nello stesso tratto atomico.
*/