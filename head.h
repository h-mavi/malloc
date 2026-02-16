# ifndef HEAD_H
# define HEAD_H

# include "libft/libft.h"
# include "libft/printf/ft_printf.h"

# include <stddef.h>
# include <stdbool.h>
# include <stdalign.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <bits/mman-linux.h>

# include <valgrind/memcheck.h>

# define RESET "\033[0m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define B_RED "\033[1;31m"
# define B_BLUE "\033[1;34m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"

# define DEBUG 1
# define PAGE_SIZE sysconf(_SC_PAGESIZE)
# define N_TINY (size_t)(PAGE_SIZE * 16)	// max TINY-block size = 16KB
# define M_SMALL (size_t)(PAGE_SIZE * 256)	// max SMALL-block size = 1MB
# define TINY_ZONE (size_t)((N_TINY + sizeof(struct blockdata)) * 100)   // TINY-zone size = 6400KB
# define SMALL_ZONE (size_t)((M_SMALL + sizeof(struct blockdata)) * 100) // SMALL-zone size = 100MB

typedef struct blockdata
{
	size_t	size;
	bool	free;
	void	*mem;
	struct blockdata	*next;
}   __attribute__((aligned(16)))    block;

typedef struct zonedata
{
	size_t	size;
	void	*beg;
	block	*lst;
	struct zonedata	*next;
}   zone;

typedef struct metadata
{
	zone	*tiny;
	zone	*small;
	zone	*large;
}   meta;

extern meta info;

// in check.c
void	CheckNext();
void	CheckForCoalesce();
void	__attribute__((destructor)) CheckForTotalFree();

// in find.c
void	*FindFreeBlock(size_t size, zone *zone);
zone	*FindFirstZone();
block	*FindBlock(void *ptr);

// in malloc.c
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

// in utils.c
void	__attribute__((constructor)) InitializeZone();
block	*AddBlock(size_t size, const zone *zone);
void	*AddLargeBlock(size_t size);
block	*SplitBlock(block* chunk, size_t size);
void	FreeLargeBlock(block *chunk);

#endif