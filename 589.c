#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Node {
    int val;
    int numChildren;
    struct Node** children;
};

void func(struct Node* root, int* arr, int* returnSize) {
    arr[(*returnSize)++] = root->val;
    for (int i = 0; i < root->numChildren; i++) {
        func(root->children[i], arr, returnSize);
    }
}

int* preorder(struct Node* root, int* returnSize) {
    *returnSize = 0;
    if (!root) return NULL;//判断是否为空树，不是递归终点判断；
    int* arr = (int*)calloc(10,sizeof(int));
    func(root, arr, returnSize);
    return arr;
}

struct Node* CreateTree()//1->3->5->0->6->0->0->2->0->4->0->0，前序建立；
{
    int num;
    struct Node* node;
	scanf ("%d", &num);
	if (num == 0) node = NULL;
	else
	{
        node = (struct Node*)malloc(sizeof(struct Node));
        node->children = (struct Node**)malloc(sizeof(struct Node*));
		node->val = num;	
        for (int i = 0; ; i++) {
            node->children[i] = (struct Node*)malloc(sizeof(struct Node));
            node->children[i] = CreateTree();
            if (node->children[i] == NULL) {
                node->numChildren = i;
                break;
            };
        }
	}
    return node;
}

void main() {
    int* res = NULL;
    int initsize = 0;
    int* returnSize = &initsize;
    struct Node* root;//不需要malloc，因为子函数中使用malloc，所以在子函数结束时，内存空间不会释放；
    root = CreateTree();
    res = preorder(root, returnSize);
    printf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d", *res, *(res+1), *(res+2), *(res+3), *(res+4), *(res+5), *(res+6), *(res+7), *(res+8), *(res+9));
}