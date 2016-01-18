#include "list.h"


//二叉树的结点数据类型
typedef struct t_bitreeNode
{
    void* pData;//结点数据
    struct t_bitreeNode* pLeft;//左子结点指针
    struct t_bitreeNode* pRight;//右子结点指针
} T_BITREE_NODE;

//二叉树的数据结构
typedef struct t_bitreeTbl
{
    int size;//二叉树的结点数量
    T_BITREE_NODE* pRoot;//二叉树的根结点指针
} T_BITREE_TBL;

//初始化二叉树
int BitreeInit( T_BITREE_TBL* pTree )
{
    if( NULL == pTree )
    {
        return -1;
    }
    pTree->size = 0;
    pTree->pRoot = NULL;
    return 0;
}

//清空二叉树
void BitreeDestory( T_BITREE_TBL* pTree )
{
    //按照某种顺序：先序、后序、中序等方式删除二叉树所有结点
}

//二叉树的某个结点增加一个左子结点
int BitreeInsertLeft( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode, void* pData )
{
    T_BITREE_NODE* pNewNode = NULL;
    T_BITREE_NODE** pPosition = NULL;//记录要插入结点的位置

    //pNode可以为空，空表示作为根结点
    if( ( NULL == pTree ) || ( NULL == pData ) )
    {
        return -1;
    }
    //作为根结点插入，原来必须是空树
    if( NULL == pNode )
    {
        //如果不是空树，直接返回失败
        if( pTree->size > 0 )
        {
            return -1;
        }
        //后续更新根结点位置
        pPosition = &(pTree->pRoot);
    }
    //插入到结点的左子结点，插入的结点必须是叶子结点
    else
    {
        //必须是叶子结点
        if( BitreeIsLeaf( pNode ) != 0 )
        {
            return -1;
        }
        //后续更新插入的结点位置
        pPosition = &(pNode->pLeft);
    }
    //分配新结点位置
    pNewNode = malloc( sizeof( T_BITREE_NODE ) );
    if( NULL == pNewNode )
    {
        return -1;
    }
    //更新树新插入的结点位置和结点数量
    *pPosition = pNewNode;
    pNewNode->pData = pData;
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;
    pTree->size++;
    return 0;
}

//二叉树的某个结点增加一个右子结点
int BitreeInsertRight( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode, void* pData )
{
    T_BITREE_NODE* pNewNode = NULL;
    T_BITREE_NODE** pPosition = NULL;

    //pNode可以为空，空表示作为根结点
    if( ( NULL == pTree ) || ( NULL == pData ) )
    {
        return -1;
    }
    //作为根结点插入，原来必须是空树
    if( NULL == pNode )
    {
        //如果不是空树，直接返回失败
        if( pTree->size > 0 )
        {
            return -1;
        }
        pPosition = &(pTree->pRoot);
    }
    //插入到结点的右子结点，插入的结点必须是叶子结点
    else
    {
        //必须是叶子结点
        if( BitreeIsLeaf( pNode ) != 0 )
        {
            return -1;
        }
        pPosition = &(pNode->pRight);
    }
    //分配新结点空间
    pNewNode = malloc( sizeof( T_BITREE_NODE ) );
    if( NULL == pNewNode )
    {
        return -1;
    }
    //更新树新插入的结点位置和结点数量
    *pPosition = pNewNode;
    pNewNode->pData = pData;
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;
    pTree->size++;
    return 0;
}

//二叉树的某个结点删除它的左子树
int BitreeRemoveLeft( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode )
{
    if( NULL == pTree )
    {
        return -1;
    }
    //删除结点的左子树

    return 0;
}

//二叉树的某个结点删除它的右子树
int BitreeRemoveRight( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode )
{
    return 0;
}



