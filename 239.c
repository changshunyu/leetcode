#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    if (nums == NULL || returnSize == NULL) {
        return NULL;
    }
    int outLen = numsSize - k + 1;
    int *result = (int *)malloc(sizeof(int) * outLen);
    int *deque = (int *)malloc(sizeof(int) * numsSize);//存放nums中元素的索引；
    int start = 0;//start和end是deque中的头指针和尾指针；
    int end = 0;
    int i = 0, j = 0;//i是nums中元素的索引；
    while (i < numsSize) {//遍历nums中的所有元素；
        //若右边成员的值小于即将入队的值，就从右边依次出队
        while (start != end && nums[i] > nums[deque[end - 1]]) {//num[i]即将入队的元素，nums[deque[end - 1]]队尾元素；           
            end--;//通过end指针的移动，来表示元素的出队；始终保持deque[start]是最大元素的索引；
        }
        //从右边入队
        deque[end++] = i;//while中的start != end 保证了用即将入队的新的最大值覆盖旧的最大值；
        //已入队了K次，需要开始记录当前窗口最大值
        if (i >= k - 1) {//i>=2时满足条件
            result[i - k + 1] = nums[deque[start]];//将队首的元素储存到result中；
            if (start != end && deque[start] <= i - k + 1) {//i-k+1是窗口内首元素的下标；deque[start]是最大元素对应的下标
                //最大值已出窗口，左边出队
                start++;
            }
        }
        i++;
    }
    free(deque);
    *returnSize = outLen;
    return result;
}

void main(){
    int initresult = 0, nums[8] = {1, 3, -1, -3, 5, 3, 6, 7}, numsSize = 8, k = 3, initreturnSize = 0;
    int *result = &initresult, *returnSize = &initreturnSize;
    result = maxSlidingWindow(nums, numsSize, k, returnSize);
    printf("result[0] = %d, result[1] = %d, result[2] = %d, result[3] = %d, result[4] = %d, result[5] = %d", result[0], result[1], result[2], result[3], result[4], result[5]);
}