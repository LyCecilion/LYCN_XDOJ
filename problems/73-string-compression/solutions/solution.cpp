/* 字符串压缩 for problem 73 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;

    string out;

    const int n = static_cast<int>(s.size());
    for (int i = 0; i < n;)
    {
        char ch = s[i++];
        int cnt = 0;
        while (i < n && isdigit(static_cast<unsigned char>(s[i])))
        {
            cnt = cnt * 10 + (s[i] - '0');
            ++i;
        }

        if (cnt == 0) cnt = 1;
        out.append(cnt, ch);
    }

    cout << out << '\n';
    return 0;
}
