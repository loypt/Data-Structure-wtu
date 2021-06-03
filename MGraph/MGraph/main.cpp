//
//  main.cpp
//  MGraph
//
//  Created by Loyio Hex on 6/3/21.
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

#define INFINITE 65535    // 最大值，用来表示网中的两个顶点不直接连接
#define MAX_VERTEX_NUM 26   // 最大顶点个数

// 顶点类型
typedef char VertexType;

/*
 * 顶点关系类型
 *
 * 在无权图中，该值通常为0或1，表示两顶点是否直接连通；
 * 在有权图中，该值通常为权值。
 */
typedef int VRType;

// 边的类型，每条边上可能有附加信息info
typedef struct ArcCell {
    VRType adj;  // 顶点关系，在有权图跟无权图中的含义不同
} ArcCell;

/* 图/网的数组(邻接矩阵)存储表示类型定义 */
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];               // 顶点向量
    ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵
    int vexnum, arcnum;                            // 图/网的顶点数和弧数
} MGraph;

Status CreateUDNetwork(MGraph* G);

int LocateVex(MGraph G, VertexType u);

Status DestroyGraph(MGraph* G);

void skipBlank(FILE* fp);

int main(int argc, const char * argv[]) {
    MGraph G;
    CreateUDNetwork(&G);
}


Status CreateUDNetwork(MGraph* G) {
    int i, j, k;
    ArcCell arcs = {INFINITE};    // 无向网每条边的初始值
    VertexType v1, v2;
    VRType w;
    
    printf("请输入无向网的顶点数：");
    scanf("%d", &((*G).vexnum));
    printf("请输入无向网的边数：");
    scanf("%d", &((*G).arcnum));

    // 录入顶点集
    printf("请录入 %d 个顶点，不同顶点之间用空格隔开：", (*G).vexnum);
    for(i = 0; i < (*G).vexnum; i++) {
        // 跳过空白，寻找下一个"可读"符号
        skipBlank(stdin);
        scanf("%c", &((*G).vexs[i]));
    }
    
    // 初始化无向网的邻接矩阵
    for(i = 0; i < (*G).vexnum; i++) {
        for(j = 0; j < (*G).vexnum; j++) {
            (*G).arcs[i][j] = arcs;
        }
    }
    
    // 仅在控制台录入信息时输出此提示
    if((*G).arcnum != 0) {
        printf("请为无向网依次录入 %d 条边(带权值)的信息，顶点及权值之间用空格隔开：\n", (*G).arcnum);
    }
    
    // 录入边的信息
    for(k = 0; k < (*G).arcnum; k++) {
        printf("第 %2d 条边及其权值：", k + 1);
        skipBlank(stdin);   // 跳过空白，寻找下一个可读符号
        scanf("%c", &v1);
        skipBlank(stdin);   // 跳过空白，寻找下一个可读符号
        scanf("%c", &v2);
        scanf("%d", &w);
        
        i = LocateVex(*G, v1);  // 获取顶点v1在顶点集中的位置
        j = LocateVex(*G, v2);  // 获取顶点v2在顶点集中的位置
        
        (*G).arcs[i][j].adj = w;
        
        // 填充对称点
        (*G).arcs[j][i] = (*G).arcs[i][j];
    }
    
    return OK;
}

/*
 * 查找
 *
 * 返回顶点u在图/网中的位置
 */
int LocateVex(MGraph G, VertexType u) {
    int i;
    
    for(i = 0; i < G.vexnum; i++) {
        if(G.vexs[i] == u) {
            return i;
        }
    }
    
    return -1;
}

Status DestroyGraph(MGraph* G) {
    (*G).vexnum = 0;
    (*G).arcnum = 0;
    
    return OK;
}


void skipBlank(FILE* fp) {
    int ch;
    if(fp == NULL) {
        return;
    }
    while((ch = getc(fp)) != EOF) {
        if(ch >= 0 && ch <= 127) {
            if(ch != '\r' && ch != '\n' && ch != ' ' && ch != '\t' && ch != '\f') {
                ungetc(ch, fp);
                break;
            }
        }
    }
}



