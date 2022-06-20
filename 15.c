#include <stdio.h>
#include <stdlib.h>
//为避免内存泄漏，二级指针和一级指针都需要被释放；采用循环的方式，先释放一级指针再释放二级指针
//*不能作用于野指针和空指针(NULL)，但是它们可以被修改指向；
//解法1：暴力
//时间复杂度：O(n^3)；空间复杂度：O(1)；
//不宜用C语言来做二维数组内一维数组的重复性检测，所以此方法未按照要求完成题目；但这段暴力代码以及内存释放部分仍具有参考价值；
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int *columnSize = (int *)malloc(sizeof(int) * (numsSize * numsSize * numsSize));
    int **res = (int **)malloc(sizeof(int *) * (numsSize * numsSize * numsSize));

    for(int i = 0; i < numsSize - 2; i++) {
        for(int j = i + 1; j < numsSize - 1; j++) {
            for(int k = j + 1; k < numsSize; k++) {
                if(nums[i] + nums[j] + nums[k] == 0) {
                    res[(*returnSize)] = (int *)malloc(sizeof(int) * 3);
                    res[(*returnSize)][0] = nums[i];
                    res[(*returnSize)][1] = nums[j];
                    res[(*returnSize)][2] = nums[k];
                    columnSize[*returnSize] = 3;
                    (*returnSize) += 1;
                }
            }
        }
    }
    *returnColumnSizes = columnSize;
    return res;
}


//解法2：排序+双指针：根据一定的判断条件移动首指针或尾指针；
//时间复杂度：排序O(nlogn)，搜索解O(n^2)；空间复杂度：O(1)；

void main() {
    int initreturnSize = 0;
    int *returnSize = &initreturnSize;
    int nums[6] = {-1, 0, 1, 2, -1, -4}, numsSize = 6;
    int **res = NULL, **returnColumnSizes = (int **)malloc(sizeof(int *));
    res = threeSum(nums, numsSize, returnSize, returnColumnSizes);
    for (int i = 0; i < *returnSize; i++) {
        for (int j = 0; j < (*returnColumnSizes)[i]; j++) printf("%d", res[i][j]);
        printf("\n");
    }
    free((*returnColumnSizes));
    free(returnColumnSizes);
    for (int k = 0; k < *returnSize; k++) free(res[k]);
    free(res);
}