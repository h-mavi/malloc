# include "head.h"

void    InitializeZone()
{
    info.small = mmap(NULL, sizeof(struct zonedata) + SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (info.small == MAP_FAILED) { ft_putstr_fd("\033[1;31mERROR ALLOCATION FAILED\n\033[0m", 2); }
    VALGRIND_MALLOCLIKE_BLOCK(info.small, sizeof(struct zonedata) + SMALL_ZONE, 0, 0);
    info.small->lst = NULL;
    info.small->next = NULL;
    info.small->size = sizeof(struct zonedata) + SMALL_ZONE;
    info.small->beg = (void*)info.small + sizeof(struct zonedata);

    info.tiny = mmap(NULL, sizeof(struct zonedata) + TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (info.tiny == MAP_FAILED) { ft_putstr_fd("\033[1;31mERROR ALLOCATION FAILED\n\033[0m", 2); }
    VALGRIND_MALLOCLIKE_BLOCK(info.tiny, sizeof(struct zonedata) + TINY_ZONE, 0, 0);
    info.tiny->lst = NULL;
    info.tiny->next = info.small;
    info.tiny->size = sizeof(struct zonedata) + TINY_ZONE;
    info.tiny->beg = (void*)info.tiny + sizeof(struct zonedata);
}

block   *AddBlock(size_t size, const zone *zone)
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

void *AddLargeBlock(size_t size)
{
    block   *chunk, *ex;
    void    *ptr;
    if (!info.large)
    {
        info.large = mmap(NULL, sizeof(struct zonedata) + sizeof(struct blockdata) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (info.large == MAP_FAILED) { return (NULL); }
        VALGRIND_MALLOCLIKE_BLOCK(info.large, sizeof(struct zonedata) + sizeof(struct blockdata) + size, 0, 0);

        info.large->lst = NULL;
        info.large->next = NULL;
        info.large->beg = (void *)info.large + sizeof(struct zonedata);
        info.large->size = sizeof(struct zonedata) + sizeof(struct blockdata) + size;
        info.large->lst = AddBlock(size, info.large);
        CheckNext();
        return ((void *)info.large->lst->mem);
    }
    ptr = FindFreeBlock(size, info.large);
    if (ptr) { return (ptr); }

    chunk = mmap(NULL, sizeof(struct blockdata) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (chunk == MAP_FAILED) { return (NULL); }
    VALGRIND_MALLOCLIKE_BLOCK(chunk, sizeof(struct blockdata) + size, 0, 0);

    chunk->next = NULL;
    chunk->free = false;
    chunk->size = size + sizeof(struct blockdata);
    chunk->mem = (void*)chunk + sizeof(struct blockdata);
    ex = info.large->lst;
	while (ex->next)
		ex = ex->next;
	ex->next = chunk;
    return ((void *)chunk->mem);
}

block *SplitBlock(block* chunk, size_t size)
{
    block *new = chunk->mem + size;

    new->free = true;
    new->next = chunk->next;
    new->mem = (void *)new + sizeof(struct blockdata);
    new->size = chunk->size - size - sizeof(struct blockdata);

    chunk->next = new;
    chunk->free = false;
    chunk->size = size + sizeof(struct blockdata);
    
    return (chunk);
}

void    *FindFreeBlock(size_t size, zone *zone)
{
    block *pres = zone->lst;

    while (pres)
    {
        if (pres->size == size + sizeof(struct blockdata) && pres->free)
        {
            pres->free = false;
            return ((void *)pres->mem);
        }
        else if (zone != info.large && pres->size > size + sizeof(struct blockdata) && pres->free && \
            pres->size - size - sizeof(struct blockdata) > sizeof(struct blockdata))
            return ((void *)SplitBlock(pres, size)->mem);

        if (pres->next == NULL) { break; }
        pres = pres->next;
    }
    if (zone == info.large) { return (NULL); }
    pres->next = AddBlock(size, zone);
    return ((void *)pres->next->mem);
}

zone *FindFirstZone()
{
    if (info.tiny)       { return (info.tiny); }
    else if (info.small) { return (info.small); }
    else if (info.large) { return (info.large); }
    return (NULL);
}

block *FindBlock(void *ptr)
{
    zone    *zone = FindFirstZone();
    block   *chunk = NULL;

    if (!ptr) { return (NULL); }
    while (zone)
    {
        chunk = zone->lst;
        while(chunk)
        {
            if (chunk->mem == ptr)
                return (chunk);
            chunk = chunk->next;
        }
        zone = zone->next;
    }
    return (NULL);
}
