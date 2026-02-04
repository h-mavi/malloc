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

# include <stddef.h>
# include <stdalign.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <bits/mman-linux.h>

typedef struct chuckzone_lst
{
    long        size;
    chunk_lst_t *prev;
    chunk_lst_t *next;
}   __attribute__((aligned(16)))    chunk_lst_t;


typedef struct metainfo_lst
{
    long alloc_size;
    chunk_lst_t *mini_head;
    chunk_lst_t *small_head;
}   info_lst_t;

void    ft_free(void *ptr);
void    *ft_malloc(size_t size);
void    *ft_realloc(void *ptr, size_t size);

#endif