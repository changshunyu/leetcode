#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//手动维护栈：左括号就入栈，右括号就和栈顶括号进行匹配；
//时间复杂度：O(n)；空间复杂度：O(n)；
char pairs(char a) { //为了快速判断括号的类型，使用hashmap存储每一种括号；
    if (a == '}') return '{';
    if (a == ']') return '[';
    if (a == ')') return '(';
    return 0;
}

bool isValid_stack(char* s) {
    int n = strlen(s);
    if (n % 2 == 1) { //字符串长度必须是偶数
        return false;
    }
    int *stk = (int *)malloc(sizeof(int) * (n+1));
    int top = 0; //维护了一个栈顶指针top，top指向下一个字符将要存储的位置，top-1指向栈顶元素，stk是维护的栈；
    for (int i = 0; i < n; i++) { //遍历输入的字符串，时间复杂度O(n)
        char ch = pairs(s[i]); //获得输入括号的配对括号，或者说判断括号是左括号还是右括号；
        if (ch) { //输入右括号
            if (top == 0 || stk[top - 1] != ch) {
                return false; //返回false的条件：栈为空即右括号字符串的首字符，或者输入括号与栈顶括号不匹配；
            }
            top--; //匹配成功，通过栈顶指针下移弹出栈顶元素；
        } else { //输入左括号，进行入栈操作；
            stk[top++] = s[i];
        }
    }
    free(stk);
    return top == 0; //所有括号匹配成功，弹出，返回true，如果输入为空字符串也将返回true；
}

void main() {
    char *s = "{[()]}";
    bool ans = isValid(s);
    printf("ans = %d\n", ans);
}