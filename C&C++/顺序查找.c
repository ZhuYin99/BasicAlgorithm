//˳��������ַ����������ҡ����ҵ��󡢴��ڱ�Ԫ�أ���ϸ�ڶԱȳ���

#include<stdio.h>
#include<windows.h>

#define datawidth 5     //����������ʾ���
#define arraymaxnum 21  //Լ�������С,0�ŵ�ԪĬ�ϲ��ã����û����ݿ��Խ���20��
#define defaultnum  13  //Լ��Ĭ�����������С������ʹ�ý̲�ʵ�ʷ���
int defaultdata[defaultnum]={0,32,10,41,60,24,82,60,90,45,60,23,75};//0���±�Ĭ�ϲ��ã��ʴ�0
int flag=0;             //��ʾ�û�û���������ݣ�ʹ��Ĭ������



int  ltorsearching(int *data,int length,int seekdata);//l:left�� r:right�� to:��
int  rtolsearching(int *data,int length,int seekdata);
int guardsearching(int *data,int length,int seekdata);//�ڱ�Ԫ�ز��ҷ�
void   displaydata(int *data,int length             );

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
	SetConsoleTitle("˳����ң�C�棩���ߣ�heqinghqocsh");
    while (1)
	{
		showmenu();
		processmenu();
		system("pause");
		system("cls");
    }
}//����������

/*����������������������������������������������������//
�� �� ��:ltorsearching
��    ��:�����Ҳ���
��ڲ���:Ŀ�����飬���鳤�ȣ�Ҫ���ҵ�����
���ڲ���:���ݵ�λ����Ϣ
//����������������������������������������������������*/
int ltorsearching(int *data,int length,int seekdata)
{
	int i=1;//������ʱ����ʼ���ҵ��±�Ϊ1
	while(i<=length && data[i]!=seekdata)//��������Ϊ����û���������û���ҵ�ʱһֱѭ��
		i++;
	if(i<=length)//�����������Χ�ڽ�����˵���ҵ��ˣ�����˵������ʧ��
		return i;
	else
		return 0;
}

/*����������������������������������������������������//
�� �� ��:rtolsearching
��    ��:���ҵ������
��ڲ���:Ŀ�����飬���鳤�ȣ�Ҫ���ҵ�����
���ڲ���:���ݵ�λ����Ϣ
//����������������������������������������������������*/
int rtolsearching(int *data,int length,int seekdata)
{
	int i=length;//���ҵ���ʱ����ʼ���ҵ��±�Ϊlength
	while(i>0 && data[i]!=seekdata)
		i--;
	if(i>=1)
		return i;
	else
		return 0;
}

/*����������������������������������������������������//
�� �� ��:guardsearching
��    ��:�ڱ�����
��ڲ���:Ŀ�����飬���鳤�ȣ�Ҫ���ҵ�����
���ڲ���:���ݵ�λ����Ϣ
//����������������������������������������������������*/
int guardsearching(int *data,int length,int seekdata)
{
	int i=length;//�ڱ�����
	data[0]=seekdata;
	while(data[i]!=seekdata)//���㷨���ŵ㣬�����������ĳ���һ�����������߼�������	
		i--;
	return i;
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
��    ��:��ʾ�˵�
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void showmenu(void)
{
	printf("  ˳����ҹ�����ʾ  \n");
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
		printf("���������ݣ��ո��������\n");
		for(i=1;i<=datanumber;i++)
			scanf("%d",&workingdata[i]);
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
		printf("���ҽ�����£�\n");
		//��ʼ���ҵĹ���
		position=ltorsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("�����Ҳ��ҳɹ��������� %-2d ��λ���ϡ�\n",position);
		else
			printf("�����Ҳ��ҷ�����ʧ�ܡ�\n");
		position=rtolsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("���ҵ�����ҳɹ��������� %-2d ��λ���ϡ�\n",position);
		else
			printf("���ҵ�����ҷ�����ʧ�ܡ�\n");
		position=guardsearching(workingdata,datanumber,searchdata);
		if(position)
			printf("���ڱ������ҳɹ��������� %-2d ��λ���ϡ�\n",position);
		else
			printf("���ڱ����ҷ�������ʧ�ܡ�\n");
		printf("==============\n");
		break;
	case 0:
		system("pause");
		exit(1);
	default: 
		printf("�����д�����������...\n");
	}
}
