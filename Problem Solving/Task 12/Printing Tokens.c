#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
     char arr[1000];
     scanf("%[^\n]*c",arr);
     for(int i = 0 ; i < strlen(arr);i++)
     {
         if (arr[i]==' ')
         {
         printf("\n");
         }
         else {
          printf("%c",arr[i]);
         }
     }
    return 0;
}
