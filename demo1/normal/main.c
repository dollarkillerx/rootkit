#include <stdio.h>
#include <string.h>
#include "libstr.h"

int main(int argc,char **argv) {
    printf("Init main\n");

    char password[] = "password"; // 定义default password

    if (argc < 2) {
        printf("usage: %s <password \n>",argv[0]);
        return 1;
    }

    if (!my_strcmp(password, argv[1])) {
        printf("Corrent Passwod! \n");
        return 0;
    }
    printf("Invalid Password! \n");

    return 0;
}