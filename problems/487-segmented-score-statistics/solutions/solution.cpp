/* 分段统计学生成绩 for problem 487 on XDOJ by LyCecilion - C++ Version */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n))
        return 0;

    int tier1 = 0, tier2 = 0, tier3 = 0;
    string name;
    int score;

    for (int i = 0; i < n; ++i)
    {
        if (!(cin >> name >> score) || score < 0 || score > 100)
            return 0;

        if (score >= 80)
            ++tier1;
        else if (score >= 60)
            ++tier2;
        else
            ++tier3;
    }

    cout << tier1 << ' ' << tier2 << ' ' << tier3;
    return 0;
}