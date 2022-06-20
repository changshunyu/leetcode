#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Node {
    int val;
    int numChildren;
    struct Node** children;
};

#define MAXSIZE 5000
#define MAXDEPTH 1000

typedef struct{//顺序队列
    struct Node** data;
    int front;//头
    int rear;//尾
}SeqQueue;

//定义循环队列并初始化，循环队列由链表实现，
SeqQueue* createSeqQueue(){
    SeqQueue* obj;
    obj = (SeqQueue *)malloc(sizeof(SeqQueue));
    obj->data = (struct Node **)malloc(sizeof(struct Node *) * MAXSIZE);//申请的连续空间为一层结点数的最大值，因为队列始终保持出一层，入一层，即仅储存一层的结点数；
    obj->front = 0;
    obj->rear = 0;
    return obj;//obj是一个队列
}

//队列长度
int QueueLength(SeqQueue* obj){
    return (obj->rear - obj->front + MAXSIZE)%MAXSIZE;//这个表达式一定要记住！！！
}

//队列是否为空
bool QueueEmpty(SeqQueue* obj){
    return obj->front == obj->rear;//头尾指针重合，队列即为空；
}

//队列是否为满
bool QueueFull(SeqQueue* obj){
    return (obj->rear+1)%MAXSIZE == obj->front;
}

//入队
void EnQueue(SeqQueue* obj, struct Node* node){
    if( (obj->rear+1)%MAXSIZE != obj->front ){//确定队列未满
        obj->data[obj->rear] = node;//将root结点放在0这个位置
        obj->rear = (obj->rear+1)%MAXSIZE;//尾指针后移，同为避免越界；
    }
}

//出队
struct Node* DeQueue(SeqQueue* obj){
    if(obj->front != obj->rear){//队列非空，则可以出队；
        int k = obj->front;//出队时考虑对弹出结点的需求，定义局部变量，用于储存弹出结点；
        obj->front = (obj->front+1)%MAXSIZE;//头指针后移，同为避免越界；
        return obj->data[k];
    }
    return NULL;
}

struct Node* CreateTree()//1->3->5->0->6->0->0->2->0->4->0->0，前序建立；
{
    int num, MAXN = 5;
    // struct Node* node;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));//因为在函数执行完后，N叉数仍需存在，所以需要malloc空间；
	scanf ("%d", &num);
	if (num == 0) node = NULL;
	else
	{
        // node = (struct Node*)malloc(sizeof(struct Node));//因为在函数执行完后，N叉数仍需存在，所以需要malloc空间；
		node->val = num;	
        node->children = (struct Node**)malloc(sizeof(struct Node*) * MAXN);//既然不是空结点，那就值得拥有孩子结点；预先无法判断N叉数中的N值，所以应该申请一块足够大的连续空间来存放孩子结点，但这不妨碍孩子结点为NULL；
        for (int i = 0; ; i++) {
            // node->children[i] = (struct Node*)malloc(sizeof(struct Node));
            node->children[i] = CreateTree();//孩子结点至少应该是一个NULL；
            if (node->children[i] == NULL) {
                node->numChildren = i;
                break;
            };
        }
	}
    return node;
}

int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes){
    int** nums = malloc(sizeof(int *) * MAXDEPTH); //定义二维数组存储节点值
    int sizes[MAXDEPTH] = {0};  //定义一维数组存储每一层节点个数

    int i, j, k;//i是层数索引；j为队列中元素的相对索引；k为每一层中的结点索引
    for(i=0; i<MAXDEPTH; i++)
        nums[i] = (int *)malloc(sizeof(int) * MAXSIZE);//为每个元素申请空间
    
    i = -1;//将i值置为-1？
    if(root){//判断N叉数是否为空；
        SeqQueue* Q = createSeqQueue();//队列的Q的二级指针逐个指向队列中的结点地址；队列有预先分配地址么？
        EnQueue(Q, root);//一棵看树占队列的一个位置？！

        while(!QueueEmpty(Q)){//弹出了上一层的结点，但是入队了本层的结点；若本层结点都没有孩子结点，则结束循环；
            i++;//i为层数索引，因为上面赋值为了-1，所以初始值为第0层；
            sizes[i] = QueueLength(Q);//记录每一层的结点数，每一次将上一层的结点出队完毕，将本层的结点全部入队，所以队列的长度即为本层结点数；
            //QueuePrint(Q);

            for(j=0; j<sizes[i]; j++){
                k = (Q->front+j)%MAXSIZE;//通过j索引，遍历存储本层的所有结点，%MAXSIZE是为了始终保持k小于队列长度，防止越界；
                nums[i][j] = Q->data[k]->val;//第i层，第j个结点，k随着头尾指针的移动也在不断移动；
            }
            
            k = Q->rear;//本层的最后一个结点；
            struct Node* temp;//局部变量，遍历本层的每一个结点；

            while(Q->front != k){//遍历本层的所有结点；
                temp = Q->data[Q->front];//因为队列已弹出，所以front指针已更新，可用front指针索引；
                DeQueue(Q); //弹出一个结点且不用接收，改变循环的判定条件；

                for(j=0; j<temp->numChildren; j++)//遍历本层所有结点的孩子结点，让他们入队；
                    EnQueue(Q, temp->children[j]);
            }
        }
    }

    *returnSize = i+1; //二叉树的深度，即层数
    int* columnSizes = malloc(sizeof(int) * (*returnSize));//再次申请了一个一级指针，但此时树的深度已经确定，此处申请一块连续的空间还是很有必要的，因为其被一个二级指针所指；
    for(i=0; i<*returnSize; i++)
        columnSizes[i] = sizes[i];
    *returnColumnSizes = columnSizes;
    
    return nums;
}

void main() {
    int initsize = 0;
    int* returnSize = &initsize;
    int** nums = NULL, **returnColumnSizes = malloc(sizeof(int *) );//一级指针是连续的，所以二级指针只要指向一级指针的头指针即可；
    struct Node* root;//不需要malloc，因为子函数中使用malloc，所以在子函数结束时，内存空间不会释放；
    root = CreateTree();
    nums = levelOrder(root, returnSize, returnColumnSizes);//returnSize是层数，returnColumnSizes是各层结点数；
    printf("%d, %d, %d, %d, %d, %d", nums[0][0], nums[1][0], nums[1][1], nums[1][2], nums[2][0], nums[2][1]);
}