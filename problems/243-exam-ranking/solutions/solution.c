/* 考试排名 for problem 243 on XDOJ by LyCecilion - Pure C Version */

#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_STUDENTS = 100,
    NAME_LEN = 21 /* 20 chars + '\0' */
};

typedef struct
{
    char name[NAME_LEN];
    int score_1, score_2, score_3, score_4, score_5, additional;
    int sum;
} student;

int cmp(const void *a, const void *b)
{
    const student *sa = (const student *)a;
    const student *sb = (const student *)b;
    if (sa->sum > sb->sum)
        return -1;
    if (sa->sum < sb->sum)
        return 1;

    return (sa->additional < sb->additional) - (sa->additional > sb->additional);
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_STUDENTS)
        return 0;

    student stu[MAX_STUDENTS];

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%20s %d %d %d %d %d %d", stu[i].name, &stu[i].score_1, &stu[i].score_2, &stu[i].score_3,
                  &stu[i].score_4, &stu[i].score_5, &stu[i].additional) != 7)
            return 0;

        stu[i].sum =
            stu[i].score_1 + stu[i].score_2 + stu[i].score_3 + stu[i].score_4 + stu[i].score_5 + stu[i].additional;
    }

    qsort(stu, n, sizeof(stu[0]), cmp);

    for (int i = 0; i < n; ++i)
        printf("%s %d %d\n", stu[i].name, stu[i].sum, stu[i].additional);

    return 0;
}