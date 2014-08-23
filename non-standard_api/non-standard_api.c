#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifdef USE_JEMALLOC
#include <jemalloc/jemalloc.h>
#endif

void
test_mallocx()
{
    void *ptr;

    /* align ptr address with multiple of 2^11 */
    ptr = (void *)mallocx(3, MALLOCX_LG_ALIGN(11));
    if (ptr != NULL){
        printf("ptr : %p \n", ptr);
        assert(((unsigned long)ptr % (1 << 11)) == 0);
    }else{
        fprintf(stderr, "ptr is NULL\n");
    }

}


int
main(void)
{
    printf("#### mallocx ####\n");
    test_mallocx();

#if defined(USE_JEMALLOC) && defined(STATS_PRINT)
    malloc_stats_print(NULL, NULL, NULL);
#endif

    return 0;
}
