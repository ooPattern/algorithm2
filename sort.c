#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义排序的数据结构，用数组或者连续内存空间方便查找元素
#define SORT_MAX_SIZE   (100)//最多排序的元素个数
#define SORT_USE_SIZE 	 (20)//当前排序的元素个数

//定义排序的数据结构
typedef struct t_sortTbl 
{
    int picket;//哨兵
    int tbl[SORT_MAX_SIZE];//数组元素
    int size;//元素个数
} T_SORT_TBL;

//内部函数接口
static void GetRand( T_SORT_TBL* pSort );
static void ShowData( const char* pTip, const T_SORT_TBL* pSort );
//冒泡排序
static void SortSwap( T_SORT_TBL* pSort, int i, int j );
static void SortBubblePrimary( T_SORT_TBL* pSort );
static void SortBubbleMidLevel( T_SORT_TBL* pSort );
static void SortBubbleHighLevel( T_SORT_TBL* pSort );

//交换数组的2个元素
void SortSwap( T_SORT_TBL* pSort, int i, int j )
{
    int temp = 0;

    if( NULL == pSort )
    {
        return;
    }
    //判断是否数组越界
    if( ( i >= SORT_MAX_SIZE ) || ( j >= SORT_MAX_SIZE ) )
    {
        return;
    }
    //交换数据
    temp = pSort->tbl[j];
    pSort->tbl[j] = pSort->tbl[i];
    pSort->tbl[i] = temp;
}

//冒泡排序 - 初级版
//初级版的问题是最上面的元素不动，每次将下面的数据和最上面的数据比较
//还是会有可能导致小的数值放到了下面
void SortBubblePrimary( T_SORT_TBL* pSort )
{
    int i = 0, j = 0;
    if( NULL == pSort )
    {
        return;
    }
    //需要排序n趟
    for( i = 0; i < pSort->size; i++ )
    {
        //每一趟需要排序n-i次
        for( j = i + 1; j < pSort->size; j++ )
        {
            //将小的元素放到最上面
            if( pSort->tbl[i] > pSort->tbl[j] )
            {
                SortSwap( pSort, i, j );
            }
        }
    }    
}

//冒泡排序 - 中级版
//将相邻的2个数据排序，不断的将小的数据往上挤，大的数据往下挤
void SortBubbleMidLevel( T_SORT_TBL* pSort )
{
    int i = 0, j = 0;
    if( NULL == pSort )
    {
        return;
    }
    //需要排序n趟
    for( i = 0; i < pSort->size; i++ )
    {
        //从后面往前面比较，两两比较，最后将最小的放在最上面
        for( j = pSort->size - 1; j > i; j-- )
        {
            //这样可以将大的数据往下面挤，小的数据往上面挤
            if( pSort->tbl[j-1] > pSort->tbl[j] )
            {
                SortSwap( pSort, j - 1, j );
            }
        }
    }
}

//冒泡排序 - 高级版
//避免无意义的排序，已排好序的数据不用排序
void SortBubbleHighLevel( T_SORT_TBL* pSort )
{
    int i = 0, j = 0;
    int flg = 1;

    if( NULL == pSort )
    {
        return;
    }
    //需要排序n趟
    flg = 1;
    for( i = 0; ( i < pSort->size ) && ( flg != 0 ); i++ )
    {        
        //设置标志初始值
        flg = 0;
        //从后面往前面比较，两两比较，最后将最小的放在最上面
        for( j = pSort->size - 1; j > i; j-- )
        {
            //这样可以将大的数据往下面挤，小的数据往上面挤
            if( pSort->tbl[j-1] > pSort->tbl[j] )
            {
                SortSwap( pSort, j - 1, j );
                //如果交换过元素表示还需要再排序
                flg = 1;
            }
        }
    }
}

//简单选择排序
//特点：通过比较锁定目标，最后交换数值，交换次数少
void SortSelect( T_SORT_TBL* pSort )
{
    int i = 0, j = 0;
    int minPos = 0;

    if( NULL == pSort )
    {
        return;
    }
    //比较n趟
    for( i = 0; i < pSort->size; i++ )
    {
        //初始化最小值的初始位置
        minPos = i;
        for( j = i + 1; j < pSort->size; j++ )
        {
            //检查最小值位置是否需要更新
            if( pSort->tbl[minPos] > pSort->tbl[j] )
            {
                minPos = j;
            }
        }
        //如果最小值位置发生变化，则交换最小值
        if( minPos != i )
        {
            SortSwap( pSort, minPos, i );
        }
        //打印排序的过程
        //ShowData( "第n趟", pSort );
    }
}

//获取随机数
void GetRand( T_SORT_TBL* pSort )
{
	int i = 0;

    if( NULL == pSort )
    {
        return;
    }
    //获取随机数，然后利用冒泡排序法排序
    for( i = 0; i < SORT_USE_SIZE; i++ )
    {
        pSort->tbl[i] = rand() % 100;
    }
    pSort->size = SORT_USE_SIZE;
}

//打印数组元素
void ShowData( const char* pTip, const T_SORT_TBL* pSort )
{
    int i = 0;

    if( NULL == pSort )
    {
        return;
    }
    //打印提示信息，可以为空
    if( pTip != NULL )
    {
        printf( "\n %s \n", pTip );
    }
    //打印数组元素
    for( i = 0; i < pSort->size; i++ )
    {
        printf( "%d ", pSort->tbl[i] );
    }
    fflush( stdout );
}

//冒泡排序 - 测试例子
void BubbleTest( void )
{
    T_SORT_TBL sortTbl;
    memset( &sortTbl, 0x0, sizeof(sortTbl) );

    //获取随机数
    GetRand( &sortTbl );
    //输出未排序的结果
    ShowData( "排序前:", &sortTbl );
    //冒泡排序
    SortBubbleHighLevel( &sortTbl );
    //打印排序后的结果
    ShowData( "排序后:", &sortTbl );
}

//选择排序 - 测试例子
void SelectTest( void )
{
    T_SORT_TBL sortTbl;
    memset( &sortTbl, 0x0, sizeof(sortTbl) );

    //获取随机数
    GetRand( &sortTbl );
    //输出未排序的结果
    ShowData( "排序前:", &sortTbl );
    //选择排序
    SortSelect( &sortTbl );
    //打印排序后的结果
    ShowData( "排序后:", &sortTbl );
}

//主程序
int main(void)
{
    //BubbleTest();
	SelectTest();
	return 0;
}
