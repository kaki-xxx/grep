#include <stdio.h>
#include "grep.h"

int main(void) {
    printf("%d\n", grep_line("hogehoge", "hoge"));
    printf("%d\n", grep_line("hogefuga", "fuga"));
    printf("%d\n", grep_line("hogefuga", "moge"));
    return 0;
}
