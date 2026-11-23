# include "malloc_bonus.h"

// void	CheckNext()
// {
// 	if (info.tiny)
// 	{
// 		if (info.small)			{ info.tiny->next = info.small; }
// 		else if (info.large)	{ info.tiny->next = info.large; }
// 		else					{ info.tiny->next = NULL; }
// 	}
// 	if (info.small)
// 	{
// 		if (info.large)			{ info.small->next = info.large; }
// 		else					{ info.small->next = NULL; }
// 	}
// 	if (info.large && info.large->next) { info.large->next = NULL; }
// }

void	CheckForCoalesce()
{
	zone	*zone = FindFirstZone();
	block	*chunk, *next;

	while (zone && zone != info.large)
	{
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
		zone = FindNextZone(zone);
	}
}

void	CheckForTotalFree()
{
	CheckForCoalesce();
	if (info.tiny && (!info.tiny->lst || (info.tiny->lst->next == NULL && info.tiny->lst->free)))
	{
		munmap((void *)info.tiny, info.tiny->size);
		VALGRIND_FREELIKE_BLOCK(info.tiny, 0);
		info.tiny = NULL;
		// CheckNext();
	}
	if (info.small && (!info.small->lst || (info.small->lst->next == NULL && info.small->lst->free)))
	{
		munmap((void *)info.small, info.small->size);
		VALGRIND_FREELIKE_BLOCK(info.small, 0);
		info.small = NULL;
		// CheckNext();
	}
	if (info.large && info.large->lst->next == NULL && info.large->lst->free)
	{
		munmap((void *)info.large, info.large->size);
		VALGRIND_FREELIKE_BLOCK(info.large, 0);
		info.large = NULL;
		// CheckNext();
	}
	if (DEBUG && (info.tiny || info.small || info.large)) { ft_putstr_fd("\033[1;31mERROR LEAKS\n\033[0m", 2); }
}
