#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//从后往前贪心；
//此题的贪心在于只记录能到达endReachable的一个位置(距endReachable最近的位置)；
bool canJump(int* nums, int numsSize) {
    if (nums == NULL) return false;

    int endReachable = numsSize - 1; //能够到达最后位置的下标；
    for (int i = numsSize - 1; i >= 0; i--) {
        if (nums[i] + i >= endReachable) endReachable = i;
    }
    return endReachable == 0;
}


// //两层循环
// bool canJump(int* nums, int numsSize) {

//     int *flag;
//     flag = (int *)malloc(sizeof(int) * numsSize);
//     flag[0] = 1;
//     for (int i = 1; i < numsSize; i++) flag[i] = 0;
//     for (int m = 0; m < numsSize; m++) {
//         if (flag[m] == 1) {
//             for (int n = 0; n <= nums[m]; n++) {
//                 if (m + n < numsSize) flag[m+n] = 1;
//             }
//         }
//     }
//     return flag[numsSize-1];
// }

void main() {
    int nums[2] = {2, 0};
    printf("%d", canJump(nums, 2));
}