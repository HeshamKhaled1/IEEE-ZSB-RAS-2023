#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b){
    return strcmp(a, b) > 0 ;
}

int lexicographic_sort_reverse(const char* a, const char* b){
    return strcmp(a, b) < 0 ;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b){
    int first_length = 0, second_length = 0;
    int arr_1[50] = {0}, arr_2[50] = {0};
    int length_a = strlen(a);
    int length_b = strlen(b);

    for(int i = 0; i < length_a; i++){
        arr_1[a[i] - 'a'] = 1;   
    }

    for(int i = 0; i < length_b; i++){
        arr_2[b[i] - 'a' ] = 1;   
    }

    for(int i = 0; i < 50; i++){
        if(arr_1[i])
            first_length++;
        if(arr_2[i])
            second_length++;
    }
    if( first_length != second_length)
        return first_length > second_length;
    else
        return strcmp(a, b)  > 0;

}

int sort_by_length(const char* a, const char* b){
    if(strlen(a) != strlen(b))
        return strlen(a) > strlen(b) ;   
    else
        return strcmp(a, b) > 0;
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    for(int i = 1; i < len; i++){
        int j = i;
        char* p = arr[i];
        while(j > 0){
            if((*cmp_func)(arr[j-1],p) > 0 )
                arr[j] = arr[j-1];
            else
                break;
            j--;
        }
        arr[j] = p;
    }
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
  arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}