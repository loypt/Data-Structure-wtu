//
//  main.cpp
//  TripletDemo
//
//  Created by Loyio Hex on 6/1/21.
//

#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;
typedef ElemType *Triplet;

Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3);
Status DestroyTriplet(Triplet &T);
Status get(Triplet T,int i,ElemType &e);
Status put(Triplet &T,int i,ElemType e);
Status IsAscending(Triplet T);
Status IsDescending(Triplet T);
Status Max(Triplet T,ElemType &e);
Status Min(Triplet T,ElemType &e);
void PrintE(ElemType e);
void PrintT(Triplet T);

int main()
{
    Triplet T;
    int e;
    Status flag;
    flag = InitTriplet(T,90,95,100);
    if(flag)
    {
        printf("初始化成功！\nT中元素是：");
        PrintT(T);
    }
    else
    {
        printf("初始化失败！");
    }
    flag = get(T,1,e);
    if(flag)
    {
        printf("第1个元素的值为：%d\n",e);
    }
    flag = put(T,2,96);
    if(flag)
    {
        printf("将T中第2个元素改为96，重新输出T为：");
        PrintT(T);
    }

    flag = IsAscending(T);
    if(flag)
        printf("T中元素是升序！\n");
    else if(flag = IsDescending(T))
        printf("T中元素是降序！\n");
    else
        printf("T中元素无序！\n");

    flag = Max(T,e);
    if(flag)
    {
        printf("T中最大元素是：");
        PrintE(e);
    }
    flag = Min(T,e);
    if(flag)
    {
        printf("T中最小元素是：");
        PrintE(e);
    }
    DestroyTriplet(T);
    printf("销毁T后，T = %u\n",T);

    printf("\n");
    return 0;
}

Status InitTriplet(Triplet &T,ElemType v1,ElemType v2,ElemType v3)
{
    T = (ElemType*)malloc(3*sizeof(ElemType));
    if(!T)
        exit(-1);
    T[0] = v1,T[1] = v2,T[2] = v3;
    return OK;
}

Status DestroyTriplet(Triplet &T)
{
    free(T);
    T = NULL;
    return OK;
}

Status get(Triplet T,int i,ElemType &e)
{
    e = T[i-1];
    return OK;
}

Status put(Triplet &T,int i,ElemType e)
{
    T[i-1] = e;
    return OK;
}

Status IsAscending(Triplet T)
{
    return(T[0] <= T[1])&&(T[1] <= T[2]);
}

Status IsDescending(Triplet T)
{
    return(T[0] >= T[1])&&(T[1] >= T[2]);
}

Status Max(Triplet T,ElemType &e)
{
    e = (T[0] >= T[1])?(T[0] >= T[2]?T[0]:T[2]):(T[1] >= T[2]?T[1]:T[2]);
    return OK;
}

Status Min(Triplet T,ElemType &e)
{
    e = (T[0] <= T[1])?(T[0] <= T[2]?T[0]:T[2]):(T[1] <= T[2]?T[1]:T[2]);
    return OK;
}

void PrintE(ElemType e)
{
    printf("%d\n",e);
}

void PrintT(Triplet T)
{
    printf("%d,%d,%d\n",T[0],T[1],T[2]);
}
