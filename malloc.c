# include "malloc.h"

meta info = {NULL, NULL, NULL};

void	*ft_malloc(size_t req)
{
	zone	**zone = NULL;

	if (!req)					{ req = 16; }
	if (req > SIZE_MAX - 15)	{ return NULL; }
	size_t	size = ALIGN16(req);

	if (size <= N_TINY)			{ ft_printf("Tiny!!!!!\n"); zone = &info.tiny; }
	else if (size <= M_SMALL)	{ ft_printf("Small!!!!\n"); zone = &info.small; }
	else { ft_printf("Large!!!!\n"); return (AddLargeBlock(size)); }

	if (!(*zone)->lst)
	{
		(*zone)->lst = AddBlock(size, *zone);
		return ((void *)(*zone)->lst->mem);
	}
	return (FindFreeBlock(size, *zone));
}

void	ft_free(void *ptr)
{
	block	*chunk = FindBlock(ptr);

	if (!chunk) { return ; }
	chunk->free = true;
	if (chunk->size > M_SMALL + sizeof(struct blockdata))
		FreeLargeBlock(chunk);
	CheckForCoalesce();
}

void	*ft_realloc(void *ptr, size_t req)
{
	block	*new = NULL, *chunk = FindBlock(ptr);

	if (!ptr)			{ return (ft_malloc(req)); }
	if (ptr && !req)	{ ft_free(ptr); }
	if (!req || !chunk || req > SIZE_MAX - 15)	{ return (NULL); }
	size_t	size = ALIGN16(req);

	if (size + sizeof(struct blockdata) == chunk->size)
		return ((void *)chunk->mem);

	ft_printf("\n\nchunk->size = %d  > %d ??\n\n", chunk->size, M_SMALL + sizeof(struct blockdata));

	if		(size <= N_TINY)	{ ft_printf("New Tiny!!!!\n"); new = FindBlock(FindFreeBlock(size, info.tiny)); }
	else if (size <= M_SMALL)	{ ft_printf("New Small!!!!\n"); new = FindBlock(FindFreeBlock(size, info.small)); }
	else						{ ft_printf("New Large!!!!\n"); new = FindBlock(AddLargeBlock(size)); }

	if (!new)	{ return (NULL); }
	ft_memcpy(new->mem, chunk->mem, chunk->size - sizeof(struct blockdata));

	chunk->free = true;
	ft_printf("\n\nchunk->size = %d  > %d ??\n\n", chunk->size, M_SMALL + sizeof(struct blockdata));
	if (chunk->size > M_SMALL + sizeof(struct blockdata))
	{
		ft_printf("Old Large!!!!\n");
		FreeLargeBlock(chunk);
	}

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
		if (zone == info.tiny)			{ ft_printf("TINY : %p\n", zone->beg); }
		else if (zone == info.small)	{ ft_printf("SMALL : %p\n", zone->beg); }
		else if (zone == info.large)	{ ft_printf("LARGE : %p\n", zone->beg); }
		if (DEBUG) { ft_printf("~   %sZONE%s  struct %p : %d bytes\n", B_BLUE, RESET, zone, sizeof(struct zonedata)); }

		r_tot += sizeof(struct zonedata);
		chunk = zone->lst;
		while(chunk)
		{
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
		zone = zone->next;
	}
	ft_printf("Total : %d bytes\n", tot);
	if (DEBUG) { ft_printf("~   %sREAL%s Total : %d bytes\n", B_GREEN, RESET, r_tot); } 
}

// else if (chunk->size > M_SMALL + sizeof(struct blockdata))
	// {
	// 	if (size <= N_TINY)
	// 		 new = FindBlock(FindFreeBlock(size, info.tiny));
	// 	else if (size <= N_SMALL)
	// 		 new = FindBlock(FindFreeBlock(size, info.small));
	// 	else if (size > M_SMALL)
	// 		new = FindBlock(AddLargeBlock(size));
	// 	ft_memcpy(new->mem, chunk->mem, size);
	// 	FreeLargeBlock(chunk);
	// 	return ((void *)new->mem);
	// }