#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef USE_JEMALLOC
#include <jemalloc/jemalloc.h>
#endif

void
fill_region(void){
    char *ptr;
    int   i;

    ptr = (char *)malloc(32);

    for (i = 0; i < 32; i++){
        printf("%02x", ptr[i] & 0x000000ff);
    }

    putchar('\n');
    fflush(stdout);

    free(ptr);

    return;
}


void
leak_memory(void){
    char *ptr1, *ptr2;

    ptr1 = (char *)malloc(32);
    ptr2 = (char *)malloc(1024);

/*
<jemalloc>: Leak summary: 1056 bytes, 2 objects, 2 contexts
<jemalloc>: Run pprof on "jeprof.out.46863.0.f.heap" for leak detail
*/

    return;
}


void
double_free(void){
    char *ptr;

    ptr = (char *)malloc(32);

    free(ptr);
    free(ptr);

    return;
}


void
bad_free(void){
    char *ptr;

    ptr = (char *)malloc(32);

    ptr++;

    free(ptr);

    return;
}


void
overflow(void) {
    char *ptr;
    int   i;

    /* Can not detect */
    ptr = (char *)malloc(3);
    for (i = 0; i < 8; i++){
        ptr[i] = 'a';
    }
    free(ptr);

    /* OK */
/* <jemalloc>: Corrupt redzone 0 bytes after 0x2b0f58f5a100 (size 8), byte=0x32 */
    ptr = (char *)malloc(3);
    for (i = 0; i < 9; i++){
        ptr[i] = 'b';
    }
    free(ptr);

    /* OK */
/*
<jemalloc>: Corrupt redzone 0 bytes after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 1 byte after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 2 bytes after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 3 bytes after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 4 bytes after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 5 bytes after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 6 bytes after 0x2b387c731180 (size 32), byte=0x61
<jemalloc>: Corrupt redzone 7 bytes after 0x2b387c731180 (size 32), byte=0x61
*/
    ptr = (char *)malloc(24);
    for (i = 0; i < 40; i++){
        ptr[i] = 'a';
    }
    free(ptr);

    /* OK */
/*
<jemalloc>: Corrupt redzone 1 byte before 0x2b0908c0f081 (size 32), byte=0x64
<jemalloc>: Corrupt redzone 2 bytes before 0x2b0908c0f081 (size 32), byte=0x64
<jemalloc>: Corrupt redzone 3 bytes before 0x2b0908c0f081 (size 32), byte=0x64
<jemalloc>: Corrupt redzone 4 bytes before 0x2b0908c0f081 (size 32), byte=0x64
<jemalloc>: Corrupt redzone 5 bytes before 0x2b0908c0f081 (size 32), byte=0x64
<jemalloc>: Corrupt redzone 6 bytes before 0x2b0908c0f081 (size 32), byte=0x64
<jemalloc>: Corrupt redzone 7 bytes before 0x2b0908c0f081 (size 32), byte=0x64
*/

    ptr = (char *)malloc(24);
    for (i = 0; i > -8; i--){
        ptr[i] = 'd';
    }
    free(ptr);


    return;
}


int
main(void)
{
    printf("#### Fill region test ####\n");
    fill_region();

    printf("#### Leak Memory test ####\n");
    leak_memory();

    printf("#### Double free test ####\n");
    double_free();

    printf("#### Free incorrect pointer test ####\n");
    bad_free();

    printf("#### Overflow test ####\n");
    overflow();

#if defined(USE_JEMALLOC) && defined(STATS_PRINT)
    malloc_stats_print(NULL, NULL, NULL);
#endif

    return 0;
}
