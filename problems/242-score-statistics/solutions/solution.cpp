/* 成绩统计 for problem 242 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

namespace
{
constexpr int MAX_STUDENTS = 100;
constexpr int NAME_LEN = 10;
} // namespace

struct Student
{
    int stu_id{};
    string name;
    int course_1{}, course_2{}, course_3{};
    double average_score{};
};

static int cmp(const Student &a, const Student &b)
{
    if (a.average_score > b.average_score)
        return -1; /* higher average first */
    else if (a.average_score < b.average_score)
        return 1;

    /* smaller id first */
    return (a.stu_id > b.stu_id) - (a.stu_id < b.stu_id);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n <= 0 || n > MAX_STUDENTS)
        return 0;

    vector<Student> stu(n);

    for (int i = 0; i < n; ++i)
    {
        stu[i].name.reserve(NAME_LEN);
        cin >> stu[i].stu_id;

        cin.width(NAME_LEN + 1);
        cin >> stu[i].name >> stu[i].course_1 >> stu[i].course_2 >> stu[i].course_3;
        const int sum = stu[i].course_1 + stu[i].course_2 + stu[i].course_3;
        stu[i].average_score = sum / 3.0;
    }

    sort(stu.begin(), stu.end(), [](const Student &a, const Student &b) {
        const int r = cmp(a, b);
        return r < 0;
    });

    cout.setf(ios::fixed);
    cout << setprecision(1);

    for (const auto &s : stu)
    {
        cout << s.stu_id << ' ' << s.name << ' ';
        cout << s.average_score << '\n';
    }

    return 0;
}