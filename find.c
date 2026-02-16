# include "head.h"

void	*FindFreeBlock(size_t size, zone *zone)
{
	block	*pres = zone->lst;

	while (pres)
	{
		if (pres->size == size + sizeof(struct blockdata) && pres->free)
		{
			pres->free = false;
			return ((void *)pres->mem);
		}
		else if (zone != info.large && pres->size > size + sizeof(struct blockdata) && pres->free && \
			pres->size - size - sizeof(struct blockdata) > sizeof(struct blockdata))
			return ((void *)SplitBlock(pres, size)->mem);

		if (pres->next == NULL) { break; }
		pres = pres->next;
	}
	if (zone == info.large) { return (NULL); }
	pres->next = AddBlock(size, zone);
	return ((void *)pres->next->mem);
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
