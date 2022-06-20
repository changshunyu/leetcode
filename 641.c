#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>

//队列——>循环队列——>双端循环队列：
//循环表现在可以充分利用队列空间，队列是一个环；双端表现在插入、删除和获取操作既可以在队首执行，也可以在队尾执行；
//总结：无论是队首指针还是队尾指针，考虑到循环队列的循环特性，后移（队首删除&队尾添加，+1并除以队列长度）表达式相同且比较简单，
//前移（队首添加&队尾删除，-1加队列长度再除以队列长度）表达式相同不要忘记进行+obj->size操作；
//删除元素只需移动指针；添加元素要赋值并移动指针；获取元素并不删除，即指针位置不移动；
//注意：队首指针指向队列头部第1个有效数据的位置；队尾指针指向队列最后一个元素的下一个位置；这影响这添加、删除和获取操作；
typedef struct {
	int *arr;
	int head;
	int tail;
	int size;
} MyCircularDeque; //1个结构体就代表1个双端队列，队列空间用结构体中的数组成员来表示；

bool myCircularDequeIsFull(MyCircularDeque* obj) ;
bool myCircularDequeIsEmpty(MyCircularDeque* obj) ;
/** Initialize your data structure here. Set the size of the deque to be k. */

MyCircularDeque* myCircularDequeCreate(int k) {

	MyCircularDeque *obj = malloc(sizeof(MyCircularDeque));
	obj->arr = malloc(sizeof(int) * (k+1)); //循环队列有意浪费一个位置；
	obj->head = 0; //用整形表示队首和队尾指针，索引从0开始；
	obj->tail = 0; 
	obj->size = k + 1;
	return obj;
}

/** Adds an item at the front of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {

	if (myCircularDequeIsFull(obj)) return false;

	int pos = (obj->head - 1 + obj->size) % obj->size;
	//因为循环队列存在队首指针指向索引为0的情况，此时队首指针-1为负数索引；
	obj->arr[pos] = value;
	obj->head = pos;
	return true;
}

/** Adds an item at the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {

	if ( myCircularDequeIsFull(obj)) return false;

	obj->arr[obj->tail] = value;
	obj->tail = (obj->tail + 1) % obj->size;

	return true;
}

/** Deletes an item from the front of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
	if ( myCircularDequeIsEmpty(obj)) return false;

	obj->head = (obj->head + 1) % obj->size;
	//因为循环队列存在队首指针后移越界的情况；
	return true;

}

/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
	if ( myCircularDequeIsEmpty(obj)) return false;

	obj->tail = (obj->tail - 1 + obj->size) % obj->size; 
	//因为循环队列存在队尾指针指向索引为0的情况，此时队尾指针-1为负数索引；
	return true;
}

/** Get the front item from the deque. */
int myCircularDequeGetFront(MyCircularDeque* obj) {
	if ( myCircularDequeIsEmpty(obj) ) return -1;

	return obj->arr[obj->head];
}

/** Get the last item from the deque. */
int myCircularDequeGetRear(MyCircularDeque* obj) {
	if ( myCircularDequeIsEmpty(obj) ) return -1;

	int pos = (obj->tail - 1 + obj->size) % obj->size;
	//考虑队尾指针指向位置0的情况；

	return obj->arr[pos];


}

/** Checks whether the circular deque is empty or not. */
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {

	return (obj->head == obj->tail) ? true : false;//头尾指针重合

}

/** Checks whether the circular deque is full or not. */
bool myCircularDequeIsFull(MyCircularDeque* obj) {

	return (obj->head == (obj->tail + 1) % obj->size) ? true : false;
	//队尾指针+1与队首指针重合，考虑队尾指针+1后越界的情况；
}

void myCircularDequeFree(MyCircularDeque* obj) {

	free(obj->arr); //先释放队列空间即结构体内的数组成员；
	free(obj); //再释放队列结构体指针；
	return ;

}

//测试代码；
void main() {
	MyCircularDeque *obj;
	obj = myCircularDequeCreate(3);
	printf("%d\n", myCircularDequeInsertLast(obj, 1));
	printf("%d\n", myCircularDequeInsertLast(obj, 2));
	printf("%d\n", myCircularDequeInsertFront(obj, 3));
	printf("%d\n", myCircularDequeInsertFront(obj, 4));
	printf("%d\n", myCircularDequeGetRear(obj));
	printf("%d\n", myCircularDequeIsFull(obj));
	printf("%d\n", myCircularDequeDeleteLast(obj));
	printf("%d\n", myCircularDequeInsertFront(obj, 4));
	printf("%d\n", myCircularDequeGetFront(obj));
}
