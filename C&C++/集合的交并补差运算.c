//�������������򹹽� 3-3�����ϵĽ���������ܣ���C�棩.cpp
//���ܣ���ɼ��ϵ��󽻣��󲢣�����ʾ���ܡ�

//�Ľ���1.���û������벻������Ӣ����ĸ  2.�Ż���������  3.�޸�һЩbug����֮ǰû���ͷſռ�Ĳ���  4.�Ż����ִ���

#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h>
#include<string.h>
#include<windows.h>

typedef struct Setmember//���弯����Ԫ�ؽṹ��
{ 
	char data; 
	Setmember *next;
} Setmember; 

#define len sizeof(struct Setmember)//�궨��Ҫ���ٵĿռ��С
//��������ͷ��㣬�ֱ��Ǽ���һ�ͼ��϶��Լ����ǵĽ��������������ͷ���
Setmember *head1,*head2,*headresult;

//��������
void init();                                                        //��ʼ��������Ϊ������������׼��
int  main_menu();                                                  	//���˵�����
void read_data(Setmember *head);                                   	//��ȡ���ݺ���
void display(Setmember *head);                                      //��ʾ���ݺ���
void destroy(Setmember *head);                                                     //���������ͷſռ�
void Setintersection(Setmember *head1,Setmember *head2, Setmember *headresult);   //�󼯺Ͻ�������
void Setunion(Setmember *head1,Setmember *head2, Setmember *headresult);          //�󼯺ϲ�������
void Setdifference(Setmember *head1,Setmember *head2, Setmember *headresult);     //�󼯺ϲ����
/*����������������������������������������������������//
�� �� ��:main
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void main()
{ 
	init();//��ʼ��
	system("color f0");
	SetConsoleTitle("���ϵĽ���������");
	for(;;)//��������ѭ�����
	{
		system("cls");								/*����*/
		switch(main_menu())
		{
			
		case 1:
			
			destroy(head1);//���ͷ�����head1
			destroy(head2);//���ͷ�����head2
			
			printf("�������ַ��������뼯��һ�ͼ��϶��е�Ԫ�أ�\n");
			fflush(stdin);//�����س�Ӱ��
			printf("�����뼯��1��\n"); 
			read_data(head1); 
			fflush(stdin);
			printf("�����뼯��2��\n"); 
			read_data(head2); 
			system("pause");
			break;
		case 2:
			printf("����1Ϊ��\n"); 
			display(head1); 
			printf("����2Ϊ��\n"); 
			display(head2); 
			system("pause");
			break;
		case 3:
			printf("����1Ϊ��\n"); 
			display(head1); 
			printf("����2Ϊ��\n"); 
			display(head2); 
			printf("����1�뼯��2�Ĳ�Ϊ:\n"); 
			Setunion(head1,head2,headresult); 
			display(headresult); 
			system("pause");
			destroy(headresult);//�����ƺ��ͷ�����headresult
			break;
		case 4:
			printf("����1Ϊ��\n"); 
			display(head1); 
			printf("����2Ϊ��\n"); 
			display(head2); 
			printf("����1�뼯��2�Ľ�Ϊ:\n"); 
			Setintersection(head1,head2,headresult); 
			display(headresult); 
			system("pause");
			destroy(headresult);//�����ƺ��ͷ�����headresult
			break;
		case 5:
			printf("����1Ϊ��\n"); 
			display(head1); 
			printf("����2Ϊ��\n"); 
			display(head2);
			printf("����1�뼯��2�Ĳ�Ϊ:\n"); 
			Setdifference(head1,head2,headresult); 
			display(headresult); 
			system("pause");
			destroy(headresult);//�����ƺ��ͷ�����headresult
			break;
		case 0: 
			system("cls");
			exit(0);
		default :
			{	
				fflush(stdin);											/*�建��*/
				printf("\tѡ���������ȷ��������ѡ��(1~6):\n");
				system("pause");
			}
			
		}
	}
}

/*����������������������������������������������������//
�� �� ��:init()
��    ��:��ʼ��������Ϊ������������׼��
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void init()
{
	//���ټ���һ��ͷ���
	head1=(Setmember *)malloc(len); 
	head1->next=NULL; 
	//���ټ��϶���ͷ���
	head2=(Setmember *)malloc(len); 
	head2->next=NULL; 
	//���ټ�����������ͷ���
	headresult=(Setmember *)malloc(len); 
	headresult->next=NULL;
}

/*����������������������������������������������������//
�� �� ��:destroy()
��    ��:��ʼ��������Ϊ������������׼��
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void destroy(Setmember *head)
{
	Setmember *presentp,*searchp; 
	searchp = head->next;               //�ͷ�head1����
	while(searchp)
	{
		presentp = searchp;
		searchp = searchp->next;
		delete presentp;
	}
}

/*����������������������������������������������������//
�� �� ��:main_menu()
��    ��:��ʾ���ܲ˵�
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
int main_menu()
{
	
	int choose;
	printf("\n\n\n");
	printf("\t\t****************���ϵĳ�������ϵͳ****************\n");
	printf("\t\t   1�����뼯��һ�ͼ��϶�\n");
	printf("\t\t   2����ʾ�Ѿ�����ļ���һ�ͼ��϶�\n");
	printf("\t\t   3������һ�뼯�϶��Ĳ���Ϊ\n");
	printf("\t\t   4������һ�뼯�϶��Ľ���Ϊ\n");
	printf("\t\t   5������һ�뼯�϶��ĲΪ\n");
	printf("\t\t   0���˳�\n");
	printf("\t\t******************************************************\n");
	printf("�����빦��ѡ�");
	scanf("%d",&choose);
	return choose;
}
/*����������������������������������������������������//
�� �� ��:read_data
��    ��:��ȡ����
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void read_data(Setmember *head)
{ 
	Setmember *newdatap,*searchp = head; 
	char temp; 
	scanf("%c",&temp); 
	while(temp!='\n') //�ж��û�������Ƿ��ǻس������Դ��ж��û��Ƿ��������
	{
		newdatap=(Setmember *)malloc(len); 
		newdatap->data=temp;                      //��ֵ
		searchp->next = newdatap;                //����
		searchp = searchp->next;
		scanf("%c",&temp); 
	}
	searchp->next = NULL;
} 
/*����������������������������������������������������//
�� �� ��:display
��    ��:��ʾ����Ԫ�غ���
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void display(Setmember *head)
{ 
	Setmember *searchp=head->next; 
	printf("\t{");
	if(searchp == NULL)
		printf("��");
	else
		while(searchp!=NULL) 
		{ 
			printf("%c ",searchp->data); 
			searchp=searchp->next; 
		} 
		printf("}\n"); 
} 
/*����������������������������������������������������//
�� �� ��:Setunion
��    ��:���㼯��һ�뼯�϶��Ĳ�����
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void Setunion(Setmember *head1,Setmember *head2, Setmember *headresult)
{ 
	Setmember *searchp1,*searchp2,*newdata,*temp;
	temp = headresult;
	searchp1=head1->next; 
	while(searchp1!=NULL) 
	{ 
		newdata=(Setmember *)malloc(len); //���ٿռ�
		newdata->data=searchp1->data;     //��ֵ
		temp->next = newdata;             //����
		temp = temp->next; 
		searchp1=searchp1->next; 
	} 
	searchp2=head2->next; 
	while(searchp2!=NULL) 
	{ 
		searchp1=head1->next; 
		while(searchp1!=NULL)
		{
			if(searchp2->data==searchp1->data)
				break;
			searchp1=searchp1->next; 
		}
		if(searchp1 == NULL)
		{
			newdata=(Setmember *)malloc(len); 
			newdata->data=searchp2->data; 
			temp->next = newdata;             //����
			temp = temp->next; 
		}
		searchp2=searchp2->next; 
	} 
	temp->next = NULL;
} 
/*����������������������������������������������������//
�� �� ��:Setintersection
��    ��:���㼯��һ�ͼ��϶��Ľ�����
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void Setintersection(Setmember *head1,Setmember *head2, Setmember *headresult)
{ 
	Setmember *searchp1,*searchp2,*newdata,*temp; 
	temp = headresult;
	searchp1=head1->next; 
	while(searchp1!=NULL) 
	{ 
		searchp2=head2->next; 
		while(searchp2!=NULL)
		{
			if(searchp1->data==searchp2->data)//�ж�Ԫ���Ƿ���ȣ�����Ǿͽ�Ԫ�ع�����headresult����
			{
				newdata=(Setmember *)malloc(len); 
				newdata->data=searchp1->data; 
				temp->next = newdata;             //����
				temp = temp->next; 
				break;
			}
			searchp2=searchp2->next; 
		}
		searchp1=searchp1->next; 
	} 
	temp->next = NULL;
} 
/*����������������������������������������������������//
�� �� ��:Setdifference
��    ��:���㼯��һ�뼯�϶��Ĳ��
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void Setdifference(Setmember *head1,Setmember *head2, Setmember *headresult)
{ 
	Setmember *searchp1,*searchp2,*newdata,*temp; 
	searchp1=head1->next;
	temp = headresult;
	while(searchp1!=NULL) 
	{
		searchp2=head2->next; 
		while((searchp2!=NULL)&&(searchp1->data!=searchp2->data)) 
			searchp2=searchp2->next; 
		if(searchp2==NULL) //����searchp2==NULL��ʾ���ֱȽ����
		{ 
			newdata=(Setmember *)malloc(len); 
			newdata->data=searchp1->data; 
			temp->next = newdata;             //����
			temp = temp->next; 
			
		}
		searchp1=searchp1->next; 
	} 
	temp->next = NULL;
} 
