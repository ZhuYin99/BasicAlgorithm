//���ܣ�ͨ�����������������ݣ�Ȼ���С�������������
//˼·:���ú���display(int data[],int length)�����ʾ������
// ���� bubblesort(int data[],int length)��������ܡ�
//����������80����

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 11  //�����СԤ����,����0��Ԫ


void bubblesort(int data[],int length);//ð��������
void generaterandomdata(int data[],int length);//�����������
void display(int data[],int length);//������������

/*����������������������������������������������������//
�� �� ��:main����
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
int main()
{
	int i,data[MAXSIZE];
	char choose;
	while(1)
	{
		system("cls");
		printf("��ѡ�������������� heqinghqocsh\n\n");
		printf("ϵͳ���Զ�����10��11��99֮�������\n");
		generaterandomdata(data,MAXSIZE);
		printf("ϵͳ����������������ǰ��\n");
		display(data,MAXSIZE);
		bubblesort(data,MAXSIZE);
		printf("�����Ϊ�� \n");
		display(data,MAXSIZE);
		printf("�Ƿ������Y/N����");
		scanf("%c",&choose);
		fflush(stdin);//���Ե����س���
		if(choose!='Y'&&choose!='y')
			break;
	}
	return 0;
}

/*����������������������������������������������������//
�� �� ��:display
��    ��:������������
��ڲ���:�����������Ա���
���ڲ���:��
//����������������������������������������������������*/
void generaterandomdata(int data[],int length)//�����������
{
	int i;
	for(i=1;i<length;i++)
		data[i]=rand()%88+11;//��ϵͳ�������10��11��99֮�������
}

/*����������������������������������������������������//
�� �� ��:display
��    ��:������������
��ڲ���:�����������Ա���
���ڲ���:��
//����������������������������������������������������*/
void display(int data[],int length)//������������
{
	int i;
	for(i=1;i<length;i++)
	{
		printf("%d  ",data[i]);
	}
	printf("\n");
}

/*����������������������������������������������������//
�� �� ��:simpleselectsort
��    ��:���Ԫ�ص�����
��ڲ���:�����������Ա���
���ڲ���:��
//����������������������������������������������������*/
void bubblesort(int data[],int length)  //ð��������
{
	int i,item,term;
	for(term=1;term<length-1;term++)//����0��Ԫ,�±��1��ʼ
	{
		for(i=1;i<length-term;i++)//��ÿһ�˱Ƚ��н���10-term�������Ƚ�
			if(data[i]>data[i+1])//�����������Ƚ�
			{
				item=data[i];//��������
				data[i]=data[i+1];
				data[i+1]=item;
			}
	}
}