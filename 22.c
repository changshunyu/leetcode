#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//在函数内部修改一维数组和字符串时，函数接受的参数不同，分别是二级指针和指针；
//解法1：暴力搜索：递归出所有的情况，再判断其是否有效；
bool valid(char *str, int n) {
    int balance = 0;
    for (int i = 0; i < 2*n; i++) {
        if (str[i] == '(') balance += 1;
        else balance -= 1;
        if (balance < 0) return false;
    }
    return balance == 0;
}

void generateAll(char *str, int pos, int n, char **result, int *returnSize) {
    if (pos == 2 * n) {
        if (valid(str, n)) {
            result[*returnSize] = (char *)calloc((2 * n + 1), sizeof(char));
            strcpy(result[(*returnSize)++], str);
        }
    }
    else {
        str[pos] = '(';
        generateAll(str, pos+1, n, result, returnSize);
        str[pos] = ')';
        generateAll(str, pos+1, n, result, returnSize);
    }
}

char ** generateParenthesis(int n, int* returnSize) {
    char **result = (char **)malloc(sizeof(char *) * 10);
    char *str = (char *)calloc((2 * n + 1), sizeof(char));
    generateAll(str, 0, n, result, returnSize);
    return result;
}


//解法2：关键词：递归（DFS）、回溯（提前剪枝）；
//使用系统栈，在递归完成时，系统栈顶就把我们需要的状态信息直接弹出；
//要先把递归树画出来；
void generate(int left, int right, int n, char *str, int index, char **result, int *returnSize) {
    if (index == 2 * n) {
        result[*returnSize] = (char *)calloc((2 * n + 1), sizeof(char));
        strcpy(result[(*returnSize)++], str);
        return;
    }
    if (left < n) {
        str[index] = '(';
        generate(left+1, right, n, str, index+1, result, returnSize);
    }
    if (right < left) {
        str[index] = ')';
        generate(left, right+1, n, str, index+1, result, returnSize);
    }
}

char ** generateParenthesis_dfs(int n, int* returnSize) {
    char **result = (char **)malloc(sizeof(char *) * 10);
    char *str = (char *)calloc((2 * n + 1), sizeof(char));
    *returnSize = 0;

    generate(0, 0, n, str, 0, result, returnSize);
    return result;
}

void main() {
    int initreturnSize = 0;
    int *returnSize = &initreturnSize;
    char **res;
    res = generateParenthesis(3, returnSize);
    for (int i = 0; i < *returnSize; i++) printf("%s\n", res[i]);
}
