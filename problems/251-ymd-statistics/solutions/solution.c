/* 年月日统计 for problem 251 on XDOJ by LyCecilion - Pure C Version */

#include <stdio.h>

typedef struct
{
    int year, month, day;
} date;

int cnt[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int cnt_leap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static inline int is_leap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// clang-format off

/* md[leap][month - 1] */
static const int md[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* prefix[leap][month] */
static const int prefix[2][13] = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
    {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}};

// clang-format on

int main(void)
{
    // The problem requires using a struct here, which is quite unnecessary.
    // However, out of respect for the intended focus of this problem,
    // we will still use a struct here in this context.
    date input;

    if ((scanf("%d,%d,%d", &input.year, &input.month, &input.day)) != 3 || input.month < 1 || input.month > 12)
        return 0;

    const int leap = is_leap(input.year);
    const int max_day = md[leap][input.month - 1];
    if (input.day < 1 || input.day > max_day)
        return 0;

    const int day_cnt = prefix[leap][input.month - 1] + input.day;
    printf("%d", day_cnt);
    return 0;
}