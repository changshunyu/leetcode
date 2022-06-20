#include <stdio.h>
#include <stdlib.h>

//贪心并不难，难在证明问题可以用贪心法解决；
//排序+贪心

int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
    qsort(g, gSize, sizeof(int), cmp);
    qsort(s, sSize, sizeof(int), cmp);
    int numOfChildren = gSize, numOfCookies = sSize;
    int count = 0;
    for (int i = 0, j = 0; i < numOfChildren && j < numOfCookies; i++, j++) {
        while(j < numOfCookies && g[i] > s[j]) { //小孩子的胃口大于饼干的大小；
            j++;
        }
        if (j < numOfCookies) { //找到满足小孩子胃口的饼干；
            count++; //count是得到满足的小孩子的数量；
        }
    }
    return count;
}

void main() {
    int g[2] = {1, 2}, s[3] = {1, 2, 3};
    printf("%d", findContentChildren(g, 2, s, 3));
}