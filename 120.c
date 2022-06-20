#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//解法1：递归
//trianglesSize:三角形的高；
//虽然没有占用空间，但是存在大量的重复计算；
int dfs(int **triangle, int triangleSize, int i, int j) {
    if (i == triangleSize) return 0; //递归终止条件
    return fmin(dfs(triangle, triangleSize, i + 1, j), dfs(triangle, triangleSize, i + 1, j + 1)) + triangle[i][j];
}

int minimumTotal_recursion(int **triangle, int triangleSize) {
    return dfs(triangle, triangleSize, 0, 0);
}


//递归+记忆化
//时间复杂度:O(n^2)；空间复杂度:O(n^2)；
int dfs2(int **triangle, int **memo, int triangelSize, int i, int j) {
    if (i == triangelSize) return 0;
    if (memo[i][j] != 0) return memo[i][j];
    return memo[i][j] = fmin(dfs2(triangle, memo, triangelSize, i+1, j), dfs2(triangle, memo, triangelSize, i+1, j+1)) + triangle[i][j];
}

int minimumTotal_recursion2(int **triangle, int triangleSize) {

    int **memo; //考虑这里能否用栈上的空间解决？
    memo = (int **)malloc(sizeof(int *) * triangleSize);
    for (int i = 0; i < triangleSize ; i++) {
        memo[i] = (int *)malloc(sizeof(int) * triangleSize);
        for (int j = 0; j < triangleSize; j++) memo[i][j] = 0;
    }

    return dfs2(triangle, memo, triangleSize, 0, 0); //dfs2会被反复调用，memo定义在其中不合适；
}


//解法3：动态规划
//边界条件：当j=0时，f[i-1][j-1]没有意义;当j=i时，f[i-1][j]没有意义（因为第i-1行有i个元素，它们对应的j的范围为[0, i-1]。）；
//这样一来，我们从1开始递归地枚举i，并在[0, i]的范围内递增地枚举j，就可以完成所有状态的计算。
//时间复杂度:O(n^2)；空间复杂度:O(n^2)；
int minimumTotal_dp(int **triangle, int triangleSize) {
    int **f;
    f = (int **)malloc(sizeof(int *) * triangleSize);
    for (int i = 0; i < triangleSize ; i++) {
        f[i] = (int *)malloc(sizeof(int) * triangleSize);
        for (int j = 0; j < triangleSize; j++) f[i][j] = 0;
    }
    
    f[0][0] = triangle[0][0];
    for (int i = 1; i < triangleSize; i++) {
        f[i][0] = f[i-1][0] +triangle[i][0];
        for (int j = 1; j < i; j++) f[i][j] = fmin(f[i-1][j-1], f[i-1][j]) + triangle[i][j];
        f[i][i] = f[i-1][i-1] + triangle[i][i];
    }

    int ret = f[triangleSize-1][0];
    for (int i = 1; i < triangleSize; i++) ret = fmin(ret, f[triangleSize-1][i]);
    return ret;
}


//解法4:动态规划+空间优化（滚动数组）；
//时间复杂度:O(n^2)；空间复杂度:O(n)；
int minimumTotal_dp2(int **triangle, int triangleSize) {
    int **f;
    f = (int **)malloc(sizeof(int *) * 2);
    f[0] = (int *)malloc(sizeof(int) * triangleSize);
    f[1] = (int *)malloc(sizeof(int) * triangleSize);
    f[0][0] = triangle[0][0];
    
    for(int i = 1; i < triangleSize; i++) {
        int curr = i % 2;
        int prev = 1 - curr;
        f[curr][0] = f[prev][0] + triangle[i][0];
        for(int j = 1; j < i; j++) f[curr][j] = fmin(f[prev][j], f[prev][j-1]) + triangle[i][j];
        f[curr][i] = f[prev][i-1] + triangle[i][i];
    } 

    int ret = f[(triangleSize-1) % 2][0];
    for (int i = 1; i < triangleSize; i++) ret = fmin(ret, f[(triangleSize-1) % 2][i]);
    return ret;
}


//解法5：动态规划+空间优化2
//时间复杂度:O(n^2)；空间复杂度:O(n)；
int minimumTotal_dp3(int **triangle, int triangleSize) {
    int *f;
    f = (int *)malloc(sizeof(int) * triangleSize);
    for (int k = 0; k < triangleSize; k++) f[k] = 0;
    f[0] = triangle[0][0];
    for (int i = 1; i < triangleSize; i++) {
        f[i] = f[i-1] + triangle[i][i];
        for (int j = i-1; j > 0; j--) f[j] = fmin(f[j-1], f[j]) + triangle[i][j];
        f[0] += triangle[i][0];
    } 
    int ret = f[0];
    for (int k = 1; k < triangleSize; k++) ret = fmin(ret, f[k]);
    return ret;
}


void main() {
    int **triangle, triangleSize = 4;
    triangle = (int **)malloc(sizeof(int *) * triangleSize);
    for (int i = 0; i < triangleSize; i++) triangle[i] = (int *)malloc(sizeof(int) * (i + 1));
    triangle[0][0] = 2;
    triangle[1][0] = 3;
    triangle[1][1] = 4;
    triangle[2][0] = 6;
    triangle[2][1] = 5;
    triangle[2][2] = 7;
    triangle[3][0] = 4;
    triangle[3][1] = 1;
    triangle[3][2] = 8;
    triangle[3][3] = 3;

    printf("%d", minimumTotal_recursion2(triangle, triangleSize));
}


//2维数组按行存储，因此2维数组作为函数参数必须指明列数，
//即需要让编译器知道1、存储的起始位置；2、每个存储单元的大小（列数）；而不必指明存储单元的数量；