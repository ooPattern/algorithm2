#include "list.h"

//栈的数据结构
typedef T_STACK_TBL T_LIST_TBL

//栈的宏定义
#define STACK_HEAD(pStack)  LIST_HEAD(pStack)//栈顶
#define STACK_TAIL(pStack)  LIST_TAIL(pStack)//栈底
#define STACK_SIZE(pStack)  LIST_SIZE(pStack)//栈的元素个数

//栈的初始化
int StackInit( T_STACK_TBL* pStack )
{
    ListInit( pStack );
}

//栈顶增加一个元素
int StackPush( T_STACK_TBL* pStack, void* pData )
{
    //相当于在链表头指针增加一个元素
    return ListInsertNext( pStack, NULL, pData );
}

//栈顶删除一个元素
int StackPop( T_STACK_TBL* pStack, void** pData )
{
    //相当于在链表头指针删除一个元素
    return ListRemoveNext( pStack, NULL, pData );
}

//清空栈
void StackDestory( T_STACK_TBL* pStack )
{
    ListDestory( pStack );
}
