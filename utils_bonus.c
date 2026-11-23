# include "malloc_bonus.h"

void	InitializeZone()
{
	// pthread_mutex_init(&info.mutex_i, NULL);

	info.small = mmap(NULL, sizeof(struct zonedata) + SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (info.small == MAP_FAILED) { ft_putstr_fd("\033[1;31mERROR ALLOCATION FAILED\n\033[0m", 2); }
	VALGRIND_MALLOCLIKE_BLOCK(info.small, sizeof(struct zonedata) + SMALL_ZONE, 0, 0);
	info.small->lst = NULL;
	info.small->size = sizeof(struct zonedata) + SMALL_ZONE;
	info.small->beg = (void*)info.small + sizeof(struct zonedata);
	// pthread_mutex_init(&info.small->mutex_z, NULL);

	info.tiny = mmap(NULL, sizeof(struct zonedata) + TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (info.tiny == MAP_FAILED) { ft_putstr_fd("\033[1;31mERROR ALLOCATION FAILED\n\033[0m", 2); }
	VALGRIND_MALLOCLIKE_BLOCK(info.tiny, sizeof(struct zonedata) + TINY_ZONE, 0, 0);
	info.tiny->lst = NULL;
	info.tiny->size = sizeof(struct zonedata) + TINY_ZONE;
	info.tiny->beg = (void*)info.tiny + sizeof(struct zonedata);
	// pthread_mutex_init(&info.tiny->mutex_z, NULL);
}

/* Extern Mutex-locking */
block	*AddBlock(size_t size, const zone *zone)
{
	block	*ex, *chunk;

	if (zone->lst)
	{
		ex = zone->lst;
		while (ex->next)
			ex = ex->next;
		chunk = (block*)((void*)ex + ex->size);
		ex->next = chunk;
	}
	else
		chunk = zone->beg;

	chunk->next = NULL;
	chunk->free = false;
	chunk->f_zone = size > N_TINY ? SMALL : TINY;
	chunk->size = size + sizeof(struct blockdata);
	chunk->mem = (void*)chunk + sizeof(struct blockdata);
	return (chunk);
}

/* Auto Mutex-locking */
void	*AddLargeBlock(size_t size)
{
	block	*chunk, *ex;

	// pthread_mutex_lock(&info.mutex_i);
	if (!info.large)
	{
		info.large = mmap(NULL, sizeof(struct zonedata) + sizeof(struct blockdata) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		if (info.large == MAP_FAILED) {
			// pthread_mutex_unlock(&info.mutex_i);
			ft_putstr_fd("\033[1;31mERROR ALLOCATION FAILED\n\033[0m", 2);
			return (NULL);
		}
		VALGRIND_MALLOCLIKE_BLOCK(info.large, sizeof(struct zonedata) + sizeof(struct blockdata) + size, 0, 0);

		info.large->beg = (void *)info.large + sizeof(struct zonedata);
		info.large->size = sizeof(struct zonedata) + sizeof(struct blockdata) + size;
		info.large->lst = info.large->beg;
		// pthread_mutex_init(&info.large->mutex_z, NULL);

		// pthread_mutex_lock(&info.large->mutex_z);
		info.large->lst->mem = info.large->lst + sizeof(struct blockdata);
		info.large->lst->size = size + sizeof(struct blockdata);
		info.large->lst->free = false;
		info.large->lst->next = NULL;
		info.large->lst->f_zone = LARGE;
		// pthread_mutex_unlock(&info.large->mutex_z);

		// pthread_mutex_unlock(&info.mutex_i);
		return ((void *)info.large->lst->mem);
	}
	// pthread_mutex_unlock(&info.mutex_i);

	// pthread_mutex_lock(&info.large->mutex_z);
	chunk = mmap(NULL, sizeof(struct blockdata) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (chunk == MAP_FAILED) {
		// pthread_mutex_unlock(&info.large->mutex_z);
		ft_putstr_fd("\033[1;31mERROR ALLOCATION FAILED\n\033[0m", 2);
		return (NULL);
	}
	VALGRIND_MALLOCLIKE_BLOCK(chunk, sizeof(struct blockdata) + size, 0, 0);

	chunk->next = NULL;
	chunk->free = false;
	info.large->lst->f_zone = LARGE;
	chunk->size = size + sizeof(struct blockdata);
	chunk->mem = (void*)chunk + sizeof(struct blockdata);
	ex = info.large->lst;
	while (ex->next)
		ex = ex->next;
	ex->next = chunk;
	// pthread_mutex_unlock(&info.large->mutex_z);

	// pthread_mutex_lock(&info.mutex_i);
	info.large->size += chunk->size;
	// pthread_mutex_unlock(&info.mutex_i);

	return ((void *)chunk->mem);
}

/* Extern Mutex-locking */
block	*SplitBlock(block* chunk, size_t size)
{
	block	*new = chunk->mem + size;

	new->free = true;
	new->next = chunk->next;
	new->mem = (void *)new + sizeof(struct blockdata);
	new->size = chunk->size - size - sizeof(struct blockdata);

	chunk->next = new;
	chunk->free = false;
	chunk->size = size + sizeof(struct blockdata);
	
	return (chunk);
}

/* Extern Mutex-locking */
void	FreeLargeBlock(block *chunk)
{
	block *prev = info.large->lst;

	while(prev)
	{
		if (prev == chunk)			{ return; }
		if (prev->next == chunk)	{ break; }
		prev = prev->next;
	}
	prev->next = chunk->next;
	info.large->size -= chunk->size;
	munmap((void *)chunk, chunk->size);
	VALGRIND_FREELIKE_BLOCK(chunk, 0);
}
