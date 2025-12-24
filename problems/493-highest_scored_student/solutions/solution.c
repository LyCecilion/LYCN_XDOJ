/* 找出总分最高的学生 for problem 493 on XDOJ by LyCecilion - Pure C Version */

#include <stdio.h>

enum
{
    MAX_STUDENTS = 10,
    ID_LEN = 6,   /* 5 chars + '\0'*/
    NAME_LEN = 11 /* 10 chars + '\0' */
};

typedef struct
{
    char id[ID_LEN];
    char name[NAME_LEN];
    int sum;
} student;

int main(void)
{
    int n, s1, s2, s3;
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX_STUDENTS)
        return 0;

    student stu[MAX_STUDENTS];

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%5s %10s %d %d %d", stu[i].id, stu[i].name, &s1, &s2, &s3) != 5)
            return 0;
        stu[i].sum = s1 + s2 + s3;
    }

    int high = 0;
    for (int i = 0; i < n; ++i)
    {
        if (stu[i].sum > stu[high].sum)
            high = i; // the problem guarantees that such a student is unique.
    }

    printf("%s %s %d\n", stu[high].name, stu[high].id, stu[high].sum);

    return 0;
}