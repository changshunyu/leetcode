#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

int trap(int* height, int heightSize){
    int sum = 0, current = 0, top = -1;//current为遍历height数组的索引;
    int *stack = (int *)malloc(sizeof(int) * heightSize);//是否需要加哨兵？
    while(current < heightSize){
        while(top > -1 && height[current] > height[stack[top]]){//如果栈不为空(即尚未有元素入栈的情况)且待入栈索引指向的高度大于栈顶索引指向的高度，则进行出栈操作，并计算水量，计算完水量再进行与栈顶索引指向高度的比较...如此循环下去；
            int h = height[stack[top]];//取出要出栈的元素，便于后面计算水深；
            top--;//出栈操作；
            if (top == -1) break;//如果取出的是栈内最后一个索引，则无需计算水量，直接进行入栈操作
            int distance = current - stack[top]-1;//此处和84题略有不同；
            int min = height[current] < height[stack[top]] ? height[current]:height[stack[top]];
            sum += distance * (min-h);
        }
        stack[++top] = current;//待入栈元素小于等于栈顶元素，进行入栈操作；top指针指向此时的栈顶元素,
        current++;
    }
    return sum;
}

void main(){
    int height[12] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, heightSize = 12, sum = 0;
    sum = trap(height, heightSize);
    printf("sum = %d", sum);
}