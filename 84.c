#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

int largestRectangleArea(int* heights, int heightsSize){
    int top = -1;//栈顶指针，top指向的就是此时的栈顶元素，是栈内元素的索引；
    int area, i;//i索引每一根棒子
    int maxarea = 0;
    int *stack = (int *)malloc(sizeof(int) * (heightsSize + 2));//维护的栈，stack[0]始终是前哨兵；
    int *buff = (int *)malloc(sizeof(int) * (heightsSize + 2));//buff就是加完哨兵后的heights

    // 在前面加哨兵
    buff[0] = 0;//保证buff[stack[top] = 0，从而保证第一个操作是入栈；
    for (int i = 1; i <= heightsSize; i++) {//heightsSize是数组的长度；
        buff[i] = heights[i - 1];//所有元素进行偏移；
    }
    // 在最后加哨兵；
    buff[heightsSize + 1] = 0;//前后哨兵就是在原heightsSize数组前后各加一个0元素；

    stack[++top] = 0;//先进行top+1操作，再进行数组的赋值；先向栈内压入一个前哨兵元素0，他的索引是0；
    for (i = 1; i < heightsSize + 2; i++) {//总共进行了heightsSize+1次循环；buff[i]包含后哨兵，因为要保证所有元素出栈；不包含前哨兵；
        while (top > 0 && buff[i] < buff[stack[top]]) {//出栈条件：1、栈非空（前哨兵不算）；2、入栈元素对应的高小于栈顶元素对应的高；初始值i=1，是因为前哨兵已放入要从buff[1]即第一个有效元素开始放入；这里的"<""保证了前哨兵不出栈，进而避免了下面索引越界；
            area = (i - stack[top - 1] - 1) * buff[stack[top]];//（入栈元素-栈顶元素的前一元素-1）*（栈顶元素对应的高）
            maxarea = maxarea > area ? maxarea : area;//更新最大面积
            top--;//出栈
        }
        stack[++top] = i;//入栈，入栈的元素是heights数组的索引；1——>heightsSize+1；
    }
    return maxarea;
}

void main(){
    int heights[] = {2, 1, 5, 6, 2, 3}, heightsSize = 6, maxarea = 0;
    maxarea = largestRectangleArea(heights, heightsSize);
    printf("maxarea = %d", maxarea);
}
