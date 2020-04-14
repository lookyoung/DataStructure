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

//2.1 初始化单链表线性表（带头结点）
Status InitList(LinkList *L){
    //产生头结点,并使用L指向此头结点
    //头结点主要作用是辅助增删改查，标志位结点。其后继为首元结点
    *L = (LinkList)malloc(sizeof(Node));
    //申请存储空间失败
    if(*L==NULL) return ERROR;
    //将头结点的指针域置空
    (*L)->next = NULL;
    
    return OK;
}
//2.1 初始化单链表线性表（不带头结点）
void InitLinkList2(LinkList L)
{
  L=NULL;
}

//2.2 单链表插入
/*
 初始条件:链式线性表L已存在,1≤i≤ListLength(L);
 操作结果：在L中第i个位置之后插入新的数据元素e，L的长度加1;
 */
Status ListInsert(LinkList *L, int i, ElemType e) {
    // 寻找第i个结点
    LinkList p, s;
    p = *L;
    for (int j = 1; j<i; j++) {
        p = p->next;
    }
    //第i个元素不存在
    if (!p) return ERROR;
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

//2.3 单链表取值
/*
 初始条件: 链式线性表L已存在,1≤i≤ListLength(L);
 操作结果：用e返回L中第i个数据元素的值
 */
Status GetElem(LinkList L,int i,ElemType *e){
    //j: 计数.
    int j;
    //声明结点p;
    LinkList p;
    //将结点p 指向链表L的第一个结点;
    p = L->next;
    //j计算=1;
    j = 1;
    
    //p不为空,且计算j不等于i,则循环继续
    while (p && j<i) {
        //p指向下一个结点
        p = p->next;
        ++j;
    }
    
    //如果p为空或者j>i,则返回error
    if(!p || j>i) return ERROR;
    
    //e = p所指的结点的data
    *e = p->data;
    return OK;
}

//2.4 单链表删除元素
/*
 初始条件：链式线性表L已存在，1≤i≤ListLength(L)
 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
 */

Status ListDelete(LinkList *L,int i,ElemType *e){
    int j;
    LinkList p,q;
    
    p = (*L)->next;
    j = 1;
    //查找第i-1个结点,p指向该结点
    while (p->next && j<i-1) {
        p = p->next;
        ++j;
    }
    //当i>n 或者 i<1 时,删除位置不合理
    if (!(p->next) || j>i-1) return ERROR;
    //q指向要删除的结点
    q = p->next;
    //将q的后继赋值给p的后继
    p->next = q->next;
    //将q结点中的数据给e
    *e = q->data;
    //让系统回收此结点,释放内存;
    free(q);
    
    return OK;
}
//2.5 清空链表
/* 初始条件：链式线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L) {
    LinkList p, q;
    // p指向第一个节点
    p = (*L)->next;
    // 若为空表
    if(p == NULL) return OK;
    // 没到表尾
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    
    // 头结点指针域为空
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

//2.6 单链表头插法
/* 随机产生n个元素值,建立带表头结点的单链线性表L(头插法)*/
void CreateListHead(LinkList *L, int n) {
    // 创建头结点
    *L = (LinkList)malloc(sizeof(Node));
    // 头结点后继为NULL
    (*L)->next = NULL;
    
    LinkList p;
    for (int i=1; i<=n; i++) {
        //生成新结点
        p = (LinkList)malloc(sizeof(Node));
        //i赋值给新结点的data
        p->data = i;
        //p->next = 头结点的L->next
        p->next = (*L)->next;
        //头结点后继指向该节点p
        (*L)->next = p;
    }
}
//2.7 单链表尾插法
/* 随机产生n个元素值,建立带表头结点的单链线性表L(后插法)*/
void CreateListTail(LinkList *L, int n)  {
    // 创建头结点
    *L = (LinkList)malloc(sizeof(Node));
    // 头结点后继首元节点指向NULL
    (*L)->next = NULL;
    
    LinkList p, q;
    // 辅助节点 q = 头结点
    q = (*L);
    for (int i = 1; i<=n; i++) {
        // 生成新节点
        p = (LinkList)malloc(sizeof(Node));
        // 新节点赋值
        p->data = i;
        // 新节点后继指向NULL
        p->next = NULL;
        // 辅助节点q 后继指向新节点p
        q->next = p;
        // 辅助节点后移，即q=p
        q = p;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 线性表链式存储\n");

    Status iStatus;
    LinkList L;
    ElemType e;
    
    //2.1 单链表初始化
    iStatus = InitList(&L);
    printf("L 是否初始化成功?(0:失败,1:成功) %d\n",iStatus);

    //2.2 单链表插入数据
    for(int j = 1;j<=10;j++)
    {
        iStatus = ListInsert(&L, 1, j);
    }
    printf("L 插入后\n");
    PrintfList(L);
    
    //2.3 单链表取值
    GetElem(L, 4, &e);
    printf("L中第4个元素取值是 %d\n",e);
    
    //2.4 删除L中第3个元素
    ListDelete(&L, 3, &e);
    printf("删除L中第3个元素值 %d\n",e);
    printf("L 删除后\n");
    PrintfList(L);
    
    //2.5 清空链表
    iStatus = ClearList(&L);
    printf("清空链表(0:失败,1:成功) %d\n",iStatus);
    PrintfList(L);
    
    //2.6 头插法创建链表
    CreateListHead(&L, 8);
    printf("头插法创建链表\n");
    PrintfList(L);

    iStatus = ClearList(&L);
    printf("清空链表(0:失败,1:成功) %d\n",iStatus);
    
    //2.7 尾插法创建链表
    CreateListTail(&L, 9);
    printf("尾插法创建链表\n");
    PrintfList(L);
    
    return 0;
}
