#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

class Stu
{
public:
	void print()
	{
		cout << _name << endl;
		cout << _age << endl;
	}

	void SetStu(int age,char *name)
	{
		_age = age;
		strcpy(_name, name);
	}
private:
	//成员变量
	char  _name[10];
	int _age;
	//成员函数

};
 

int main()
{
	Stu stu;
	stu.SetStu(20, "张三");
	stu.print();
	getchar();
	return 0;
}
