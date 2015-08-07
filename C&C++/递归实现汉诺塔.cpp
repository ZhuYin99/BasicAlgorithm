//��������:�ݹ�ʵ�ֺ�ŵ����C�棩.cpp
//���ܣ�ͨ���ݹ�ʵ�ֺ�ŵ�����

#include<iostream.h>
#include<windows.h>


void move(char pillarsource,int num,char pillartarget);//�ƶ�ʱ����ʾ��Ϣ
void hanoi(int num,char pillar01,char pillar02,char pillar03);//������ͨ���ݹ鿪ʼ�ƶ�
void startmove(void);//��ʾ��Ϣ
int num;

/*����������������������������������������������������//
�� �� ��:main
��    ��:������
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void main(void)
{
	SetConsoleTitle("�ݹ�ʵ�ֺ�ŵ����C�棩"); //���ñ���
	system("color f0");
	cout<<"ͨ���ݹ�ʵ�ֺ�ŵ��:"<<endl;
	startmove();
	cout<<"������ɣ�����"<<endl;
    system("pause"); 
}


/*����������������������������������������������������//
�� �� ��:hanoi
��    ��:������ͨ���ݹ鿪ʼ�ƶ�
��ڲ���:pillar01Ϊ��ʼ��, pillar02Ϊ������, pillar03ΪĿ����
���ڲ���:��
//����������������������������������������������������*/
void hanoi(int num,char pillar01,char pillar02,char pillar03)// pillar01Ϊ��ʼ��, pillar02Ϊ������, pillar03ΪĿ����
{
    if(num==1)
        move(pillar01,1,pillar03);//�ݹ���ֹ����
    else
	{
		hanoi(num-1,pillar01,pillar03,pillar02);//�ݹ����
		move(pillar01,num,pillar03);
		hanoi(num-1,pillar02,pillar01,pillar03);//�ݹ����
	}
}

/*����������������������������������������������������//
�� �� ��:move
��    ��:�ƶ�ʱ����ʾ��Ϣ
��ڲ���:pillarsourceΪ��ʼ��, pillartargetΪĿ����
���ڲ���:��
//����������������������������������������������������*/
void move(char pillarsource,int num,char pillartarget) // pillarsourceΪ��ʼ��, pillartargetΪĿ����
{
	cout<<"�� "<< num <<" ���� �ӵ� "<< pillarsource<<" ���� �Ƶ� �� "<<pillartarget<<" ����"<<endl;
}

/*����������������������������������������������������//
�� �� ��:startmove
��    ��:��ʾ��Ϣ
��ڲ���:��
���ڲ���:��
//����������������������������������������������������*/
void startmove(void)
{
	cout<<"������������:";
	cin>>num;
	hanoi(num,'1','2','3');
}
