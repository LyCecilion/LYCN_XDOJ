/* 分段统计学生成绩 for problem 487 on XDOJ by LyCecilion - Pure C Version */

#include <stdio.h>

enum
{
    MAX_STUDENTS = 100,
    NAME_LEN = 21 /* 20 chars + '\0' */
};

typedef struct
{
    char name[NAME_LEN];
    int points;
} student;

int main(void)
{
    // This problem has an obvious solution that does not require structs:
    // we can process only the scores. A better approach is provided in the C++ version.

    // tier1 -> [80, 100]; tier2 -> [60, 79]; tier3 -> [0, 59]
    int n, tier1 = 0, tier2 = 0, tier3 = 0;

    if (scanf("%d", &n) != 1)
        return 0;

    student stu[MAX_STUDENTS] = {0};
    for (int i = 0; i < n; ++i)
    {
        if (scanf("%20s %d", stu[i].name, &stu[i].points) != 2 || stu[i].points > 100 || stu[i].points < 0)
            return 0;

        if (stu[i].points >= 80)
            tier1++;
        else if (stu[i].points >= 60)
            tier2++;
        else
            tier3++;
    }

    printf("%d %d %d", tier1, tier2, tier3);

    return 0;
}