#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

#include "HuffmanTree.h"
#include "FileCompress.h"
#include<windows.h>
int main()
{
	//TestHuffmanTree();

	int begin = GetTickCount();
	TestComoress();
	int end = GetTickCount();

	cout << "ѹ���ļ���ʱ��" << end - begin << endl;
	
	begin = GetTickCount();
	TestUncomoress();
	end = GetTickCount();

	cout << "�����ļ���ʱ��" << end - begin << endl;

	getchar();
	return 0;
  }