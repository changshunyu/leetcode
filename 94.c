#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    };

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

void inorder(struct TreeNode* root, int* res, int* resSize) {
    if (!root) {  //递归终止条件；
        return;
    }
    inorder(root->left, res, resSize); //左；
    res[(*resSize)++] = root->val; //根；前中后序遍历的区别仅在于此句的位置不同；
    inorder(root->right, res, resSize); //右；
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    inorder(root, res, returnSize);
    return res;
}

void main() {
    struct TreeNode *root;
    int initreturnSize = 0;
    int *res, *returnSize = &initreturnSize;
    root = CreateBiTree();
    res = inorderTraversal(root, returnSize);
    for (int i = 0; i < *returnSize; i++) printf("%d", res[i]);
    free(res);
    //思考一下二叉树申请的内存空间应该如何释放？
}
