#include <stdio.h>
#include <string.h>

int my_strcmp(const char *s1, const char *s2) {
    printf("内置password: %s  输入password: %s \n", s1, s2);
    return 0;  // 永远相等
}