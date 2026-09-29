# include "head.h"

meta info = {NULL, NULL, NULL};

void	*malloc(size_t size)
{
	zone	**zone = NULL;
	size_t	size_zone;

	if (!size)					{ size = 16; }
	if (size <= N_TINY)			{ zone = &info.tiny; size_zone = TINY_ZONE; }
	else if (size <= M_SMALL)	{ zone = &info.small; size_zone = SMALL_ZONE; }
	else { return (AddLargeBlock(size)); }

	if (!(*zone)->lst)
	{
		(*zone)->lst = AddBlock(size, *zone);
		return ((void *)(*zone)->lst->mem);
	}
	else { return (FindFreeBlock(size, *zone)); }

	return (NULL);
}

void	free(void *ptr)
{
	block	*chunk = FindBlock(ptr);

	if (!chunk) { return ; }
	chunk->free = true;
	if (chunk->size > M_SMALL + sizeof(struct blockdata))
		FreeLargeBlock(chunk);
	CheckForCoalesce();
}

void	*realloc(void *ptr, size_t size)
{
	block	*new = NULL, *chunk = FindBlock(ptr);

	if (!ptr)			{ return (malloc(size)); }
	if (ptr && !size)	{ free(ptr); return (NULL); }
	if (!chunk)			{ return (NULL); }

	if (size + sizeof(struct blockdata) == chunk->size)
		return ((void *)chunk->mem);
	else if (size + sizeof(struct blockdata) < chunk->size)
		return ((void *)SplitBlock(chunk, size)->mem);
	else if (!chunk->next && size + sizeof(struct blockdata) > chunk->size)
		chunk->size = size + sizeof(struct blockdata);

	if (chunk->next && chunk->mem + size > (void *)chunk->next)
	{
		chunk->free = true;
		CheckForCoalesce();
		if (size <= N_TINY)			{ new = FindBlock(FindFreeBlock(size, info.tiny)); }
		else if (size <= M_SMALL)	{ new = FindBlock(FindFreeBlock(size, info.small)); }
		else						{ new = FindBlock(FindFreeBlock(size, info.large)); }
		ft_memcpy(new->mem, chunk->mem, chunk->size - sizeof(struct blockdata));
		return ((void *)new->mem);
	}

	return ((void *)chunk->mem);
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
			if (chunk->free == false)
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

