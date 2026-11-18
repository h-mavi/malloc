# include "malloc.h"

void	*FindFreeBlock(size_t size, zone *zone)
{
	block	*pres = zone->lst;

	if (zone == info.large) { return (NULL); }
	while (pres)
	{
		if (pres->size >= size + sizeof(struct blockdata) && pres->free) // pres->size = 64,size = 32
		{
			ft_printf("%d - (%d + %d) = %d >= %d + 16", pres->size, size, sizeof(struct blockdata), pres->size - (size + sizeof(struct blockdata)), sizeof(struct blockdata));
			if (pres->size - (size + sizeof(struct blockdata)) >= sizeof(struct blockdata) + 16)
				return ((void *)SplitBlock(pres, size)->mem);
			else if (pres->size - sizeof(struct blockdata) == size) //entra qui ma non va bene? forse è sbagliato l'arrotondamento a mult. di 16
			{
				pres->free = false;
				return ((void *)pres->mem);
			}
		}
		pres = pres->next;
	}
	return ((void *)AddBlock(size, zone)->mem);
}

zone	*FindFirstZone()
{
	if (info.tiny)			{ return (info.tiny); }
	else if (info.small)	{ return (info.small); }
	else if (info.large)	{ return (info.large); }
	return (NULL);
}

block	*FindBlock(void *ptr)
{
	zone	*zone = FindFirstZone();
	block	*chunk = NULL;

	if (!ptr) { return (NULL); }
	while (zone)
	{
		chunk = zone->lst;
		while(chunk)
		{
			if (chunk->mem == ptr)
				return (chunk);
			chunk = chunk->next;
		}
		zone = zone->next;
	}
	return (NULL);
}
