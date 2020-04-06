//
//  main.c
//  线性表
//
//  Created by LIUYANG on 2020/4/5.
//  Copyright © 2020 LYG. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* ElemType类型根据实际情况而定，这里假设为int */
typedef int ElementType;
/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

/*线性结构使用顺序表的方式存储*/
// 连续内存空间

//顺序表结构设计
typedef struct {
    ElementType *data;
    int length;
} Sqlist;


// 1.1 顺序表初始化
// 修改链表本身，要传链表的地址 即*L。 只是打印，可以传L
// 函数入参 *L，则其属性 L->data。 函数入参 L （只读），则访问其属性为L.data
Status InitList(Sqlist *L){
    //为顺序表分配一个大小为MAXSIZE 的数组空间
    L->data = malloc(sizeof(ElementType) * MAXSIZE);
    //存储分配失败退出
    if (!L->data) return ERROR;
    //空表长度为0
    L->length = 0;
    return OK;
}
// 1.2 顺序表的插入
Status ListInsert(Sqlist *L, int i, ElementType e) {
    //i值不合法判断
    if((i<1)||(i>L->length+1)) return ERROR;
    //存储空间已满
    if(L->length == MAXSIZE) return ERROR;
    //插入位置不在表尾，则先移动出空余位置
    if(i<=L->length) {
        for (int j=L->length-1; j>=i-1; j--) {
            L->data[j+1] = L->data[j];
        }
    }
    //将新元素e放到第i个位置
    L->data[i-1] = e;
    //长度+1
    L->length++;
    return OK;
}
//1.3 顺序表的取值
Status GetElem(Sqlist L, int i, ElementType *e) {
    //判断i值是否合理, 若不合理,返回ERROR
    if((i<1) || (i>L.length)) return ERROR;
    //data[i-1]单元存储第i个数据元素.
    *e = L.data[i-1];
    return OK;
}
//1.4 顺序表删除
/*
 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)
 操作结果: 删除L的第i个数据元素,L的长度减1
 */
Status ListDelete(Sqlist *L, int i) {
    //线性表为空
    if(L->length==0) return ERROR;
    //i值不合法判断
    if((i<1)||(i>L->length)) return ERROR;
    
    for(int j = i; j < L->length;j++){
        //被删除元素之后的元素向前移动即可，在顺序存储时可以这样操作。
        //不用清除内存，只需把可访问的区域减少即可（length-1）
        //对于频繁添删元素的场景下，这种方式能够减少频繁申请释放内存的性能损耗
        //注意⚠️在链表存储时还需要释放该元素所占空间，否则野指针。
        L->data[j-1] = L->data[j];
    }
    //表长度-1;
    L->length--;
    
    return OK;
}

//1.5 清空顺序表（区别于销毁）
/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(Sqlist *L)
{
    //⚠️ 顺序表创建时，连续内存空间已经分配好了，只需要将length置为0，后面就不会被访问到了。
    // 因为插入、删除、查找等操作都会对参数有一个类似限制条件：if(i>L.length || i<1)，这样就保证了在把length设为0后，其他操作就不能访问到原来的那些元素，那么就可以认为length=0的表是空表
    //（实质上原来的元素还是在内存空间里的，如果直接用索引去访问，任然可以把元素读取出来的）
    L->length=0;
    return OK;
}
//1.6 销毁顺序表
// 销毁操作，则是把表的整个结构给消灭掉，把原来所占有的内存空间都给释放出来
Status DestroyList(Sqlist *L)
{
    if(L->data) {
        free(L->data);
        L->data = NULL;
        L->length = 0;
    } else {
        return ERROR;
    }
    return OK;

}

//1.7 判断顺序表清空
/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(Sqlist L)
{
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

//1.8 顺序表查找元素并返回位置
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(Sqlist L, ElementType e) {
    if(L.length == 0) return 0;
    
    int i;
    for (i=0; i<L.length; i++) {
        if(L.data[i]==e) break;
    }
    
    if(i>=L.length) return 0;
    
    return i+1;
}


//1.9 顺序输出List
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status PrinfList(Sqlist L){
    int i;
    for (i = 0; i < L.length; i++) {
        printf("%d\n",L.data[i]);
    }
    printf("\n");
    return OK;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, Data Structure!\n");
    printf("线性表顺序存储实现\n");
    
    Sqlist L;
    ElementType e;
    Status iStatus;
    
    //1.1 顺序表初始化
    iStatus = InitList(&L);
    printf("初始化L后: L.Length = %d\n", L.length);
    
    //1.2 顺序表数据插入
    for(int j=1; j <= 5;j++){
        iStatus = ListInsert(&L, 1, j);
    }
    printf("插入数据L长度: %d\n",L.length);
    PrinfList(L);
    
    //1.3 顺序表的取值
    int getIndex = 4;
    GetElem(L, getIndex, &e);
    printf("顺序表L第%d个元素的值为:%d\n",getIndex,e);
    
    //1.9 顺序表查找元素并返回位置
    int locate = LocateElem(L,4);
    printf("顺序表L元素值为4的位置在:%d\n",locate);


    //1.4 顺序表删除第2个元素
    ListDelete(&L, 2);
    printf("顺序表删除第%d元素,长度为%d\n",2,L.length);
    PrinfList(L);
    
    //1.5 清空顺序表
    iStatus = ClearList(&L);
    printf("清空后,L.length = %d\n",L.length);
    PrinfList(L);
    
    //1.6 判断List是否为空
    iStatus=ListEmpty(L);
    printf("L是否空：%d(1:是 0:否)\n",iStatus);

    return 0;
}
