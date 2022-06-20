#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode * CreateList() {
    int n;
    scanf("%d", &n); //链表的结点个数;
    struct ListNode *p, *q, *head = NULL;
    for (int i = 0; i < n; i++) {
        p = (struct ListNode *)malloc(sizeof(struct ListNode));
        scanf("%d", &(p->val));
        if (head == NULL) head = p; //判断输入的是否为第一个结点；
        else q->next = p; //若不是第一个结点，则将p挂在上一个结点后面；
        q = p;
    }
    p->next = NULL; //尾结点没有指向；
    for (p = head; p != NULL; p = p->next) printf("%d", p->val);
    return head;
}

//解法1：递归；
//时间复杂度：O(n)；空间复杂度：O(n)；
struct ListNode * reverseList_recursion(struct ListNode* head){
    struct ListNode *p = head;
    if (p == NULL || p -> next == NULL) //递归终止条件；为什么p == NULL也作为递归终止条件？
        return p;
    struct ListNode *ret = reverseList_recursion(p->next);
    p->next->next = p; //对链表从后往前，依次翻转相邻的两个结点；
    head->next = NULL; //这里对形成的环执行截断；
    return ret;
}


//解法2：迭代；
//时间复杂度：O(n)；空间复杂度：O(1)；
struct ListNode * reverseList(struct ListNode* head) {
    struct ListNode *ret = NULL, *curr = head;
    while(curr) {
        struct ListNode *next = curr->next; //先存储下一个结点；
        curr->next = ret;
        ret = curr;
        curr =next; //更新下一个结点；
    }
    return ret;
}

void main() {
    struct ListNode *head, *ret, *p;
    head = CreateList();
    ret = reverseList(head);
    printf("\n");
    for (p = ret; p != NULL; p = p->next) printf("%d", p->val);
}