# include "head.h"

zone    *InitializeZone(size_t size)
{
    size_t full_size = sizeof(struct zonedata) + size;
    zone *zone = mmap(NULL, full_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (zone == MAP_FAILED) { return (NULL); }
    VALGRIND_MALLOCLIKE_BLOCK(zone, full_size, 0, 0);

    zone->lst = NULL;
    zone->size = full_size;
    zone->beg = (void*)zone + sizeof(struct zonedata);

    return (zone);
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

        info.large->size = sizeof(struct zonedata) + sizeof(struct blockdata) + size;
        info.large->beg = (void *)info.large + sizeof(struct zonedata);
        info.large->lst = AddBlock(size, info.large);
        CheckNext();
        return ((void *)info.large->lst->mem);
    }
    ptr = FindFreeBlock(size, info.large);
    if (ptr) { return (ptr); }

    chunk = mmap(NULL, sizeof(struct blockdata) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (chunk == MAP_FAILED) { return (NULL); }
    VALGRIND_MALLOCLIKE_BLOCK(chunk, sizeof(struct blockdata) + size, 0, 0);

    chunk->free = false;
    chunk->size = size + sizeof(struct blockdata);
    chunk->mem = (void*)chunk + sizeof(struct blockdata);
    ex = info.large->lst;
	while (ex->next)
		ex = ex->next;
	ex->next = chunk;
    chunk->next = NULL;
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
        else if (pres->size > size + sizeof(struct blockdata) && pres->free && \
            pres->size - size - sizeof(struct blockdata) > sizeof(struct blockdata))
            return ((void *)SplitBlock(pres, size)->mem);

        if (pres->next == NULL) { break; }
        pres = pres->next;
    }
    if (zone == info.large) { return (NULL); }
    pres->next = AddBlock(size, zone);
    return ((void *)pres->next->mem);
}
