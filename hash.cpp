#include "list.h"

//哈希表的数据结构
typedef struct t_hashTbl 
{
    int size;//哈希表的元素个数
    int buckets;//桶的数量
    T_LIST_TBL *pList;//链式哈希表,最多有buckets个链表        
    int ( *hashKey )( void* pKey );//计算哈希键值的函数
    int ( *hashMatch )( void* pKey1, void *pKey2 );//匹配2个元素是否相同    
} T_HASH_TBL;

//初始化哈希表
int HashInit( T_HASH_TBL* pHash, int buckets )
{
    if( ( NULL == pHash ) || ( buckets <= 0 ) )
    {
        return -1;
    }
    //根据桶的数量创建链表,桶的数据量由负载因子计算得出
    if( NULL == ( pHash->pList = malloc( buckets * sizeof( T_LIST_TBL ) ) ) )
    {
        return -1;
    }
    //刚开始哈希表没有一个元素,链式哈希表没有限制元素的个数,可能会导致搜索较慢
    pHash->size = 0;
    pHash->buckets = buckets;
    pHash->hashKey = NULL;
    pHash->match = NULL;
    return 0;
}

//计算哈希键值
int HashKey( void* pKey )
{
    if( NULL == pKey )
    {
        return -1;
    }
    //计算哈希键值的算法通常用求余法或者乘法
    return 0;
}

//匹配2个元素是否相同
int HashMatch( void* pKey1, void* pKey2 )
{
    if( ( NULL == pKey1 ) || ( NULL == pKey2 ) )
    {
        return -1;
    }

}

//哈希表增加一个元素
int HashInsert( T_HASH_TBL* pHash, void* pData )
{
    int key = 0;
    if( ( NULL == pHash ) || ( NULL == pData ) )
    {
        return -1;
    }
    //计算哈希键值
    if( ( key = HashKey( pData ) ) < 0 )
    {
        return -1;
    }
    //需要判断哈希键值是否冲突吗,还是说直接插入元素
    return ListInsertNext( &(pHash->pList[key]), NULL, pData );    
}

//哈希表删除一个元素
int HashRemove( T_HASH_TBL* pHash, void** pData )
{
    int key = 0;
    T_LIST_ELMT* pPrev = NULL;
    T_LIST_ELMT* pCur = NULL;
    if( ( NULL == pHash ) || ( NULL == pData ) )
    {
        return -1;
    }
    //计算哈希键值
    if( ( key = HashKey( *pData ) ) < 0 )
    {
        return -1;
    }
    //上一个元素指针初始化必须为空,这样才能删除匹配的头结点
    pPrev = NULL;
    pCur = LIST_HEAD( &(pHash->pList[key]) );
    while( pCur != NULL )
    {
        //在链表中遍历是否存在该元素,找到后就删除它
        if( pCur->pData == *pData )
        {
            return ListRemoveNext( &(pHash->pList[key]), pPrev, pData );
        }
        //遍历下一个元素,但是要记录上一个元素的位置
        pPrev = pCur;
        pCur = pCur->pNext;
    }
    //没有找到要删除的元素
    return -1;
}



