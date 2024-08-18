#include <stdio.h>
#include <stdarg.h>


#define tong(...)   sum(__VA_ARGS__, 0)


int sum(int count,...) 
{
    va_list va;

    int sum = count;
    va_start(va, count);
    int value;

    while ((value = va_arg(va, int)) != 0)
    {
        sum += value;
    }

    va_end(va);

    return sum;
    
}

int main()
{
    printf("Tong: %d\n", tong(6, 1,4, 5,9,6,4));

    return 0;
}