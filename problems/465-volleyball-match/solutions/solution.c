/* 排球比赛排名 for problem 465 on XDOJ by LyCecilion - Pure C Version */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    MAX_TEAMS = 10,
    NAME_LEN = 13 /* 12 chars + '\0' */
};

typedef struct
{
    char name[NAME_LEN];
    int wins;
    int pts;
} Team;

static int cmp(const void *a, const void *b)
{
    const Team *ta = (const Team *)a;
    const Team *tb = (const Team *)b;

    if (ta->wins != tb->wins)
        return (tb->wins - ta->wins);
    if (ta->pts != tb->pts)
        return (tb->pts - ta->pts);
    return strcmp(ta->name, tb->name);
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 1 || n > MAX_TEAMS)
        return 0;

    Team teams[MAX_TEAMS] = {0};

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%12s", teams[i].name) != 1)
            return 0;
    }

    int v;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (scanf("%d", &v) != 1)
                return 0;

            if (j == i)
                continue;

            if (v == 5) // 3:2, winner + 2pts, loser + 1pt
            {
                teams[i].wins++;
                teams[i].pts += 2;
            }
            else if (v == 4 || v == 3) // 3:1 or 3:0, winner + 3pts, loser + 0pt
            {
                teams[i].wins++;
                teams[i].pts += 3;
            }
            else if (v == -5) // 2:3, loser + 1pt, winner + 2pts
                teams[i].pts++;
        }
    }

    qsort(teams, n, sizeof(teams[0]), cmp);

    for (int i = 0; i < n; ++i)
        printf("%s %d %d\n", teams[i].name, teams[i].wins, teams[i].pts);

    return 0;
}