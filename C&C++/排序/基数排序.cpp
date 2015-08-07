//���ܣ�������������ʾ����
#include<iomanip.h>
#include<iostream.h>   
#include<windows.h>   
#include<math.h> 
#define Maxnum 100000	  //��������������ֵ
#define Defaultnumber 10  //����Ĭ������Ĵ�С
#define Datawidth 7		  //������ʾ���ݿ��
#define QueueNum 10		  //����10���ӣ��ֱ𱣴�0 ~ 9�Ĺؼ��� 
#define Maxsize 1000  	  //�����������
/////
int flag=0;				  //��־λ���ж��û��Ƿ��������ݣ�û������Ϊ0�������Ϊ1
int defaultdata[Defaultnumber]={126,342,75,673,198,95,913,436,223,531};//Ĭ������
class queuenode;		  //�ӽ����
class linkqueue;		  //�Ӳ�����
class radixsort;		  //����������
class interfacebase;	  //�˵���
/////
class queuenode			  //�ӽ����
{	
	friend class linkqueue;
private: 
    int data;			  //���н������
    queuenode *link;      //�����ָ��
public:
    queuenode ( int d=0, queuenode *l = NULL ) : data (d), link (l) { }
};
class linkqueue			  //�Ӳ�����
{	
private: 
    queuenode *front, *rear;                             //��ͷ����βָ��ָ��
public: 
    linkqueue ( ) : rear(NULL), front(NULL){ }
    ~linkqueue ( );						                 //���е���������
    void enqueue (const int &item );                    //����Ԫ��item���뵽���еĶ�β
    void dequeue ( );					                 //ɾ�������ض�ͷԪ��
    int  getfront ( );					                 //�鿴����ͷԪ��ֵ
	int  isempty ( ) const{ return front == NULL; }	     //�ж϶����Ƿ�Ϊ��
};
/*���е���������*/         
linkqueue:: ~linkqueue ( ) 
{
    queuenode *tempp;
    while ( front!=NULL )						//���ͷŷǿս��
	{   
        tempp=front;  
		front=front->link;  
		delete tempp;								
    }
}
/*����Ԫ��item���뵽���еĶ�β*/
void linkqueue:: enqueue ( const int& item ) 
{
    if (front == NULL)//������һ�����
		front=rear=new queuenode(item, NULL);
	//���в���, ����
    else        
         rear=rear->link=new queuenode(item, NULL);
}
/*ɾ�������ض�ͷԪ��*/
void linkqueue:: dequeue ( ) 
{
	queuenode *tempp = front;		   
	front = front->link;   	
	delete tempp;    			
}
/*�鿴����ͷԪ��ֵ*/
int linkqueue:: getfront ( )
{
	return front->data;
}
///////////// 
class radixsort//����������
{
public:
	radixsort(){}
	~radixsort(){}
	int  searchmax();					//�ҵ������е����ֵ
	void send(int *datasent,int total); //���ݺ���
	void displayresult();				//��ʾ
	void doradixsort();				    //����

private:
	linkqueue queue[QueueNum];          //������У������������ 
	int inputdata[Maxsize];			    //������������
	int count;							//��������
	int index;							//��λ��־
	int max;							//�������λ��
};
int radixsort::searchmax()
{	
		int maxvalue=inputdata[0];	    //maxvalue���������������ֵ����ʼֵΪ��һ������
		for(int i=1;i<count;i++)        //ɨ�跨ȷ�����ֵ
			if(maxvalue<inputdata[i])
				maxvalue=inputdata[i];
		return maxvalue;
	
}
void radixsort::send(int *datasent,int total)//���ݺ���
{
	count=total;
	for(int i=0;i<count;i++)
		inputdata[i]=datasent[i];
	max=searchmax();//��������е����ֵ
	for(i=1;;i++)//������ݵ����λ��
	{
		if(max/((int)pow(10,i))==0)
		{
			max=i;
			break;
		}
	}
	index=1;//�Ӹ�λ��ʼ����
}
void radixsort::displayresult()
{
	if(!inputdata)
		cout<<"���ݻ�û�д�����"<<endl;
	else
	{
    	doradixsort();
    	cout<<endl<<"�����������:"<<endl;
    	for(int i=0;i<count;i++)
		{
	    	cout<<setw(Datawidth)<<inputdata[i];
    		if((i+1)%10==0)
	    		cout<<endl;
		} 
		cout<<endl;
		cout<<"===================="<<endl;
		cout<<"��������ɹ�������  "<<endl;
		cout<<"===================="<<endl;
	}
}
void radixsort::doradixsort()
{
	for(int i=0;i<max;i++)							//����λ��ֵ����ѭ������
	{
		for(int j=0;j<count;j++)					//���������ݽ���
		{						
			int k=inputdata[j]%(10*index)/index;	//�Ӻ�
			queue[k].enqueue(inputdata[j]);		    //��λ����С���󣬷ֱ����
		}
		int outqueueindex=0;						//���������±�
		for(j=0;j<QueueNum;j++)						//���Ӻų���
		{
			while(!queue[j].isempty())				//�ж϶���Ϊ�ǿ�
			{
				inputdata[outqueueindex++]=queue[j].getfront(); //ȡͷ���
				queue[j].dequeue();					//����
			}
		}
		index*=10;									//��߽�λ
		/*��ʾ������һ�κ������*/
    	cout<<endl<<"��"<<i+1<<"�γ��Ӻ�Ч��Ϊ��"<<endl;
    	for(int k=0;k<count;k++)
		{
	    	cout<<setw(Datawidth)<<inputdata[k];
    		if((k+1)%10==0)
	    		cout<<endl;
		} 
	}
}
///////
class interfacebase//�˵���
{
private:
	radixsort radix;							//�����������������
	int datasent[Maxsize];						//�洢����
	int total;									//��������
public:
	void clearscreen(void);						//����
	void showmenu(void);						//�˵�
	int  userchoice(void);						//�˵�ѡ�����
	void processmenu(int menuchoice);			//�˵�ѡ��
	void display();								//��ʾ����
};
void interfacebase::clearscreen(void)			//����
{
    system("cls");
}
void interfacebase::showmenu(void)				//�˵�
{
  	cout<<"������������ʾ����"<<endl;
    cout<<"===================="<<endl;
	cout<<"1.�ֹ���������"<<endl;
    cout<<"2.�Զ���������"<<endl;
    cout<<"3.��ʼ��������"<<endl;
    cout<<"4.�˳�����"<<endl;
	cout<<"===================="<<endl;
}
int interfacebase::userchoice(void)				//�˵�ѡ�����
{	int menuchoice;
	cout<<"����������ѡ��";   
	cin>>menuchoice;
	cout<<"===================="<<endl;
	return menuchoice;
}
void interfacebase::processmenu(int menuchoice)//�˵�ѡ��
{
	int j;										//ѭ������
	switch(menuchoice)							//�����û���ѡ�������Ӧ�Ĳ���
	{
	case 1:
			    cout<<"����������Ҫ��������������ݵĸ�����";
				cin>>total;
				while(total<1||total>Maxsize)	//��ֹ����������
				{
					cout<<"����������Ҫ��������������ݵĸ�����";
					cin>>total;
				}
				cout<<"�뿪ʼ��������(��ʾ��һ�� "<<total<<"�����ݣ��ÿո�ֿ�)��"<<endl;
				for(j=0;j<total;j++)
					cin>>datasent[j];
				radix.send(datasent,total);		//�����ݴ��뵽����������
				flag=1;
				break;
				
	case 2:
				cout<<"����������Ҫϵͳ�����������ݵĸ�����";
				cin>>total;
				while(total<1||total>Maxsize)	//��ֹ����������
				{
					cout<<"����������Ҫ��������������ݵĸ�����";
					cin>>total;
				}
				cout<<"ϵͳ�Զ�����"<<total<<"������!"<<endl;
				for(j=0;j<total;j++)
					datasent[j]=rand()%Maxnum;  //ϵͳ����һ��0-Maxnum֮��������
				radix.send(datasent,total);		//�����ݴ��뵽����������
				flag=1;
				break;
	case 3:
				if(flag==0)
					radix.send(defaultdata,Defaultnumber);	//��Ĭ�����ݴ��뵽����������
				radix.displayresult();
				break;
	case 4:
				exit(0);
	default:
				cout<<"�Բ���������Ĺ��ܱ���д�!����������!!!"<<endl;
		    	break;
	}
}
void interfacebase::display()
{
	if(flag==0)
	{
		cout<<"�����������ݣ�Ĭ������Ϊ��"<<endl;
		for(int j=0;j<Defaultnumber;j++)
			cout<<setw(Datawidth)<<defaultdata[j];
		cout<<endl;
	}
	if(flag==1)
	{
		cout<<"�û����������Ϊ��"<<endl;
		for(int j=0;j<total;j++)
		{	
			cout<<setw(Datawidth)<<datasent[j];
			if((j+1)%10==0)
	    		cout<<endl;
		}
		cout<<endl;
	}
}
/////
void main(void)                     //���������
{   
	system("color f0");
	int menuchoice;                 //����Ҫ�õ�
	interfacebase interfacenow;
	interfacenow.clearscreen();
    while (1)
	{
  		interfacenow.showmenu();
		interfacenow.display();
		menuchoice=interfacenow.userchoice();
		interfacenow.processmenu(menuchoice);
		system("pause"); 
		interfacenow.clearscreen();
    }
}//����������