#include <stdio.h>
#include <stdlib.h>

//归并排序：当初从哪里分，后面就从里合；
int mergeSort(int *nums, int l, int r) {
    if (l >= r) return 0;
    int mid = l + (r - l) / 2;
    int count = mergeSort(nums, l, mid) + mergeSort(nums, mid + 1, r);
    int *cache;
    cache = (int *)malloc(sizeof(int) * (r - l + 1));
    int i = l, t = l, c = 0; //i用于统计逆序对，t用于归并排序；
    for (int j = mid + 1; j <= r; j++, c++) { //外循环是第二个数组的循环；
        while (i <= mid && nums[i] <= 2 * nums[j]) { //统计非逆序对；
            i++; //i最大可累加到mid+1，即左边数组所有元素与右边数组的该元素均不构成逆序对；
        } 
        //这里的i++还有一个比较tricky的含义：就是左右数组都是已排好序的，所以如果左边数组部分元素和右边数组中较小的元素都不能都成逆序对，
        //那么对于右边数组中较大的元素，左边数组中的这些元素更不能构成逆序对，因此i++这条语句也避免了在第2,3,4...次外循环中不必要的计算；
        while (t <= mid && nums[t] < nums[j]) { //归并过程：将左边数组中所有小于右边数组中该元素的元素放入cache中；
            cache[c++] = nums[t++];
        }
        cache[c] = nums[j]; //将左边数组中所有小于右边数组中该元素的元素放入cache后，再将该元素放入cache中；

        count += mid - i + 1; 
        //对于右边数组中的某一个元素，统计该元素和左边数组所有元素能构成的逆序对数，
        //针对右边数组中的第2,3,4...个元素，并不是考虑左边数组中的所有元素，因为前面i++的缘故，
        //已经将一些明显不构成逆序对的左边数组元素忽略；
        //在每次内循环中最多产生mid+1-left对逆序对，最少产生0对(即在上面的while中，i从left累加到mid+1)；
    }
    while (t <= mid) { //可能存在左边数组部分元素大于右边数组所有元素的情况，因此左边数组未完全放入cache，在这里将它们统一放入(它们本身就是有序的)；
        cache[c++] = nums[t++];
        }
    for (int k = 0; k < r - l + 1; k++) {
        nums[l + k] = cache[k]; //将cache中排好序的部分元素(l并非一直为0)放入原数组；
    }
    return count;
}

int reversePairs(int *nums, int numsSize) {
    if (numsSize == 0) return 0;
    return mergeSort(nums, 0, numsSize-1);
}

void main() {
    int nums[5] = {2, 4, 3, 5, 1}, numsSize = 5;
    printf("%d", reversePairs(nums, numsSize));
}


//归并排序
// //将两个已排序的数组(left到mid，mid+1到right)合并在一起；
// void merge(int *arr, int left, int mid, int right) {
//     int *temp; //需要申请一块额外的内存空间；
//     temp = (int *)malloc(sizeof(int) * (right - left + 1));
//     int i = left, j = mid + 1, k = 0; //i和j分别代表两个已排序数组的起始位置；k表示已经填入temp的元素个数；

//     while (i <= mid && j <= right) { //两个数组都还没有循环完；
//         temp[k++] = arr[i] <= arr[j] ? arr[i++] : arr[j++]; //把两者中的较小者赋值给temp[k]，同时较小者的索引往后挪；
//     }
//     while(i <= mid) temp[k++] = arr[i++]; //如果i数组没有走完；子数组已有序，所以可以直接填充；
//     while(j <= right) temp[k++] = arr[j++]; //如果j数组没有走完；

// //注意这里的left保证了将排序结果temp放回原arr中；
//     for (int p = 0; p < (right - left + 1); p++) {
//         arr[left + p] = temp[p];
//     }
// }

// void mergeSort(int *array, int left, int right) {
//     if (right <= left) return;
//     int mid = (left + right) >> 1;

//     mergeSort(array, left, mid);
//     mergeSort(array, mid + 1, right);
//     merge(array, left, mid, right);
// }


// //快速排序，不需要额外申请内存空间；
// int partition(int *arr, int begin, int end) { //begin和end并非一直为0和arrSize-1；
//     int pivot = end, counter = begin;
//     for (int i = begin; i < end; i++) { //枚举数组中除了最后一个元素(即pivot指向的元素)外所有的元素；
//         if (arr[i] < arr[pivot]) {
//             int temp = arr[counter]; arr[counter] = arr[i]; arr[i] = temp;
//             counter++; //i和counter的初始值相同均为begin，但counter仅在判断成立的条件下+1；
//             //counter指向第一个大于pivot指向元素的元素；
//         } 
//     } 
//     int temp = arr[pivot]; arr[pivot] = arr[counter]; arr[counter] = temp;
//     return counter;
// }

// void quickSort(int *arr, int begin, int end) {
//     if (end <= begin) return;
//     int pivot = partition(arr, begin, end);
//     quickSort(arr, begin, pivot - 1);
//     quickSort(arr, pivot + 1, end);
// }