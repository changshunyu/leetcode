#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

 struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

void preorder(struct TreeNode* root, int* res, int* resSize) {
    if (!root) {
        return;
    }
    res[(*resSize)++] = root->val;
    preorder(root->left, res, resSize);
    preorder(root->right, res, resSize);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 501);
    *returnSize = 0;
    preorder(root, res, returnSize);
    return res;
}

struct TreeNode* CreateBiTree()
{
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

void main() {
    int* res = malloc(sizeof(int) * 501);
    int initsize = 0;
    int* returnSize = &initsize;
    struct TreeNode* root;
    root = CreateBiTree();
    res = preorderTraversal(root, returnSize);
    printf("%d, %d, %d", *res, *(res+1), *(res+2));
}