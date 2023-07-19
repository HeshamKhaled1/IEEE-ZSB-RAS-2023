#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* longestPalindrome(char* s) {
    int len = strlen(s);
    if (len == 0) {
        // Empty string, no palindrome to find
        return "";
    }

    bool dp[len][len]; // dp[i][j] will be true if substring s[i..j] is a palindrome
    memset(dp, false, sizeof(dp)); // Initialize the dp array to false

    int start = 0; // Start index of the longest palindromic substring found so far
    int maxLength = 1; // Length of the longest palindromic substring found so far

    // All substrings of length 1 are palindromes
    for (int i = 0; i < len; i++) {
        dp[i][i] = true;
    }

    // Check substrings of length 2
    for (int i = 0; i < len - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Check substrings of length 3 or more
    for (int subLen = 3; subLen <= len; subLen++) {
        for (int i = 0; i < len - subLen + 1; i++) {
            int j = i + subLen - 1; // Ending index of current substring

            // Check if the current substring is a palindrome
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLength = subLen;
            }
        }
    }

    // Allocate memory for the palindromic substring and copy it
    char* result = (char*)malloc((maxLength + 1) * sizeof(char));
    strncpy(result, s + start, maxLength);
    result[maxLength] = '\0';

    return result;
}