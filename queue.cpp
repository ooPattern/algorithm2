#include "list.h"

//队列的数据结构
typedef T_QUEUE_TBL T_LIST_TBL

//队列的宏定义
#define QUEUE_HEAD(pQueue)  LIST_HEAD(pQueue)//队列头
#define QUEUE_TAIL(pQueue)  LIST_TAIL(pQueue)//队列尾
#define QUEUE_SIZE(pQueue)  LIST_SIZE(pQueue)//队列的元素个数

//队列的初始化
int StackInit( T_QUEUE_TBL* pQueue )
{
    ListInit( pQueue );
}

//队列尾部增加一个元素
int QueueEnqueue( T_QUEUE_TBL* pQueue, void* pData )
{
    //相当于在队列尾指针增加一个元素
    return ListInsertNext( pQueue, QUEUE_TAIL( pQueue ), pData );
}

//队列头部删除一个元素
int QueueDequeue( T_QUEUE_TBL* pQueue, void** pData )
{
    //相当于在队列头指针删除一个元素
    return ListRemoveNext( pQueue, NULL, pData );
}

//清空队列
void QueueDestory( T_QUEUE_TBL* pQueue )
{
    ListDestory( pQueue );
}
