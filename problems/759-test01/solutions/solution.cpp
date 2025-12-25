/* 找奇偶数的数量 for problem 759 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

namespace{
    constexpr int MAX_NUMBERS = 1000;
    constexpr int MAX_VALUE = 999;
    constexpr int MIN_VALUE = -999;
} // namespace

int main(void)
{
    int n;
    if (!(cin >> n)) return 0;

    int temp;
    int cnt[2] = {0};

    for (int i = 0; i < n; ++i)
    {
        if (!(cin >> temp) || temp < MIN_VALUE || temp > MAX_VALUE)
            return 0;

        cnt[temp % 2]++;
    }

    cout << cnt[1] << ' ' << cnt[0] << endl;
    return 0;
}
