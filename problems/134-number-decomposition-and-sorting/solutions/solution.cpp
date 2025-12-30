/* 数字分解排序 for problem 134 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

namespace
{
    constexpr int kMaxNum = 1'000'000'000;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n <= 0 || n >= kMaxNum)
        return 0;

    array<int, 10> cnt{};
    for (int x = n; x > 0; x /= 10)
    {
        ++cnt[x % 10];
    }

    bool first = true;
    for (int d = 9; d >= 0; --d)
    {
        for (int k = 0; k < cnt[d]; ++k)
        {
            if (!first)
                cout << ' ';
            first = false;
            cout << d;
        }
    }

    return 0;
}
