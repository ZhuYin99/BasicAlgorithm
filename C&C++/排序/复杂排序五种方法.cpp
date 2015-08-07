//����:�������򷽷��Ĺ�����ʾ
#include<iomanip.h>
#include<iostream.h>
#include<windows.h>
#define MAXNUM  100					    //���ݸ������ֵ
#define MAXSIZE 1000					//���ݱ������ֵ
int flag=0;						    	//������ʶ���������Ƿ����
class node    
{
	friend class list;				    //��Ԫ����
public:
	node(){};
	~node(){};
};
class list   
{
public:
	list(){};
	~list(){};
	void create();				    	//�����������ݺ���
	void copy(list initlist);	    	//���ƶ������ݺ���
	void display();				    	//��ʾ���ݺ���
	int  binaryfind(int *data, int from, int to, int find);//�۰����
	void halfinsert();                  //�۰����������
	int  totalnumbers(list initlist);   //ϣ������ʱͨ����������ȷ������ȡֵ��Χ
	void shell(int step);               //ϣ��������
	void quick();                       //������������Ҫ���
	int  quicksort(int * Data,int n);   //�����������ݹ�ʵ��
	void heap();                        //����������Ҫ���
	void list::heapadjust(int begin,int end);//�������������
	void merge();						//�鲢��������Ҫ���
	int  mergesort(int Data[],int n);   //�鲢����������ʵ��
private:
	int heapdata[MAXNUM];			//��̬������Ϊ��������Ա�Ĵ洢�ṹ
	int data[MAXNUM];				//��̬������Ϊ���Ա�Ĵ洢�ṹ
	int total;						//������
};

int list::totalnumbers(list initlist)//������������
{
	return initlist.total;
}
void list::create()					//�����������ݺ���
{
	int choice,i;
	char ch;
	if(flag==1)					   //�����ʱ�Ѿ���һ�齨���õ�����
	{
		cout<<"��ʱϵͳ�Ѿ���һ�齨���õ����ݣ���ȷ�����滻��(Y||y)��";
		cin>>ch;
		if(ch=='Y'||ch=='y')
			flag=0;
	}
	if(flag==0)
	{
		cout<<"�����������ݣ� <1>��������    <2>�Զ�����  "<<endl<<"��ѡ��";
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"����������Ҫ��������������ݵĸ�����";
			cin>>total;
			cout<<"�뿪ʼ��������(��ʾ��һ�� "<<total<<"�����ݣ��ÿո�ֿ�)��"<<endl;
			for(i=0;i<total;i++)
				cin>>data[i];
			flag=1;
			break;
		case 2:
			cout<<"����������Ҫϵͳ�����������ݵĸ�����";
			cin>>total;
			cout<<"ϵͳ�Զ�����"<<total<<"������!"<<endl;
			for(i=0;i<total;i++)	
				data[i]=rand()%MAXSIZE;  //ϵͳ����һ��0-MAXSIZE֮��������
			flag=1;
			break;
		default:
			cout<<"����������!���������룺"<<endl;
			break;
		}
		if(flag==1)
		{
			cout<<"������������..."<<endl;
			display();
			cout<<"�������ݳɹ�����!"<<endl;
		}
	}
	else
	{
		cout<<"���Ѿ��ɹ�ȡ������������!"<<endl;
	}
} 
void list::copy(list initlist)//���ƶ������ݺ���
{
	int i;
	for(i=0;i<initlist.total;i++)
		data[i]=initlist.data[i];
	total=initlist.total;
}
void list::display()//��ʾ����
{
	int i;
	for(i=0;i<total;i++)
		cout<<setw(5)<<setiosflags(ios::left)<<data[i];
	cout<<endl;
}
int list::binaryfind(int *data, int from, int to, int find)//�۰����
{
	if(from > to)
		return from; //�������ݺ��ʵ�λ��
	if(find == data[(from+to)/2])
		return (from+to)/2;//�������ݺ��ʵ�λ��
	else if(find < data[(from+to)/2])//����������С���м�����ʱ��ͨ���ݹ����������ȷ��λ��
		return binaryfind(data,from,(from+to)/2-1,find);
	return binaryfind(data,(from+to)/2+1,to,find);//����ֵ  �������ݺ��ʵ�λ��
}
///������/////////////
void list::halfinsert()//�۰����������
{
	if(total == 0)
	{
		cout<<"��ʱû������!����ʧ��!"<<endl;
		return ;
	}
	cout<<"����������:"<<endl;
	display();
	for(int i =1; i<total; i++)
	{
		int position = binaryfind(data,0,i-1,data[i]);//�������ݺ��ʵ�λ��
		int temp =data[i];
		for(int j = i-1; j>=position;j--)
			data[j+1] = data[j];//�Ӻ�һλ��ǰһλ����ƶ�����
		if(j != i-1)
			data[position] = temp;//���������ݷ�����ʵ�λ��
		cout<<"�� "<<i+1<<" ������ "<<temp<<"�ҵ�λ����"<<position+1<<",�����:"<<endl;
		display();
	}
	cout<<"�����������!"<<endl;
}
void list::shell(int step)//ϣ��������
{
	int temp;
	int w;

	while(step>0)//������СΪ1
	{
		for(int j=step;j<total;j++)
		{
			temp=data[j];
			w=j-step;
			while((temp<data[w])&&(w>=0)&&(w<=total))
			{
				data[w+step]=data[w];
				w=w-step;//��С�����ķ�Χ�Ƚ�����
			}
			data[w+step]=temp;
		}
		/*��ʾϣ������*/
		cout<<endl<<"������Ϊ"<<step<<"ʱ����ʱ��������:"<<endl;
		display();
		cout<<endl;
		step=step/2;//��������
	}
}
void list::quick()//����������
{
	cout<<endl<<"�����������Ҫ������ʾ��"<<endl;
	quicksort(data,total);
	cout<<"��������Ľ����"<<endl;
	display();
}
int list::quicksort(int * Data,int n)
{
	int from=0;
	int to=n-1;
	int middle;
	int position=0;
	int space;
	if(n<=1)
		return 0;
    while(from<to)
	{
		if(from==position)
		{
			if(Data[position]<Data[to])
			{
			    to--;
			}
		    else if(Data[position]>Data[to])
			{
				//��������
				space=Data[position];
				Data[position]=Data[to];
				Data[to]=space;
				//��ʾ�����������
				cout<<endl;
				display();
				//��¼��λ�ã�Ȼ������������
			    position=to;
			    from++;
			}
		    else if(Data[position]==Data[to])
			{
			    to--;
			}
		}
		else if(position==to)
		{
			if(Data[from]>Data[position])
			{
				//��������
				space=Data[position];
				Data[position]=Data[from];
				Data[from]=space;
				//��ʾ�����������
				cout<<endl;
				display();
				//��¼��λ�ã�Ȼ�������ǰ����
			    position=from;
			    to--;
			}
		    else if(Data[from]<Data[position])
			{
			    from++;
			}
		    else if(Data[from]==Data[position])
			{
			    from++;
			}
		}
	}
	middle=position;
	quicksort(Data,middle);
	quicksort(Data+middle+1,n-middle-1);
	return 0;
}
void list::heap()//��������
{
	for(int k=0;k<total;k++)
		heapdata[k+1]=data[k];
	int i,temp;
	cout<<endl<<"��ʼ��Ӧ�Ķ�����:"<<endl;
	for(i=1;i<=total;i++)
		cout<<setw(6)<<heapdata[i];
	cout<<endl<<"ÿ�����к�Ľ����:"<<endl;
	for(i=total/2;i>0;--i) //��heapdata[1..i]���ɴ���ѣ��Ӻ��濪ʼ
		heapadjust(i,total);
	for(i=total;i>1;--i)
	{
		temp=heapdata[1]; //���Ѷ���¼�͵�ǰδ������������heapdata[1..i] 
		heapdata[1]=heapdata[i]; //�е����һ����¼�໥����
		heapdata[i]=temp;
		heapadjust(1,i-1); //��heapdata[1..i-1]���µ���Ϊ�����
	}
}
void list::heapadjust(int begin,int end)
{
	//��֪heapdata[begin..end]�г�heapdata[begin]֮�������ѵĶ���,����������heapdata[begin]
    //ʹheapdata[begin..end]��Ϊһ�������
	int i,value;
	value=heapdata[begin];
	for(i=2*begin;i<=end;i*=2) //�عؼ��ֽд�Ľ������ɸѡ
	{
		if(i<end&&heapdata[i]<heapdata[i+1])
			++i; //iΪ�ؼ��ֽϴ�ļ�¼���±�
		if(value>=heapdata[i]) 
			break; //valueӦ������λ��begin��
		heapdata[begin]=heapdata[i];
		begin=i;
	}
	heapdata[begin]=value; //����
	for(i=1;i<=total;i++)
		cout<<setw(6)<<heapdata[i];
	cout<<endl;
}
void list::merge()//�鲢������
{
	cout<<endl<<"�鲢����Ĺ�����ʾ��"<<endl;
	mergesort(data,total);
	cout<<"�鲢����Ľ����"<<endl;
	for(int i=0;i<total;i++)
		cout<<data[i]<<' ';
}
int list::mergesort(int Data[],int n)
{
	int swap;
	int * divide;
	//������ֹ����
	if(n==1)
		return 0;
	//�����ݽ��зָ�
	divide=Data+n-n/2;
	mergesort(Data,n-n/2);
	mergesort(divide,n/2);
    //�ϲ����ݲ�����
	for(int i=0;i<n/2;i++)
	{
		for(int j=n-n/2-1+i;j>=0;j--)
			if(Data[j]<divide[i])
				break;
		swap=divide[i];
		for(int k=n-n/2-1+i;k>j;k--)
		{
			Data[k+1]=Data[k];
		}
		Data[k+1]=swap;
		//������
		for(i=0;i<total;i++)
			cout<<data[i]<<' ';
		cout<<endl;
	}
	return 0;
}
//����������//////
void showmenu(void)//�˵����溯��
{
	cout<<"============================================="<<endl;
	cout<<"  ��      �߼������㷨����չʾϵͳ           "<<endl;
	cout<<"    ------------------------------------     "<<endl;
	cout<<"             1: ����������ݣ�����100�����ڣ�"<<endl;
    cout<<"             2: ��ʾ��������                 "<<endl;
	cout<<"             3: �۰��������                 "<<endl;
    cout<<"             4: ϣ������		            	"<<endl;
	cout<<"             5: ��������                     "<<endl;
	cout<<"             6: ������       			    "<<endl;
	cout<<"             7: �鲢����			            "<<endl;
 	cout<<"             0: �˳���ϵͳ                   "<<endl;
	cout<<"============================================ "<<endl;
	cout<<"��ѡ�� ";
}

void processmenu(void)//�˵�ѡ���
{
	int choice;
	list fromlist,mylist;      //Դ����fromlist;�������mylist;
	while(1)
	{
		system("cls");
		showmenu();
		cin>>choice;
		switch(choice)
		{
			case 1:
				fromlist.create();//����Դ��������
				break;
			case 2:
				if(flag==1)
				{
					mylist.copy(fromlist);//���ƶ���
					cout<<"��������Ϊ:"<<endl;
					mylist.display();
				}
				break;
			case 3:
				if(flag==1)
				{
					cout<<"��飺"<<endl;
					cout<<"    �۰���������ǲ�������ĸĽ�������˼·"<<endl;
					cout<<"�ǰ��ҵ���ȷλ�õĹ��̴���һ�Ƚϸ�Ϊ���ֲ��ұȽϣ�"<<endl;
					cout<<"�����ڲ�����ȷλ��ʱ�Ϳ��Դ������ʱ��Ч�ʡ�"<<endl;
					cout<<"���˼·����������ƶ��ͱ����Ϊ�����ƶ��Ĺ��̡�"<<endl;
					mylist.copy(fromlist);
					mylist.halfinsert();
					cout<<endl<<"����ɹ�!"<<endl<<endl;
				}
				break;
			case 4:
				if(flag==1)
				{
					cout<<"��飺"<<endl;
					cout<<"    ϣ�������ֳ�Ϊ����С�������򡱣�����˼·"<<endl;
					cout<<"�Ƚϼ򵥣���ȷ��һ��������Ȼ�����������ĳ����"<<endl;
					cout<<"���������ݽ��в�������֮��Ѳ�����С��ͨ����"<<endl;
					cout<<"�Գ���2��Ȼ���ظ����˼·��ֱ�����Ĳ���Ϊ1��"<<endl;
					int step;
					mylist.copy(fromlist);
					cout<<endl<<"�����벽����";
					cin>>step;
					while(step<1||step>mylist.totalnumbers(mylist))
					{
						cout<<endl<<"���벽�������ʣ�"<<"�����벽��:";
						cin>>step;
					}
					mylist.shell(step);
					cout<<endl<<"����ɹ�!"<<endl<<endl;
				}
				break;
			case 5:
				if(flag==1)
				{
					cout<<"��飺"<<endl;
					cout<<"    ��������˼·�ǵ�һ�ΰѵ�һ�����ݻ�������"<<endl;
					cout<<"ȷ��λ���ϣ���ν��ȷ��λ����ָ����ߵ����ݶ���"<<endl;
					cout<<"��С�����ұߵ����ݶ����������������Ľ����"<<endl;
					cout<<"��������λ�þ�����ȷ�ġ�Ȼ���õݹ��˼�������"<<endl;
					cout<<"�����ߵ����ݼ�������ֱ�������������������"<<endl;
					mylist.copy(fromlist);
					mylist.quick();
					cout<<endl<<"����ɹ�!"<<endl<<endl;
				}
				break;
			case 6:
				if(flag==1)
				{
					cout<<"��飺"<<endl;
					cout<<"    ����������n��Ԫ�أ����Ƚ���n��Ԫ�ذ���"<<endl;
					cout<<"���뽨�ɶѣ����Ѷ�Ԫ��������õ�n��Ԫ���йؼ� "<<endl;
					cout<<"�����С��ֵԪ�ء���ʣ�µ�n-1��Ԫ��������ѣ�"<<endl;
					cout<<"����Ѷ�Ԫ�أ��õ��δ�С��ֵԪ�ء��������С�"<<endl;
					mylist.copy(fromlist);
					mylist.heap();
					cout<<endl<<"����ɹ�!"<<endl<<endl;
				}
				break;
			case 7:
				if(flag==1)
				{
					cout<<"��飺"<<endl;
					cout<<"    �鲢�������Ļ��������ǽ����������ϲ�Ϊ"<<endl;
					cout<<"һ�����������˼·��ͻ�Ƶ���ͬʱ�����������"<<endl;
					cout<<"�ռ䣬֮���𽥺ϲ���Щ���ſռ䣬ֱ��ȫ�����ݳ�"<<endl;
					cout<<"Ϊһ�����ſռ䡣                              "<<endl;
					mylist.copy(fromlist);
					mylist.merge();
					cout<<endl<<"����ɹ�!"<<endl<<endl;
				}
				break;
			case 0:
				cout<<endl<<"���Ѿ��ɹ��˳���ϵͳ����ӭ�ٴ�ʹ��!!!"<<endl;
				exit(1);
				break;
			default:
				{
					cout<<"�Բ�������������! ���ٴ�����<0~7>:"<<endl;
					system("pause"); 
				}
		}
	if(flag==0)
		cout<<"�Բ��𣬻�û�н�����������!"<<endl;
	system("pause"); 	
	}	
}

//=======������=========	
void main(void)
{
	system("color f0"); //��һ��Ϊ������ɫ(f)���ڶ���Ϊ������ɫ��ɫ(0)
	processmenu();		//�˵�ѡ���
}
