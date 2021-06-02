//
//  main.cpp
//  BiTree
//
//  Created by Loyio Hex on 6/2/21.
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

typedef char TElemType;

// 测试函数，打印元素
Status PrintElem(TElemType c) {
    printf("%c", c);
    return OK;
}

typedef struct BiTNode {
    TElemType data;             // 结点元素
    struct BiTNode* lchild;     // 左孩子指针
    struct BiTNode* rchild;     // 右孩子指针
} BiTNode;

typedef BiTNode* BiTree;

Status InitBiTree(BiTree* T);

Status BiTreeEmpty(BiTree T);

Status DestroyBiTree(BiTree* T);

Status CreateBiTree(BiTree* T);

Status ClearBiTree(BiTree* T);

Status PreOrderTraverse(BiTree T, Status(Visit)(TElemType));

Status InOrderTraverse(BiTree T, Status(Visit)(TElemType));

Status PostOrderTraverse(BiTree T, Status(Visit)(TElemType));

// 创建二叉树的内部函数
static void CreateTree(BiTree* T, FILE* fp);

// 先序遍历的内部实现
static Status PreTraverse(BiTree T, Status(Visit)(TElemType));

// 中序遍历的内部实现
static Status InTraverse(BiTree T, Status(Visit)(TElemType));

// 后序遍历的内部实现
static Status PostTraverse(BiTree T, Status(Visit)(TElemType));

int main(int argc, const char * argv[]) {
    BiTree T;
    printf("初始化空二叉树 T ...\n");
    InitBiTree(&T);
    printf("\n");
    
    printf("按先序序列创建二叉树 T ...\n");
    CreateBiTree(&T);
    printf("\n");
    
    printf("前序遍历二叉树 T = ");
    PreOrderTraverse(T, PrintElem);
    printf("\n");
    
    printf("中序遍历二叉树 T = ");
    InOrderTraverse(T, PrintElem);
    printf("\n");
    
    printf("后序遍历二叉树 T = ");
    PostOrderTraverse(T, PrintElem);
    printf("\n");
    
    printf("清空前：");
    BiTreeEmpty(T) ? printf("T 为空！\n") : printf("T 不为空！\n");

    ClearBiTree(&T);

    printf("清空后：");
    BiTreeEmpty(T) ? printf("T 为空！\n") : printf("T 不为空！\n");
    
    return 0;
}

Status InitBiTree(BiTree* T) {
    if(T == NULL) {
        return ERROR;
    }
    
    *T = NULL;
    
    return OK;
}

Status BiTreeEmpty(BiTree T) {
    return T == NULL ? TRUE : FALSE;
}

Status CreateBiTree(BiTree* T) {
    
    printf("请输入二叉树的先序序列，如果没有子结点，使用^代替：");
    CreateTree(T, NULL);
    return OK;
}


Status DestroyBiTree(BiTree* T) {
    // 无需销毁，使用置空就可以
    return ERROR;
}

Status ClearBiTree(BiTree* T) {
    if(T == NULL) {
        return ERROR;
    }
    
    // 在*T不为空时进行递归清理
    if(*T) {
        if((*T)->lchild!=NULL) {
            ClearBiTree(&((*T)->lchild));
        }
        
        if((*T)->rchild!=NULL) {
            ClearBiTree(&((*T)->rchild));
        }
        
        free(*T);
        *T = NULL;
    }
    
    return OK;
}

/*
 * 先序遍历
 */

Status PreOrderTraverse(BiTree T, Status(Visit)(TElemType)) {
    Status status;
    
    status = PreTraverse(T, Visit);
    printf("\n");
    
    return status;
}

/*
 * 中序遍历
 */
Status InOrderTraverse(BiTree T, Status(Visit)(TElemType)) {
    Status status;
    
    status = InTraverse(T, Visit);
    printf("\n");
    
    return status;
}


/*
 * 后序遍历
 */
Status PostOrderTraverse(BiTree T, Status(Visit)(TElemType)) {
    Status status;
    
    status = PostTraverse(T, Visit);
    printf("\n");
    
    return status;
}


// 创建二叉树的内部函数
static void CreateTree(BiTree* T, FILE* fp) {
    char ch;
    
    // 读取当前结点的值
    scanf("%c", &ch);
    
    if(ch == '^') {
        *T = NULL;
    } else {
        // 生成根结点
        *T = (BiTree) malloc(sizeof(BiTNode));
        if(!(*T)) {
            exit(OVERFLOW);
        }
        (*T)->data = ch;
        CreateTree(&((*T)->lchild), fp); // 创建左子树
        CreateTree(&((*T)->rchild), fp); // 创建右子树
    }
}


// 先序遍历的内部实现
static Status PreTraverse(BiTree T, Status(Visit)(TElemType)) {
    if(T) {
        if(Visit(T->data)) {
            if(PreTraverse(T->lchild, Visit)) {
                if(PreTraverse(T->rchild, Visit)) {
                    return OK;
                }
            }
        }
        
        return ERROR;
    
        // 遇到空树则无需继续计算
    } else {
        return OK;
    }
}

// 中序遍历的内部实现
static Status InTraverse(BiTree T, Status(Visit)(TElemType)) {
    if(T) {
        if(InTraverse(T->lchild, Visit)) {
            if(Visit(T->data)) {
                if(InTraverse(T->rchild, Visit)) {
                    return OK;
                }
            }
        }
        
        return ERROR;
        
        // 遇到空树则无需继续计算
    } else {
        return OK;
    }
}

// 后序遍历的内部实现
static Status PostTraverse(BiTree T, Status(Visit)(TElemType)) {
    if(T) {
        if(PostTraverse(T->lchild, Visit)) {
            if(PostTraverse(T->rchild, Visit)) {
                if(Visit(T->data)) {
                    return OK;
                }
            }
        }
        
        return ERROR;
        
        // 遇到空树则无需继续计算
    } else {
        return OK;
    }
}
