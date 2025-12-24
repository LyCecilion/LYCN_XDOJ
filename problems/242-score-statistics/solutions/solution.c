/* 成绩统计 for problem 242 on XDOJ by LyCecilion - Pure C version */

#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_STUDENTS = 100,
    NAME_LEN = 11 /* 10 chars + '\0' */
};

typedef struct
{
    int stu_id;
    char name[NAME_LEN];
    int course_1, course_2, course_3;
    double average_score;
} student;

static int cmp(const void *a, const void *b)
{
    const student *sa = (const student *)a;
    const student *sb = (const student *)b;
    if (sa->average_score > sb->average_score)
        return -1; /* higher average first */
    else if (sa->average_score < sb->average_score)
        return 1;

    /* smaller id first */
    return (sa->stu_id > sb->stu_id) - (sa->stu_id < sb->stu_id);
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STUDENTS)
        return 0;

    student stu[MAX_STUDENTS];

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%d %10s %d %d %d", &stu[i].stu_id, stu[i].name, &stu[i].course_1, &stu[i].course_2,
                  &stu[i].course_3) != 5)
            return 0;

        const int sum = stu[i].course_1 + stu[i].course_2 + stu[i].course_3;
        stu[i].average_score = sum / 3.0;
    }

    qsort(stu, (size_t)n, sizeof(stu[0]), cmp);

    for (int i = 0; i < n; ++i)
        printf("%d %s %.1f\n", stu[i].stu_id, stu[i].name, stu[i].average_score);

    return 0;
}