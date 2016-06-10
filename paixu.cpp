#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include<iostream>
using namespace std;
#include<assert.h>

template<class T>
class Sort
{
public:
	Sort(T* a, size_t size);
public:
	void InsertSort();//≤Â»Î≈≈–Ú
	void ShellSort();//œ£∂˚≈≈–Ú
	void SelectSort();//—°‘Ò≈≈–Ú
	void HeapSort();//∂—≈≈–Ú
	void BubbleSort();//√∞≈›≈≈–Ú
	void QuickSort();//øÏ≈≈

	void Print()
	{
		for (int i = 0; i < _size; i++)
		{	
			cout << _a[i] << "  "  ;
		}
		cout << endl;
	}
protected:

protected:
	T* _a;
	size_t _size;
};

template<class T>
 Sort<T>::Sort(T* a, size_t size)
	:_a(a)
	, _size(size)
{}

template<class T>
void Sort<T>::InsertSort()
{
	assert(_a);
	for (int begin = 0; begin < _size; begin++)
	{
		int tmp = _a[begin];
		int end = begin - 1;
		while (end >= 0 && tmp < _a[end])
		{
			_a[end + 1] = _a[end];
			_a[end] = tmp;
			end--;
		}
	}
}

template<class T>
void Sort<T>::ShellSort()
{
	assert(_a);
	int gap = _size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < _size - gap; i++)
		{
			int end = i;
			int tmp = _a[end + gap];
			while (end >= 0 && _a[end]>_a[end + gap])
			{
				_a[end + gap] = _a[end];
				_a[end] = tmp;
				end -= gap;
			}
		}
	}
}

template<class T>
void Sort<T>::SelectSort()
{
	assert(_a);
	for (int i = 0; i < _size; i++)
	{
		int minnum = i;
		for (int j = i + 1; j < size; j++)
		{
			if (a[minnum]>a[j])
			{
				minnum = j;
			}
			{
				swap(a[i], a[minnum]);
			}
		}
	}

	template<class T>
	void Sort<T>:: HeapSort()
	{

	}


}

void test()
{
	int arr[] = {6,5,3,4,7};
	Sort<int> s(arr, 5);
	//s.InsertSort();
	s.ShellSort();
	s.Print();



}


int main()
{
	test();
	getchar();
	return 0;
}

