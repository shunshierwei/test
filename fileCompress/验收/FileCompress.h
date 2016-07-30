#pragma once
#include<string.h>
#include "HuffmanTree.h"
#include <iostream>
#include"assert.h"
using namespace std;
typedef unsigned long LongType;

struct CharInfo
{
	unsigned char _ch;    //字符
	LongType _count;  //次数
	string _code;    //编码

	CharInfo(LongType count = 0)
		:_count(count)
	{}

	bool operator<(const CharInfo& info) const
	{
		return _count < info._count;
	}
	
	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_count + info._count);
	}

	bool operator!=(const CharInfo& info) const
	{
		return _count!= info._count;
	}
};

class FileCompress
{
public:

	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}
	}

	void GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root, string code)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL && root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
			return;
		}
		GenerateHuffmanCode(root->_left, code + '0');
		GenerateHuffmanCode(root->_right, code + '1');

	}

	void Compress(const char* filename)
	{
		//统计文件字符出现的次数
		FILE* fout = fopen(filename, "rb");
		assert(fout);
		char ch = fgetc(fout);
		while (ch != EOF) // 	!feof(fout)
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fout);
		}
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		//生成Huffman编码
		string code;
		GenerateHuffmanCode(tree.GetRoot(), code);

		//压缩文件
		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fin = fopen(compressFilename.c_str(), "wb");
		assert(fin);

		//读源文件，进行压缩
		fseek(fout, 0,SEEK_SET);
		ch = fgetc(fout);
		int value = 0;
		int size = 0;
		while (ch != EOF)
		{
			string& code = _infos[(unsigned char)ch]._code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				value <<= 1;
				if (code[i] == '1')
				{
					value |= 1;
				}
				++size;
				if (size == 8)
				{
					fputc(value, fin);
					size = 0;
					value = 0;
				}
			}
			ch = fgetc(fout);
		}
		//不满8位，低位补0
		if (size)
		{
			value<<= (8 - size);
			fputc(value, fin);
		}

		//写配置文件（字符出现次数）
		string configFileName = filename;
		configFileName += ".config";
		FILE* finConfig = fopen(configFileName.c_str(), "wb");
		assert(finConfig);
		char buff[128];
		for (size_t i = 0; i < 256; ++i)
		{
			string line;
			if (_infos[i]._count>0)
			{
				line += _infos[i]._ch;
				line += ',';
				line += _itoa(_infos[i]._count,buff,10);
				line += '\n';
				fputs(line.c_str(), finConfig);
			}
		}

		fclose(fout);
		fclose(fin);
		fclose(finConfig);
	}

	bool ReadLine(FILE* fout, string& line)
	{
		char ch = fgetc(fout);
		if (ch == EOF)
			return false;

		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(fout);
		}
		return true;
	}

	void Uncompress(const char* filename)
	{
		string compressFileName = filename;
		compressFileName += ".compress";
		FILE* fout = fopen(compressFileName.c_str(), "rb");
		assert(fout);

	//解析配置文件，获取文件字符出现的次数
		//于重建huffman树
		string configFileName = filename;
		configFileName += ".config";
		FILE* foutConfig = fopen(configFileName.c_str(), "rb");
		assert(foutConfig);
		string line;
		while (ReadLine(foutConfig, line))
		{
			//统计换行成符出现的次数
			if (line.empty())
			{
				line += '\n';
			}
			else
			{
				//a,100
				_infos[(unsigned char)line[0]]._count = atoi(line.substr(2).c_str());
				line.clear();
			}

			
		}

		//重建Huffman树
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);
		HuffmanTreeNode<CharInfo>* root = tree.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;

		LongType charCount = root->_weight._count;

		string uncompressFilename = filename;
		uncompressFilename += ".uncompress";
		FILE* fin = fopen(uncompressFilename.c_str(), "wb");
		assert(fin);

		char ch = fgetc(fout);
		int pos = 7;
		//while (ch != EOF)  EOF代表-1
		while (!feof(fout))
		{
			if (ch & (1 << pos))
				cur = cur->_right;
			else
				cur = cur->_left;

			if (cur->_left == NULL&&cur->_right == NULL)
			{
				--charCount;
				fputc(cur->_weight._ch, fin);
				cur = root;
			}

			if (charCount == 0)
			{
				break;
			}

			--pos;
			if (pos < 0)
			{
				ch = fgetc(fout);
				pos = 7;
			}
		}
		fclose(fin);
	}

protected:
	CharInfo _infos[256];
};

void TestComoress()
{
	FileCompress fc;
	fc.Compress("Input.BIG");
	//fc.Uncompress("Input");
}

void TestUncomoress()
{
	FileCompress fc;
	fc.Uncompress("Input.BIG");
}