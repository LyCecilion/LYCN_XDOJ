/* 数字分解排序 for problem 134 on XDOJ by LyCecilion - Pure C version */

#include <stdio.h>

enum
{
    MAX_NUM = 1000000000
};

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_NUM)
        return 0;

    int count[10] = {0};

    while (n > 0)
    {
        ++count[n % 10];
        n /= 10;
    }

    int first = 1;
    for (int d = 9; d >= 0; --d)
    {
        for (int k = 0; k < count[d]; ++k)
        {
            if (!first)
                printf(" ");
            first = 0;
            printf("%d", d);
        }
    }

    return 0;
}
