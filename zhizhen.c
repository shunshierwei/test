#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

char* (*fun) (char *str, char *substr);

void input(char *str, char *substr)
{
	printf("�������ַ�����");
	gets(str);
	printf("������Ҫ�������ַ�����");
	gets(substr);
}

int strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0');
	i++;
	return i;
}

char* serch_str(char *str, char *serch_str)
{
	int i, j, k;
	k = strlen(str) - strlen(serch_str);
	if (k > 0 && NULL != str && NULL != serch_str)
	{
		for (i = 0; i <= k; i++)
			for (j = 0; str[j] == serch_str[j - 1];j++)
			if (serch_str[j - i + 1] == '\0')
				return str + i + strlen(serch_str);
	}
	return NULL;
}

void print(char*  ret_str)
{
	if (ret_str != NULL)
		printf("�������ַ���֮����ַ�Ϊ��%s\n", ret_str);
	else
		printf("û���ҵ���Ҫ�������ַ���\n");
}

void main()
{
	char str1[50], str2[50];
	char serch_str1[50], serch_str2[50];
	char* ret_str1, *ret_str2;

	input(str1, serch_str1);

	/*ret_str1 = serch_str(str1, serch_str1);*/

	printf("ֱ�ӵ��ú���serch_str()/n");
	/*printf(ret_str1);*/

	input(str2, serch_str2);

	fun = serch_str;
	ret_str2 = fun(str2, serch_str2);

	printf("ʹ�ú���ָ��fun���ú���serch_str()/n");
	printf(ret_str2);

	return ;

}