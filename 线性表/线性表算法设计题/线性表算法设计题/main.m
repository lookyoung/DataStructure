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

/*

作业1:
题目:
将2个递增的有序链表合并为一个有序链表; 要求结果链表仍然使用两个链表的存储空间,不另外占用其他的存储空间. 表中不允许有重复的数据

关键词:递增有序链表,不允许有重复数据,保留递增关系(后插法)
     不占用额外的存储空间指的是不能开辟新节点,赋值在链接到链表上;

算法思想:
(1)假设待合并的链表为La和Lb,合并后的新表使用头指针Lc(Lc的表头结点设为La的表头结点，“借腹生子”)指向. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
(2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时,依次摘取其中较小值重新链表在Lc表的最后.
(3)如果两个表中的元素相等,只摘取La表中的元素,删除Lb表中的元素,这样确保合并后表中无重复的元素;
(4)当一个表到达表尾结点为空时,非空表的剩余元素直接链接在Lc表最后.
(5)最后释放链表Lb的头结点;

*/
void MergeList(LinkList *La, LinkList *Lb, LinkList *Lc){
    LinkList pa,pb,pc;
    
    // 已知输入链表 的首元结点
    pa = (*La)->next;
    pb = (*Lb)->next;
    // 输出链表 指向链表La
    pc = (*Lc) = (*La);// pc此时为Lc头结点
    
    // 遍历两个已知链表 直到其中一个链表的结尾
    while (pa && pb) {
        // 如果链表La结点pa值 较小，则输出链表Lc的尾结点pc后继 指向pa
        if (pa->data < pb->data) {
            // 用pc->next 而不是pc = pa，是由于上面初始化的pc为头结点，pc->next为首元结点
            pc->next = pa;
            // 链表Lc的尾结点pc后移
            pc = pc->next;
            // 链表La的遍历结点pa后移
            pa = pa->next;
        } else if (pa->data > pb->data) {
            // Lb处理同上
            pc->next = pb;
            pc = pc->next;
            pb = pb->next;
        } else if (pa->data == pb->data) {
            // pa,pb结点值相等，则取pa，删pb，确保合并后表中无重复元素
            pc->next = pa;
            pc = pc->next;
            pa = pa->next;
            // 因为Lc是借La的链表头指针,所以对于没用的元素要释放Lb的结点pb
            LinkList temp = pb;
            pb = pb->next;
            free(temp);
        }
    }
    // 上面while遍历完后，可能还有非空表的剩余元素没遍历到，此时要将这些元素直接链接在Lc表的最后
    pc->next = pa ? pa : pb;
    // 释放Lb的头指针
    free(*Lb);
}
/*
 作业2:
 题目:
 已知两个链表A和B分别表示两个集合.其元素递增排列. 设计一个算法,用于求出A与B的交集,并存储在A链表中;
 例如:
 La = {2,4,6,8}; Lb = {4,6,8,10};
 Lc = {4,6,8}

 关键词:依次摘取2个表中相等的元素重新进行链接,删除其他不等的元素;

 
 算法思想:
 (1)假设待合并的链表为La和Lb,合并后的新表使用头指针Lc(Lc的表头结点设为La的表头结点)指向. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
 (2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时.
 (3)如果两个表中的元素相等,只摘取La表中的元素,删除Lb表中的元素;
 (4)如果其中一个表中的元素较小,删除此表中较小的元素. 此表的工作指针后移;
 (5)当链表La和Lb有一个先到达表尾结点为空时,依次删除另一个非空表中的所有元素,最后释放链表lb;

 */
void Intersection(LinkList *La, LinkList *Lb, LinkList *Lc){
    
    //目标: 求2个递增的有序链表La,Lb的交集, 使用头指针Lc指向带回;
    LinkList pa,pb,pc,temp;
    
    pa = (*La)->next;
    pb = (*Lb)->next;
    
    pc = (*Lc) = (*La);
    
    while (pa && pb) {
        if (pa->data == pb->data) {
            //相等,交集并入结果链表中; 取一个，删另一个。
            //(1).取La中的元素,将pa链接到pc的后面,pa指针后移;
            pc->next = pa;
            pc = pc->next;
            pa = pa->next;
            //(2)删除Lb中对应相等的元素
            temp = pb;
            pb = pb->next;
            free(temp);
        } else if (pa->data < pb->data) {
            // 不相等，谁小删除谁再后移
            temp = pa;
            pa = pa->next;
            free(temp);
            
        } else {
            temp = pb;
            pb = pb->next;
            free(temp);
        }
    }
    
    //Lb为空,删除非空表La中的所有元素
    while (pa) {
        
        temp = pa;
        pa = pa->next;
        free(temp);
    }
    
    //La为空,删除非空表Lb中的所有元素
    while (pb) {
        temp = pb;
        pb = pb->next;
        free(temp);
    }
    pc->next = NULL;
    free(*Lb);
}

/*
 作业3:
 题目:
 设计一个算法,将链表中所有节点的链接方向"原地旋转",即要求仅仅利用原表的存储空间. 换句话说,要求算法空间复杂度为O(1);
 例如:L={0,2,4,6,8,10}, 逆转后: L = {10,8,6,4,2,0};
  {2,0,4,6,8,10} ->{4,2,0,6,8,10} ->{6,4,2,0,8,10} ->{8,6,4,2,0,10} ->{10,8,6,4,2,0}
 关键词:【头插法 逆转链表】
 不能开辟新的空间,只能改变指针的指向; 可以考虑逐个摘取结点,利用前插法创建链表的思想,将结点一次插入到头结点的后面; 因为先插入的结点为表尾,后插入的结点为表头,即可实现链表的逆转;
 
 
 算法思想:
 (1)利用原有的头结点*L,p为工作指针, 初始时p指向首元结点. 因为摘取的结点依次向前插入,为确保链表尾部为空,初始时将头结点的指针域置空;
 (2)从前向后遍历链表,依次摘取结点,在摘取结点前需要用指针q记录后继结点,以防止链接后丢失后继结点;
 (3)将摘取的结点插入到头结点之后,最后p指向新的待处理节点q(p=q);
 */

void Inverse(LinkList *L){
        
    LinkList p = (*L)->next;//首元结点
    (*L)->next = NULL;
    
    // 不断把遍历的结点p移到首元结点前，也就是老的首元结点不断后移， 类似铰链
    while (p != NULL) {
        // 暂存p的后继结点
        LinkList temp = p->next;
        // p后继指向 原首元结点， 即 p移到首元结点前
        p->next = (*L)->next;
        // 首指针 指向p， 即 把p 当成新的首元结点
        (*L)->next = p;
        // 重新获取p的后继
        p = temp;
    }
}


/*
 作业4:
 题目:
 设计一个算法,删除递增有序链表中值大于等于mink且小于等于maxk(mink,maxk是给定的两个参数,其值可以和表中的元素相同,也可以不同)的所有元素;
 
 关键词: 通过遍历链表能够定位带删除元素的下边界和上边界, 即可找到第一个值大于mink的结点和第一个值大于等于maxk的结点;
 
 
 算法思想:
 (1)查找第一个值大于mink的结点,用q指向该结点,pre 指向该结点的前驱结点;
 (2)继续向下遍历链表, 查找第一个值大于等于maxk的结点,用p指向该结点;
 (3)修改下边界前驱结点的指针域, 是其指向上边界(pre->next = p);
 (4)依次释放待删除结点的空间(介于pre和p之间的所有结点);
 */

void DeleteMinMax(LinkList *L, int mink, int maxk){
    //目标: 删除递增有序链表L中值大于等于mink 和小于等于maxk的所有元素
    
    LinkList p,q,pre;
    pre = *L;
    LinkList temp;
    
    //p指向首元结点
    p = (*L)->next;
    
    //1.查找第一值大于mink的结点
    while (p && p->data < mink) {
        //指向前驱结点
        pre = p;
        p = p->next;
    }
    
    //2.查找第一个值大于等于maxk的结点
    while (p && p->data<=maxk) {
        p = p->next;
    }
    
    //3.修改待删除的结点指针
    q = pre->next;
    pre->next = p;
    
    while (q != p) {
        temp = q->next;
        free(q);
        q = temp;
    }
}


int main(int argc, const char * argv[]) {
    printf("线性表练习篇!\n");
    
    Status iStatus;
    LinkList La,Lb,Lc,L;
    InitList(&La);
    InitList(&Lb);
    
//   /*  ---------作业1--------*/
//    printf("******题目1:链表并集********\n");
//    //设计2个递增链表La,Lb
//    for(int j = 18;j>=0;j-=3)
//    {
//        iStatus = ListInsert(&La, 1, j);
//    }
//    printf("La:\n");
//    ListTraverse(La);
//
//    for(int j = 11;j>0;j-=2)
//    {
//        iStatus = ListInsert(&Lb, 1, j);
//    }
//    printf("Lb:\n");
//    ListTraverse(Lb);
//
//    MergeList(&La, &Lb, &Lc);
//    printf("Lc:\n");
//    ListTraverse(Lc);

//    /*---------作业2--------*/
//    printf("******题目2: 链表交集********\n");
//    ListInsert(&La, 1, 8);
//    ListInsert(&La, 1, 6);
//    ListInsert(&La, 1, 4);
//    ListInsert(&La, 1, 2);
//    printf("La:\n");
//    ListTraverse(La);
//
//    ListInsert(&Lb, 1, 10);
//    ListInsert(&Lb, 1, 8);
//    ListInsert(&Lb, 1, 6);
//    ListInsert(&Lb, 1, 4);
//    printf("Lb:\n");
//    ListTraverse(Lb);
//
//    Intersection(&La, &Lb, &Lc);
//    printf("Lc:\n");
//    ListTraverse(Lc);
    
    /*---------作业3--------*/
    printf("******题目3:********\n");
    InitList(&L);
    for(int j = 10;j>=0;j-=2)
    {
        iStatus = ListInsert(&L, 1, j);
    }
    printf("L逆转前:\n");
    ListTraverse(L);
    
    Inverse(&L);
    printf("L逆转后:\n");
    ListTraverse(L);
    
    return 0;
}
