//
//  main.c
//  单向循环链表
//
//  Created by Hao on 2020/4/14.
//  Copyright © 2020 LYG. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 // 存储空间初始分配量

typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int ElemType;// ElemType类型根据实际情况而定，这里假设为int

// 定义结点
typedef struct Node{
    ElemType data;
    struct Node *next;
}Node;

typedef Node * LinkList;

/*
 3.1 循环链表创建! （不考虑头结点，头指针指向的是首元结点）
 2种情况:① 第一次开始创建; ②已经创建,往里面新增数据
 
 1. 判断是否第一次创建链表
    YES->创建一个新结点,并使得新结点的next 指向自身; (*L)->next = (*L);
    NO-> 找链表尾结点,将尾结点的next = 新结点. 新结点的next = (*L);
 */
Status CreateList(LinkList *L){
    LinkList temp = NULL;
    LinkList target = NULL;
    printf("输入节点的值，输入0结束\n");
    int n;
    while (1) {
        scanf("%d",&n);
        if(n==0) break;
        
        //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己（首元结点） (*head)->next=*head;
        if(*L==NULL){
            *L = (LinkList)malloc(sizeof(Node));
            if(!L) return ERROR;
            (*L)->data = n;
            (*L)->next = (*L);
        } else {
            
            //输入的链表不是空的，寻找链表的尾节点，使尾节点的next=新节点。新节点的next指向首元节点
            // 找尾结点target
            target = (*L);
            while (target->next != (*L)) {
                target = target->next;
            }
            
            temp = (LinkList)malloc(sizeof(Node));
            if (!temp) return ERROR;
            temp->data = n;
            temp->next = (*L);      //新节点指向首元节点
            target->next = temp;    //尾节点指向新节点
        }
    }
    
    return OK;
}
//  方法2
Status CreateList2(LinkList *L){
    LinkList temp = NULL;
    LinkList target = NULL;
    printf("输入节点的值，输入0结束\n");
    int n;
    while (1) {
        scanf("%d",&n);
        if(n==0) break;
        
        //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己（首元结点） (*head)->next=*head;
        if(*L==NULL){
            *L = (LinkList)malloc(sizeof(Node));
            if(!L) return ERROR;
            (*L)->data = n;
            (*L)->next = (*L);
            target = (*L);
        } else {
            
            temp = (LinkList)malloc(sizeof(Node));
            if (!temp) return ERROR;
            temp->data = n;
            temp->next = (*L);      //新节点指向首元节点
            target->next = temp;    //尾节点指向新节点
            
            target = temp;      //目标结点 指向尾结点
        }
    }
    
    return OK;
}

//3.3 循环链表插入数据
Status ListInsert(LinkList *L, int place, ElemType num){
    
    LinkList temp, target;
    
    if (place==1) {
        // 如果插入的位置为0,则属于插入首元结点,所以需要特殊处理
        // 创建新结点
        temp = (LinkList)malloc(sizeof(Node));
        
        if (!temp) return ERROR;
        temp->data = num;
        // 新结点后继指向 首元结点
        temp->next = *L;
        // 找到尾结点
        for(target = (*L); target->next != (*L); target = target->next);
        // 尾结点后继指向 新结点temp
        target->next = temp;
        // 头指针指向 该新结点
        *L = temp;
    } else {
        //如果插入的位置在其他位置;
        temp = (LinkList)malloc(sizeof(Node));
        if (!temp) return ERROR;
        temp->data = num;
        // 判断插入位置大于链表长度，则插入到尾结点之后
        int length;
        for(target = (*L), length = 1; target->next != *L; target = target->next, length++);
        if (place > length) {
            // 此时target为尾结点， *L即为target->next
            // 新结点后继指向首元结点
            temp->next = *L;
            // 尾结点后继指向新结点
            target->next = temp;
        } else {
            // 找到插入位置的前一个结点
            for(target = (*L), length = 1; length != place-1; target = target->next, length++);
            // 新结点后继指向 插入位置的后继结点
            temp->next = target->next;
            // c待插入位置的后继 指向新结点
            target->next = temp;
        }
        
        /*
         // 以上if判断可以合并成以下
         int length;
         for (target = (*L), length = 1; target->next != *L && length != place-1; target = target->next,length++);
         temp->next = target->next;
         target->next = temp;
         */
        
    }
    
    return OK;
}

//3.4 循环链表删除元素
Status LinkListDelete(LinkList *L,int place){
        
    LinkList temp, target;
    int length;
    temp = *L;
    
    if (*L == NULL) return ERROR;
    // 如果待删除位置是首元结点
    if (place == 1) {
        //.如果删除到只剩下首元结点了,则直接将*L置空;
        if (temp->next == *L) {
            *L = NULL;
            return OK;
        }
        //.如果链表还有很多数据,但是删除的是首结点;
        // 找到尾结点
        for(target = (*L); target->next != (*L); target = target->next);
        // 尾结点的后继 指向 首元结点的后继
        target->next = (*L)->next;
        // 将首元结点 赋给 temp
        temp = (*L);
        // 将头指针 指向 原首元结点的后继
        (*L) = (*L)->next;
        // 释放temp，即原首元结点
        free(temp);
        
    } else {
    // 待删除为非首元结点
        // 判断插入位置大于链表长度，则删除尾结点
        // 找到尾结点的前一个结点
        for(target = (*L), length = 1; target->next->next != *L; target = target->next, length++);
        if (place > length) {
            // 此时target为尾结点的前一个结点， *L即为target->next->next
            temp = target->next;
            // 尾结点的前一个结点后继指向 首元结点 *L
            target->next = *L; // 即temp->next
            free(temp);
        } else {
            // 找到删除位置的前一个结点
            for(target = (*L), length = 1; length != place-1; target = target->next, length++);
            // temp 为待删除结点
            temp = target->next;
            // 待删除结点的前一个结点 的后继 指向待删除结点的后继结点
            target->next = temp->next;
            // 释放待删除结点
            free(temp);
        }
    }
    
    return OK;
}

//3.5 循环链表查询值
int findValue(LinkList L,ElemType value){
    int i = 1;
    LinkList p;
    p = L;
    
    //寻找链表中的结点 data == value
    do {
        p = p->next;
        i++;
    } while (p->data!=value && p->next != L);
    
    //没找到值
    if (p->next == L && p->data != value) {
        return  -1;
    }
    
    return i;
}

//3.6 遍历循环链表，循环链表的遍历最好用do while语句，因为头节点就有值
Status printList(LinkList L) {
    
    printf("开始遍历链表结点数据：\n");
    //如果链表是空
    if(L == NULL){
        printf("打印的链表为空!\n");
    }else {
        
        LinkList p = L;
        do {
            printf("%5d\n", p->data);
            p = p->next;
        }while (p!= L);
        
        /*
         第二种遍历方式
         */
//        LinkList p = L;
//        while (p->next != L) {
//            printf("%5d",p->data);
//            p = p->next;
//        }
//        // 最后尾结点需要单独打印
//        printf("%5d\n",p->data);
        

        /*
        第三种遍历方式
        */
//        for (LinkList p = L; p->next!=L; p=p->next) {
//            printf("%5d\n", p->data);
//        }
//        // 最后尾结点需要单独打印
//        printf("%5d\n", p->data);

        printf("\n");
    }
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 单向循环链表\n");
    
    LinkList L1, L2;
    int iStatus;
    int place,num;

    
    // 创建循环链表
    printf("创建循环链表\n");
    iStatus = CreateList(&L1);
    iStatus = CreateList2(&L2);
    printf("原始的链表：\n");
    printList(L1);
    
    //3.3 循环链表插入数据
    printf("循环链表插入数据\n");
    printf("输入要插入的位置和数据用空格隔开：");
    scanf("%d %d",&place,&num);
    iStatus = ListInsert(&L1,place,num);
    printList(L1);
    
    //3.4 循环链表删除元素
    printf("循环链表删除元素\n");
    printf("输入要删除的位置：");
    scanf("%d",&place);
    LinkListDelete(&L1, place);
    printList(L1);
    
    //3.5 循环链表查询值
    printf("输入你想查找的值:");
    scanf("%d",&num);
    place=findValue(L1,num);
    if(place!=-1)
        printf("找到的值的位置是place = %d\n",place);
    else
        printf("没找到值\n");

    return 0;
}
