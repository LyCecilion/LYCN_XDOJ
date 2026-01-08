/* 输入联想 for problem 469 on XDOJ by LyCecilion - Pure C version */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    MAX_WORDS = 1000,
    MAX_LETTERS = 21, /* 20 chars + '\0' */
    MAX_CANDIDATES = 5
};

typedef struct
{
    char word[MAX_LETTERS];
    int frequency;
} word_info;

static size_t normalize_word(char *s)
{
    size_t pos = 0;
    for (size_t i = 0; s[i] && pos + 1 < MAX_LETTERS; ++i)
    {
        unsigned char ch = (unsigned char)s[i];
        if (isalpha(ch))
        {
            s[pos++] = (char)tolower(ch);
        }
    }
    s[pos] = '\0';
    return pos;
}

static int compare_words(const void *a, const void *b)
{
    const word_info *wa = (const word_info *)a;
    const word_info *wb = (const word_info *)b;
    if (wa->frequency < wb->frequency)
        return 1;
    if (wa->frequency > wb->frequency)
        return -1;
    return strcmp(wa->word, wb->word);
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
        return 0;

    word_info candidates[MAX_WORDS];
    int candidates_cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        char temp_word[MAX_LETTERS] = {0};
        if (scanf("%20s", temp_word) != 1)
            return 0;

        if (normalize_word(temp_word) == 0)
            continue;

        bool found = false;

        for (int j = 0; j < candidates_cnt; ++j)
        {
            if (strcmp(temp_word, candidates[j].word) == 0)
            {
                candidates[j].frequency++;
                found = true;
                break;
            }
        }
        if (!found && candidates_cnt < MAX_WORDS)
        {
            strcpy(candidates[candidates_cnt].word, temp_word);
            candidates[candidates_cnt++].frequency = 1;
        }
    }

    qsort(candidates, (size_t)candidates_cnt, sizeof(candidates[0]), compare_words);

    char first_char;
    if (scanf(" %c", &first_char) != 1)
        return 0;
    first_char = (char)tolower((unsigned char)first_char);

    int shown = 0;
    bool first_output = true;

    for (int i = 0; i < candidates_cnt && shown < MAX_CANDIDATES; ++i)
    {
        if (candidates[i].word[0] == first_char)
        {
            if (first_output)
            {
                first_output = false;
                printf("%s", candidates[i].word);
            }
            else
                printf(" %s", candidates[i].word);
            ++shown;
        }
    }

    return 0;
}
