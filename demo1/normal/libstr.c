#include <stdio.h>
#include <string.h>
#include "libstr.h"

// 内部就是调用标准库中的函数
int my_strcmp(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}