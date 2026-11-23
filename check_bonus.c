# include "malloc_bonus.h"

/* Auto Mutex-locking */
void	CheckForCoalesce()
{
	zone	*zone = FindFirstZone();
	block	*chunk, *next;

	while (zone && zone != info.large)
	{
		// pthread_mutex_lock(&zone->mutex_z);
		chunk = zone->lst;
		while(chunk)
		{
			if (chunk->next && chunk->free == true && chunk->next->free == true)
			{
				next = chunk->next;
				chunk->next = next->next;
				chunk->size += next->size;
				continue;
			}
			chunk = chunk->next;
		}
		// pthread_mutex_unlock(&zone->mutex_z);
		zone = FindNextZone(zone);
	}
}

void	CheckForTotalFree()
{
	CheckForCoalesce();
	// pthread_mutex_lock(&info.mutex_i);
	if (info.tiny && (!info.tiny->lst || (info.tiny->lst->next == NULL && info.tiny->lst->free)))
	{
		// pthread_mutex_destroy(&info.tiny->mutex_z);
		munmap((void *)info.tiny, info.tiny->size);
		VALGRIND_FREELIKE_BLOCK(info.tiny, 0);
		info.tiny = NULL;
	}
	if (info.small && (!info.small->lst || (info.small->lst->next == NULL && info.small->lst->free)))
	{
		// pthread_mutex_destroy(&info.small->mutex_z);
		munmap((void *)info.small, info.small->size);
		VALGRIND_FREELIKE_BLOCK(info.small, 0);
		info.small = NULL;
	}
	if (info.large && info.large->lst->next == NULL && info.large->lst->free)
	{
		// pthread_mutex_destroy(&info.large->mutex_z);
		munmap((void *)info.large, info.large->size);
		VALGRIND_FREELIKE_BLOCK(info.large, 0);
		info.large = NULL;
	}
	if (DEBUG && (info.tiny || info.small || info.large)) { ft_putstr_fd("\033[1;31mERROR LEAKS\n\033[0m", 2); }
	// pthread_mutex_unlock(&info.mutex_i);
	// pthread_mutex_destroy(&info.mutex_i);
}
