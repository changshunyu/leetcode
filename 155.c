#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAXSIZE 800

typedef struct {
    int *data;
    int top;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
    MinStack *obj=(MinStack *)malloc(sizeof(MinStack));
    obj->data=(int *)malloc(MAXSIZE*sizeof(int));
    obj->top=-1;
    return obj;
}

void minStackPush(MinStack* obj, int x) {
  if(obj->top==MAXSIZE-1){//栈满；
      
  }else{
      obj->top++;//栈顶指针指向栈顶元素，所以在入栈前需要先进行栈顶指针++
      obj->data[obj->top]=x;
  }
}

void minStackPop(MinStack* obj) {
  if(obj->top==-1){//空栈无法进行弹出操作；
      
  }else{
      obj->top--;
  }
}

int minStackTop(MinStack* obj) {
  if(obj->top==-1){
      return;
  }
  return obj->data[obj->top];
  
}

int minStackGetMin(MinStack* obj) {
  if(obj->top==-1) return;
  if(obj->top==0){//如果栈内只有一个元素；
      return obj->data[obj->top];
  }
  int min=obj->data[0];
  for(int i=0;i<=obj->top;i++){//obj->top的最大值是MAXSIZE-1
      if(obj->data[i]<min){//每次操作都要遍历栈内所有元素，最坏情况下的时间复杂度为O(n)；
          min=obj->data[i];
      }
  }
  return min;
}

void minStackFree(MinStack* obj) {
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