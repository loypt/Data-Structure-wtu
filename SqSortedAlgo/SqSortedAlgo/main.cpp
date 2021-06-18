//
//  main.cpp
//  SqSortedAlgo
//
//  Created by Loyio Hex on 6/18/21.
//

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

#define  MAXSIZE  20
typedef  int  KeyType;

#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

typedef struct
{
    KeyType key;
    char color[10];
}RedType;

typedef struct
{
    RedType r[MAXSIZE+1];// r[0] 闲置
    int length;
}SqList;


void PrintKey(KeyType e);
Status CreateSortList(FILE *fp, SqList *L);
void Traverse(SqList L, void(Visit)(KeyType));



//直接插入排序
void InsertSort(SqList *L);

// 冒泡排序
void BubbleSort(SqList *L);

// 简单选择排序
void SelectSort(SqList *L);
int SelectMinKey(SqList L, int i);

int Scanf(FILE *fp, char *format, ...);

int main(int argc, const char * argv[]) {
    SqList L;
                
    printf("创建并输出一个任意序列...\n");
    FILE *fp;
    
    fp = fopen("TestData.txt", "r");
    CreateSortList(fp, &L);
    Traverse(L, PrintKey);
    printf("\n");
        
    printf("直接插入排序测试...\n");    //1.函数InsertSort测试
    printf("将关键字按递增顺序排列...\n");
    InsertSort(&L);
    Traverse(L, PrintKey);
    printf("\n");
    
    printf("冒泡排序 测试...\n");                    //1.函数BubbleSort测试
    printf("将关键字按递增顺序排列...\n");
    BubbleSort(&L);
    Traverse(L, PrintKey);
    printf("\n");
    
    
    printf("简单选择排序测试...\n");                    //1、2.函数SelectSort等测试
    printf("将关键字按递增顺序排列...\n");
    SelectSort(&L);
    Traverse(L, PrintKey);
    printf("\n");
    
    
            
    return 0;
}

void PrintKey(KeyType e)
{
    printf("%d ", e);
}

Status CreateSortList(FILE *fp, SqList *L)
{
    int i;
    
    Scanf(fp, "%d", &((*L).length));
    
    if((*L).length>MAXSIZE)
        return ERROR;

    for(i=1; i<=(*L).length; i++)
        Scanf(fp, "%d", &((*L).r[i].key));

    return OK;
}

void Traverse(SqList L, void(Visit)(KeyType))
{
    int i;
    
    for(i=1; i<=L.length; i++)
        Visit(L.r[i].key);
    
    printf("\n");
}


//插入排序
void InsertSort(SqList *L)
{
    int i, j;
    
    for(i=2; i<=(*L).length; i++)
    {
        if(LT((*L).r[i].key, (*L).r[i-1].key))        //"<"，需将L.r[i]插入有序子表
        {
            (*L).r[0] = (*L).r[i];                    //复制为哨兵
            (*L).r[i] = (*L).r[i-1];
            for(j=i-1; LT((*L).r[0].key, (*L).r[j].key); --j)
                (*L).r[j+1] = (*L).r[j];            //记录后移
            (*L).r[j+1] = (*L).r[0];                //插入到正确位置
        }
    }
}

// 冒泡排序
void BubbleSort(SqList *L)
{
    int i, j;
    RedType tmp;
    Status tag;
    
    for(i=(*L).length; i>=2; i--)
    {
        tag = FALSE;                    //tag标记遍历过程是否发生的交换
        
        for(j=1; j<=i-1; j++)
        {
            if(LT((*L).r[j+1].key, (*L).r[j].key))
            {
                tmp = (*L).r[j+1];
                (*L).r[j+1] = (*L).r[j];
                (*L).r[j] = tmp;
                
                tag = TRUE;                //若遍历不发生交换，说明序列已经有序
            }
        }
        
        if(!tag)
            break;
    }
}

// 简单选择排序
void SelectSort(SqList *L)
{
    int i, j;
    RedType tmp;
    
    for(i=1; i<(*L).length; i++)
    {
        j = SelectMinKey(*L, i);
        
        if(i!=j)
        {
            tmp = (*L).r[i];
            (*L).r[i] = (*L).r[j];
            (*L).r[j] = tmp;
        }
    }
}

int SelectMinKey(SqList L, int i)
{
    int min, k;
    
    min = i;
    L.r[0] = L.r[i];
    
    for(k=i; k<=L.length; k++)
    {
        if(L.r[k].key<L.r[0].key)
        {
            min = k;
            L.r[0] = L.r[k];
        }
    }
    
    return min;
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
