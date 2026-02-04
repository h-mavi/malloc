#include "head.h"

void    *ft_malloc(size_t size)
{
    void *ptr;
    long r_size = size / sysconf(_SC_PAGESIZE);

    if (size % sysconf(_SC_PAGESIZE))
        r_size += 1;

    ptr = mmap(NULL, r_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    return (ptr);
}

int main(void)
{
    int     *third = ft_malloc(sizeof(int));
    char    *fourth = ft_malloc(sizeof(char) * 12);

    alignof(max_align_t);

    *third = 2;
    fourth = "hello world";

    printf("int memory test = %d\n", *third);
    printf("string memory test = %s\n", fourth);

    // ft_free(third);
    // ft_free(fourth);
}

int main1(void)
{
    uint8_t *first = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    uint8_t *second = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    printf("Page size = %ld\n", sysconf(_SC_PAGESIZE));
    printf("first address = %p\n", first);
    printf("second address = %p\n", second);

    munmap(first, sysconf(_SC_PAGESIZE));
    munmap(second, sysconf(_SC_PAGESIZE));

    int *third = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    char *fourth = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    *third = 2;
    fourth = "hello world";

    printf("int memory test = %d\n", *third);
    printf("string memory test = %s\n", fourth);

    munmap(third, sysconf(_SC_PAGESIZE));
    munmap(fourth, sysconf(_SC_PAGESIZE));
}
