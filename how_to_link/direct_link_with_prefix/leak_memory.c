#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_JEMALLOC
  #include <jemalloc/jemalloc.h>
  #define ayac_malloc(sz) hoge_malloc(sz)
#else
  #define ayac_malloc(sz) malloc(sz)
#endif /* USE_JEMALLOC */

#define other_malloc(sz) malloc(sz)

void
leak_memory(void){
    char *ptr1, *ptr2;

    ptr1 = (char *)ayac_malloc(32);
    ptr2 = (char *)ayac_malloc(1024);

    (void)ptr1; // For warnings
    (void)ptr2; // For warnings

    return;
}

void
other_func(void){
    char *ptr;
    ptr = (char *)other_malloc(32);
    (void)ptr; // For warnings
    return ;
}

int
main(void)
{
    printf("#### Leak Memory test ####\n");
    leak_memory();
    other_func();

#if defined(USE_JEMALLOC) && defined(STATS_PRINT)
    hoge_malloc_stats_print(NULL, NULL, NULL);
#endif /* USE_JEMALLOC */
    return 0;
}
