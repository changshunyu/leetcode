#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
//思路：每一次执行push操作时，进行两次入栈，第一次入栈此元素，第二次入栈此时栈中最小的元素；执行pop操作与之相对；
//所以真正的有效存储元素是800个；

#define MAXSIZE 1600//累计压入栈中的最大元素数

typedef struct {
    int *data;//栈的元素由一级指针索引；
    int top;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
    MinStack *obj=(MinStack *)malloc(sizeof(MinStack));
    obj->data=(int *)malloc(MAXSIZE*sizeof(int));//申请一块连续的地址用来存储栈内元素，obj->data为地址的首地址；
    obj->top=-1;//栈顶元素初始化为-1；
    return obj;
}

void minStackPush(MinStack* obj, int x) {
  if(obj->top==MAXSIZE-1){//如果栈已满，则无法执行压入操作；
      
  }else if(obj->top==-1){
      obj->top++;
      obj->data[obj->top]=x;
      obj->top++;
      obj->data[obj->top]=x;//此时最小的元素就是第一个元素本身；
  }else{
      int tmp=obj->data[obj->top];//temp存储此时栈内最小的元素；
      obj->top++;
      obj->data[obj->top]=x;
      if(tmp<x){
        obj->top++;
        obj->data[obj->top]=tmp;
      }else{
        obj->top++;
        obj->data[obj->top]=x;
      }
  }
}

void minStackPop(MinStack* obj) {//弹出
  if(obj->top==-1){//如果是空栈，无法完成弹出操作；
      
  }else{
      obj->top--;//弹出此时栈内最小的元素；
      obj->top--;//弹出此时的栈顶元素；目前的两个栈顶元素分别为前一时刻的最小元素，和前一时刻压入的元素；
  }
}

int minStackTop(MinStack* obj) {//获取
  if(obj->top==-1){//栈为空
      return;
  }
  return obj->data[obj->top-1];//栈顶指针top指向此时栈内的最小元素，top-1才是指向真正的栈顶元素；
  
}

int minStackGetMin(MinStack* obj) {
  return obj->data[obj->top];//无需判断栈是否为空，空栈的最小元素直接是-1
}

void minStackFree(MinStack* obj) {//释放栈
    free(obj->data);
    obj->data=NULL;
    free(obj);
    obj=NULL;
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/