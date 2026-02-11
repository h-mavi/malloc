# include "head.h"

meta info = {NULL, NULL, NULL};

void    *ft_malloc(size_t size)
{
    if (!size) { return (NULL); }
    if (size <= N_TINY)
    {
        if (!info.tiny)     { info.tiny = InitializeZone(TINY_ZONE); }
        CheckNext();
        if (!info.tiny->lst)
        {
            info.tiny->lst = AddBlock(size, info.tiny);
            return ((void *)info.tiny->lst->mem);
        }
        else { return (FindFreeBlock(size, info.tiny)); }
    }
    else if (size <= M_SMALL)
    {
        if (!info.small)    { info.small = InitializeZone(SMALL_ZONE); }
        CheckNext();
        if (!info.small->lst)
        {
            info.small->lst = AddBlock(size, info.small);
            return ((void *)info.small->lst->mem);
        }
        else { return (FindFreeBlock(size, info.small)); }
    }
    else
        return (AddLargeBlock(size));
    return (NULL);
}

void    ft_free(void *ptr)
{
    zone    *zone = FindFirstZone();
    block   *chunk;

    if (!ptr) { return ; }
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
    CheckForCoalesce();
    CheckForTotalFree();
}

void    show_alloc_mem()
{
    block   *chunk;
    zone    *zone = FindFirstZone();
    long     r_size, tot = 0, r_tot = 0;

    if (DEBUG) { ft_printf("[ DEBUG MODE : %sON%s ]\n", B_GREEN, RESET); }
    while (zone)
    {
        if (zone == info.tiny) { ft_printf("TINY : %p\n", zone->beg); }
        else if (zone == info.small) { ft_printf("SMALL : %p\n", zone->beg); }
        else if (zone == info.large) { ft_printf("LARGE : %p\n", zone->beg); }
        if (DEBUG) { ft_printf("~   %sZONE%s  struct %p : %d bytes\n", B_BLUE, RESET, zone, sizeof(struct zonedata)); }

        r_tot += sizeof(struct zonedata);
        chunk = zone->lst;
        while(chunk)
        {
            r_size = chunk->size - sizeof(struct blockdata);
            if (DEBUG) { ft_printf("~   %sBLOCK%s struct %p : %d bytes\n", B_RED, RESET, chunk, sizeof(struct blockdata)); }
            if (chunk->free == false)
            {
                tot += r_size;
                r_tot += chunk->size;
                ft_printf("%p - %p : %d bytes\n", chunk->mem, chunk->mem + r_size, r_size);
            }
            if (DEBUG && chunk->free)
            {
                r_tot += chunk->size;
                ft_printf("%p - %p : %d bytes <- FREED\n", chunk->mem, chunk->mem + r_size, r_size);
            }
            chunk = chunk->next;
        }
        zone = zone->next;
    }
    ft_printf("Total : %d bytes\n", tot);
    if (DEBUG) { ft_printf("~   %sREAL%s Total : %d bytes\n", B_GREEN, RESET, r_tot); } 
}

int main(void)
{
    int *i = ft_malloc(sizeof(int));
    if (!i) { printf("malloc fallita\n"); return (1); }
    *i = 23;

    int *j = ft_malloc(sizeof(int));
    *j = 12;

    char *s = ft_malloc(sizeof(char) * 58);
    ft_strlcpy(s, "test test, prova prova!! Il dottor Thomas non e' in sede!", 58);

    show_alloc_mem();

    ft_free(j);
    ft_free(i);
    ft_free(s);
    ft_printf("\n");
    show_alloc_mem();

    int *a = ft_malloc(sizeof(int));
    *a = 'a';

    char *b = ft_malloc(sizeof(char) * 28);
    ft_strlcpy(b, "abcdefghilmnopqrstuvwykjxz", 28);

    int *x = ft_malloc(sizeof(int));
    *x = 90;

    ft_printf("\n");
    show_alloc_mem();

    char *c = ft_malloc(sizeof(char) * 34);
    ft_strlcpy(c, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 34);

    ft_printf("\n");
    show_alloc_mem();

    ft_printf("\n[ AddLargeBlock tests ]\n");
    size_t big1 = M_SMALL + 128;
    size_t big2 = M_SMALL + 4096;
    char *l1 = ft_malloc(big1);
    char *l2 = ft_malloc(big2);
    if (!l1 || !l2)
        printf("large allocation failed\n");
    else
    {
        ft_bzero(l1, big1);
        ft_bzero(l2, big2);
        l1[0] = 'L';
        l2[0] = 'R';
    }

    ft_printf("\n");
    show_alloc_mem();

    ft_free(l2);

    ft_printf("\n");
    show_alloc_mem();

    ft_free(l1);

    ft_printf("\n");
    show_alloc_mem();

    ft_free(a);
    ft_free(b);
    ft_free(x);
    ft_free(c);
}
