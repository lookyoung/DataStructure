//
//  main.c
//  双向链表
//
//  Created by Hao on 2020/4/15.
//  Copyright © 2020 LYG. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define ERROR 0
#define OK  1
#define FALSE 0
#define TRUE 1

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

//定义结点
typedef struct Node{
    ElemType data;  //数据域
    struct Node *prior; //前驱指针
    struct Node *next;  //后继指针
}Node;

typedef Node* LinkList;

//5.1 创建双向链接
Status createLinkList(LinkList *L){
    // 创建头结点
    (*L) = (LinkList)malloc(sizeof(Node));
    if (!(*L)) {
        return ERROR;
    }
    (*L)->data = -1;
    (*L)->prior = NULL;
    (*L)->next = NULL;
    
    // 新增数据 (后插法)
    LinkList p = (*L);
    for (int i = 1; i<10; i++) {
        //1.创建1个临时的结点
        LinkList temp = (LinkList)malloc(sizeof(Node));
        if (!temp) {
            return ERROR;
        }
        temp->data = i;
        //2.为新增的结点建立双向链表关系
        //① temp的前驱是p
        temp->prior = p;
        temp->next = NULL;
        //② temp 是p的后继
        p->next = temp;
        //③ p 要记录最后的结点的位置,方便下一次插入
        p = temp;
    }
    
    
    return OK;
}

//5.2 打印循环链表的元素
void printLinkList(LinkList L){
    LinkList temp = L->next;
    if (temp == NULL) {
        printf("打印的双向链表为空!\n");
        return ;
    }
    
    while (temp) {
        printf(" %d  ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}
//5.3 双向链表插入元素
Status ListInsert(LinkList *L, int i, ElemType data){
    //1. 插入的位置不合法 为0或者为负数
    if (i<1) {
        printf("插入的位置不合法\n");
        return ERROR;
    }
    
    //2. 新建结点
    LinkList temp = (LinkList)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    temp->prior = NULL;
    
    //3. 将p指向头结点
    LinkList p = (*L);
    //4. 查找待插入位置的前一个结点
    for (int j=1; j<i && p; j++) {
        p = p->next;
    }
    //5. 如果插入的位置超过链表本身的长度
    if (p == NULL) {
        printf("插入的位置超出链表本身\n");
        return ERROR;
    }
    //6. 判断插入位置是否为链表尾部; 即判断是否尾结点
    if (p->next == NULL) {
        p->next = temp;
        temp->prior = p;
    } else {
        LinkList nextNode = p->next;
        // ①将p->next 结点的前驱prior = temp
        nextNode->prior = temp;
        // ②将temp->next 指向原来的p->next
        temp->next = nextNode;
        // ③p->next 更新成新创建的temp
        p->next = temp;
        // ④新创建的temp前驱 = p
        temp->prior = p;
    }
    
    return OK;
}
//5.4 删除双向链表指定位置上的结点
Status ListDelete(LinkList *L, int i, ElemType *e){
    // 判断双向链表是否为空,如果为空则返回ERROR;
    if (*L == NULL) {
        printf("双向链表为空\n");
        return ERROR;
    }
    // 删除位置不合法
    if (i<1) {
        printf("删除位置不合法，需>0\n");
        return ERROR;
    }
    // 将p指向头结点
    LinkList p = (*L);
    // 找到待删除位置的结点
    for (int j = 0; j<i && p; j++) {
        p = p->next;
    }
    // 插入的位置超出链表本身
    if (p == NULL) {
        printf("插入的位置超出链表本身\n");
        return ERROR;
    }
    // 将待删除结点的data 赋值给*e,带回到main函数
    *e = p->data;
    
    // 判断待删除结点是否尾结点
    if (p->next == NULL) {
        // 删除尾结点 只需要将前一个结点的后继置为NULL即可
        p->prior->next = NULL;
    } else {
        // 待删不是尾结点，则将待删结点的前驱结点后继 指向 待删结点的后继结点
        p->prior->next = p->next;
        // 将待删结点的后继结点的前驱 指向 待删结点的前驱
        p->next->prior = p->prior;
    }
    // 释放待删除结点
    free(p);
    
    return OK;
}

//5.5 删除双向链表指定的元素
Status LinkListDeletVAL(LinkList *L, ElemType data){
    // 链表判空
    if (*L == NULL) {
        printf("双向链表为空\n");
        return ERROR;
    }
    
    // 链表遍历 找到待删结点
    LinkList p = (*L);// 头结点
    for (int i = 1; p != NULL; p = p->next, i++) {
        if (p->data == data) {
            // 待删结点 的前驱结点的后继 指向 待删结点的后继结点
            p->prior->next = p->next;
            // 判断待删结点是否尾结点
            if (p->next != NULL) {
                // 不是尾结点，则将待删结点的 后继结点的前驱 指向 戴珊结点的前驱
                p->next->prior = p->prior;
            }
            // 释放待删结点
            free(p);
            // 退出遍历
            break;
        }
    }
    return OK;
}
//5.6.1 在双向链表中查找元素位置
int selectElem(LinkList L,ElemType elem){
    // 链表判空
    if (L == NULL) {
        printf("双向链表为空\n");
        return -1;
    }
    // 遍历
    LinkList p = L;
    int i = 0;
    while (p) {
        if (p->data == elem) {
            return i;
        }
        p = p->next;
        i++;
    }
    return -1;
}


//5.6.2 在双向链表中更新结点
Status replaceLinkList(LinkList *L,int index,ElemType newElem){
    // 链表判空
    if (*L == NULL) {
        printf("链表为空\n");
        return ERROR;
    }
    // 遍历
    LinkList p = (*L);
    for (int i = 1; p != NULL; i++) {
        p = p->next;
        // 注意边界条件
        if (i == index && p != NULL) {
            p->data = newElem;
            return OK;
        }
    }
    return ERROR;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, 双向链表\n");
    
    Status iStatus = 0;
    LinkList L;
    int temp,item,e;

    
    iStatus =  createLinkList(&L);
    printf("iStatus = %d\n",iStatus);
    printf("链表创建成功,打印链表:\n");
    printLinkList(L);
    
//    printf("请输入插入的位置和数值以空格隔开\n");
//    scanf("%d %d",&temp,&item);
//    iStatus = ListInsert(&L, temp, item);
//    printf("插入数据,打印链表:\n");
//    printLinkList(L);
    
//    printf("请输入删除的位置\n");
//    scanf("%d",&temp);
//    iStatus = ListDelete(&L, temp, &e);
//    if (iStatus == ERROR) {
//        printf("删除操作失败\n");
//    } else {
//        printf("删除元素: 删除位置为%d,data = %d\n",temp,e);
//        printf("删除操作之后的,双向链表:\n");
//    }
//    printLinkList(L);
    
//    printf("请输入你要删除的内容\n");
//    scanf("%d",&temp);
//    iStatus = LinkListDeletVAL(&L, temp);
//    if (iStatus == ERROR) {
//        printf("删除操作失败\n");
//    } else {
//        printf("删除指定data域等于%d的结点,双向链表:\n",temp);
//        printf("删除操作之后的,双向链表:\n");
//    }
//    printLinkList(L);

//    printf("请输入你要查找的内容\n");
//    scanf("%d",&temp);
//    ElemType index = selectElem(L, temp);
//    printf("在双向链表中查找到数据域为%d的结点,位置是:%d\n",temp,index);
    
    printf("请输入你要更新的结点以及内容\n");
    scanf("%d %d",&temp,&item);
    iStatus = replaceLinkList(&L, temp, item);
    printf("更新结点数据后的双向链表:\n");
    printLinkList(L);
    return 0;
}
