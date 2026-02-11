# include "head.h"

void    CheckNext()
{
    zone *zone;
    if (info.tiny)
    {
        zone = info.tiny;
        if (!info.small && !info.large && zone->next != NULL)           { zone->next = NULL; }
        else if (!info.small && info.large && zone->next != info.large) { zone->next = info.large; }
        else if (info.small && zone->next != info.small)                { zone->next = info.small; }
    }
    if (info.small)
    {
        zone = info.small;
        if (!info.large && zone->next != NULL)    { zone->next = NULL; }
        else if (zone->next != info.large)        { zone->next = info.large; }
    }
    if (info.large && info.large->next != NULL) { info.large->next = NULL; }
}

void    CheckForCoalesce()
{
    zone    *zone = info.tiny;
    block   *chunk, *next;

    while (zone && zone != info.large)
    {
        chunk = zone->lst;
        while(chunk)
        {
            if (chunk->next && chunk->free == true && chunk->next->free == true)
            {
                next = chunk->next;
                chunk->size += next->size;
                chunk->free = true;
                chunk->next = next->next;
            }
            chunk = chunk->next;
        }
        zone = zone->next;
    }
}

void    CheckForTotalFree()
{
    block   *chunk, *mid, *prev = NULL;

    if (info.tiny && info.tiny->lst->next == NULL && info.tiny->lst->free)
    {
        munmap((void *)info.tiny, info.tiny->size);
        VALGRIND_FREELIKE_BLOCK(info.tiny, 0);
        info.tiny = NULL;
        CheckNext();
    }
    if (info.small && info.small->lst->next == NULL && info.small->lst->free)
    {
        munmap((void *)info.small, info.small->size);
        VALGRIND_FREELIKE_BLOCK(info.small, 0);
        info.small = NULL;
        CheckNext();
    }

    if (info.large)
    {
        chunk = info.large->lst;
        while(chunk)
        {
            mid = chunk;
            chunk = chunk->next;
            if (mid->free && mid != info.large->lst)
            {
                munmap((void *)mid, mid->size);
                VALGRIND_FREELIKE_BLOCK(mid, 0);
                prev->next = chunk;
            }
            prev = mid;
        }
        if (info.large->lst->free && info.large->lst->next == NULL)
        {
            munmap((void *)info.large, info.large->size);
            VALGRIND_FREELIKE_BLOCK(info.large, 0);
            info.large = NULL;
            CheckNext();
        }
    }

}
