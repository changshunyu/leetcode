#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    };

struct TreeNode* CreateBiTree() {
    int num;
    struct TreeNode* node;
	scanf ("%d", &num);
	if (num == 0) node = NULL;
	else
	{
        node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		node->val = num;	
		node->left = CreateBiTree();
		node->right = CreateBiTree();
	}
    return node;
    }

//有如下两种方式在函数内返回一个数组：
//1、C语言函数通过返回指针来返回数组；
//2、通过传入数组的地址(二级指针)，在函数内部对数组进行操作。值得注意，形参是实参的拷贝，因此函数参数不能简单的为数组，而需要是数组的地址(详细测试见文末)；
//总结：想要在一个函数内修改一个数，则传入指针；想要在一个函数内修改一个数组，则传入二级指针；

//returnSize:用来返回二维数组的行数；
//returnColumnSizes:用来返回每层结点的个数(用一维数组存储)，该数组在函数内部被修改，因此函数参数为数组的地址(即上述方式2)；

//解法1：BFS：自己编写结点类，显示使用队列数据结构；
// int** levelOrder_bfs(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
//     int **res = NULL;
//     int *columnSize = NULL;
//     struct TreeNode *queue[20] = {0};
//     struct TreeNode *pNode = NULL;
//     int front = 0, rear = 0, pre_rear;
//     int i = 0, j = 0;
    
//     if(!root) {
//         *returnSize = 0;
//         return NULL;
//     }

//     queue[rear++] = root;
//     while(front < rear) {
//         pre_rear = rear;
//         res = realloc(res, (i + 1) * sizeof(int *));
//         res[i] = calloc(pre_rear - front, sizeof(int));
//         while(front < pre_rear) {
//             pNode = queue[front++];
//             res[i][j++] = pNode->val;
//             if (pNode->left) queue[rear++] = pNode->left;
//             if (pNode->right) queue[rear++] = pNode->right;
//         }
//         columnSize = realloc(columnSize, (i + 1) * sizeof(int));
//         columnSize[i++] = j;
//         j = 0;
//     }

//     *returnSize = i;
//     *returnColumnSizes = columnSize;
//     return res;
// }


//解法2：DFS
#define max(a, b) ((a) > (b) ? (a) : (b))
void dfs(struct TreeNode* root, int level, int* returnSize, int** returnColSize, int ***res) {
    if (!root) {
        *returnSize = max(*returnSize, level);
        return; //递归终止；
    }
    dfs(root->left, level + 1, returnSize, returnColSize, res);
    dfs(root->right, level + 1, returnSize, returnColSize, res);
    if (!returnColSize[0][level]) {
        (*res)[level] = (int *)calloc(10, sizeof(int));
    }
    (*res)[level][returnColSize[0][level]++] = root->val;
    return;
}

int** levelOrder_dfs(struct TreeNode* root, int* returnSize, int** returnColSize) {
    if (!root) return NULL;
    returnColSize[0] = (int *)calloc(10, sizeof(int));
    int **res = (int **)malloc(sizeof(int *) * 10);

    dfs(root, 0, returnSize, returnColSize, &res);
    return res;
}

void main() {
    int initreturnSize = 0, init2returnColSize = 0;
    int *returnSize = &initreturnSize, *initreturnColSize = &init2returnColSize;
    int **res = NULL, **returnColSize = &initreturnColSize;
    struct TreeNode *root = NULL;
    root = CreateBiTree();
    printf("%d, %d, %d, %d, %d\n", root->val, root->left->val, root->right->val, root->right->left->val, root->right->right->val);
    res = levelOrder_dfs(root, returnSize, returnColSize);
    printf("%d, %d, %d, %d, %d\n", res[0][0], res[1][0], res[1][1], res[2][0], res[2][1]);
    // printf("%d, %d, %d, %d\n", *returnSize, returnColSize[0][0], returnColSize[0][1],returnColSize[0][2]);
}

// //观察传入什么类型的参数，能在test函数中成功修改外面的字符串和数组；
// void test(char *str, int *arr) {
//     int arr2[2] = {2,1};
//     char *str2 = ")(" ;
//     printf("%x\n", arr2);
//     arr = arr2;
//     str = str2;
// }

// void main() {
//     char *str = (char *)malloc(sizeof(char) * 3);
//     int *arr = (int *)malloc(sizeof(int) * 2);
//     str[0] = '(';
//     str[1] = ')';
//     arr[0] = 1;
//     arr[1] = 2;
//     test(str, arr);
//     printf("str[0]=%c, str[1]=%c\narr[0]=%d, arr[1]=%d\n", str[0], str[1], arr[0], arr[1]);
// }