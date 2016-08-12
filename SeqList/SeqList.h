
#pragma once
#include <string.h>
#include<assert.h>

#define MAX_SIZE  1000
typedef int DataType;

typedef struct SeqList
{
	DataType array[MAX_SIZE];
	size_t size;
}SeqList;

void InitSeqList(SeqList* pSeq);//初始化
void PushBack(SeqList* pSeq, DataType x);//尾插
void PopBack(SeqList* pSeq);//尾删
void PushFront(SeqList* pSeq,DataType x);// 头插
void PopFront(SeqList* pSeq);//头删

void Insert(SeqList*pSeq, size_t pos, DataType x);//插入
int  Find(SeqList* pSeq, size_t pos, DataType x);//查找
void Erase(SeqList* pSeq, size_t pos);//删除某个位置上的数据
int  Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);

void BubbleSort(SeqList* pSeq);//冒泡排序

//一次选出最大最小的数据分别放在序列的两端
void SeclectSort(SeqList* pSeq);//选择排序

//int BinarySearch(SeqList* pSeq, DataType x)//二分查找
//{
//    []左闭右闭
//	int left = 0;
//	int right = pSeq->size - 1;
//	assert(pSeq);
//
//
//	while (left <= right)
//	{
//		/*int mid = (right + left) / 2;*/
//		int mid = left + (right - left) / 2;
//		if (x > pSeq->array[mid])
//		{
//			left = mid + 1;
//		}
//		else if (x < pSeq->array[mid])
//		{
//			right = mid - 1;
//		}
//		else
//		{
//			return mid;
//		}
//	}
//	return -1;
//}

int BinarySearch(SeqList* pSeq, DataType x)//二分查找
{
	//[)左闭右开
	int left = 0;
	int right = pSeq->size ;
	assert(pSeq);


	while (left < right)
	{
		/*int mid = (right + left) / 2;*/
		int mid = left + (right - left) / 2;
		if (x > pSeq->array[mid])
		{
			left = mid + 1;
		}
		else if (x < pSeq->array[mid])
		{
			right = mid ;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

void PrintSeqList(SeqList*pSeq);//打印


void InitSeqList(SeqList* pSeq)//初始化链表
{
	assert(pSeq);
	memset(pSeq->array, 0, sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}

//1,检查参数
//2.边界条件的检查  静态顺序表容量有限
//3.完成我们的功能逻辑

void PushBack(SeqList* pSeq, DataType x)//尾插
{
	//assert(pSeq);
	//if (pSeq->size >= MAX_SIZE)
	//{
	//	printf("SeqList is Full\n");
	//	return;
	//}
	//pSeq->array[pSeq->size++] = x;
	Insert(pSeq, pSeq->size, x);
}

void PushFront(SeqList* pSeq, DataType x)//头插
{
	//int begin = pSeq->size - 1;
	//assert(pSeq);
	//if (pSeq->size >= MAX_SIZE)
	//{
	//	printf("SeqList is Full\n");
	//	return;
	//}
	//for (; begin >= 0;--begin)
	//{
	//	pSeq->array[begin + 1] = pSeq->array[begin];
	//}
	//pSeq->array[0] = x;
	//++pSeq->size;
	Insert(pSeq, 0, x);
}


void PopBack(SeqList* pSeq)//尾删
{
	assert(pSeq);
	if (pSeq->size <= 0)
	{
		printf("SeqList is Empty\n");
		return;
	}
	//pSeq->array[--pSeq->size] = 0;
	--pSeq->size;
}

void PopFront(SeqList* pSeq)//头删
{
	int begin = 1;
	assert(pSeq);
	if (pSeq->size <= 0)
	{
		printf("SeqList is Empty\n");
		return;
	}
	for (; begin < pSeq->size; ++begin)
	{
		pSeq->array[begin - 1] = pSeq->array[begin];
	}
	--pSeq->size;
}


void Insert(SeqList*pSeq, size_t pos, DataType x)//插入
{
	int begin = pSeq->size - 1;
	assert(pSeq);
	assert(pos <= pSeq->size);
	if (pSeq->size >= MAX_SIZE)//检查是否为空
	{
		printf("SeqList is Full\n");
		return;
	}

	for (; begin >= (int)pos; --begin)
	{
		pSeq->array[begin + 1] = pSeq->array[begin];
	}
	pSeq->array[pos] = x;
	++pSeq->size;
}

int  Find(SeqList* pSeq, size_t pos, DataType x)//查找
{
	int i = pos;
	assert(pSeq);
	for (; i < pSeq->size; ++i)
	{
		if (pSeq->array[i] == x)
		{
			return i;
		}
	}
	return -1;
}
void Erase(SeqList* pSeq, size_t pos)//删除某个位置上的数据
{
	int begin = pos + 1;
	assert(pSeq);
	if (pSeq->size <= 0)
	{
		printf("SeqList is Empty\n");
		return;
	}
	assert(pos < pSeq->size);
	for (; begin < pSeq->size; ++begin)
	{
		pSeq->array[begin - 1] = pSeq->array[begin];
	}
	--pSeq->size;

}
int Remove(SeqList* pSeq, DataType x)
{
	int pos;
	assert(pSeq);
	pos = Find(pSeq,0, x);
	if (pos != -1)
	{
		Erase(pSeq, pos);
	}
	return pos;
}
//void RemoveAll(SeqList* pSeq, DataType x)
//{
//	int pos;
//	assert(pSeq);
//
//	pos = Find(pSeq,0, x);
//	while (pos != -1)
//	{
//		Erase(pSeq, pos);
//		pos = Find(pSeq,pos, x);
//	}
//}

void RemoveAll(SeqList* pSeq, DataType x)
{
	int count = 0;
	int begin = 0;
	assert(pSeq);
	for (; begin < pSeq->size;++begin)
	{
		if (pSeq->array[begin] == x)
		{
			++count;
		}
		else
		{
			pSeq->array[begin - count] = pSeq->array[begin];
		}
	}
	pSeq->size -= count;

}
void PrintSeqList(SeqList*pSeq)//打印
{
	int i = 0;
	assert(pSeq);
	for (; i < pSeq->size; ++i)
	{
		printf(" %d", pSeq->array[i]);
	}
	printf("\n");
}
