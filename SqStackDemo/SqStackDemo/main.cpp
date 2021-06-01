//
//  main.cpp
//  SqStackDemo
//
//  Created by Loyio Hex on 6/1/21.
//

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10

typedef int SElemType;

typedef struct {
    SElemType* base;               // 栈底指针
    SElemType* top;                // 栈顶指针
    int stacksize;                 // 当前已分配的存储空间，以元素为单位
} SqStack;

void PrintElem(SElemType e) {
    printf("%d ", e);
}

Status InitStack(SqStack* S);

Status DestroyStack(SqStack* S);

Status ClearStack(SqStack* S);

Status StackEmpty(SqStack S);

int StackLength(SqStack S);

Status GetTop(SqStack S, SElemType* e);

Status Push(SqStack* S, SElemType e);

Status Pop(SqStack* S, SElemType* e);

Status StackTraverse(SqStack S, void(Visit)(SElemType));

// 判定表达式开闭括号是否配对出现，且类型是否匹配
Status Algo_BracketMatching(char* s);

// 判断括号a和括号b之间的类型是否匹配
Status Matching(char a, char b);



int main(int argc, const char * argv[]) {
    SqStack S;
    int i;
    SElemType e;
    
    printf("函数 InitStack \n");
    printf("初始化顺序栈 S ...\n\n");
    InitStack(&S);
    
    printf("函数 StackEmpty \n");
    StackEmpty(S) ? printf("S 为空！！\n\n") : printf("S 不为空！\n\n");
    
    printf("函数 Push \n");
    for(i = 1; i <= 6; i++) {
        Push(&S, 2 * i);
        printf("将 \"%2d\" 压入栈 S ...\n", 2 * i);
    }
    printf("\n");
    
    printf("函数 StackTraverse \n");
    printf("S 中的元素为：S = ");
    StackTraverse(S, PrintElem);
    printf("\n");
    
    printf("函数 StackLength \n");
    i = StackLength(S);
    printf("S 的长度为 %d \n", i);
    printf("\n");
    
    printf("函数 Pop \n");
    Pop(&S, &e);
    printf("栈顶元素 \"%d\" 出栈...\n", e);
    printf("S 中的元素为：S = ");
    StackTraverse(S, PrintElem);
    printf("\n");
    
    printf("函数 GetTop \n");
    GetTop(S, &e);
    printf("栈顶元素的值为 \"%d\" \n", e);
    printf("\n");
    
    printf("函数 ClearStack \n");
    printf("清空 S 前：");
    StackEmpty(S) ? printf(" S 为空！！\n") : printf(" S 不为空！\n");
    ClearStack(&S);
    printf("清空 S 后：");
    StackEmpty(S) ? printf(" S 为空！！\n") : printf(" S 不为空！\n");
    printf("\n");
    
    printf("函数 DestroyStack \n");
    printf("销毁 S 前：");
    S.base != NULL && S.top != NULL ? printf(" S 存在！\n") : printf(" S 不存在！！\n");
    DestroyStack(&S);
    printf("销毁 S 后：");
    S.base != NULL && S.top != NULL ? printf(" S 存在！\n") : printf(" S 不存在！！\n");
    printf("\n");
    
    char* s = "(1+2)*3/{2/[(4-5)*3]-5*(8-7)}";
        
    printf("判断表达式 %s 括号是否匹配...\n", s);
    
    if(Algo_BracketMatching(s)) {
        printf("表达式括号匹配！\n");
    } else {
        printf("表达式括号不匹配！！\n");
    }
    
    return 0;
}


Status InitStack(SqStack* S) {
    if(S == NULL) {
        return ERROR;
    }
    
    (*S).base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if((*S).base == NULL) {
        exit(OVERFLOW);
    }
    
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    
    return OK;
}

Status DestroyStack(SqStack* S) {
    if(S == NULL) {
        return ERROR;
    }
    
    free((*S).base);
    
    (*S).base = NULL;
    (*S).top = NULL;
    (*S).stacksize = 0;
    
    return OK;
}

Status ClearStack(SqStack* S) {
    if(S == NULL || (*S).base == NULL) {
        return ERROR;
    }
    
    (*S).top = (*S).base;
    
    return OK;
}


Status StackEmpty(SqStack S) {
    if(S.top == S.base) {
        return TRUE;
    } else {
        return FALSE;
    }
}


int StackLength(SqStack S) {
    if(S.base == NULL) {
        return 0;
    }
    
    return (int) (S.top - S.base);
}

Status GetTop(SqStack S, SElemType* e) {
    if(S.base == NULL || S.top == S.base) {
        return 0;
    }
    
    // 不会改变栈中元素
    *e = *(S.top - 1);
    
    return OK;
}


Status Push(SqStack* S, SElemType e) {
    if(S == NULL || (*S).base == NULL) {
        return ERROR;
    }
    
    // 栈满时，追加存储空间
    if((*S).top - (*S).base >= (*S).stacksize) {
        (*S).base = (SElemType*) realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if((*S).base == NULL) {
            exit(OVERFLOW);     // 存储分配失败
        }
        
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    
    // 进栈先赋值，栈顶指针再自增
    *(S->top++) = e;
    
    return OK;
}

Status Pop(SqStack* S, SElemType* e) {
    if(S == NULL || (*S).base == NULL) {
        return ERROR;
    }
    
    if((*S).top == (*S).base) {
        return ERROR;
    }
    
    // 出栈栈顶指针先递减，再赋值
    *e = *(--(*S).top);
    
    return OK;
}

Status StackTraverse(SqStack S, void(Visit)(SElemType)) {
    SElemType* p = S.base;
    
    if(S.base == NULL) {
        return ERROR;
    }
    
    while(p < S.top) {
        Visit(*p++);
    }
    
    printf("\n");
    
    return OK;
}

Status Algo_BracketMatching(char* s) {
    SqStack S;
    SElemType e;
    int i;
    
    InitStack(&S);
    
    for(i = 0; s[i] != '\0'; i++) {
        switch(s[i]) {
            // 遇到左括号，则入栈
            case '(':
            case '[':
            case '{':
                Push(&S, s[i]);
                break;
        
            // 遇到右括号，则出栈
            case ')':
            case ']':
            case '}':
                if(StackEmpty(S)) {
                    return ERROR;
                }
                
                Pop(&S, &e);
                
                // 判断括号是否匹配
                if(!Matching(e, s[i])) {
                    return ERROR;
                }
                break;
            
            default:
                break;
        }
    }
    
    if(StackEmpty(S)) {
        return OK;
    }
    
    return ERROR;
}

// 判断括号a和括号b之间的类型是否匹配
Status Matching(char a, char b) {
    switch(a) {
        case '(':
            if(b != ')') {
                return ERROR;
            }
            break;
        
        case '[':
            if(b != ']') {
                return ERROR;
            }
            break;
        
        case '{':
            if(b != '}') {
                return ERROR;
            }
            break;
        
        default:
            return ERROR;
    }
    
    return OK;
}
