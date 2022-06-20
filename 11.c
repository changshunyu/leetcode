#include <stdio.h>
#include <math.h>
//解法1：暴力(这种j=i+1的双重循环枚举要写熟练)；
//时间复杂度：O(n^2)；空间复杂度：O(1)；
int maxArea(int* heights, int n) {
    int maxarea = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) maxarea = fmax(maxarea, fmin(heights[i], heights[j]) * (j - i));
    }
    return maxarea;
}

//解法2：双指针；
//时间复杂度：O(n)；空间复杂度：O(1)；
int maxArea(int* heights, int n) {
    int water = 0, *i = heights, *j = i + n-1;
    while(i < j) {
        int h = *i < *j? *i: *j; //选其中一个较小的高度；
        int w =(j - i)*h; //底 * 高；
        if (w > water) water = w;
        while(*i <= h && i < j) i++; //底变小了，如果高再没有增加，那面积肯定减小；
        while(*j <= h && i < j) j--;
    }
    return water;
}

void main() {
    int height[9] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    printf("%d", maxArea(height, 9));
}