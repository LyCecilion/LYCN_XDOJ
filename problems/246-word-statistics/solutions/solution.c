/* 单词统计 for problem 246 on XDOJ by LyCecilion - Pure C version */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    MAX_LINE = 102, /* 100 chars + '\n' + '\0' */
    MAX_WORD = 10, /* 8 chars + '\n' + '\0' */
};

static void chomp(char *s)
{
    size_t n = strlen(s);
    if (n && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

static int ci_word_eq(const char *s, size_t len, const char *w)
{
    for (size_t i = 0; i < len; i++)
    {
        if (w[i] == '\0')
            return 0; // length not match, w is shorter
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)w[i]))
            return 0;
    }
    return w[len] == '\0'; // length not match, s is shorter
}

static int count(const char *line, const char *word)
{
    int cnt = 0;
    const char *p = line;

    while (*p)
    {
        while (*p && isspace((unsigned char)*p))
            p++;
        if (!p)
            break;

        const char *start = p;
        while (*p && !isspace((unsigned char)*p))
            p++;
        size_t len = (size_t)(p - start);

        if(ci_word_eq(start, len, word))
            cnt++;
    }
    return cnt;
}

int main(void)
{
    char line[MAX_LINE];
    char word[MAX_WORD];

    if (!fgets(line, sizeof(line), stdin))
        return 0;
    if (!fgets(word, sizeof(word), stdin))
        return 0;

    chomp(line);
    chomp(word);

    int c = count(line, word);
    printf("%s %d\n", word, c);
    return 0;
}
