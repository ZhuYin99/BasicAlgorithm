#include<stdio.h>
#include<windows.h>
class swapClass
{
public:
	swapClass(){};
	~swapClass(){};
	void swap(int &a,int &b);
	void swap(char &a,char &b);//���ص�һ��
};

void swapClass::swap(int &a,int &b)
{
	a = a-b;
	b = b+a;
	a = b-a;
}

void swapClass::swap(char &a,char &b)
{
	a = a-b;
	b = b+a;
	a = b-a;
}

void main()
{
	system("color f0");
	char ch1,ch2;
	int a = 10,b = 20;
	ch1 = 'a';
	ch2 = 'd';
	swapClass swapInstance;

	printf("ע���������غ����ĺ����嶼һ����\n����ʵ���ַ��������Ľ�����\n�������м����.\n\n");

	printf("������Ҫ�����������ַ����ո������:\n");
	fflush(stdin);
	scanf("%c %c",&ch1,&ch2);

	printf("������Ҫ�����������������ո������:\n");
	fflush(stdin);
	scanf("%d%d",&a,&b);

	printf("����֮ǰΪ��\n");
	printf("ch1=%c ch2=%c\n",ch1,ch2);
	printf("a=%d b=%d\n",a,b);

	swapInstance.swap(ch1,ch2);
	swapInstance.swap(a,b);

	printf("����֮��Ϊ��\n");
	printf("ch1=%c ch2=%c\n",ch1,ch2);
	printf("a=%d b=%d\n",a,b);
}
