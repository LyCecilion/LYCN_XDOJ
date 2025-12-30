/* 拼数字 for problem 108 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

namespace
{
    constexpr int MAX_LEN = 100;
} // namespace

static uint32_t max_factor(uint32_t n)
{
    if (n == 0)
        return 0;
    if (n <= 3)
        return n == 1 ? 1u : n;
    if ((n & 1u) == 0)
        return n >> 1;

    const uint32_t limit = static_cast<uint32_t>(sqrt(static_cast<double>(n)));
    for (uint32_t d = 3; d <= limit; d += 2)
    {
        if (n % d == 0)
            return n / d;
    }
    return n;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char buf[MAX_LEN];
    if (!cin.getline(buf, sizeof(buf))) return 0;

    uint32_t val = 0;
    for (const char *p = buf; *p; ++p)
    {
        unsigned char c = static_cast<unsigned char>(*p);
        if (c >= '0' && c <= '9')
        {
            val = val * 10u + static_cast<uint32_t>(c - '0');
        }
    }

    cout << max_factor(val) << '\n';
    return 0;
}
