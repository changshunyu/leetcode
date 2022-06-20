#include <stdio.h>
#include <stdlib.h>

int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize, int *obstacleGridColSize) {
    
    int n = obstacleGridSize, m = obstacleGridColSize[0]; //m是行数，n是列数；

    int *f, k;
    f = (int *)malloc(sizeof(int) * m); //逐列处理,减少空间复杂度，f[m]表示某一列；
    for(k = 0; k < m; k++) f[k] = 0;

    f[0] = (obstacleGrid[0][0] == 0); //初始位置肯定没有石头，是累加的起点；
    for (int i = 0; i < n; i++) { //外循环是列循环；
        for (int j = 0; j < m; j++) { //内循环是行循环；
            if (obstacleGrid[i][j] == 1) {
                f[j] = 0;
                continue;
            }
            if (j - 1 >= 0 && obstacleGrid[i][j-1] == 0) { //1、上一个网格不在上边框上；2、上一格不为石头
                f[j] += f[j-1]; //这里f[j]代表到达到左一格的路径数，f[j-1]代表到达上一格的路径数；
                // printf("%d", f[j]);
            }
        }
    }
    return f[m-1];
}

void main() {
    int **obstacleGrid, *obstacleGridColSize, i, j;

    obstacleGrid = (int **)malloc(sizeof(int *) * 3);
    for(i = 0; i < 3; i++) {
        obstacleGrid[i] = (int *)malloc(sizeof(int) * 3);
        for(j = 0; j < 3; j++) {
            if(i==1 && j==1) obstacleGrid[i][j] = 1;
            else obstacleGrid[i][j] = 0;
        }
    }
    obstacleGridColSize = (int *)malloc(sizeof(int) * 3);
    for(i = 0; i < 3; i++) obstacleGridColSize[i] = 3;

//第2个参数表示有多少网格有多少列，第3个参数表示每一列有多少个元素即行数，这里有一个疑问：每一列的元素数不应该是相同的么？
    printf("%d", uniquePathsWithObstacles(obstacleGrid, 3, obstacleGridColSize)); 
}