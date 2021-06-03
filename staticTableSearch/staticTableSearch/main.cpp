//
//  main.cpp
//  staticTableSearch
//
//  Created by Loyio Hex on 6/3/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define Max 100

typedef int Status;

typedef int ElemType;            //关键字类型

//0号单元弃用
typedef struct
{
    ElemType elem[Max+1];        //数据元素存储空间基址，0号单元为空
    int length;                  //表长度
}Table;

void Create(Table *T);

int SeqSearch(Table T, ElemType x);

int BinarySearch(Table T, ElemType x);


int main(int argc, const char * argv[]) {
    Table T;
    
    
    Create(&T);
    printf("\n");
    
    printf("关键字 39 在有序查找表中的位序为（顺序查找）：");
    printf("%d\n", SeqSearch(T, 39));
    printf("\n");
    
    printf("关键字 39 在有序查找表中的位序为(通过折半查找算法)：");
    printf("%d\n", BinarySearch(T, 39));
    printf("\n");
    return 0;
}

void Create(Table *T)
{
    int i, n;
     
    printf("请输入元素个数：");
    scanf("%d", &n);
    while (n > Max || n < 1)
    {
        printf("个数超出范围，重新输入：");
        scanf("%d", &n);
    }
    T->length = n;
 
    printf("请依次输入元素值：\n");
    for (i = 1; i <= T->length; i++)
        scanf("%d", &(T->elem[i]));
}

int SeqSearch(Table T, ElemType x)
{
    int i = 1;
    
    while (i <= T.length && T.elem[i] != x) i++;
    if (i <= T.length) return i;
    return 0;
}

int BinarySearch(Table T, ElemType x)
{
    int low, mid, high;
 
    low = 1; high = T.length;
    while (low <= high)
    {
        mid = (high + low) / 2;
 
        if (x == T.elem[mid]) return mid;
        else if (x < T.elem[mid]) high = mid - 1;
        else low = mid + 1;
    }
    
    return 0;
}
