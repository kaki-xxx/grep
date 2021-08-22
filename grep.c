#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grep.h"
#define MIN(a, b) (((a) < (b))? (a) : (b))
#define MAX(a, b) (((a) > (b))? (a) : (b))
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int grep_line(const char *str, const char *pattern) {
    /**
     * BM法による部分文字列の検索
     *
     * @param[in] str 検索対象となる文字列
     * @param[in] pattern 検索する文字列
     * @return strにpatternが見つかった最初の位置
     */
    size_t str_len = strlen(str);
    size_t pattern_len = strlen(pattern);
    if (pattern_len > str_len) {
        return -1;
    }
    int shift_tab[1<<CHAR_BIT];
    for (int i = 0; i < ARRAY_SIZE(shift_tab); ++i) {
        shift_tab[i] = pattern_len;
    }
    for (int i = 0; i < pattern_len; ++i) {
        char p = pattern[i];
        shift_tab[p] = MIN(shift_tab[p], pattern_len - 1 - i);
    }
    for (int offset = 0; offset < str_len - pattern_len + 1;) {
        bool equal = true;
        for (int i = pattern_len - 1; i >= 0; --i) {
            if (str[offset + i] != pattern[i]) {
                offset += MAX(1, shift_tab[str[offset + i]] - (pattern_len - 1 - i));
                equal = false;
                break;
            }
        }
        if (equal) {
            return offset;
        }
    }
    return -1;
}

void grep(FILE *fp, const char *pattern) {
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
        if (grep_line(line, pattern) != -1) {
            printf("%s", line);
        }
    }

    free(line);
    fclose(fp);
}
