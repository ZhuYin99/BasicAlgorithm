
//���ܣ���ɴӼ���¼�����ݣ�Ȼ���С�������������
//˼·:���ú���readkeyboarddata(int data[],int length)������룬����
// ���� directinsertsorting(int data[],int length)��������ܡ�
//����������100����

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 21  //�����СԤ����

void showMenu();                            //��ʾ�˵�
void readkeyboarddata(int data[],int length);//�Ӽ��̶�������
void directinsertsorting(int data[],int length);//ֱ�Ӳ���������

/*����������������������������������������������������//
�� �� ��:main����
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
int main()
{
	int i,data[MAXSIZE],choose;
	int length;//���Ա���
	while(1)
	{
		system("cls");
		showMenu();
		printf("��ѡ���ܱ��:\n");
		scanf("%d",&choose);
		switch(choose)
		{
		case 1:
			printf("������Ҫ��������ݸ�����(ע�ⲻ����%d��)\n",MAXSIZE-1);
			scanf("%d",&length);
			if(length>20)
			{
				printf("������ĸ��������������\n",length);
				system("pause");
				continue;
			}
			printf("�뿪ʼ�������ݣ�һ��%d�����ݣ����ÿո�ֿ���\n",length);
			readkeyboarddata(data,length);
			directinsertsorting(data,length);
			printf("�����Ϊ�� \n");
			for(i=1;i<=length;i++)
				printf("%d  ",data[i]);
			printf("\n");
			system("pause");
			break;
		case 2:
			return 0;
		}	

	}
}

/*����������������������������������������������������//
�� �� ��:showMenu
��    ��:��ʾ���ܲ˵�
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void showMenu()
{
	printf("                ===========================\n");
	printf("                ֱ�Ӳ�������\n");
	printf("                ���ߣ�heqinghqocsh\n");
	printf("                ===========================\n");
	printf("                1.�������ݲ��������\n");
	printf("                2.�˳�����\n");
	printf("                ===========================\n");
}

/*����������������������������������������������������//
�� �� ��:readkeyboarddata
��    ��:�Ӽ���¼������
��ڲ���:�����������Ա���
���ڲ���:��
//����������������������������������������������������*/
void readkeyboarddata(int data[],int length)     //�Ӽ��̶�������
{
	int i;
	for(i=1;i<=length;i++)//����0��Ԫ����Ҫ�� <=
		scanf("%d",&data[i]);
}

/*����������������������������������������������������//
�� �� ��:directinsertsorting
��    ��:���Ԫ�ص�����
��ڲ���:�����������Ա���
���ڲ���:��
//����������������������������������������������������*/
void directinsertsorting(int data[],int length)  //ֱ�Ӳ���������
{
	int term;//ָ��δ�����ݵ���λ��
	int i,j,item;
	for(term=1;term<=length;term++)
	{
		for(i=1;i<term;i++)
			if(data[i]>data[term])
			{
				item=data[term];
				for(j=term;j>i;j--)//����С�������Ƶ�ǰ��
					data[j]=data[j-1];
				data[i]=item;
				break ;
			}
	}
}