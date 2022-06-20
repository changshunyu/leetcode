#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

//创建1个环形链表；
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
    // p->next = NULL; //尾结点没有指向；
    p->next = head->next; //尾结点指向第二个结点；
    // for (p = head; p != NULL; p = p->next) printf("%d", p->val);
    return head;
}

//快慢指针：慢指针一次移动1步，快指针一次移动两步，观察快指针是否重叠上慢指针；
//时间复杂度：O(N)；空间复杂度：O(1)；
bool hasCycle(struct ListNode* head) {
    if (head == NULL || head->next == NULL) { //空链表或链表只有1个结点，则不可能存在环；
        return false;
    }
    struct ListNode* slow = head; //慢指针初始为头结点；
    struct ListNode* fast = head->next; //快指针初始为头结点的下一个节点；
    while (slow != fast) { //二者重合，说明有环，停止循环；
        if (fast == NULL || fast->next == NULL) { //若不存在环，则一定是快指针先抵达链表尾结点；
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}

void main() {
    struct ListNode *head;
    head = CreateList(); 
    printf("%d", hasCycle(head));
    //考虑如何释放链表申请的内存空间？
}