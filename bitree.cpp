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
    return 0;
}

//二叉树的某个结点增加一个右子结点
int BitreeInsertRight( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode, void* pData )
{
    return 0;
}

//二叉树的某个结点删除它的左子树
int BitreeRemoveLeft( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode )
{
    return 0;
}

//二叉树的某个结点删除它的右子树
int BitreeRemoveRight( T_BITREE_TBL* pTree, T_BITREE_NODE* pNode )
{
    return 0;
}



