/* 找奇偶数的数量 for problem 759 on XDOJ by LyCecilion - Pure C version */

#include <stdio.h>

enum
{
    MAX_NUMBERS = 1000,
    MAX_VALUE = 999,
    MIN_VALUE = -999
};

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1)
        return 0;

    int temp;
    int cnt[2] = {0};

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%d", &temp) != 1 || temp < MIN_VALUE || temp > MAX_VALUE)
            return 0;

        cnt[temp % 2]++;
    }

    printf("%d %d", cnt[1], cnt[0]);
    return 0;
}
