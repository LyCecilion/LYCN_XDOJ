/* 子串定位 for problem 560 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    if (!(cin >> s >> t))
        return 0;

    if (t.empty())
        return 0;

    if (s.size() < t.size())
    {
        cout << -1 << endl;
        return 0;
    }

    size_t pos = s.find(t);
    if (pos == string::npos)
        cout << -1 << endl;
    else
        cout << static_cast<int>(pos);
    return 0;
}
