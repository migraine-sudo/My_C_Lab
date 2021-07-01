#include <stdio.h>

void test(char *s)
{
    printf(s);
    return ;
}

int main()
{
    char *str = "aaaaaaaaaa";
    test(str);
}