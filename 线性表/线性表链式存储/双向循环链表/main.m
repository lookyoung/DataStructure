//
//  main.m
//  双向循环链表
//
//  Created by Hao on 2020/4/17.
//  Copyright © 2020 LYG. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define OK  1
#define FALSE 0
#define TRUE 1

#define MAXSIZE 20 /* 存储空间初始分配量 */
typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

//  定义结点
typedef struct Node {
    ElemType data;
    struct Node *prior;
    struct Node *next;
}Node;

typedef Node * LinkList;
//  注意:循环链表尾结点的后继指针 指向头结点，如果没有头结点，则指向首元结点。
// 1. 双向循环链表初始化（尾插法）
Status creatLinkList(LinkList *L){
    *L = (LinkList)malloc(sizeof(Node));

    if (*L == NULL) {
        return ERROR;
    }
    (*L)->data = -1;
    (*L)->next = *L;
    (*L)->prior = *L;

    LinkList p = (*L);// 头结点
    for (int i=1; i<10; i++) {
        // 尾插法： 将新结点 加到链表尾，变成尾结点
        LinkList temp = (LinkList)malloc(sizeof(Node));
        temp->data = i;
        // 新结点prior指向是链表尾
        temp->prior = p;
        // 新结点next 要指向链表头结点
        temp->next = (*L);
        // 新结点变成链表尾结点
        p->next = temp;
        // 将尾结点赋给p
        p = temp;
    }
    
    return OK;
}
// 2. 遍历打印链表
void printList(LinkList L){
    if (!L) {
        printf("链表为空\n");
        return;
    }
    
    LinkList p = L->next;//首元结点
    // 遍历链表 从首元结点到尾结点
    while (p != L) {
        printf(" %d", p->data);
        p = p->next;
    }
    printf("\n");
}
// 3. 双向循环链表插入元素
/*当插入位置超过链表长度则插入到链表末尾*/
Status LinkListInsert(LinkList *L, int index, ElemType data) {
    
    // 双向循环链表为空,则返回error
    if(*L == NULL) return ERROR;
    
    if(index < 1) return ERROR;
    
    // 创建指针p,指向双向链表头
    LinkList p = (*L);
    int i = 1;
    
    // 找到插入位置的前一个结点
    for (; i < index && p->next != (*L); i++) {
        p = p->next;
    }
    
    // 创建新节点
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if(temp == NULL) return ERROR;
    temp->data = data;
    // p后继的前驱指针 指向 temp
    p->next->prior = temp;
    // temp 后继指向 p后继
    temp->next = p->next;
    // temp前驱 指向 p
    temp->prior = p;
    // p后继 指向 temp
    p->next = temp;
    
    
    return OK;
}

// 4. 双向循环链表删除结点
Status LinkListDelete(LinkList *L,int index,ElemType *e){
    *e = -1;
    // 双向循环链表为空,则返回error
    if(*L == NULL) return ERROR;
    
    if(index < 1) return ERROR;
    
    // 创建指针p,指向双向链表头
    LinkList p = (*L);
    
    // 找到待删位置的结点
    for (int i = 0; i < index && p->next != (*L); i++) {
        p = p->next;
        
        // 超出链表长度，不删除处理
        if (i<index-1 && p->next==(*L)) {
            return ERROR;
        }
    }
    
    p->prior->next = p->next;
    p->next->prior = p->prior;
    
    *e = p->data;
    
    free(p);
    
    return OK;
}
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        printf("Hello, 双向循环链表\n");
        
        LinkList L;
        Status iStatus;
        ElemType temp,item;
        
        iStatus = creatLinkList(&L);
        printf("双向循环链表初始化是否成功(1->YES)/ (0->NO):  %d\n\n",iStatus);
        printList(L);
        
//        printf("输入要插入的位置和数据用空格隔开：");
//        scanf("%d %d",&temp,&item);
//        iStatus = LinkListInsert(&L,temp,item);
//        printList(L);
        
        printf("输入要删除位置：");
        scanf("%d",&temp);
        iStatus = LinkListDelete(&L, temp, &item);
        printf("删除链表位置为%d,结点数据域为:%d\n",temp,item);
        printList(L);

    }
    return 0;
}
