/* 年月日统计 for problem 251 on XDOJ by LyCecilion - C++ Version */

#include <array>
#include <cstdio>

// clang-format off

namespace {
constexpr bool is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

/* md[leap][month - 1] */
constexpr std::array<std::array<int, 12>, 2> md{{
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
}};

/* prefix[leap][month] */
constexpr std::array<std::array<int, 13>, 2> prefix{{
    {0, 31, 59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
    {0, 31, 60,  91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
}};
} // namespace

// clang-format on

int main()
{
    int y, m, d;
    if (std::scanf("%d,%d,%d", &y, &m, &d) != 3)
        return 0;

    if (m < 1 || m > 12)
        return 0;

    const int leap = is_leap(y);
    const int max_day = md[leap][m - 1];
    if (d < 1 || d > max_day)
        return 0;

    const int day_cnt = prefix[leap][m - 1] + d;
    std::printf("%d", day_cnt);
    return 0;
}