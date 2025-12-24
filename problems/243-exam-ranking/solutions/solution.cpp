/* 考试排名 for problem 243 on XDOJ by LyCecilion - C++ Version */

#include <bits/stdc++.h>
#include <numeric>
using namespace std;

namespace
{
constexpr int MAX_STUDENTS = 100;
constexpr int NAME_LEN = 20;
}; // namespace

struct Student
{
    string name{};
    array<int, 5> score{};
    int additional{}, sum{};
};

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n <= 0 || n >= MAX_STUDENTS)
        return 0;

    vector<Student> stu(n);

    for (int i = 0; i < n; ++i)
    {
        Student s{};
        if (!(cin >> setw(NAME_LEN + 1) >> s.name >> s.score[0] >> s.score[1] >> s.score[2] >> s.score[3] >>
              s.score[4] >> s.additional))
            return 0;

        s.sum = accumulate(s.score.begin(), s.score.end(), s.additional);
        stu[i] = s;
    }

    sort(stu.begin(), stu.end(), [](const Student &a, const Student &b) {
        if (a.sum != b.sum)
            return a.sum > b.sum;           // higher sum first
        return a.additional > b.additional; // higher additional score first
    });

    for (int i = 0; i < n; ++i)
        cout << stu[i].name << ' ' << stu[i].sum << ' ' << stu[i].additional << '\n';

    return 0;
}