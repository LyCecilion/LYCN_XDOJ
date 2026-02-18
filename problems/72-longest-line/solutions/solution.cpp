/* 寻找最长的行 for problem 72 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    string best;
    size_t max_len = 0;
    
    while (getline(cin, line))
    {
        if (line == "***end***") break;
        const size_t len = line.size();
        if (len > max_len)
        {
            max_len = len;
            best = std::move(line);
        }
    }

    if ((max_len == 0) & best.empty()) return 0;

    cout << max_len << '\n' << best << '\n';
    return 0;
}
