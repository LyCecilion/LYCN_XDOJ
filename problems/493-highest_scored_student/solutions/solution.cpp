/* 找出总分最高的学生 for problem 493 on XDOJ by LyCecilion - C++ Version */

#include <bits/stdc++.h>
using namespace std;

namespace
{
constexpr int MAX_STUDENTS = 10;
constexpr int ID_LEN = 5;
constexpr int NAME_LEN = 10;
} // namespace

struct student
{
    string id, name;
    int sum;
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n < 0 || n > MAX_STUDENTS)
        return 0;

    vector<student> stu;
    stu.reserve(n);

    int best_idx = -1;
    for (int i = 0; i < n; ++i)
    {
        string id, name;
        int s1, s2, s3;
        if (!(cin >> id >> setw(NAME_LEN + 1) >> name >> s1 >> s2 >> s3))
            return 0;

        int sum = s1 + s2 + s3;
        stu.push_back({id, name, sum});

        if (best_idx == -1 || sum > stu[best_idx].sum)
            best_idx = i; // the problem guarantees that such a student is unique.
    }

    const auto &best = stu[best_idx];
    cout << best.name << ' ' << best.id << ' ' << best.sum << '\n';

    return 0;
}