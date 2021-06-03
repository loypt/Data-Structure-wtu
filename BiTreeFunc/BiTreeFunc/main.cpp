//
//  main.cpp
//  BiTree
//
//  Created by Loyio Hex on 6/2/21.
//

#include <stdio.h>
#include <string.h>
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

/*
 * 计算二叉树中叶子结点数目
 */
int Algo_LeafNode(BiTree T);

/*
 * 返回二叉树的深度（层数）。
 */
int BiTreeDepth(BiTree T);

/*
 * 计算结点的层次
 */
Status getLever(BiTree T,BiTNode *p);

// 创建二叉树的内部函数
static void CreateTree(BiTree* T, FILE* fp);

int main(int argc, const char * argv[]) {
    BiTree T;
    printf("初始化空二叉树 T ...\n");
    InitBiTree(&T);
    printf("\n");
    
    printf("按先序序列创建二叉树 T ...\n");
    CreateBiTree(&T);
    printf("\n");
    
    printf("计算二叉树中叶子结点数目 ...\n");
    printf("%d",Algo_LeafNode(T));
    printf("\n");
    
    printf("返回二叉树的深度（层数） ...\n");
    printf("%d",BiTreeDepth(T));
    printf("\n");
    
    BiTNode *p;
    p = (BiTree) malloc(sizeof(BiTNode));
    p->data = 'A';
    printf("计算结点的层次 ...\n");
    //printf("%d",getLever(T, p));
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
 * 计算二叉树中叶子结点数目
 */
int Algo_LeafNode(BiTree T){
    int count = 0;
        
    if(T != NULL) {
        if(T->lchild == NULL && T->rchild == NULL) {
            count++;
        } else {
            count += Algo_LeafNode(T->lchild);  // 左子树叶子结点数量
            count += Algo_LeafNode(T->rchild);  // 右子树叶子结点数量
        }
    }
    
    return count;
}

/*
 * 返回二叉树的深度（层数）
 */
int BiTreeDepth(BiTree T) {
    int LD, RD;
    
    if(T == NULL) {
        return 0;                       // 空树深度为0
    } else {
        LD = BiTreeDepth(T->lchild);    // 求左子树深度
        RD = BiTreeDepth(T->rchild);    // 求右子树深度
        
        return (LD >= RD ? LD : RD) + 1;
    }
}


/*
 * 计算结点的层次
 */
Status getLever(BiTree T,BiTNode *p){
    if(T==NULL) return 0;
    if(T->data==p->data) return 1;//如果相等，返回第一层
    int l=getLever(T, T->lchild);
    int r=getLever(T, T->rchild);
    if(l||r){//注意这个，只有当在树中找到P时才进入
        if(l>r)
         return l+1;
        else
          return r+1;
    }
    return ERROR;
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
