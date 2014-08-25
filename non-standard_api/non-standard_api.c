#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <jemalloc/jemalloc.h>
#include "../jemalloc/include/jemalloc/internal/arena.h"

#define JEMALLOC_H_TYPES
typedef struct arena_s arena_t;
extern arena_t **arenas;

void
test_mallocx()
{
    void *ptr;

    /* MALLOCX_LG_ALIGN(x), x should be power of 2 */
    /* align ptr address with multiple of 2^11 */
    ptr = (void *)mallocx(3, MALLOCX_LG_ALIGN(11));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

    /* MALLOCX_ALIGN(x), x should be power of 2 */
    /* align ptr address with multiple of 2^11 */
    ptr = (void *)mallocx(3, MALLOCX_ALIGN(2048));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

    /* MALLOCX_ZERO */
    /* initialize region by 0 */
    ptr = (void *)mallocx(1000,MALLOCX_ZERO);
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        printf("size : %zu \n", malloc_usable_size(ptr));
        for (int i = 0; i < 1024/ sizeof(int);i++)
            printf("%d", *((int*)ptr + i));
//        assert(malloc_usable_size(ptr) == 0);
//        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

    /* MALLOCX_ARENA(a), a is index of arena */
    /* specify the arena by a */
    /* TODO This option is maybe invalid when thread-cache is enabled */
    ptr = (void *)mallocx(8,MALLOCX_ARENA(2));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        printf("size : %zu \n", malloc_usable_size(ptr));

//        printf("%p\n", arenas[2]);
//        assert(malloc_usable_size(ptr) == 0);
//        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }
}


void
test_rallocx()
{
    void *ptr;

    /* MALLOCX_LG_ALIGN(x), x should be power of 2 */
    /* align ptr address with multiple of 2^11 */
    ptr = (void *)mallocx(3, MALLOCX_LG_ALIGN(8));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 8)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

    ptr = (void *)rallocx(ptr, 4, MALLOCX_LG_ALIGN(11));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }


    /* MALLOCX_ALIGN(x), x should be power of 2 */
    /* align ptr address with multiple of 2^11 */
    ptr = (void *)mallocx(3, MALLOCX_ALIGN(512));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 9)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }
    ptr = (void *)rallocx(ptr, 4, MALLOCX_ALIGN(2048));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

    /* MALLOCX_ZERO */
    /* initialize region by 0 */
    ptr = (void *)mallocx(1000,MALLOCX_ZERO);
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        printf("size : %zu \n", malloc_usable_size(ptr));
        for (int i = 0; i < 1024/ sizeof(int);i++)
            printf("%d", *((int*)ptr + i));
//        assert(malloc_usable_size(ptr) == 0);
//        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }
    ptr = (void *)rallocx(ptr, 4, MALLOCX_ZERO);
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

    /* MALLOCX_ARENA(a), a is index of arena */
    /* specify the arena by a */
    /* TODO This option is maybe invalid when thread-cache is enabled */
    ptr = (void *)mallocx(8,MALLOCX_ARENA(2));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        printf("size : %zu \n", malloc_usable_size(ptr));

//        printf("%p\n", arenas[2]);
//        assert(malloc_usable_size(ptr) == 0);
//        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");

    }
    ptr = (void *)rallocx(ptr, 4, MALLOCX_ARENA(2));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }
}


int
main(void)
{
    printf("#### mallocx ####\n");
    test_mallocx();

    printf("#### rallocx ####\n");
    test_rallocx();

#if defined(USE_JEMALLOC) && defined(STATS_PRINT)
    malloc_stats_print(NULL, NULL, NULL);
#endif

    return 0;
}
