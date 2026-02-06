# include "head.h"

meta info = {NULL, NULL, NULL};

zone    *InitializeZone(size_t size)
{
    size_t full_size = sizeof(struct zonedata) + size;
    zone *zone = mmap(NULL, full_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (zone == MAP_FAILED)
        return (NULL);
    
    zone->size = full_size;
    zone->beg = (void*)zone + sizeof(struct zonedata);
    zone->lst = NULL;

    if (size == TINY_ZONE)          { zone->next = info.small; }
    else if (size == SMALL_ZONE)    { zone->next = info.large; }
    else { zone->next = NULL; }

    return (zone);
}

block *AddBlock(size_t size, const zone *zone)
{
    block *ex;
    block *chunk;

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
    chunk->size = size + sizeof(struct blockdata);
    chunk->mem = (void*)chunk + sizeof(struct blockdata);
    return (chunk);
}

void    *FindFreeBlock(size_t size, zone *zone)
{
    block *pres = zone->lst;

    while (pres)
    {
        if (pres->size >= size + sizeof(struct blockdata) && pres->free)
        {
            pres->free = false;
            return ((void *)pres->mem);
        }
        if (pres->next == NULL) { break; }
        pres = pres->next;
    }
    pres->next = AddBlock(size, zone);
    return ((void *)pres->next->mem);
}

void    *ft_malloc(size_t size)
{
    if (!size) { return (NULL); }

    if (size <= N_TINY)
    {
        if (!info.tiny)     { info.tiny = InitializeZone(TINY_ZONE); }

        if (!info.tiny->lst)
        {
            info.tiny->lst = AddBlock(size, info.tiny);
            return ((void *)info.tiny->lst->mem);
        }
        else
            return (FindFreeBlock(size, info.tiny));
    }
    else if (size <= M_SMALL)
    {
        if (!info.small)    { info.small = InitializeZone(SMALL_ZONE); }

        if (!info.small->lst)
        {
            info.small->lst = AddBlock(size, info.small);
            return ((void *)info.small->lst->mem);
        }
        else
            return (FindFreeBlock(size, info.small));
    }
    // else if (info.large)
    //     return (AddLarge());
    return (NULL);
}

void    ft_free(void *ptr)
{
    zone    *zone = info.tiny;
    block   *chunk;
    while (zone)
    {
        chunk = zone->lst;
        while(chunk)
        {
            if (chunk->mem == ptr)
                break;
            chunk = chunk->next;
        }
        zone = zone->next;
    }
    if (!chunk)
        { printf("Free faild\n"); return ; }
    chunk->free = true;
}

int main(void)
{
    int *i = ft_malloc(sizeof(int));
    if (!i) { printf("malloc fallita\n"); return (1); }
    *i = 23;
    printf("addr. = %p | i = %d\n", i, *i);

    int *j = ft_malloc(sizeof(int));
    *j = 12;
    printf("addr. = %p | j = %d\n", j, *j);

    char *s = ft_malloc(sizeof(char) * 58);
    ft_strlcpy(s, "test test, prova prova!! Il dottor Thomas non e' in sede!", 58);
    printf("addr. = %p | s = \"%s\"\n", s, s);

    ft_free(j);
    ft_free(i);
    ft_free(s);

    int *a = ft_malloc(sizeof(char));
    *a = 'a';
    printf("addr. = %p | a = %c\n", a, *a);

    char *b = ft_malloc(sizeof(char) * 28);
    ft_strlcpy(b, "abcdefghilmnopqrstuvwykjxz", 28);
    printf("addr. = %p | b = \"%s\"\n", b, b);

    int *x = ft_malloc(sizeof(int));
    *x = 90;
    printf("addr. = %p | x = %d\n", x, *x);



    // if (s && info.small && info.small->lst)
    //     printf("info.small branch: OK\n");
    // else
    //     printf("info.small branch: FAIL\n");

    if (info.tiny)
    {
        printf("Freeing tiny zone\n");
        munmap(info.tiny, info.tiny->size);
    }
    if (info.small)
    {
        printf("Freeing small zone\n");
        munmap(info.small, info.small->size);
    }
}
