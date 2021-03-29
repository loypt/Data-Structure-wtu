//
//  main.cpp
//  SequenceList
//
//  Created by Loyio Hex on 3/16/21.
//

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;

typedef int ElemType;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MaxSize 50

#ifndef LELEMTYPE_SQ
#define LELEMTYPE_SQ
typedef int LElemType_Sq;
#endif

typedef struct
{
    LElemType_Sq *elem;
    int length;
    int listsize;
}SqList;


void PrintElem(ElemType e) {
    printf("%d ", e);
}
Status CmpGreater(ElemType data, ElemType e) {
    return data > e ? TRUE : FALSE;
}

/* 顺序表函数列表 */
Status InitList_Sq(SqList *L);

void ClearList_Sq(SqList *L);

void DestroyList_Sq(SqList *L);
      
Status ListEmpty_Sq(SqList L);

int ListLength_Sq(SqList L);
    
Status GetElem_Sq(SqList L, int i, LElemType_Sq *e);

int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq));

Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e);

Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e);

Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e);

Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e);

Status ListTraverse_Sq(SqList L, void (Visit)(LElemType_Sq));

Status* visit();

void Union(SqList *La, SqList Lb);

Status equal(LElemType_Sq e1, LElemType_Sq e2);

void MergeSqList(SqList La, SqList Lb, SqList *Lc);



int main(int argc, const char * argv[]) {
    

    SqList LA;
    int i;
    LElemType_Sq e;
    
    InitList_Sq(&LA);
    
    // Question 2
    int LA_list[] = {5, 3, 6, 9};
    for (i=0; i<4; i++) {
        ListInsert_Sq(&LA, i+1, LA_list[i]);
    }
    printf("创建LA成功");
    printf("\n\n");
    
    // Question 3
    PriorElem_Sq(LA, 6, &e);
    printf("元素 \"6\" 的前驱为 \"%d\" \n", e);
    printf("\n\n");
    
    // Question 4
    printf("遍历LA: ");
    ListTraverse_Sq(LA, PrintElem);
    printf("\n\n");
    
    // Question 5
    SqList LB;
    InitList_Sq(&LB);
    printf("\n");
    int LB_list[] = {9, 8, 5, 2, 7};
    for (i=0; i<5; i++) {
        ListInsert_Sq(&LB, i+1, LB_list[i]);
    }
    printf("创建LB成功");
    printf("\n\n");
    
    // Questoin 6
    NextElem_Sq(LB, 8, &e);
    printf("元素 \"8\" 的后继为 \"%d\" \n", e);
    printf("\n\n");
    
    
    // Question 7
    printf("遍历LB: ");
    ListTraverse_Sq(LB, PrintElem);
    printf("\n\n");
    
    //Question 8
    ListDelete_Sq(&LB, 2, &e);
    printf("删除 LB 中第 2 个元素 \"%d\" ...\n", e);
    printf(" LB 中的元素为：L = ");
    ListTraverse_Sq(LB, PrintElem);
    printf("\n\n");
    
    // Question 9 10
    printf("LA = LA ∪ LB = ");
    Union(&LA, LB);
    ListTraverse_Sq(LA, PrintElem);
    printf("\n\n");
    
    // Question 11
    ClearList_Sq(&LA);
    ListEmpty_Sq(LA) ? printf("LA 为空！！\n") : printf("LA 不为空！\n");
    ClearList_Sq(&LB);
    ListEmpty_Sq(LB) ? printf("LB 为空！！\n") : printf("LB 不为空！\n");
    printf("\n\n");

    // Question 12
    int LA_newlist[] = {3, 5, 6, 8, 11};
    for (i=0; i<5; i++) {
        ListInsert_Sq(&LA, i+1, LA_newlist[i]);
    }
    printf("创建LA成功");
    printf("\n\n");
    
    // Question 13
    int LB_newlist[] = {2, 6, 8, 9, 11, 15, 20};
    for (i=0; i<7; i++) {
        ListInsert_Sq(&LB, i+1, LB_newlist[i]);
    }
    printf("创建LB成功");
    printf("\n\n");
    
    // Question 14
    printf("遍历LA: ");
    ListTraverse_Sq(LA, PrintElem);
    printf("\n\n");
    printf("遍历LB: ");
    ListTraverse_Sq(LB, PrintElem);
    printf("\n\n");
    
    // Question 15
    SqList LC;
    MergeSqList(LA, LB, &LC);
    
    // Question 16
    printf("合并LA和LB为LC = ");
    ListTraverse_Sq(LC, PrintElem);
    printf("\n\n");
    
    // Questoin 17
    DestroyList_Sq(&LA);
    DestroyList_Sq(&LB);
    DestroyList_Sq(&LC);
    printf("销毁LA、LB、LC成功\n");
    return 0;
}

Status InitList_Sq(SqList *L)
{
    (*L).elem = (LElemType_Sq*)malloc(LIST_INIT_SIZE*sizeof(LElemType_Sq));
    if(!(*L).elem)
        exit(OVERFLOW);
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;

    return OK;
}

void ClearList_Sq(SqList *L)
{
    (*L).length = 0;
}

void DestroyList_Sq(SqList *L)
{
    free((*L).elem);

    (*L).elem = NULL;
    (*L).length = 0;
    (*L).listsize = 0;
}

Status ListEmpty_Sq(SqList L)
{
    return     L.length==0 ? TRUE : FALSE;
}

int ListLength_Sq(SqList L)
{
    return L.length;
}

Status GetElem_Sq(SqList L, int i, LElemType_Sq *e)
{
    if(i<1 || i>L.length)
        return ERROR;
    else
        *e = L.elem[i-1];

    return OK;
}

int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq))
{
    int i = 1;
    
    while(i<=L.length && !Compare(e, L.elem[i-1]))
        ++i;

    if(i<=L.length)
        return i;
    else
        return 0;
}

int LocateElem_SqM(SqList L, LElemType_Sq e){
    for (int i = 0; i<L.length; i++) {
        if (L.elem[i] == e) {
            return i+1;
        }
    }
    return 0;
}

Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e)
{
    int i = 1;
    
    if(L.elem[0]!=cur_e)
    {
        while(i<L.length && L.elem[i]!=cur_e)
            ++i;
        
        if(i<L.length)
        {
            *pre_e = L.elem[i-1];
            return OK;
        }
    }
            
    return ERROR;
}

Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e)
{
    int i = 0;
    
    while(i<L.length && L.elem[i]!=cur_e)
        ++i;

    if(i<L.length-1)
    {
        *next_e = L.elem[i+1];
        return OK;
    }

    return ERROR;
}


Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e)
{
    LElemType_Sq *newbase;
    LElemType_Sq *p, *q;

    if(i<1 || i>(*L).length+1)
        return ERROR;
    
    //动态分配空间
    if((*L).length >= (*L).listsize)
    {
        newbase = (LElemType_Sq*)realloc((*L).elem, ((*L).listsize+LISTINCREMENT)*sizeof(LElemType_Sq));
        if(!newbase)
            exit(OVERFLOW);

        (*L).elem = newbase;
        (*L).listsize += LISTINCREMENT;
    }
    
    q = &(*L).elem[i-1];
    
    //移动元素
    for(p=&(*L).elem[(*L).length-1]; p>=q; --p)
        *(p+1) = *p;
    
    *q = e;
    (*L).length++;

    return OK;
}

bool ListInsert_SqM(SqList *L, int i, LElemType_Sq e){
    if(i<1 || i>L->length+1){
        return false;
    }
    if (L->length == MaxSize) {
        return false;
    }
    for (int j = L->length; j>=i; j--) {
        L->elem[j] = L->elem[j-1];
    }
    L->elem[i-1] = e;
    L->length++;
    return true;
    
}

Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e)
{
    LElemType_Sq *p, *q;
        
    if(i<1 || i>(*L).length)
        return ERROR;
    
    p = &(*L).elem[i-1];
    *e = *p;
    q = (*L).elem+(*L).length-1;
    
    for(++p; p<=q; ++p)
        *(p-1) = *p;

    (*L).length--;

    return OK;
}

bool ListDelete_SqM(SqList *L, int i, LElemType_Sq *e){
    if (i < 1 || i > L->length) {
        return false;
    }
    e=&L->elem[i-1];
    for (int j = i-1; j<L->length-1; j++) {
        L->elem[j]=L->elem[j+1];
    }
    L->length--;
    return true;
}

Status ListTraverse_Sq(SqList L, void(Visit)(LElemType_Sq))
{
    int i;

    for(i=0; i<L.length; i++)
        Visit(L.elem[i]);
    
    return OK;
}

void Union(SqList *La, SqList Lb)
{
    int La_len, Lb_len;
    int i;
    LElemType_Sq e;
    
    La_len = ListLength_Sq(*La);
    Lb_len = ListLength_Sq(Lb);
    
    for(i=1; i<=Lb_len; i++)
    {
        GetElem_Sq(Lb, i, &e);
        if(!LocateElem_Sq(*La, e, equal))
            ListInsert_Sq(La, ++La_len, e);
    }
}

Status equal(LElemType_Sq e1, LElemType_Sq e2)
{
   return e1==e2 ? TRUE : FALSE;
}

void MergeSqList(SqList La, SqList Lb, SqList *Lc)
{
    LElemType_Sq *pa, *pb, *pc;
    LElemType_Sq *pa_last, *pb_last;
        
    pa = La.elem;
    pb = Lb.elem;
    
    (*Lc).listsize = (*Lc).length = La.length + Lb.length;
    pc = (*Lc).elem = (LElemType_Sq *)malloc((*Lc).listsize*sizeof(LElemType_Sq));
    if(!pc)
        exit(OVERFLOW);
    
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;
    
    while(pa<=pa_last && pb<=pb_last)
    {
        if(*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    
    while(pa <= pa_last)
        *pc++ = *pa++;

    while(pb <= pb_last)
        *pc++ = *pb++;
}
