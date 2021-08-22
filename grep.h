#ifndef GREP_H
#define GREP_H

#include <stdio.h>
int grep_line(const char *str, const char *pattern);
void grep(FILE *fp, const char *pattern);

#endif /* GREP_H */
