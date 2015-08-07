//��Ҫ���ܣ�������ͼʾ�ķ�ʽչʾn�ʺ󾭵��������⣨C�棩��
//����������϶ֱ࣬��д���ı��ļ���򿪼��ɡ�
//�������ƣ�n�ʺ󾭵�����������

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>  

#define QUEENMAXCOUNT  40		//���ûʺ��������
#define KINDSOFWRITEFILE  1000	//���ñ����ļ������������ֵ
int queenarray[QUEENMAXCOUNT];		//���ڱ���ʺ�������Ϣ
tm starttimer, finishtimer; //��ʼʱ�����ʱ��
int  kindscount;			 //�������������
int  actualcount;			 //��ǰ����»ʺ����


void startruning();			 //��ʼ������
void finish();				 //����������
void nNQueens(int queesnumnow);	//���ݷ���⺯��
bool place(int queesnumnow,int col); //�����жϺ���
bool writefile();				 //д�ļ�����

void clearscreen(void);//��������
void showmenu(void);//��ʾ�˵�
void processmenu(void);//��������ִ��ָ������

/*����������������������������������������������������//
�� �� ��:main
 ��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void main(void)                     //���������
{   
	system("color f0");//������ɫ
	clearscreen();//������
    while (1)
	{
		showmenu();//��ʾ�˵�
		processmenu();//ִ��ָ������
		system("pause");//��ͣһ��
		clearscreen();//����
    }
}//����������

 /*����������������������������������������������������//
 �� �� ��:startruning
 ��    ��:��ʼ������
 ��ڲ���:��
 ���ڲ���:��
//����������������������������������������������������*/
void startruning()
{
	kindscount = 0;				//��������ʼ��

	time_t presemtTime;

	printf("������ʺ������ע�ⲻ����%d)\n",QUEENMAXCOUNT);
	scanf("%d",&actualcount);//����ʺ�ĸ���
	if(actualcount > QUEENMAXCOUNT)
	{
		printf("\n����ܰ��ʾ���ʺ��������%d��������Ҫ��\n",QUEENMAXCOUNT);
		printf("==============================================\n");
		return ;
	}
	else if(actualcount > 10)		//���ʺ��������10ʱ���������ܴ�
	{
		printf("\n����ܰ��ʾ���ʺ�����϶࣬�����У���ȴ�......\n");
	}
	else if(actualcount < 4)
	{
		printf("\n����ʾ��%d�ʺ�����û�н�!!!\n",actualcount);
		printf("==============================================\n");
		return;   //��ʱ�޽�
	}		
	time(&presemtTime);
	starttimer = *localtime(&presemtTime);  //����ʼʱ��
	nNQueens(0); 
	time(&presemtTime);
	finishtimer = *localtime(&presemtTime); //�������ʱ��
	finish();
}

void nNQueens(int queesnumnow)
{
	if(kindscount < KINDSOFWRITEFILE )
	{  //����д���ļ��ĸ���
		for(int col = 0;col < actualcount;col++)
		{
			if(place(queesnumnow,col))//�ж�λ���Ƿ����Ҫ��
			{
				queenarray[queesnumnow] = col;
				if(queesnumnow == actualcount-1) //Լ������
				{
					kindscount++;	 //������
					writefile();	 //д���ļ���
				}
				else
					nNQueens(queesnumnow+1);
			}
		}
	}
}

/*����������������������������������������������������//
�� �� ��:finish
��    ��:����������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void finish()//���ؽ����Ϣ
{
	int hour,minute,second;//Сʱ�����ӣ���
	hour = finishtimer.tm_hour-starttimer.tm_hour;
	minute = finishtimer.tm_min-starttimer.tm_min;
	second = finishtimer.tm_sec-starttimer.tm_sec;

	if(actualcount<11)
		printf("\n�ʺ����з�ʽһ����%d�֡�\n\n",kindscount);
	else
		printf("\n�ʺ����е�����̫�࣬�������������ֻȡ���е�%d��д���ļ���\n",KINDSOFWRITEFILE);
	printf("\n��ʱ����ʾ�������β�������ʱ��Ϊ(ע����ȷ����)��");

	printf("%dʱ%d��%d�롣\n\n",hour,minute,second);

	printf("������ϣ�ϵͳ���Զ����ļ�����鿴...\n");		
	ShellExecute(NULL,"open","n-�ʺ�����.txt",NULL,NULL,SW_SHOWNORMAL);
	printf("==============================================\n");
}

/*����������������������������������������������������//
�� �� ��:place
��    ��:�ж������ʺ��Ƿ���ͬһ�л���һ��б����
��ڲ���:
���ڲ���:���������ʺ��Ƿ���ͬһ�л���һ��б���ϵ���Ϣ
//����������������������������������������������������*/
bool place(int queesnumnow,int col)//�ж������ʺ��Ƿ���ͬһ�л���һ��б����
{     
	for(int row = 0;row < queesnumnow;row++)
		if((queenarray[row] == col) 
			|| (abs(queenarray[row]-col) == abs(row-queesnumnow)))
			return false;
		return true;
}

/*����������������������������������������������������//
�� �� ��:writefile
��    ��:�����д���ļ�
��ڲ���:��
���ڲ���:����д���ļ�����Ϣ
//����������������������������������������������������*/
bool writefile()
{
	if(kindscount == 1)   //��count=1ʱ����.txt�ļ���ա�
	{
			FILE * out = fopen("n-�ʺ�����.txt","w");//�����ļ�ָ��
		if(out)			
			fprintf(out,"\t\t\t  %d�ʺ������������ \n",actualcount);
		fclose(out);
	}		
	FILE * out = fopen("n-�ʺ�����.txt","ab");//�����ļ�ָ��

	int colcount,rowcount,col;
	fprintf(out,"\n\t\t�ڡ�%d���ַ�ʽ��(",kindscount);
	for(col = 0;col < actualcount-1;col++)
		fprintf(out,"%d,",queenarray[col]+1);
	fprintf(out,"%d)\r\n",queenarray[actualcount-1]+1);
	for(colcount = 0;colcount < actualcount;colcount++)
	{
		if(colcount==0)
		{
			fprintf(out,"\t\t����");
			for(col = 1;col < actualcount;col++)
				fprintf(out,"�ש�");
			fprintf(out,"��\r\n");
		}
		else
		{
			fprintf(out,"\t\t�ǩ�");
			for(col = 1;col < actualcount;col++)
				fprintf(out,"�贈");
			fprintf(out,"��\r\n");
		}
		
		fprintf(out,"\t\t��");
		for(rowcount = 0;rowcount < actualcount;rowcount++)
		{
			if(rowcount == queenarray[colcount])
				fprintf(out,"�逸");
			else
				fprintf(out,"  ��");
		}
		fprintf(out,"\r\n");
	}
	fprintf(out,"\t\t����");
	for(col = 1;col < actualcount;col++)
		fprintf(out,"�ߩ�");
	fprintf(out,"��\r\n");
	fclose(out);     //�ر��ļ�
	return true;
}

/*����������������������������������������������������//
�� �� ��:clearscreen
��    ��:����
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void clearscreen(void)
{
    system("cls");
}

/*����������������������������������������������������//
�� �� ��:showmenu
��    ��:��ʾ�˵�
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void showmenu(void)
{
    printf("======================================\n");	
	printf("         n�ʺ󾭵�����������        \n");	
	printf("======================================\n");	
    printf("�������˵����                        \n");	
    printf("  ��n*n����ͼʾ�ķ�ʽչʾ�˻ʺ󾭵���\n");	
    printf("�����⡣����������϶ֱ࣬��д����\n");	
    printf("���ļ����ɡ�                          \n");	
	printf("======================================\n");	
    printf("             ���ܲ˵�                 \n");	
    printf("======================================\n");	
    printf(" 1.���n�ʺ�����                      \n");	
    printf(" 2.�˳����                           \n");	
	printf("======================================\n");	
	printf("����������ѡ��");
}
/*����������������������������������������������������//
�� �� ��:processmenu
��    ��:ִ��ָ������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void processmenu(void)
{
	char menuchoice;
	fflush(stdin);//�����س�Ӱ��
	scanf("%c",&menuchoice);
	switch(menuchoice)    //�����û���ѡ�������Ӧ�Ĳ���
	{
	case '1':
		startruning();	  //�������Ա����
		break;
	case '2':
		printf("\n\n���Ѿ��ɹ��˳���ϵͳ����ӭ�ٴ�ʹ��!!!\n");
		system("pause");
		exit(0);
	default:
		printf("�Բ���������Ĺ��ܱ���д�!����������!!!\n");
		break;
	}
}
