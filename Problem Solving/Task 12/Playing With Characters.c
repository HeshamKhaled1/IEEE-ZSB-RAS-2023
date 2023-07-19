#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char ch;
    char m[50]   ;
    char n[100];
    scanf("%c\n%s\n%[^\n]*s",&ch,m,n);
    printf("%c\n%s\n%s", ch, m, n);
    return 0;
}
