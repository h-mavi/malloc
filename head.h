# ifndef HEAD_H
# define HEAD_H

# include <stdio.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <strings.h>
# include "libft/libft.h"

# include <stddef.h>
# include <stdbool.h>
# include <stdalign.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <bits/mman-linux.h>

# define PAGE_SIZE sysconf(_SC_PAGESIZE)
# define N_TINY (size_t)(PAGE_SIZE * 16)    // max TINY-block size = 16KB
# define M_SMALL (size_t)(PAGE_SIZE * 256)  // max SMALL-block size = 1MB
# define TINY_ZONE (size_t)((N_TINY + sizeof(struct blockdata)) * 100)   // TINY-zone size = 6400KB
# define SMALL_ZONE (size_t)((M_SMALL + sizeof(struct blockdata)) * 100) // SMALL-zone size = 100MB

typedef struct blockdata
{
    size_t  size;
    bool    free;
    void    *mem;
    struct blockdata    *next;
}   __attribute__((aligned(16)))    block;

typedef struct zonedata
{
    size_t  size;
    void    *beg;
    block   *lst;
    struct zonedata     *next;
}   zone;

typedef struct metadata
{
    zone    *tiny;
    zone    *small;
    zone    *large;
}   meta;

extern meta info;


void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);

#endif