#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n = 1000;
    char arr[n];
    int counter[1000] = {0};
    scanf("%[^\n]*c",arr);
    for ( int i = 0 ; i < 10 ; i++)
    {
        for(int j = 0; j<strlen(arr);j++)
        {
            if (arr[j]==(i+'0'))
            {
              counter[i]++;
            }
        }

        printf("%d ",counter[i]);
    }

    return 0;
}
