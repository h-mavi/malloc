# include "malloc_bonus.h"

/* Auto Mutex-locking */
void	*FindFreeBlock(size_t size, zone *zone)
{
	// pthread_mutex_lock(&zone->mutex_z);
	block	*pres = zone->lst;

	if (zone == info.large) { /*pthread_mutex_unlock(&zone->mutex_z);*/ return (NULL); }
	while (pres)
	{
		if (pres->size >= size + sizeof(struct blockdata) && pres->free)
		{
			if (pres->size - (size + sizeof(struct blockdata)) >= sizeof(struct blockdata) + 16) {
				void *tmp = SplitBlock(pres, size)->mem;
				// pthread_mutex_unlock(&zone->mutex_z);
				return (tmp);
			}
			else if (pres->size - sizeof(struct blockdata) == size)
			{
				pres->free = false;
				// pthread_mutex_unlock(&zone->mutex_z);
				return ((void *)pres->mem);
			}
		}
		pres = pres->next;
	}
	void *tmp = AddBlock(size, zone)->mem;
	// pthread_mutex_unlock(&zone->mutex_z);
	return (tmp);
}

/* Auto Mutex-locking */
zone	*FindFirstZone()
{
	zone	*tmp = NULL;

	// pthread_mutex_lock(&info.mutex_i);
	if (info.tiny)			{ tmp = info.tiny; }
	else if (info.small)	{ tmp = info.small; }
	else if (info.large)	{ tmp = info.large; }
	// pthread_mutex_unlock(&info.mutex_i);
	return (tmp);
}

/* Auto Mutex-locking */
zone	*FindNextZone(const zone *req_z)
{
	zone	*tmp = NULL;

	// pthread_mutex_lock(&info.mutex_i);
	if (req_z == info.tiny)
	{
		if (info.small)			{ tmp = info.small; }
		else if (info.large)	{ tmp = info.large; }
	}
	else if (req_z == info.small && info.large)
		tmp = info.large;
	// pthread_mutex_unlock(&info.mutex_i);
	return (tmp);
}

/* Auto Mutex-locking */
block	*FindBlock(void *ptr)
{
	zone	*zone = FindFirstZone();
	block	*chunk = NULL, *tmp = NULL;

	if (!ptr) { return (NULL); }
	while (zone && !tmp)
	{
		// pthread_mutex_lock(&zone->mutex_z);
		chunk = zone->lst;
		while(chunk && !tmp)
		{
			if (chunk->mem == ptr)
				tmp = chunk;
			chunk = chunk->next;
		}
		// pthread_mutex_unlock(&zone->mutex_z);
		zone = FindNextZone(zone);
	}
	return (tmp);
}

/* Auto Mutex-locking */
zone	*FindBlockZone(void *ptr)
{
	block	*chunk = NULL;
	zone	*tmp = NULL,
			*zone = FindFirstZone();

	if (!ptr) { return (NULL); }
	while (zone && !tmp)
	{
		// pthread_mutex_lock(&zone->mutex_z);
		chunk = zone->lst;
		while(chunk && !tmp)
		{
			if (chunk->mem == ptr)
				tmp = zone;
			chunk = chunk->next;
		}
		// pthread_mutex_unlock(&zone->mutex_z);
		zone = FindNextZone(zone);
	}
	return (tmp);
}
