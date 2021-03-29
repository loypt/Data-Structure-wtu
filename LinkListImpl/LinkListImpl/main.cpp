//
//  main.cpp
//  LinkListImpl
//
//  Created by Loyio Hex on 3/26/21.
//

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;

typedef int LElemType_L;

typedef struct LNode
{
    LElemType_L data;
    struct LNode* next;
}LNode;

void PrintElem(LElemType_L e) {
    printf("%d ", e);
}
Status CmpGreater(LElemType_L data, LElemType_L e) {
    return data > e ? TRUE : FALSE;
}

typedef LNode* LinkList;

Status InitList_L(LinkList *L);

Status ClearList_L(LinkList L);

void DestroyList_L(LinkList *L);

Status ListEmpty_L(LinkList L);

int ListLength_L(LinkList L);

Status GetElem_L(LinkList L, int i, LElemType_L *e);

int LocateElem_L(LinkList L, LElemType_L e, Status(Compare)(LElemType_L, LElemType_L));

Status PriorElem_L(LinkList L, LElemType_L cur_e, LElemType_L *pre_e);

Status NextElem_L(LinkList L, LElemType_L cur_e, LElemType_L *next_e);

Status ListInsert_L(LinkList L, int i, LElemType_L e);

Status ListDelete_L(LinkList L, int i, LElemType_L *e);

Status ListTraverse_L(LinkList L, void(Visit)(LElemType_L));

Status CreateList_HL(FILE *fp, LinkList *L, int n);

Status CreateList_TL(FILE *fp, LinkList *L, int n);

// Question 5
void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc);

// Question 8
void ReverseList_L(LinkList L);

// Question 14
bool SortList_L(LinkList L);


int main(int argc, const char * argv[]) {
    LinkList L1;
    int i;
    LElemType_L e;
    
    // Question 1
    InitList_L(&L1);
    int a[] = {3, 5, 6, 8, 11};
    for(i=0; i<5; i++){
        printf("在 L1 第 %d 个位置插入 \"%d\" \n", i+1, a[i]);
        ListInsert_L(L1, i+1, a[i]);
    }
    printf("\n\n");
    
    // Question 2
    ListTraverse_L(L1, PrintElem);
    printf("\n\n");
    
    // Question 3
    LinkList L2;
    InitList_L(&L2);
    int b[] = {2, 6, 8, 9, 11, 15, 20};
    for(i=0; i<7; i++){
        printf("在 L2 第 %d 个位置插入 \"%d\" \n", i+1, b[i]);
        ListInsert_L(L2, i+1, b[i]);
    }
    printf("\n\n");
    
    // Question 4
    ListTraverse_L(L2, PrintElem);
    printf("\n\n");
    
    // Question 6
    LinkList L3;
    InitList_L(&L3);
    MergeList_L(L1, &L2, &L3);
    printf("合并La和Lb为Lc = ");
    
    // Question 7
    ListTraverse_L(L3, PrintElem);
    printf("\n\n");
    
    // Question 9
    ReverseList_L(L3);
    printf("反转链表L3\n");
    
    // Questoin 10
    ListTraverse_L(L3, PrintElem);
    printf("\n\n");
    
    
    // Question 11
    DestroyList_L(&L3);
    printf("销毁 L3 后：");
    L3 ? printf(" L3 存在！\n") : printf(" L3 不存在！！\n");
    printf("\n\n");
    
    // Question 12
    LinkList L4;
    InitList_L(&L4);
    int c[] = {8, 6, 15, 9, 20, 15, 11};
    for(i=0; i<7; i++){
        printf("在 L4 第 %d 个位置插入 \"%d\" \n", i+1, c[i]);
        ListInsert_L(L4, i+1, c[i]);
    }
    printf("\n\n");
    
    // Question 13
    ListTraverse_L(L4, PrintElem);
    printf("\n\n");
    
    
    // Question 15
    printf("L4进行排序\n");
    SortList_L(L4);
    printf("\n\n");
    
    // Question 16
    printf("遍历L4\n");
    ListTraverse_L(L4, PrintElem);
    printf("\n\n");
    
    // Question 17
    DestroyList_L(&L4);
    printf("销毁 L4 后：");
    L4 ? printf(" L4 存在！\n") : printf(" L4 不存在！！\n");
    printf("\n\n");
    
    
    
    
    return 0;
}

Status InitList_L(LinkList *L)
{
    (*L) = (LinkList)malloc(sizeof(LNode));
    if(!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL;
    
    return OK;
}

Status ClearList_L(LinkList L)
{
    LinkList pre, p;
    
    if(!L)
        return ERROR;
    
    pre = L->next;

    while(pre)
    {
        p = pre->next;
        free(pre);
        pre = p;
    }

    L->next = NULL;

    return OK;
}

void DestroyList_L(LinkList *L)
{
    LinkList p = *L;

    while(p)
    {
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }
}

Status ListEmpty_L(LinkList L)
{
    if(L!=NULL && L->next==NULL)        //链表存在且只有头结点
        return TRUE;
    else
        return FALSE;
}

int ListLength_L(LinkList L)
{
    LinkList p;
    int i;
    
    if(L)
    {
        i = 0;
        p = L->next;
        while(p)
        {
            i++;
            p = p->next;
        }
    }
    
    return i;
}

Status GetElem_L(LinkList L, int i, LElemType_L *e)
{
    int j;
    LinkList p = L->next;
    
    j = 1;
    p = L->next;
    
    while(p && j<i)
    {
        j++;
        p = p->next;
    }

    if(!p || j>i)
        return ERROR;

    *e = p->data;

    return OK;
}

int LocateElem_L(LinkList L, LElemType_L e, Status(Compare)(LElemType_L, LElemType_L))
{
    int i;
    LinkList p;
    
    i = -1;
    
    if(L)
    {
        i = 0;
        p = L->next;
        
        while(p)
        {
            i++;
            
            if(!Compare(e, p->data))
            {
                p = p->next;
                if(p==NULL)
                    i++;
            }
            else
                break;
        }
    }

    return i;
}

Status PriorElem_L(LinkList L, LElemType_L cur_e, LElemType_L *pre_e)
{
    LinkList p, suc;
    
    if(L)
    {
        p = L->next;
        
        if(p->data!=cur_e)
        {
            while(p->next)
            {
                suc = p->next;
                if(suc->data==cur_e)
                {
                    *pre_e = p->data;
                    return OK;
                }
                p = suc;
            }
        }
    }

    return ERROR;
}

Status NextElem_L(LinkList L, LElemType_L cur_e, LElemType_L *next_e)
{
    LinkList p, suc;
    
    if(L)
    {
        p = L->next;
        
        while(p && p->next)
        {
            suc = p->next;
            
            if(suc && p->data==cur_e)
            {
                *next_e = suc->data;
                return OK;
            }
            
            if(suc)
                p = suc;
            else
                break;
        }
    }

    return ERROR;
}


Status ListInsert_L(LinkList L, int i, LElemType_L e)
{
    LinkList p, s;
    int j;
    
    p = L;
    j = 0;
    
    while(p && j<i-1)
    {
        p = p->next;
        ++j;
    }
    
    if(!p || j>i-1)
        return ERROR;

    s = (LinkList)malloc(sizeof(LNode));
    if(!s)
        exit(OVERFLOW);
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

Status ListDelete_L(LinkList L, int i, LElemType_L *e)
{
    LinkList pre, p;
    int j;

    pre = L;
    j = 1;

    while(pre->next && j<i)
    {
        pre = pre->next;
        ++j;
    }
    
    if(!pre->next || j>i)
        return ERROR;

    p = pre->next;
    pre->next = p->next;
    *e = p->data;
    free(p);

    return OK;
}

Status ListTraverse_L(LinkList L, void(Visit)(LElemType_L))
{
    LinkList p;

    if(!L)
        return ERROR;
    else
        p = L->next;

    while(p)
    {
        Visit(p->data);
        p = p->next;
    }

    return OK;
}

Status CreateList_HL(FILE *fp, LinkList *L, int n)
{
    int i;
    LinkList p;
    LElemType_L tmp;
        
    *L = (LinkList)malloc(sizeof(LNode));
    if(!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL;                            //建立头结点
    
    for(i=1; i<=n; ++i)
    {
        if(fscanf(fp, "%d", &tmp)==1)
        {
            p = (LinkList)malloc(sizeof(LNode));
            if(!p)
                exit(OVERFLOW);
            p->data = tmp;                        //录入数据
            p->next = (*L)->next;
            (*L)->next = p;
        }
        else
            return ERROR;
    }
    
    return OK;
}

Status CreateList_TL(FILE *fp, LinkList *L, int n)
{
    int i;
    LinkList p, q;
    LElemType_L tmp;
            
    *L = (LinkList)malloc(sizeof(LNode));
    if(!(*L))
        exit(OVERFLOW);
    (*L)->next = NULL;
        
    for(i=1,q=*L; i<=n; ++i)
    {
        if(fscanf(fp, "%d", &tmp)==1)
        {
            p = (LinkList)malloc(sizeof(LNode));
            if(!p)
                exit(OVERFLOW);
            p->data = tmp;
            q->next = p;
            q = q->next;
        }
        else
            return ERROR;
    }
    
    q->next = NULL;

    return OK;
}

void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc){
    LinkList pa, pb, pc;
    
    pa = La->next;
    pb = (*Lb)->next;
    pc = *Lc = La;

    while(pa && pb)
    {
        if(pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }

    pc->next = pa ? pa : pb;
    
    free(*Lb);
    *Lb = NULL;
}


void ReverseList_L(LinkList L){
    LNode* p = L->next;
    LNode* q;
    L->next = NULL;
    while (p) {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}

bool  SortList_L(LinkList L){
    if (L == NULL || L->next == NULL) {
        return false;
    }
    LinkList flagNode = NULL;
    bool isChange = true;
    while (flagNode != L->next || isChange) {
        LinkList curNode = L;
        isChange = false;
        while (curNode->next && curNode->next != flagNode) {
            if(curNode->data > curNode->next->data){
                LElemType_L temp = curNode->data;
                curNode->data = curNode->next->data;
                curNode->next->data = temp;
            }
            curNode = curNode->next;
        }
        flagNode = curNode;
    }
    return true;
    
}
