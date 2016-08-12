#define _CRT_SECURE_NO_WARNINGS 1


#include"SeqList.h"

//InitSeqList/PushBack/PopBack

void Test1()
{
	SeqList seq;
	InitSeqList(&seq);
	PushBack(&seq, 1);
	PushBack(&seq, 2);
	PushBack(&seq, 3);
	PushBack(&seq, 4);
	PrintSeqList(&seq);
	
	//PopBack(&seq);
	//PopBack(&seq);
	//PopBack(&seq);
	//PopBack(&seq);
	//PopBack(&seq);

	//PrintSeqList(&seq);

}

//InitSeqList/PushFront/PopFront

void Test2()
{
	SeqList seq;
	InitSeqList(&seq);

	PushBack(&seq, 1);
	PushBack(&seq, 2);
	PushBack(&seq, 3);
	PushBack(&seq, 4);

	PushFront(&seq, 0);


	PrintSeqList(&seq);

	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);
	PopFront(&seq);

	PrintSeqList(&seq);
}

//Insert
void Test3()
{
	SeqList seq;
	InitSeqList(&seq);

	PushBack(&seq, 1);
	PushBack(&seq, 2);
	PushBack(&seq, 4);
	PushBack(&seq, 5);

	Insert(&seq, 2, 3);
	PrintSeqList(&seq);
}

void Test4()
{
	int ret;
	SeqList seq;
	InitSeqList(&seq);

	PushBack(&seq, 1);
	PushBack(&seq, 2);
	PushBack(&seq, 3);
	PushBack(&seq, 2);
	PushBack(&seq, 2);
	PrintSeqList(&seq);

	//Remove(&seq, 3);
	//PrintSeqList(&seq);

	RemoveAll(&seq, 2);
	PrintSeqList(&seq);
}

void Test5()
{
	int ret;
	SeqList seq;
	InitSeqList(&seq);

	PushBack(&seq, 1);
	PushBack(&seq, 2);
	PushBack(&seq, 3);
	PushBack(&seq, 4);
	PushBack(&seq, 5);
	PrintSeqList(&seq);
	ret = BinarySearch(&seq, 1);
	printf("ret?%d", ret);

	ret = BinarySearch(&seq, 2);
	printf("ret?%d", ret);

	ret = BinarySearch(&seq, 3);
	printf("ret?%d", ret);

	ret = BinarySearch(&seq, 4);
	printf("ret?%d", ret);

	ret = BinarySearch(&seq, 5);
	printf("ret?%d", ret);
	printf("\n");
}

int main()
{
	//Test1();
	//Test2();
	//Test3();

	//Test4();
	Test5();

	system("pause");
	return 0;

}