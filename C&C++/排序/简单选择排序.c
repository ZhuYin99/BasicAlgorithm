//���ܣ���ɴӼ���¼�����ݣ�Ȼ���С�������������
//˼·:���ú���display(int data[],int length)�����ʾ������
// ���� simpleselectsort(int data[],int length)��������ܡ�
//����������60����

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 11  //�����СԤ����,����0��Ԫ


void simpleselectsort(int data[],int length);//��ѡ��������
void display(int data[],int length);//������������

/*����������������������������������������������������//
�� �� ��:main����
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
int main()
{
	int i,data[MAXSIZE]={0,12,9,25,19,3,58,62,34,85,70};//Ĭ�����ݣ�����0��Ԫ
	printf("��ѡ����������heqinghqocsh\n\n");
	printf("�Ѵ��ڲ����鴴����10������.\n����ǰ��\n");
	display(data,MAXSIZE);
	simpleselectsort(data,MAXSIZE);
	printf("�����Ϊ�� \n");
	display(data,MAXSIZE);
	system("pause");
	return 0;	
	
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
void simpleselectsort(int data[],int length)  //ֱ�Ӳ���������
{
	int term;//ָ��δ�����ݵ���λ��
	int i,j,item;
	for(term=1;term<length;term++)
	{
		item=data[term];
		for(i=term;i<length;i++)
			if(data[i]<=item)
			{
				item=data[i];//����δ��������С����
				j=i;          //����δ��������С���ݵ�λ��
			}
			data[j]=data[term];
			data[term]=item;
	}
}