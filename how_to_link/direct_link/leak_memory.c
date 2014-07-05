#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_JEMALLOC
#include <jemalloc/jemalloc.h>
#endif /* USE_JEMALLOC */


void
leak_memory(void){
    char *ptr1, *ptr2;

    ptr1 = (char *)malloc(32);
    ptr2 = (char *)malloc(1024);

    (void)ptr1; // For warnings
    (void)ptr2; // For warnings

    return;
}

int
main(void)
{
    printf("#### Leak Memory test ####\n");
    leak_memory();


#if defined(USE_JEMALLOC) && defined(STATS_PRINT)
    malloc_stats_print(NULL, NULL, NULL);
#endif /* USE_JEMALLOC */

    return 0;
}
