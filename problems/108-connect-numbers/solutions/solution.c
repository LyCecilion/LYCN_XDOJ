/* 拼数字 for problem 108 on XDOJ by LyCecilion - Pure C version */

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

enum
{
    MAX_LEN = 101 /* 100 chars + '\0' */
};

static uint32_t max_factor(uint32_t n)
{
    if (n == 0)
        return 0;
    if (n <= 3)
        return n == 1 ? 1 : n;

    if ((n & 1u) == 0)
        return n >> 1;

    uint32_t limit = (uint32_t)sqrt((double)n);
    for (uint32_t d = 3; d <= limit; d += 2)
    {
        if (n % d == 0)
            return n / d;
    }
    return n;
}

int main(void)
{
    char buf[MAX_LEN];
    if (!fgets(buf, sizeof(buf), stdin))
        return 0;

    uint32_t val = 0;
    for (const char *p = buf; *p; ++p)
    {
        if (isdigit((unsigned char)*p))
            val = val * 10u + (uint32_t)(*p - '0');
    }

    printf("%u\n", max_factor(val));
    return 0;
}
