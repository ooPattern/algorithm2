#include <stdio.h>

//基本数据类型宏定义
#define signed      int		int32
#define unsigned	int	    uint32
#define short       int		int16
#define unsigned    short	uint16
#define char				int8
#define unsigned    char	uint8
#define float				fp32

//链表元素定义
typedef struct _ListElmt
{
	void* pData;//数据指针
	struct _ListElmt* pNext; 
} T_LIST_ELMT;

//链表结构定义
typedef struct _ListTbl
{
	int size;//链表元素个数
	T_LIST_ELMT* pHead;//链表头指针
	T_LIST_ELMT* pTail;//为了支持能在链表尾部插入新元素
} T_LIST_TBL;

//定义链表相关的宏定义
#define LIST_SIZE(pList)            ((pList)->size)//链表元素个数
#define LIST_HEAD(pList)            ((pList)->pHead)//链表头指针
#define LIST_TAIL(pList)            ((pList)->pTail)//链表尾指针
#define LIST_IS_HEAD(pList,pElmt)   (((pList)->pHead == pElmt) ? (1) : (0))//判断是否为链表头指针
#define LIST_IS_TAIL(pList,pElmt)   (((pList)->pTail == pElmt) ? (1) : (0))//判断是否为链表尾指针


//初始化链表的操作
int ListInit( T_LIST_TBL* pList )
{
	if( NULL == pList )
	{
		return -1;
	}
	pList->size = 0;
	pList->pHead = NULL;
	pList->pTail = NULL;	
	return 0;
}

//增加一个链表元素,链表必须支持插入的位置,如果只能在尾部插入新元素,就变成队列了
int ListInsertNext( T_LIST_TBL* pList, T_LIST_ELMT* pElmt, void* pData )
{
	T_LIST_ELMT* pNewElmt = NULL;
	//pElmt允许为空,空表示取代原来的头指针
	if( ( NULL == pList ) || ( NULL == pData ) )
	{
		return -1;
	}
	//为新元素分配内存
	if( NULL == ( pNewElmt = malloc( sizeof( T_LIST_ELMT ) ) ) )
	{
		return -1;
	}
	//将新元素插入到指定的位置中 - 取代原来的头指针
	if( NULL == pElmt )
	{
		//判断是否需要改变链表的尾指针,链表为空需要同时改变尾指针
		if( 0 == pList->size )
		{
			pList->pTail = pNewElmt;
		}
		//改变链表的头指针
		pNewElmt->pNext = pList->pHead;
		pList->pHead = pNewElmt;
	}
	//将新元素插入到指定的位置中 - 插入某个元素后面
	else
	{
		//如果插入链表的尾部,需要更新链表尾部指针
		if( NULL == pElmt->pNext )
		{
			pList->pTail = pNewElmt;
		}
		//将新元素插入到链表某个元素中
		pNewElmt->pNext = pElmt->pNext;
		pElmt->pNext = pNewElmt;
	}
	//更新链表新元素的数据内容
	pNewElmt->pData = pData;
	pList->size++;
	return 0;
}

//删除一个链表元素,data为什么要2颗星？如果不是2颗星,则无法获取数据内容的地址,
//因为数据内容需要额外手动释放,程序只是删除链表元素的空间,但没有删除数据内容的空间
int ListRemoveNext( T_LIST_TBL* pList, T_LIST_ELMT* pElmt, void** pData )
{
    T_LIST_ELMT* pOldElmt = NULL;       
	//pElmt可以为空,空表示删除头指针
	//pData为数据内容地址的指针变量,可以为空,因为仅是一个存放地址的变量,不会直接访问
	if( NULL == pList )
	{
		return -1;
	}
    //检查链表是否还有元素
    if( 0 == pList->size )
    {
        return -1;
    }
	//删除头节点
    if( NULL == pElmt )
    {
        //考虑尾节点是否也需要更新
        if( 1 == pList->size )
        {
            pList->pTail = NULL;
        }
        //改变头节点位置
        pOldElmt = pList->pHead;
        pList->pHead = pList->pHead->pNext;
        //获取要删除数据内容的地址,由调用者手动释放
        *pData = pList->pHead->pData;
    }
    //删除其他节点
    else
    {
        //如果删除的是尾节点的下一个节点,直接返回失败?那如果删除尾节点?
        if( NULL == pElmt->pNext )
        {
            return -1;
        }
        //如果删除的下一个节点是尾节点,需要更新尾节点的位置
        if( NULL == pElmt->pNext->pNext )
        {
            pList->pTail = pElmt;
        }
        //获取要删除的节点地址
        pOldElmt = pElmt->pNext;
        //直接跳过要删除的节点,将前后的节点连接起来
        pElmt->pNext = pElmt->pNext->pNext;
        //获取要删除数据内容的地址,由调用者手动释放
        *pData = pOldElmt->pData;
    }
    //释放要删除的节点空间
    if( pOldElmt != NULL )
    {
        free( pOldElmt );
    }
    //更新链表数据
    pList->size--;
    return 0;
}

//释放链表所有数据
void ListDestory( T_LIST_TBL* pList )
{
    T_LIST_ELMT* pCur = NULL;
    T_LIST_ELMT* pOld = NULL;
    if( NULL == pList )
    {
        return;
    }
    //遍历所有链表节点
    pCur = pList->pHead;
    while( pCur != NULL )
    {
        pOld = pCur;
        //释放链表节点的数据内容,必须先释放节点的数据内容,然后再释放节点
        if( pOld->pData != NULL )
        {            
            free( pOld->pData );
        }
        //释放链表节点
        if( pOld != NULL )
        {
            free( pOld );
        }
        pCur = pCur->pNext;
    }
    //置0链表数据
    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->size = 0;
}

int main( void )
{
	printf( "hello world\n" );
	return 0;
}
 
