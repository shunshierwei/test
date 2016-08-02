#define _CRT_SECURE_NO_WARNINGS 1
#include "BigData.h"
#include<iostream>
using namespace std;



void FunTest()
{
	cout << atoi("123456789") << endl;
	cout << atoi("+1234567890") << endl;
	cout << atoi("12345asdf23456") << endl;
	cout << atoi("-1234567") << endl;
	cout << atoi("+00001234567") << endl;
	cout << atoi("+a00001234567") << endl;

}



//void FunTest1()
//{
///*	string str("1234567")*/;
//	str[4] = '\0';
//	cout << str.c_str() << endl;
//	cout << str.size() << endl;
//
//	BigData bigData("+1234567890345678");
//	cout << bigData << endl;
//
//	BigData bigData1("+a1234567890345678");
//	cout << bigData1 << endl;
//
//	BigData bigData2("+000001234567890345678");
//	cout << bigData2 << endl;
//
//	BigData bigData3("-000001234567890345678");
//	cout << bigData3<< endl;
//}

void FunTest2()
{
	//BigData left(1234);
	//BigData right(4321);
	//BigData ret=(left+right);
	//cout << ret << endl;

	//BigData left1(9223372036854775807);
	//BigData right1(2);
	//BigData ret1 = (left1 + right1);
	//cout << ret1 << endl;

	BigData left2(0-9223372036854775808);
    BigData right2(-3);
	//BigData ret2 = (left2 + right2);
	cout << (left2 + right2) << endl;
}

void FunTest3()
{
	//BigData left2(1234);
	//BigData right2(34);
	//cout << (left2-right2) << endl;

	BigData left2("111111111111111111111111111111111");
	BigData right2("999");
	cout << (left2 - right2) << endl;

}

void FunTest4()
{
	BigData left3("110011");
	BigData right3("-2222222222222222222222222222222222222222222222");
	cout << left3 * right3 << endl;
}

void FunTest5()
{
	BigData left5("222222222222222222222222222222222222");
	BigData right5("33");
	cout << (left5/right5) << endl;
}

int main()
{


	//FunTest();
	//FunTest1();
	//FunTest2();
	//FunTest3();
      //FunTest4();

	FunTest5();
	getchar();
	return 0;
}