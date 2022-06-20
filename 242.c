#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define STR_SIZE 100

typedef struct Node{
    char str[STR_SIZE]; // key为字符串
    int row;            // value为结果所在的行
    struct Node * next;
} HashNode;


int hash(char * str, int size)//hash函数，
{
    long h = 0;
    for(int i = 0; i < strlen(str); i++){
        h = (h * 26 % size + str[i] - 'a') % size; // 字符串的hashcode, 权为26是因为小写字母，不限制时为128，这样能够让结点尽可能分布均匀，减少地址冲突
        // 取模是为了防止int型溢出
    }
    return h % size;
}

bool contain(HashNode * hashtable, char * str, int size)
{
    HashNode *head = &hashtable[hash(str, size)];//在hash表的头部插入新元素；
    HashNode *tail = head->next;//hash表的尾部后移；
    while(tail){//是否到达hash表的尾部？在整个hash表中进行字符串搜索；
        if(strcmp(tail->str, str) == 0) return true;
        tail = tail->next;
    }
    return false;
}

void add(HashNode * hashtable, char * str, int size, int row)
{
    if(contain(hashtable, str, size)) return;
    HashNode *head = &hashtable[hash(str, size)];
    // 头插建表
    HashNode *q = malloc(sizeof(HashNode));
    strcpy(q->str, str);
    q->row = row;
    q->next = head->next;
    head->next = q;
}


int getRows(HashNode * hashtable, char * str, int size)
{
    HashNode *head = &hashtable[hash(str, size)];
    HashNode *tail = head->next;
    while(tail){
        if(strcmp(tail->str, str) == 0) return tail->row;
        tail = tail->next;
    }
    return -1;
}

int cmp(const void *a, const void * b)
{
    return *(char *)a - *(char *)b;
}

char *** groupAnagrams(char ** strs, int strsSize, int* retSize, int** columnSizes){
    if(strsSize == 0 || strs == NULL){
        *retSize = 0;
        return NULL;
    }
    HashNode * hashtable = malloc(sizeof(HashNode) * strsSize);//hashtable是由hashnode构成的；
    memset(hashtable, 0, sizeof(HashNode) * strsSize);//在申请的内存上填充上0；
    char *** ans = malloc(sizeof(char **) * strsSize);

    *retSize = 0;
    *columnSizes = malloc(sizeof(int) * strsSize);

    for(int i = 0; i < strsSize; i++){
        char curStr[STR_SIZE] = "";
        strcpy(curStr, strs[i]);
        int lenStr = strlen(curStr);
        qsort(curStr, lenStr, sizeof(char), cmp); // 排序

        if(contain(hashtable, curStr, strsSize)){ // key已经存在了
            int row = getRows(hashtable, curStr, strsSize); // 获得之前key的结果所在行
            int col = (*columnSizes)[row];
            ans[row][col] = malloc(sizeof(char) * (lenStr + 1));
            strcpy(ans[row][col], strs[i]);
            (*columnSizes)[row]++;
        } else{ // key 不存在
            add(hashtable, curStr, strsSize, *retSize); // 插入表中
            ans[*retSize] = malloc(sizeof(char *) * strsSize); // 申请一行
            ans[*retSize][0] = malloc(sizeof(char) * (lenStr + 1));
            strcpy(ans[*retSize][0], strs[i]);
            (*columnSizes)[*retSize] = 1;
            (*retSize)++;
        }
    }
    return ans;
}

void main(){
    char** strs[6][4] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int strsSize = 6;
    int initretSize = 0, initcolumnSizes = 0, initans = 0;
    int* retSize = &initretSize;
    int** columnSizes = (int **)malloc(sizeof(int*) * 3);;
    char*** ans = (char ***)malloc(sizeof(char **) * strsSize);
    ans = groupAnagrams(strs, strsSize, retSize, columnSizes);
    printf("ans[0][0] = %s, ans[0][1]] = %s, ans[0][2]] = %s, ans[1][0] = %s, ans[1][1]] = %s, ans[2][0]] = %s", ans[0][0], ans[0][1], ans[0][2], ans[1][0], ans[1][1], ans[2][0]);
}