#ifndef BIGDATA_H
#define BIGDATA_H
#include<string>
#include<iostream>

#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0X8000000000000000

typedef long long INT64;
#define UN_INIT 0xcccccccccccccccc 

class BigData
{

public:
	//BigData();
	BigData(INT64 value=UN_INIT );
	BigData(char* pData);

	BigData operator+(const BigData& bigData);
	BigData operator-(const BigData& bigData);
	BigData operator*(const BigData& bigData);
	BigData operator/(const BigData& bigData);

	friend std::ostream& operator<<(std::ostream& _cout, const BigData& bigData);
	//friend std::ostream& operator<<(std::ostream& _cout);//bigdata<<cout

private:
	bool IsINT64Overflow()const;
	std::string Add(std::string left, std::string right);
	std::string Sub(std::string left, std::string right);
	std::string Mul(std::string left, std::string right);
	std::string Div(std::string left, std::string right);

	void INT64ToString();
	bool IsLeftStrBig(const char* pLeft, int LSize, const char* pRight,int RSize);
	char SubLoop(char* pLeft, int LSize, const char* pRight, int RSize);

private:
	INT64 _value;
	std::string _strData;
};

#endif