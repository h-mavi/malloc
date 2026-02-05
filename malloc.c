# include "head.h"

meta info = {NULL, NULL, NULL};

zone    *Initialize(size_t size)
{
    size_t full_size = sizeof(zone) + size;
    zone *zone = mmap(NULL, full_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (zone == MAP_FAILED)
        return (NULL);
    // printf("mappato all'inidirizzo %p di size %ld\n", zone, size);
    
    zone->size = full_size;
    zone->beg = (void *)zone + sizeof(zone);
    zone->next = NULL;
    zone->lst = NULL;
    return (zone);
}

block *AddBlock(size_t size, zone *zone)
{
    // ...
}

void    *malloc(size_t size)
{
    if (!size) { return (NULL); }

    if (size <= N_TINY)
    {
        if (!info.tiny)
            info.tiny = Initialize(TINY_ZONE);
        if (!info.tiny->lst)    { return (AddBlock(size, info.tiny)); }
        else                    { return (FindFreeBlock()); }
    }
    else if (size <= M_SMALL && info.small)
    {
        if (!info.small)
            Initialize(SMALL_ZONE);
        if (!info.small->lst)
            return (AddBlock(size, &info.small));
        else
            return (FindFreeBlock());
    }
    else if (info.large)
        return (AddLarge());
    return (NULL);
}

int main(void)
{
    int *i = malloc(sizeof(int));
    if (!i) { printf("malloc fallita\n"); return (1); }
    *i = 23;
    printf("i = %d\n", *i);
    if (info.tiny)
        munmap(info.tiny, info.tiny->size);
}
