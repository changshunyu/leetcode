#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int longestCommonSubsequence(char *text1, char *text2) {
    int m = strlen(text1), n = strlen(text2);
    int **dp; //初始化1个全0的m+1*n+1的2维数组；
    dp = (int **)malloc(sizeof(int *) * (m + 1));
    for (int i = 0; i < m + 1 ; i++) {
        dp[i] = (int *)malloc(sizeof(int) * (n + 1));
        for (int j = 0; j < n + 1; j++)
        dp[i][j] = 0;
    }

    for (int i = 1; i <= m; i++) { //注意这里索引i和j都是从1开始的，但取字符串中的字符时又是从text[0]开始取的；
        char c1 = text1[i-1];
        for (int j = 1; j <= n; j++) {
            char c2 = text2[j-1];
            if (c1 == c2) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = fmax(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}

void main() {
    char text1[] = "abcde", text2[] = "ace";
    printf("%d", longestCommonSubsequence(text1, text2));
}