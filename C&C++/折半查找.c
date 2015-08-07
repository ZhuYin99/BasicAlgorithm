//�۰���Ҷ��ַ������ǵݹ��۰���ҡ��ݹ��۰���ң���ϸ�ڶԱȳ���

#include<stdio.h>
#include<windows.h>
 
#define arraymaxnum 21//Լ�������С,0�ŵ�ԪĬ�ϲ��ã����û����ݿ��Խ���20��
#define defaultnum 10//Լ��Ĭ�����������С������ʹ�ý̲�ʵ�ʷ���
int defaultdata[defaultnum]={0,12,22,36,48,52,56,64,76,83};//0���±�Ĭ�ϲ��ã��ʴ�0
int flag=0;//��ʾ�û�û���������ݣ�ʹ��Ĭ������
int count[2]={0,0};//����ҵĴ���

int halfsearching(int *data,int length,int seekdata);//�ǵݹ��۰����
int halfrsearching(int *data,int head,int tail,int seekdata);//�ݹ��۰����,r:�ݹ�
void displaydata(int *data,int length);

//�˵���ʾ
int workingdata[arraymaxnum]; 
int datanumber,searchdata;
void showmenu(void);
void processmenu(void);

/*����������������������������������������������������//
�� �� ��:main
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void main(void) //���������
{
	system("color f0");
	system("cls");
	SetConsoleTitle("�۰���ң�C�棩���ߣ�heqinghqocsh");
    while (1)
	{
		showmenu();
		processmenu();
		system("pause");
		system("cls");
    }
}//����������

/*����������������������������������������������������//
�� �� ��:halfsearching
��    ��:�ǵݹ��۰����
��ڲ���:Ŀ�����飬���鳤�ȣ�Ҫ���ҵ�����
���ڲ���:Ŀ�����ݵ�λ����Ϣ
//����������������������������������������������������*/
int halfsearching(int *data,int length,int seekdata)
{
	int low=1,high=length,flag=0,mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		count[0]++;
		if(data[mid]==seekdata)//�˴������������±��ַ�ķ�����ȡ����
		{
			flag=1;
			break;
		}
		else if(data[mid]>seekdata)
			high=mid-1;
		else
			low=mid+1;
	}
	if(flag==1)
		return mid;
	else
		return 0;
}

/*����������������������������������������������������//
�� �� ��:halfrsearching
��    ��:�ݹ��۰����
��ڲ���:Ŀ�����飬ͷλ�ã�βλ�ã�Ҫ���ҵ�����
���ڲ���:Ŀ�����ݵ�λ����Ϣ
//����������������������������������������������������*/
int halfrsearching(int *data,int head,int tail,int seekdata)
{
	int mid=(tail+head)/2;
	count[1]++;
	if(tail<head)
		return 0;
	if(*(data+mid)==seekdata)//�˴���������������ʼ��ַ����ƫ�����ķ�����ȡ����
		return mid;
	else if(*(data+mid)<seekdata)
		return halfrsearching(data,mid+1,tail,seekdata);
	else
		return halfrsearching(data,head,mid-1,seekdata);
}

/*����������������������������������������������������//
�� �� ��:displaydata
��    ��:��ʾĿ������
��ڲ���:Ŀ�����飬���鳤��
���ڲ���:��
//����������������������������������������������������*/
void displaydata(int *data,int length)//������1��ʼ��ʾ����number������
{
	int i;
	printf("���꣺");
	for(i=1;i<=length;i++)
		printf("%-5d",i);
	printf("\n");
	printf("���ݣ�");
	for(i=1;i<=length;i++)
		printf("%-5d",data[i]);
	printf("\n");
}

/*����������������������������������������������������//
�� �� ��:showmenu
��    ��:�˵���ʾ
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void showmenu()
{
	printf("  �۰���ҹ�����ʾ  \n");
   	printf("====================\n"); 
	printf("��ʾ��ֱ��ѡ�����3 \n"); 
	printf("      ��ʹ��Ĭ������\n"); 
	printf("====================\n"); 
	printf("1.��������������    \n");
	printf("2.�ָ�ʹ��Ĭ������  \n"); 
	printf("3.��ʼ����          \n"); 
	printf("0.��������          \n"); 
	printf("====================\n");
}

/*����������������������������������������������������//
�� �� ��:processmenu
��    ��:�����û�����ִ��ָ������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void processmenu()
{   
	int choice,position,i;
	printf("������ѡ�");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		do
		{
			printf("���������ݸ�����(������%d��)\n",arraymaxnum-1);
			scanf("%d",&datanumber);
		}while(datanumber>=arraymaxnum); 
		printf("���������ݣ�ע�����Խ��Խ�󣩣�\n");
		for(i=1;i<=datanumber;i++)
		{
			printf("������� %d �����ݣ�\n",i);
			scanf("%d",&workingdata[i]);
			if(workingdata[i]<workingdata[i-1])
				do
				{
					printf("���ݲ�����Ҫ�����������뱾����(ע�����ݱ������)��\n");
					scanf("%d",&workingdata[i]);
				}while(workingdata[i]<workingdata[i-1]);
		}

		flag=1;//��ʾ�û�����������
		printf("�����������Ϊ��\n");
		printf("==============\n");
		displaydata(workingdata,datanumber);
		printf("==============\n");
		break;
	case 2:
		for(i=1;i<=defaultnum;i++)
			workingdata[i]=defaultdata[i];
		flag=0;//��ʾ���ݻָ���
		printf("==============\n");
		printf("Ĭ�������Ѿ��ָ���\n");
		printf("==============\n");
		break;

	case 3:
		if(flag==0)//���Ա�־λ
		{
			datanumber=defaultnum-1;
			for(i=1;i<=datanumber;i++)//��Ĭ�����ݴ��������Ϊ��������
				workingdata[i]=defaultdata[i];
			printf("������Ĭ�Ϲ�������Ϊ��\n");
		}
		else
		{
			printf("�û�����Ĺ�������Ϊ��\n");
		}
		displaydata(workingdata,datanumber);
		printf("��������Ҫ�ҵ����ݣ�\n");
		scanf("%d",&searchdata);
		printf("==============\n");
		count[0]=count[1]=0;
		printf("���ҽ�����£�\n");
		//��ʼ���ҵĹ���
		position=halfsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("�۰�ǵݹ鷨���ҳɹ��������� %2d ��λ���ϡ��Ƚϴ��� %d\n",position,count[0]);
		else
			printf("�۰�ǵݹ鷨����ʧ�ܡ�\n");

		position=halfrsearching(workingdata,1,datanumber,searchdata);
		if(position)
			printf("�۰�ݹ鷽�����ҳɹ��������� %2d ��λ���ϡ��Ƚϴ��� %d\n",position,count[1]);
		else
			printf("�۰�ݹ鷽������ʧ�ܡ�\n");
		break;
	case 0:
		system("pause");
		exit(1);
	default: 
		printf("�����д�����������...\n");
	}
}
