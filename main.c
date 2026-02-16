#include "head.h"
#include <stdio.h>
#include <string.h>

void print_test_header(const char *test_name)
{
    ft_printf("\n%s========================================%s\n", B_YELLOW, RESET);
    ft_printf("%s  %s%s\n", B_YELLOW, test_name, RESET);
    ft_printf("%s========================================%s\n", B_YELLOW, RESET);
}

void test_basic_malloc()
{
    print_test_header("TEST 1: Basic malloc()");
    
    int *i = malloc(sizeof(int));
    if (!i) { printf("malloc failed\n"); return; }
    *i = 42;
    
    char *str = malloc(sizeof(char) * 50);
    if (!str) { printf("malloc failed\n"); return; }
    ft_strlcpy(str, "Hello from custom allocator!", 50);
    
    double *d = malloc(sizeof(double));
    if (!d) { printf("malloc failed\n"); return; }
    *d = 3.14159;
    
    ft_printf("Integer: %d\n", *i);
    ft_printf("String: %s\n", str);
    ft_printf("Double: %d\n", (int)(*d * 100));
    
    show_alloc_mem();
    
    free(i);
    free(str);
    free(d);
}

void test_malloc_zero()
{
    print_test_header("TEST 2: malloc(0)");
    
    void *ptr = malloc(0);
    if (ptr) {
        ft_printf("malloc(0) returned non-NULL pointer: %p\n", ptr);
    } else {
        ft_printf("malloc(0) returned NULL\n");
    }
    
    show_alloc_mem();
    
    if (ptr) free(ptr);
}

void test_multiple_allocations()
{
    print_test_header("TEST 3: Multiple Allocations");
    
    #define NUM_ALLOCS 10
    int *array[NUM_ALLOCS];
    
    for (int i = 0; i < NUM_ALLOCS; i++) {
        array[i] = malloc(sizeof(int));
        if (!array[i]) {
            ft_printf("Allocation %d failed\n", i);
            return;
        }
        *array[i] = i * 100;
    }
    
    ft_printf("Allocated %d integers:\n", NUM_ALLOCS);
    for (int i = 0; i < NUM_ALLOCS; i++) {
        ft_printf("array[%d] = %d\n", i, *array[i]);
    }
    
    show_alloc_mem();
    
    // Free every other allocation
    for (int i = 0; i < NUM_ALLOCS; i += 2) {
        free(array[i]);
    }
    
    ft_printf("\nAfter freeing even indices:\n");
    show_alloc_mem();
    
    // Free the rest
    for (int i = 1; i < NUM_ALLOCS; i += 2) {
        free(array[i]);
    }
}

void test_realloc_basic()
{
    print_test_header("TEST 4: Basic realloc()");
    
    char *str = malloc(20);
    if (!str) { printf("malloc failed\n"); return; }
    ft_strlcpy(str, "Short string", 20);
    
    ft_printf("Original: %s\n", str);
    show_alloc_mem();
    
    // Expand
    str = realloc(str, 100);
    if (!str) { printf("realloc failed\n"); return; }
    ft_strlcpy(str, "This is a much longer string after realloc!", 100);
    
    ft_printf("\nAfter realloc (expand): %s\n", str);
    show_alloc_mem();
    
    // Shrink
    str = realloc(str, 30);
    ft_printf("\nAfter realloc (shrink): %s\n", str);
    show_alloc_mem();
    
    free(str);
}

void test_realloc_edge_cases()
{
    print_test_header("TEST 5: realloc() Edge Cases");
    
    // realloc with NULL pointer (should act like malloc)
    ft_printf("Test: realloc(NULL, 50)\n");
    char *ptr1 = realloc(NULL, 50);
    if (ptr1) {
        ft_strlcpy(ptr1, "Allocated via realloc(NULL)", 50);
        ft_printf("Result: %s\n", ptr1);
    }
    show_alloc_mem();
    
    // realloc with size 0 (should act like free)
    ft_printf("\nTest: realloc(ptr, 0)\n");
    char *ptr2 = realloc(ptr1, 0);
    ft_printf("Returned: %p (should be NULL)\n", ptr2);
    show_alloc_mem();
}

void test_large_allocations()
{
    print_test_header("TEST 6: Large Allocations");
    
    size_t large_size1 = M_SMALL + 1024;     // Larger than SMALL zone
    size_t large_size2 = M_SMALL + 8192;
    
    ft_printf("Allocating %zu bytes (LARGE zone)\n", large_size1);
    char *large1 = malloc(large_size1);
    if (!large1) {
        ft_printf("Large allocation 1 failed\n");
        return;
    }
    ft_bzero(large1, large_size1);
    large1[0] = 'L';
    large1[1] = 'A';
    large1[2] = 'R';
    large1[3] = 'G';
    large1[4] = 'E';
    large1[5] = '1';
    large1[6] = '\0';
    
    ft_printf("Allocating %zu bytes (LARGE zone)\n", large_size2);
    char *large2 = malloc(large_size2);
    if (!large2) {
        ft_printf("Large allocation 2 failed\n");
        free(large1);
        return;
    }
    ft_bzero(large2, large_size2);
    large2[0] = 'L';
    large2[1] = 'A';
    large2[2] = 'R';
    large2[3] = 'G';
    large2[4] = 'E';
    large2[5] = '2';
    large2[6] = '\0';
    
    ft_printf("Large1: %s\n", large1);
    ft_printf("Large2: %s\n", large2);
    
    show_alloc_mem();
    
    free(large1);
    ft_printf("\nAfter freeing large1:\n");
    show_alloc_mem();
    
    free(large2);
}

void test_tiny_small_large()
{
    print_test_header("TEST 7: TINY, SMALL, and LARGE Zones");
    
    // TINY allocation
    size_t tiny_size = 100;
    ft_printf("TINY allocation (%zu bytes):\n", tiny_size);
    char *tiny = malloc(tiny_size);
    if (tiny) ft_strlcpy(tiny, "TINY", tiny_size);
    
    // SMALL allocation
    size_t small_size = N_TINY + 1024;
    ft_printf("SMALL allocation (%zu bytes):\n", small_size);
    char *small = malloc(small_size);
    if (small) small[0] = 'S';
    
    // LARGE allocation
    size_t large_size = M_SMALL + 512;
    ft_printf("LARGE allocation (%zu bytes):\n", large_size);
    char *large = malloc(large_size);
    if (large) large[0] = 'L';
    
    show_alloc_mem();
    
    free(tiny);
    free(small);
    free(large);
}

void test_fragmentation()
{
    print_test_header("TEST 8: Fragmentation and Coalescing");
    
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    int *e = malloc(sizeof(int));
    
    if (!a || !b || !c || !d || !e) {
        ft_printf("Allocation failed\n");
        return;
    }
    
    *a = 1; *b = 2; *c = 3; *d = 4; *e = 5;
    
    ft_printf("After 5 allocations:\n");
    show_alloc_mem();
    
    // Free middle ones to create fragmentation
    free(b);
    free(d);
    
    ft_printf("\nAfter freeing b and d (fragmentation):\n");
    show_alloc_mem();
    
    // Free adjacent blocks to test coalescing
    free(c);
    
    ft_printf("\nAfter freeing c (should coalesce with b and d):\n");
    show_alloc_mem();
    
    free(a);
    free(e);
}

void test_double_free()
{
    print_test_header("TEST 9: Double Free Protection");
    
    int *ptr = malloc(sizeof(int));
    if (!ptr) {
        ft_printf("Allocation failed\n");
        return;
    }
    *ptr = 999;
    
    ft_printf("Allocated pointer: %p\n", ptr);
    show_alloc_mem();
    
    free(ptr);
    ft_printf("\nAfter first free:\n");
    show_alloc_mem();
    
    ft_printf("\nAttempting double free...\n");
    free(ptr);  // This should be handled safely
    ft_printf("Double free completed (should be safe)\n");
    show_alloc_mem();
}

void test_null_free()
{
    print_test_header("TEST 10: Free NULL Pointer");
    
    ft_printf("Calling free(NULL)...\n");
    free(NULL);  // Should handle gracefully
    ft_printf("free(NULL) completed successfully\n");
}

int main(void)
{
    ft_printf("%s╔════════════════════════════════════════╗%s\n", B_GREEN, RESET);
    ft_printf("%s║   CUSTOM ALLOCATOR TEST SUITE          ║%s\n", B_GREEN, RESET);
    ft_printf("%s╚════════════════════════════════════════╝%s\n", B_GREEN, RESET);
    
    test_basic_malloc();
    test_malloc_zero();
    test_multiple_allocations();
    test_realloc_basic();
    test_realloc_edge_cases();
    test_large_allocations();
    test_tiny_small_large();
    test_fragmentation();
    test_double_free();
    test_null_free();
    
    print_test_header("FINAL MEMORY STATE");
    show_alloc_mem();
    
    ft_printf("\n%s✓ All tests completed!%s\n\n", B_GREEN, RESET);
    
    return 0;
}
