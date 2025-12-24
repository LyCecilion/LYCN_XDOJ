/* 子串定位 for problem 560 on XDOJ by LyCecilion - Pure C version */

#include <stdio.h>
#include <string.h>

enum
{
    STR_LENGTH = 101 /* 100 chars + '\0' */
};

int main(void)
{
    char s[STR_LENGTH] = {0}, t[STR_LENGTH] = {0};
    if (scanf("%100s %100s", s, t) != 2)
        return 0;

    const size_t n = strlen(s);
    const size_t m = strlen(t);

    if (m == 0)
        return 0;

    if (n < m)
    {
        printf("-1");
        return 0;
    }

    for (size_t i = 0; i <= n - m; ++i)
    {
        if (s[i] == t[0] && memcmp(&s[i], t, m) == 0)
        {
            printf("%zu", i);
            return 0;
        }
    }

    printf("-1");
    return 0;
}
