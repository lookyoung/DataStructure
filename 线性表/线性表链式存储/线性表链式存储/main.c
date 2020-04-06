//
//  main.c
//  线性表链式存储
//
//  Created by LIUYANG on 2020/4/6.
//  Copyright © 2020 LYG. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

#define MAXSIZE 20 /* 储存空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

// 定义结点
typedef struct Node{
    ElemType data;// 数据域
    struct Node *next;// 指针域
}Node;

// 方便写法，LinkList和Node等价
typedef struct Node * LinkList;

//2.1 初始化单链表线性表
Status InitList(LinkList *L){
    //产生头结点,并使用L指向此头结点
    // 头结点主要作用是辅助增删改查，标志位结点。其后继为首元结点
    *L = (LinkList)malloc(sizeof(Node));
    //存储空间分配失败
    if(*L==NULL) return ERROR;
    //将头结点的指针域置空
    (*L)->next = NULL;
    
    return OK;
}
//2.9
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status PrintfList(LinkList L) {
    // L ：头结点，  L->next ：首元结点
    LinkList p = L->next;
    
    while (p) {
        printf("%d\n",p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 线性表链式存储\n");

    Status iStatus;
    LinkList L1,L;
    struct Node *L2;
    ElemType e;
    
    //2.1 单链表初始化
    iStatus = InitList(&L);
    printf("L 是否初始化成功?(0:失败,1:成功) %d\n",iStatus);

    
    return 0;
}
