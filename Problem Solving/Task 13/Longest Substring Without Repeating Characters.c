#include <string.h>

int lengthOfLongestSubstring(char* s) {
    int start = 0;
    int end = 0;
    int ma_len = 0;
    int len = strlen(s);
    int charSet[300] = {0};  
    
    for (int i = 0 ; i < 300; i ++){
          charSet[i]=-1 ;
      }
        
    while (end < len) {
        if (charSet[s[end]] >= start) {
            start = charSet[s[end]] + 1;
        }
        charSet[s[end]] = end;
        
        int currentLength = end - start + 1;
        ma_len = (currentLength > ma_len) ? currentLength : ma_len;
        
        end++;
    }
    
    return ma_len;
}