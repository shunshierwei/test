
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

void InitSeqList(SeqList* pSeq);//��ʼ��
void PushBack(SeqList* pSeq, DataType x);//β��
void PopBack(SeqList* pSeq);//βɾ
void PushFront(SeqList* pSeq,DataType x);// ͷ��
void PopFront(SeqList* pSeq);//ͷɾ

void Insert(SeqList*pSeq, size_t pos, DataType x);//����
int  Find(SeqList* pSeq, size_t pos, DataType x);//����
void Erase(SeqList* pSeq, size_t pos);//ɾ��ĳ��λ���ϵ�����
int  Remove(SeqList* pSeq, DataType x);
void RemoveAll(SeqList* pSeq, DataType x);

void BubbleSort(SeqList* pSeq);//ð������

//һ��ѡ�������С�����ݷֱ�������е�����
void SeclectSort(SeqList* pSeq);//ѡ������

//int BinarySearch(SeqList* pSeq, DataType x)//���ֲ���
//{
//    []����ұ�
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

int BinarySearch(SeqList* pSeq, DataType x)//���ֲ���
{
	//[)����ҿ�
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

void PrintSeqList(SeqList*pSeq);//��ӡ


void InitSeqList(SeqList* pSeq)//��ʼ������
{
	assert(pSeq);
	memset(pSeq->array, 0, sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}

//1,������
//2.�߽������ļ��  ��̬˳�����������
//3.������ǵĹ����߼�

void PushBack(SeqList* pSeq, DataType x)//β��
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

void PushFront(SeqList* pSeq, DataType x)//ͷ��
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


void PopBack(SeqList* pSeq)//βɾ
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

void PopFront(SeqList* pSeq)//ͷɾ
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


void Insert(SeqList*pSeq, size_t pos, DataType x)//����
{
	int begin = pSeq->size - 1;
	assert(pSeq);
	assert(pos <= pSeq->size);
	if (pSeq->size >= MAX_SIZE)//����Ƿ�Ϊ��
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

int  Find(SeqList* pSeq, size_t pos, DataType x)//����
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
void Erase(SeqList* pSeq, size_t pos)//ɾ��ĳ��λ���ϵ�����
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
void PrintSeqList(SeqList*pSeq)//��ӡ
{
	int i = 0;
	assert(pSeq);
	for (; i < pSeq->size; ++i)
	{
		printf(" %d", pSeq->array[i]);
	}
	printf("\n");
}
