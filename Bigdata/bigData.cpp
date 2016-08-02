#include "BigData.h"
#include<assert.h>

BigData::BigData(INT64 value)
   :_value(value)
{
	INT64ToString();
}
BigData::BigData( char* pData)
{
	assert(NULL != pData);
	char cSymbol = pData[0];

	if (pData[0] >= '0'&&pData[0<='9'])
	{
		cSymbol = '+';
	}
	else if ('+' == cSymbol || '-'==cSymbol)
	{
		pData++;
	}

	else
	{
		_value = UN_INIT;
		return;
	}

	while ('0' == *pData)
	{
		pData++;
	}

	//转化
	//"=123456789"
	_strData.resize(strlen(pData) + 1);
	_strData[0] = cSymbol;

	//_strData; value

	int iCount = 1;
	_value = 0;
	while (*pData>='0'&&*pData<='9')
	{
		_strData[iCount++] = *pData;
		_value = _value * 10 + *pData - '0';
		pData++;
	}

	if (cSymbol == '-')
	{
		_value = 0 - _value;
	}

	_strData.resize(iCount);
}

BigData BigData::operator+(const BigData& bigData)
{
	if (!IsINT64Overflow() && !bigData.IsINT64Overflow())
	{
		if (_strData[0] != bigData._strData[0])
		{
			return BigData(_value + bigData._value);
		}

		else
		{
			//10-3=7>=8
			//-10-(-3)=-7>-6-8
			INT64 temp = MIN_INT64 - _value;
			if ((_value >= 0 && (MAX_INT64 - _value >= bigData._value)) ||
				(_value < 0 && (/*MIN_INT64 - _value*/ temp<= bigData._value)))
			{
				return BigData(_value + bigData._value);
			}
		}
	}

	//至少有一个溢出
	//结果溢出
	if (_strData[0] == bigData._strData[0])//同号
	{
		return BigData((char*)Add(_strData, bigData._strData).c_str());
	}
	return BigData((char*)Sub(_strData, bigData._strData).c_str());
}

BigData BigData::operator-(const BigData& bigData)
{
	if (IsINT64Overflow() && bigData.IsINT64Overflow())
	{
		if (_strData[0] == bigData._strData[0])
		{
			return BigData(_value - bigData._value);
		}
		else
		{
			//10+(-2)=8\
						//-10+2=-8<=-9-7
			if ((_value > 0 && MAX_INT64 + bigData._value >= _value) ||
				(_value < 0 && MIN_INT64 + bigData._value <= _value))
			{
				return BigData(_value - bigData._value);
			}
		}
	}

		//异号
		if (_strData[0] != bigData._strData[0])
		{
			return BigData((char*)Add(_strData, bigData._strData).c_str());
		}
		return BigData((char*)Sub(_strData, bigData._strData).c_str());
}

BigData BigData::operator*(const BigData& bigData)
{
	if (_value == 0 || bigData._value == 0)
	{
		return BigData(INT64(0));
	}
	if (IsINT64Overflow() && bigData.IsINT64Overflow())
	{
		if (_strData[0] == bigData._strData[0])
		{
			//10/-2=-5 -3 -6
			if ((_value > 0 && MAX_INT64 / _value >= bigData._value) ||
				(_value < 0 && MAX_INT64 / _value <= bigData._value))
			{
				return BigData(_value*bigData._value);
			}
		}
		else
		{
			//-10/2= -5 -3 -6
			//-10/-2= 5 3 6
			if ((_value > 0 && MIN_INT64 / _value <= bigData._value) ||
				(_value < 0 && MIN_INT64 / _value >= bigData._value))
			{
				return BigData(_value*bigData._value);
			}
		}
	}
	return BigData((char*)Mul(_strData, bigData._strData).c_str());
}

BigData BigData::operator / (const BigData& bigData)
{
	//"+0" _value
	if ('0'==bigData._strData[1])
	{
		assert(false);
		//
	}
	if (IsINT64Overflow()&&bigData.IsINT64Overflow())
	{
		return BigData(_value / bigData._value);
	}
	if (_strData.size() < bigData._strData.size() ||
		(_strData.size() == bigData._strData.size()&&
		strcmp(_strData.c_str() + 1, bigData._strData.c_str()+1)<0))
	{
		return BigData(INT64(0));
	}

	if (bigData._strData == "+1" || _strData == "-1")
	{
		std::string ret = _strData;
		if (_strData[0]!=bigData._strData[0])
		{
			ret[0] = '-';
		}
		return BigData((char*)ret.c_str());
	}

	if (/*_strData.size() == bigData._strData.size()&&*/
		strcmp(_strData.c_str() + 1, bigData._strData.c_str() + 1)==0)
	{
		std::string ret = "+1";
		if (_strData[0] != bigData._strData[0])
		{
			ret[0] = '-';
		}
		return BigData((char*)ret.c_str());
	}

	return BigData((char*)Div(_strData, bigData._strData).c_str());
}


	
	std::string BigData::Add(std::string left, std::string right)
	{
		int iLSize = left.size();
		int iRSize = right.size();
		if (iLSize<iRSize)
		{
			std::swap(left, right);
			std::swap(iLSize, iRSize);
		}
		std::string sRet;
		sRet.resize(iLSize + 1);
		sRet[0] = left[0];
		char Step = 0;

		for (int iIdx = 1;iIdx < iLSize; iIdx++)
		{
			char cRet = left[iLSize - iIdx]-'0'+Step;
			if (iIdx < iRSize)
			{
				cRet += (right[iRSize - iIdx] - '0');
			}
			sRet[iLSize - iIdx + 1] = cRet % 10 + '0';
			Step = cRet / 10;
		}
		sRet[1] = Step + '0';
		return  sRet;
	}
	std::string BigData::Sub(std::string left, std::string right)
	{
		int iLSize = left.size();
		int iRSize = right.size();
		char cSymbol = left[0];
		if (iLSize<iRSize||iLSize==iRSize&&left<right)
		{
			std::swap(left, right);
			std::swap(iLSize, iRSize);
			if (cSymbol == '+')
			{
				cSymbol = '-';
			}
			else
			{
				cSymbol = '+';
			}
		}
		//保存结果的
		std::string strRet;
		///////////////////////////////////
		strRet.resize(iLSize);
		strRet[0] = cSymbol;
		
		//1、从底往高 取left的每一位
		//2、从底往高 取right的每一位
		//3、 判断是否借位
		for (int Idx = 1; Idx < iLSize;++Idx)
		{
			char cRet = left[iLSize - Idx] - '0';

			if (Idx < iRSize)
			{
				cRet -= (right[iRSize - Idx] - '0');
			}

			if (cRet<0)
			{
				left[iLSize - Idx - 1] -= 1;
				cRet += 10;
			}
			strRet[iLSize - Idx] = cRet + '0';
		}

		return strRet;
	}


	std::string BigData::Mul(std::string left, std::string right)
	{
		//确定符号位
		char cSymbol = left[0];
		if (left[0] != right[0])
		{
			cSymbol = '-';
		}
		int iLSize = left.size();
		int iRSize = right.size();

		if (iLSize > iRSize)
		{
			std::swap(left, right);
			std::swap(iLSize, iRSize);
		}

		std::string sRet;
		//sRet.resize(iLSize + iRSize-1);
		sRet.assign(iLSize + iRSize - 1, '0');
		sRet[0] = cSymbol;
		int iDataLen = sRet.size();
		int ioffset = 0;

		//先取上左边一个
		//和右边的每一位相乘

		for (int iLIdx = 1; iLIdx < iLSize; ++iLIdx)
		{
			char cLeft = left[iLSize - iLIdx] - '0';
			char cStep = 0;
			if (cLeft == 0)
			{
				ioffset++;
				continue;
			}
			//99*999    9*999    8991
			for (int iRIdx = 1; iRIdx < iRSize; ++iRIdx)
			{
				char cRet = cLeft*(right[iRSize - iRIdx] - '0')+cStep;
				cRet += sRet[iDataLen - iRIdx - ioffset] - '0';
				sRet[iDataLen - iRIdx - ioffset] = (cRet % 10)+'0';
				cStep = cRet / 10;
			}
			sRet[iDataLen - iRSize - ioffset] += cStep;
			ioffset++;
		}
		return sRet;
	}

	

	std::string BigData::Div(std::string left, std::string right)
	{
		//  前提 左边 大于 右边

		std::string sRet;
		sRet.append(1, '+');
		if (left[0] != right[0])
		{
			sRet[0] = '-';
		}
		//越过符号位
		char* pLeft = (char*)(left.c_str() + 1);
		char* pRight = (char*)(right.c_str() + 1);
		int LSize = left.size() - 1;
		int RSize = right.size() - 1;
		int DataLen = RSize; // 偏移 从pLeft向后总共可以看到多少位 刚开始可以为1 也可初始化为右边数值长度



		for (int iIdx = 0; iIdx < LSize;)
		{
			// 处理‘0’
			// 3300000000000/33  00  0000000000000
			if ('0' == *pLeft)
			{
				sRet.append(1, '0');
				pLeft++;
				iIdx++;
				continue;
			}


			if (!IsLeftStrBig(pLeft, DataLen, pRight, RSize))
			{
				// 左边 小于 右边 商补0
				sRet.append(1, '0');
				DataLen++; // 左边向后延长一位
				if (DataLen + iIdx > LSize) // >= 少算一位 防止越界超出左边的总长度
				{
					break;
				}
			}
			else // 左边大于右边
			{
				sRet.append(1, SubLoop(pLeft, DataLen, pRight, RSize));
				// 更新pLeft 因为上面SubLoop的pLeft用的是值传递 所以要在外面更新
				while (*pLeft == '0' && DataLen > 0)
				{
					pLeft++;
					iIdx++;

					DataLen--; // 33333/33 left 33 变成00 <33 但Datalen没减的话 -> left 0033 》= 33  -> 商11 原本要商 101   少算中间的0    DataLen--防止少算0
					// 也防止 “330000000000”
				}
				// 22222222222222/33
				// "0242222222222222"
				//  "242222222222222"
				DataLen++; // 防止下载一次用24 和 33 比较 24 < 33 商多算了一个0
				if (DataLen + iIdx > LSize) // >= 少算一位
				{
					break;
				}
			}
		}


		return sRet;
	}


	bool BigData::IsLeftStrBig(const char* pLeft, int LSize, const char* pRight,int RSize)
	{
		//"22222222222222222222222"
		//"33"
		if (LSize > RSize ||
			LSize == RSize&&strcmp(pLeft, pRight)>=0)
		{
			return true;
		}
		return false;
	}

	char BigData::SubLoop( char* pLeft, int LSize, const char* pRight, int RSize)
	{
		assert(pLeft != NULL && pRight != NULL);
		char cRet = '0';
		while (true)
		{
			if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))
			{
				break;
			}
			int LDataLen = LSize - 1;
			int RDataLen = RSize - 1;
			while (LDataLen >= 0 && RDataLen >= 0)
			{
				char ret = pLeft[LDataLen] - '0';
				ret -= pRight[RDataLen] - '0';
				if (ret < 0)
				{
					pLeft[LDataLen-1] -= 1;
					ret += 10;
				}
				pLeft[LDataLen] = ret + '0';
				LDataLen--;
				RDataLen--;
			}
			//3333000000000000
			//3333
			//0000
			while (*pLeft == '0'&& LSize>0)
			{
				pLeft++;
				LSize--;
			}
			
			cRet++;
		}
		return cRet;
	}


bool BigData::IsINT64Overflow()const
{
	std::string temp("+9223372036854775807");
	if ('-' == _strData[0])
	{
		temp = ("-9223372036854775808");
	}

	//_strData;
	if (_strData.size() < temp.size())
	{
		return true;
	}
	else if (_strData.size() == temp.size() && _strData <= temp)
	{
		return true;
	}
	return false;
}


void BigData::INT64ToString()
{
	//INT64 tem = _value;
	char cSymbol = '+';
	if (_value < 0)
	{
		cSymbol = '-';
		/*tem = 0 - tem;*/
	}
	//_str
	//12467
	//76421
	INT64 tem = _value;
	_strData.append(1,cSymbol);
	while (tem)
	{
		int c = tem % 10;
		if (c < 0)
		{
			c = 0 - c;
		}
		_strData.append(1, c + '0');
		tem /= 10;
	}
	char *pleft = (char*)_strData.c_str() + 1;
	char *pright = pleft + _strData.size() - 2;

	while (pleft < pright)
	{
		char cTemp = *pleft;
		*pleft++ = *pright;
		*pright-- = cTemp;
	}

}
//cout <<bigdata
//A>B
//A.operator>(A,B)
//cout.operator<<(cout, bigData);
std::ostream& operator<<(std::ostream& _cout, const BigData& bigData)
{
	if (bigData.IsINT64Overflow())
	{
		_cout << bigData._value;
	}
	else
	{
		char *pData = (char*)bigData._strData.c_str();

		if ('+' == bigData._strData[0])
		{
			pData++;

		}
		_cout << pData;

	}

	return _cout;
}
