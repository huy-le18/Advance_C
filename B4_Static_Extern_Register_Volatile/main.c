#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    register unsigned long i;
    clock_t start, end;
    /* time start */
    start = clock();

    for( i = 0; i < 99999999; i ++);

    /* time end */
    end = clock();

    printf("run time with registor: %f\n", (double)(end - start)/1000);
}

