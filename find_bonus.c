# include "malloc_bonus.h"

void	*FindFreeBlock(size_t size, zone *zone)
{
	block	*pres = zone->lst;

	if (zone == info.large) { return (NULL); }
	while (pres)
	{
		if (pres->size >= size + sizeof(struct blockdata) && pres->free)
		{
			if (pres->size - (size + sizeof(struct blockdata)) >= sizeof(struct blockdata) + 16)
				return ((void *)SplitBlock(pres, size)->mem);
			pres->free = false;
			return ((void *)pres->mem);
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

zone	*FindNextZone(const zone *zone)
{
	if (zone == info.tiny)
	{
		if (info.small)			{ return (info.small); }
		else if (info.large)	{ return (info.large); }
	}
	else if (zone == info.small && info.large)
		return (info.large);
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
		zone = FindNextZone(zone);
	}
	return (NULL);
}
