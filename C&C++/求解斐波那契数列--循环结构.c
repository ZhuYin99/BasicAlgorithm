//���ܣ������ѭ���ṹ��loop�������쳲��������е�ĳ��ֵ

#include<stdio.h>
#include<windows.h>

long int fibloop(long int num);//ѭ���ṹ����
void startcalcu(void);
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
	SetConsoleTitle("�����ѭ���ṹ��loop�������쳲��������е�ĳ��ֵ��C�棩");
	printf("�����ѭ���ṹ��loop�������쳲��������е�ĳ��ֵ!\n");
    startcalcu();
	system("pause"); 
}

/*����������������������������������������������������//
�� �� ��:fibloop
��    ��:ѭ���ṹ����
��ڲ���:λ��
���ڲ���:���
//����������������������������������������������������*/
long fibloop(long num)    //ѭ���ṹ����
{
	long backtwo,backone,currentdata;   
	int count;
	if(num<=2)
		return 1;
    else 
	{
		backtwo=1;backone=1;  //�����������׼����
		for(count=3;count<=num;count++)
		{  
			currentdata=backone+backtwo;   //�������µ�һ������
			backtwo=backone;    //�ѻ�׼������ǰ�ƶ� 
			backone=currentdata;
		}  
		return  currentdata;
	}
}  

/*����������������������������������������������������//
�� �� ��:startcalcu
��    ��:��ʾ
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void startcalcu(void)
{
	long int result;
	printf("����������:");
	scanf("%d",&num);
	result=fibloop(num);
	printf("����ǣ�%d\n",result);
}

