//���ܣ��õݹ麯����Recursion��������쳲��������е�ĳ��ֵ

#include<stdio.h>
#include<windows.h>


long int fibrecursion(long int num);
void startcalcu();
long int num;

/*����������������������������������������������������//
�� �� ��:main
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void main(void)
{
	system("color f0");
	SetConsoleTitle("�õݹ麯����Recursion��������쳲��������е�ĳ��ֵ");
	printf("�õݹ麯����Recursion��������쳲��������е�ĳ��ֵ!\n");
    startcalcu();
	system("pause"); 
}

/*����������������������������������������������������//
�� �� ��:fibrecursion
��    ��:�ݹ麯��
��ڲ���:Ҫ�����λ��
���ڲ���:���
//����������������������������������������������������*/
long fibrecursion(long num)
{
	if  (num<=2)  
		return 1;     //�ݹ����
	else  
		return(fibrecursion(num-1)+fibrecursion(num-2));//�ݹ����
} 

/*����������������������������������������������������//
�� �� ��:startcalcu
��    ��:��ʾ
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void startcalcu()
{
	long int product;
	printf("����������:");
	scanf("%d",&num);
	product=fibrecursion(num);
	printf("����ǣ�%d\n",product);
}        
