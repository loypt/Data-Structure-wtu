//
//  main.cpp
//  BinarySortTree
//
//  Created by Loyio Hex on 6/18/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>                //提供宏va_list、va_start、va_arg、va_end
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define Max 7

typedef int Status;

typedef int KeyType;

typedef struct
{
    int key;                    //关键字域
    float weight;                //其他域（此处可设为权重）
}ElemType_Search;

typedef ElemType_Search BSTElemType;

typedef struct
{
    ElemType_Search *elem;        //数据元素存储空间基址，0号单元为空
    int length;                    //表长度
}Table;

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a) < (b))

   //二叉排序树元素类型
typedef struct BSTNode                        //二叉排序树存储表示
{
    BSTElemType data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
    
    union                                    //匿名联合体，仅在第9章习题测试时使用
    {
        int RTag;                            //线索标志
    };
}BSTNode;                                    //二叉排序树结点
typedef BSTNode* BSTree;                    //指向二叉排序树结点的指针

// Table
Status Create(FILE *fp, Table *T, int n);

void Destory(Table *T);

void Traverse(Table T, void(Visit)(ElemType_Search));

void PrintKey(ElemType_Search e);
 
/* 二叉排序树函数列表 */
Status CreateBSTree(BSTree *BST, Table T);

BSTree SearchBST_1(BSTree BST, KeyType key);

Status SearchBST_2(BSTree BST, KeyType key, BSTree f, BSTree *p);

Status InsertBST(BSTree *BST, BSTElemType e);

void InOrderTraverse_BST(BSTree BST, void(Visit)(ElemType_Search));

Status DeleteBST(BSTree *BST, KeyType key);
 
Status Delete(BSTree *p);

int Scanf(FILE *fp, char *format, ...);


int main(int argc, const char * argv[]) {
    Table T;
    BSTree BST;
        
    printf("创建并输出一个查找表...\n");
    
    FILE *fp;
            
    fp = fopen("TestData_Table.txt", "r");
    Create(fp, &T, Max);
    Traverse(T, PrintKey);
    printf("\n");
    
    printf("▼1、3、4、5\n▲函数 CreateBSTree等 测试...\n"); //1、3、4、5.函数CreateBSTree等测试
    printf("构造二叉排序树，并输出其关键字：");
    CreateBSTree(&BST, T);
    InOrderTraverse_BST(BST, PrintKey);
    printf("\n\n");
    
    printf("▼2\n▲函数 SearchBST_1 测试...\n");                //2.函数SearchBST_1测试
    printf("关键字 24 ");
    SearchBST_1(BST, 24)==NULL ? printf("不在") : printf("在");
    printf("二叉排序树中！");
    printf("\n\n");

    printf("▼6、7\n▲函数 DeleteBST等 测试...\n");            //6、7.函数DeleteBST等测试
    printf("删除关键字 24 后的关键字序列为：");
    DeleteBST(&BST, 24);
    InOrderTraverse_BST(BST, PrintKey);
    printf("\n\n");
    return 0;
}

// Table
Status Create(FILE *fp, Table *T, int n)
{
    int i;
    int a;
    float b;
     
    T->elem = (ElemType_Search *)malloc((n+1)*sizeof(ElemType_Search));
    if(!(T->elem))
        exit(OVERFLOW);
    
    //此表0号单元是弃用的
    for((*T).length=0,i=1; i<=n; i++)
    {
        if(Scanf(fp, "%d%f", &a, &b)==2)
        {
            (*T).elem[i].key = a;
            (*T).elem[i].weight = b;
            (*T).length++;
        }
    }
    
    return OK;
}

void Destory(Table *T)
{
    if(T->elem)
        free(T->elem);
    
    T->elem = NULL;
    T->length = 0;
}

void Traverse(Table T, void(Visit)(ElemType_Search))
{
    int i;
    
    for(i=0; i<T.length; i++)
    {
        if(i && !(i%10))
            printf("\n");
        
        Visit(T.elem[i+1]);
    }
    
    printf("\n");
}

/* 输出查找表中的关键字 */
void PrintKey(ElemType_Search e)
{
    printf("%3d ", e.key);
}


Status CreateBSTree(BSTree *BST, Table T)
{
    int i;
    
    *BST = NULL;
    
    if(T.length)
    {
        for(i=1; i<=T.length; i++)
            InsertBST(BST, T.elem[i]);
    }
    
    return OK;
}

BSTree SearchBST_1(BSTree BST, KeyType key)
{
    if(!BST || EQ(key, BST->data.key))
        return BST;
    else if(LT(key, BST->data.key))
        return SearchBST_1(BST->lchild, key);
    else
        return SearchBST_1(BST->rchild, key);
}

Status SearchBST_2(BSTree BST, KeyType key, BSTree f, BSTree *p)
{//p指向查找路径上最后一个“能”被访问结点，f指向BST的双亲，初始值为NULL
    if(!BST)
    {
        *p = f;
        return FALSE;
    }
    else if(EQ(key, BST->data.key))
    {
        *p = BST;
        return TRUE;
    }
    else if(LT(key, BST->data.key))
        return SearchBST_2(BST->lchild, key, BST, p);
    else
        return SearchBST_2(BST->rchild, key, BST, p);
}


Status InsertBST(BSTree *BST, BSTElemType e)
{
    BSTree p, s;
     
    if(!SearchBST_2(*BST, e.key, NULL, &p))        //查找不成功
    {
        s = (BSTree)malloc(sizeof(BSTNode));
        s->data = e;
        s->lchild = s->rchild = NULL;
        
        if(!p)                                    //原树为空
            *BST = s;
        else if(LT(e.key, p->data.key))
            p->lchild = s;
        else
            p->rchild = s;
    
        return TRUE;                            //插入e.key
    }
    else                                        //查找成功
        return FALSE;
}

void InOrderTraverse_BST(BSTree BST, void(Visit)(ElemType_Search))
{
    if(BST)
    {
        InOrderTraverse_BST(BST->lchild, Visit);
        Visit(BST->data);
        InOrderTraverse_BST(BST->rchild, Visit);
    }

}


Status DeleteBST(BSTree *BST, KeyType key)
{
    if(!(*BST))                        //不存在与关键字相等的数据元素
        return FALSE;
    else
    {
        if(EQ(key, (*BST)->data.key))
            return Delete(BST);
        else if(LT(key, (*BST)->data.key))
            return DeleteBST(&(*BST)->lchild, key);
        else
            return DeleteBST(&(*BST)->rchild, key);
    }
}


Status Delete(BSTree *p)
{
    BSTree q, s;
    
    if(!(*p)->rchild)
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if(!(*p)->lchild)
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    {
        q = *p;
        s = (*p)->lchild;
        
        while(s->rchild)        //寻找p的直接前驱
        {
            q = s;
            s = s->rchild;
        }
        
        (*p)->data = s->data;    //用p的直接前驱取代p
        
        if(q!=*p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
            
        free(s);
    }
    
    return TRUE;
}

int Scanf(FILE *fp, char *format, ...)
{
    int *i;
    char *ch, *s;
    float *f;
    int count, k, len, n;
    int tmp;
    va_list ap;
    
    len = strlen(format);
    
    va_start(ap, format);
    
    for(count=0,k=2; k<=len; k=k+2)
    {
        while((tmp=getc(fp))!=EOF)            //跳过所有非西文字符
        {
            if((tmp>=0 && tmp<=127))
            {
                ungetc(tmp, fp);            //遇到首个西文字符，将此西文字符放入输入流
                break;
            }
        }
        
        if(tmp==EOF)
            break;
        
        if(format[k-1]=='c')                //读取字符
        {
            ch = va_arg(ap, char*);
                        
            if(tmp!=EOF)
                count += fscanf(fp, "%c", ch);
        }
        
        if(format[k-1]=='d')                //读取整型
        {
            i = va_arg(ap, int*);
            
            while((tmp=getc(fp))!=EOF)
            {
                if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+')
                {
                    ungetc(tmp, fp);
                    break;
                }
            }
            
            if(tmp!=EOF)
                count += fscanf(fp, "%d", i);
        }

        if(format[k-1]=='f')                //读取浮点型
        {
            f = va_arg(ap, float*);
            
            while((tmp=getc(fp))!=EOF)
            {
                if((tmp>='0' && tmp<='9') || tmp=='-' || tmp=='+'|| tmp=='.' )
                {
                    ungetc(tmp, fp);
                    break;
                }
            }
            
            if(tmp!=EOF)
                count += fscanf(fp, "%f", f);
        }
        
        if(format[k-1]=='s')                //读取字符串
        {
            s = va_arg(ap, char*);
            
            while((tmp=getc(fp))!=EOF && (!isprint(tmp) || tmp==' '))
                ;
            
            n = 0;
            if(!feof(fp))
            {
                ungetc(tmp, fp);
                while((tmp=getc(fp))!=EOF)
                {
                    if(isprint(tmp) && tmp!=' ')
                        s[n++] = tmp;
                    else
                        break;
                }
                ungetc(tmp, fp);
            }
                                                                                
            s[n] = '\0';
                    
            count++;
        }
    }
        
    va_end(ap);
    
    return count;
}
