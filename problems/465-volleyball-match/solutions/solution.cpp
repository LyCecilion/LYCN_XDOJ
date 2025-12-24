/* 排球比赛排名 for problem 465 on XDOJ by LyCecilion - C++ Version */

#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_TEAMS = 10;
constexpr int NAME_LEN = 12;

struct Team
{
    string name;
    int wins = 0;
    int pts = 0;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n < 2 || n > MAX_TEAMS)
        return 0;

    vector<Team> t(n);
    for (auto &x : t)
    {
        if (!(cin >> x.name))
            return 0;
        if ((int)x.name.size() > NAME_LEN)
            x.name.resize(NAME_LEN);
    }

    int v;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!(cin >> v))
                return 0;
            if (i == j)
                continue;

            if (v == 5) // 3:2, winner + 2pts, loser + 1pt
            {
                t[i].wins++;
                t[i].pts += 2;
            }
            else if (v == 4 || v == 3) // 3:1 or 3:0, winner + 3pts, loser + 0pt
            {
                t[i].wins++;
                t[i].pts += 3;
            }
            else if (v == -5) // 2:3, loser + 1pt, winner + 2pts
            {
                t[i].pts += 1;
            }
        }
    }

    sort(t.begin(), t.end(), [](const Team &a, const Team &b) {
        if (a.wins != b.wins)
            return a.wins > b.wins;
        if (a.pts != b.pts)
            return a.pts > b.pts;
        return a.name < b.name;
    });

    for (auto &x : t)
        cout << x.name << ' ' << x.wins << ' ' << x.pts << '\n';
    return 0;
}