#include <stdio.h>
#include <string.h>

int main() 
{
    const char haystack[20] = "RUNxxx";
    const char needle[10] = "NOOB";
    char *ret;
    ret = strstr(haystack, needle);
    printf("子str: %s \n",ret);
    return 0;
}