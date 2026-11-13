# include "malloc.h"

void	*FindFreeBlock(size_t size, zone *zone)
{
	block	*pres = zone->lst;

	if (zone == info.large) { return (NULL); }
	while (pres && pres->next)
	{
		if (pres->size == size + sizeof(struct blockdata) && pres->free)
		{
			pres->free = false;
			return ((void *)pres->mem);
		}
		else if (zone != info.large && pres->size > size + sizeof(struct blockdata) && pres->free && \
			pres->size - size - sizeof(struct blockdata) > sizeof(struct blockdata))
			return ((void *)SplitBlock(pres, size)->mem);

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
