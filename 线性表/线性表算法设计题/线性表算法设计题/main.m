//
//  main.m
//  线性表算法设计题
//
//  Created by Hao on 2020/4/17.
//  Copyright © 2020 LYG. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

//定义结点
typedef struct Node{
    ElemType data;
    struct Node *next;
}Node;

typedef struct Node * LinkList;

//2.1 初始化单链表线性表
Status InitList(LinkList *L){
    
    //产生头结点,并使用L指向此头结点
    *L = (LinkList)malloc(sizeof(Node));
    //存储空间分配失败
    if(*L == NULL) return ERROR;
    //将头结点的指针域置空
    (*L)->next = NULL;
    
    return OK;
}

//2.2 单链表插入
/*
 初始条件:顺序线性表L已存在,1≤i≤ListLength(L);
 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1;
 */
Status ListInsert(LinkList *L,int i,ElemType e){
    
    int j;
    LinkList p,s;
    p = *L;
    j = 1;
    
    //寻找第i个结点
    while (p && j<i) {
        p = p->next;
        ++j;
    }
    
    //第i个元素不存在
    if(!p || j>i) return ERROR;
    
    //生成新结点s
    s = (LinkList)malloc(sizeof(Node));
    //将e赋值给s的数值域
    s->data = e;
    //将p的后继结点赋值给s的后继
    s->next = p->next;
    //将s赋值给p的后继
    p->next = s;
    
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        printf("%d  ",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p,q;
    p=(*L)->next;           /*  p指向第一个结点 */
    while(p)                /*  没到表尾 */
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;        /* 头结点指针域为空 */
    return OK;
}
int main(int argc, const char * argv[]) {
    printf("Hello, World!");
    
    
    return 0;
}
