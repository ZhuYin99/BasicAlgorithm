/*����������
ͼ���ڽӱ�ʵ�ֻ�������
*/
//�������в���Դ����Ҫ��һ��������
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };					//���巵����Ϣ�嵥

#define  size 21//������Լ��Ϊ20������1�ŵ�ַ��ʼʹ��
int build;		//��־λ������ĿǰΪ�ձ�
//������
class Node                                       
{
public:
    int	  data;                                     
    Node *next;                             
    Node()                                       
    {                                           
        this->next = NULL;
    }
    Node(int data, Node *next=NULL)             //�����㣬ָ��Ԫ�غͺ�̽��
    {
        this->data = data;
        this->next = next;
    }
};
//�������
class linklist                           
{    
private:	
	Node *head;								//�������ͷָ��
public:
	int   length;							//���ݸ���
    linklist();								//���캯��     
    ~linklist();							//��������
	int   clearlink();						//��������е�����
    int   setheadNULL();					//��ͷ���������ÿ�
    void  printlinklist();					//��������	
    Node *inserthead(int data);				//�ѽ������ڵ�һ��λ����Ϊͷ���
    Node *insert(int x,int i);				//��xֵ���뵽��i��λ��           
    int   getheaddata();					//ȡ��ͷ����е�ֵ
	bool  del(int data) ;					//ɾ��ֵΪdata�Ľ��
    Node  *find(int value, Node* start);	//��start��㿪ʼ��ֵΪvalue�Ľ��      
    Node  *find(int value);					//����ֵΪvalue�Ľ��
	int   *nodetoarraydata();				//����������ת��Ϊ��������
   	int   findsmallernum(int data);			//�ҵ���dataС�����ݸ���
	int   getnextnode(int i);				//�����ڽӵ���һ�����
};
linklist::linklist()          //����յ�����
{
    this->head  =NULL;
	this->length=0;
}
linklist::~linklist()        
{
    this->head  =NULL;//�������ͷŴ˴�û��д
}
int linklist::clearlink()//��������б���Ϣ�ĵ�
{
	Node *searchp=head->next;//head�д洢���ǽ������
	Node *followp;
	while(searchp!=NULL)
	{
		followp=searchp;
		searchp=searchp->next;
		head->next=searchp;
		delete followp;
    }
	head->next=NULL;
  return 1;
}
int  linklist::setheadNULL()
{
	Node *temp=head;
	delete temp;
	head=NULL;
	return 1;
}
void linklist::printlinklist()//�����������н��
{
	Node *searchp=head;
	if(searchp==NULL)
		cout<<"�����ݣ�";
	while(searchp!=NULL)                    //ѭ����ʾ��������
	{
		cout<<"[ "<<searchp->data;   
		if (searchp->next==NULL) 
			cout<<" |^]"; 
		else 
			cout<<" |-]->";
		searchp=searchp->next;
	}
}
Node *linklist::inserthead(int data)
{
	Node *followp;
    followp = new Node(data, head);
    head = followp;
	length++;
	return followp;
}
Node *linklist::insert( int data,int pos) //����data��Ϊ��pos����㣬�����²�����ָ��
{
    Node *followp;
	int j=0; 
	if (head==NULL || pos<=0)                      //ͷ����
    {
        followp = new Node(data, head);
        head = followp;
    }
    else                                        
    {
        Node *searchp=head;
	    while (searchp->next!=NULL&&j<pos-1)           //Ѱ�Ҳ���λ��
        {
            j++;
            searchp = searchp->next;
        }                                        //ѭ��ֹͣʱ��searchpָ���pos-1�������������һ�����
        followp = new Node(data, searchp->next);             //����data��Ϊsearchp���ĺ�̽��
        searchp->next = followp;
		length++;
    }
    return followp;
}
int linklist::getheaddata()//ͷ����Ƿ�Ϊ��
{
	if(head==NULL)
		return -1;
	else
		return head->data;
}
bool linklist::del(int data)  //ɾ��data���
{
    Node *searchp=head,*followp=head;
    while(searchp->next!=NULL && searchp->data!=data)
	{
		followp=searchp;
		searchp=searchp->next;
	}
	if(searchp->data==data)
	{
		followp->next=searchp->next;
		delete searchp;
		return true;
	}
	else   
		return false; 
}
Node *linklist::find(int value, Node *start)    //�ӵ�����start��㿪ʼ˳�����ָ��Ԫ��
{                                                
    Node *searchp=start;
    while (searchp!=NULL && searchp->data!=value)
	{
        searchp = searchp->next;
	}
    return searchp;
}
Node *linklist::find(int value)    
{
    if (head==NULL)
        return NULL;
    else
    return find(value, head->next); 
}
int *linklist::nodetoarraydata()
{
	int  *followp = new int[size];
	Node *searchp=head->next;
	int  i=1;
	while(searchp!=NULL)
	{
		
		followp[i]=searchp->data;
		i++;
		searchp=searchp->next;
	}
	followp[0]=i;
	return followp;
}
int linklist::findsmallernum(int data)//�������С��ĳ�����ݵĸ���
{

    Node *searchp=head->next;
	int nums=0;
    while (searchp!=NULL && searchp->data<data)
	{
       nums++;
	   searchp=searchp->next;
	}
	return nums;
}
int linklist::getnextnode(int pos)//ȡ����ͷ�����濪ʼ�ĵ�pos������ֵ
{
	Node *searchp=head->next;
	int nextnum=1;//λ�ü�����
	while(searchp!=NULL && nextnum!=pos)
	{
		searchp=searchp->next;
		nextnum++;
	}
	if(searchp==NULL)
		return -1;
	else 
		return searchp->data;
}

//��ʽ���ж���
class linkqueue                                //��ʽ������
{
private:
	Node *front, *rear;                       //front��rear�ֱ�ָ����׺Ͷ�β���
public:
    linkqueue();                               //����ն���
    ~linkqueue();                              //����
    bool isempty();                              //�ж��Ƿ�ն���
    void enqueue(int x);                           //���
    int  dequeue();                                 //���ӣ������п����׳��쳣
    void printlinkqueue();
};
linkqueue::linkqueue()                    //����ն���
{
    front = rear = NULL;
}
linkqueue::~linkqueue()                   //��������
{
    Node *searchp=front, *followp;
    while (searchp!=NULL)//�ͷſռ�
    {
        followp = searchp;
        searchp = searchp->next;
        delete followp;
    }
    front = rear = NULL;
}
bool linkqueue::isempty()                   //�ж��Ƿ�ն���
{
    return front==NULL && rear==NULL;
}
void linkqueue::enqueue(int x)               //���
{
    Node *followp = new Node(x);
    if (isempty())
        front = followp;                               //�նӲ���
    else 
        rear->next = followp;                          //�����ڶ���֮β
    rear = followp;
}  
int linkqueue::dequeue()                      //���ӣ����ض�ͷԪ�أ������п����׳��쳣 
{
    if (!isempty())
    {
       int x = front->data;                       //ȡ�ö�ͷԪ��
       Node *searchp=front;
       front = front->next;                     //ɾ����ͷ���
       delete searchp;
       if (front==NULL)                         //�ն���ʱ����ָ��ͬ��
          rear = NULL;
       return x;
    }
	else 
		return -1;
}
void linkqueue::printlinkqueue()
{
	Node *searchp=front;
    while (searchp!=NULL)
    {
       
        cout<<searchp->data<<"---";
		searchp=searchp->next;
    }
}
void quickSort(int table[], int length, int low, int high)        //һ�˿������򣬵ݹ��㷨
{                                                          
    int lowtemp, hightemp;
    int basedata;                         
    if (low>=0 && low<length && high>=0 && high<length && low<high) 
    {
        lowtemp=low;
		hightemp=high;
        basedata=table[lowtemp];                         
        while (lowtemp!=hightemp)
        {
            while (lowtemp<hightemp && basedata<=table[hightemp])         
                hightemp--;
            if (lowtemp<hightemp)
                table[lowtemp++]=table[hightemp];             
            while (lowtemp<hightemp && table[lowtemp]<basedata)          
                lowtemp++;
            if (lowtemp<hightemp)
                table[hightemp--]=table[lowtemp];            
        }
        table[lowtemp]=basedata;                            
        quickSort(table, length, low, hightemp-1);           
        quickSort(table, length, lowtemp+1, high);        
    }
}
int *doquickSort(int array[], int length)               //��������
{
    quickSort(array, length, 0, length-1);				//�ĸ������������������ȡ����ߵ��±�
    return array;
}
/////////////////////////////////////////////////////////
//ͼ���ڽӱ����
class ALGraph
{
private:
	linklist *Graph;					//����һ�������ʵ��������ΪGraph
	linkqueue queue;					//����һ�����ӵ�ʵ��������Ϊqueue��Ϊ������ȱ���׼��
	int nodenumber;						//���ڲ�����Ž����±�λ�ã�ͬʱ��¼������
	int edgenumber;						//ʵ�ʱ�����¼
	int row;							//���ƽ�����������
	int i;								//ѭ������
	int nodenum,edgenum;				//��ʱ�洢������ͱ���
	int node[size];						//��ʱ�洢ͼ�Ľ��
	int *sortednodes;					//�洢�����Ľ��
	int startpoint,endpoint;			//��ʼ������ֹ���
public:
	ALGraph(int nodenumber=1,int edgenumber=0);//����������0�±꣬��nodenumber��1��ʼ��������ʼΪ0
	~ALGraph();
	void inigraph();					//ͼĿǰ����������Ա�������������
	void inputdata(void);				//�ֹ���������
	void autocreatgraph();				//����Ĭ������
	void showgraph();					//��ʾ�ڽӱ�
	void showtotalnodenumber();			//��ʾ����ܸ���
	void showtotaledgenumber();			//��ʾ�ߵ��ܸ���
	int  findnode(int nodedata);		//���ҽ���������е�����	
	void insertmanynodes(int data);		//һ�β���һ�����ʹ�õĲ����㺯��
	void insertonenode(int data);		//һ�ν�������һ�����ʹ�õĲ����㺯��
	int  deletenode(int data);			//ɾ�����
	void insertedge(int startpoint,int endpoint);	//����ͼ�ı�   
	int  deleteedge(int startpoint,int endpoint);	//ɾ��ͼ�ı�
	Node *findedge(int startpoint,int endpoint);	//��������֮��ı�
	void searchnext(int data);						//������һ���ڽӵ�
	void DFSTraverse();								//������ȱ������
	void TDFSTraverse(int row,int flag[],int stackarray[]);			//������ȱ�������
	void BFSTraverse();								//������ȱ������
	void TBFSTraverse(int row,int flag[]);			//������ȱ����ݹ麯��
};
ALGraph::ALGraph(int nodenumber,int edgenumber)
{
	this->Graph=new linklist[size];//�������ڽӱ��ָ������
	this->nodenumber=nodenumber;
	this->edgenumber=edgenumber;
}
ALGraph::~ALGraph()
{
   delete[] Graph;
}
void ALGraph::inigraph()//ͼĿǰ����������Ա�������������
{
	for(i=1;i<nodenumber;i++)//�˴�ʵ���ϴ�����1ֻѭ������nodeposition-1�����꣬��������������
		Graph[i].clearlink();//�Ȱѱ���Ϣ��������ȫ��ɾ�����ͷſռ�
	for(i=1;i<nodenumber;i++)//�ٰѽ����Ϣ�������е������ÿ�
		Graph[i].setheadNULL();
	nodenumber=1;
	edgenumber=0;
}
void ALGraph::inputdata(void)
{
	inigraph();
	cout<<"�����������:";
	cin>>nodenum;
	if(nodenum<=0)
	{
		cout<<"���������д����β�������!!!"<<endl;
	}
	else
	{
		cout<<"��������:";
		for (i=0; i<nodenum; i++)
		cin>>node[i];
		sortednodes=doquickSort(node,nodenum);
		for (i=0; i<nodenum; i++)
			insertmanynodes(sortednodes[i]);
		cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
		showgraph();
		cout<<"������߸���:"<<endl;
		cin>>edgenum;
		if(edgenum<=0)
		{
			cout<<"���������д����β�������!!!"<<endl;
		}
		else
		{
			cout<<"������ÿ�������ӵ�������:"<<endl;//��Ҫ���ǵ㲻����
			for(i=0;i<edgenum;i++)
			{
				cin>>startpoint>>endpoint;
				if(findnode(startpoint)!=-1&&findnode(endpoint)!=-1)
					insertedge(findnode(startpoint),findnode(endpoint));
				else
					cout<<startpoint<<"��"<<endpoint<<"֮��ı߲����ڣ�"<<endl;
			}
			cout<<"================"<<endl;
			cout<<"��ǰͼ���ڽӱ�����:"<<endl;
			showgraph();		
		}
	}
}
void ALGraph::autocreatgraph()//��������ͼĬ������
{
	int defaultnodenum=8,
		defaultnode[]={11,33,22,44,55,88,77,66},
		defaultedgenum=12,
		defaultedge[12][2]=
			{{11,22},{11,44},{11,77},
			 {22,33},{22,44},
			 {33,88},
			 {44,55},
			 {55,88},
			 {66,77},{77,66},
			 {77,44},
			 {88,66}};
	inigraph();
	for (i=0; i<defaultnodenum; i++)
		sortednodes=doquickSort(defaultnode,defaultnodenum);
	for (i=0; i<defaultnodenum; i++)
	    insertmanynodes(sortednodes[i]);
	for(i=0;i<defaultedgenum;i++)
	 	insertedge(findnode(defaultedge[i][0]),findnode(defaultedge[i][1]));
}
void ALGraph::showgraph()//��ʾͼ���ڽӱ���ʽ
{
	if(nodenumber==1)
		cout<<"Ŀǰͼû������!!!"<<endl;
	else
	{	
		cout<<"����"<<" �����"<<" �߹�ϵ����"<<endl;
		for(int i=1;i<nodenumber;i++)//�˴�ʵ���ϴ�����1ֻѭ������nodeposition-1�����꣬��������������
		{
			cout<<" "<<i<<"   ";
			Graph[i].printlinklist();//��ʾ�������е���������
			cout<<endl;
		} 
	}
}
void ALGraph::showtotalnodenumber()//��ʾ�ܽ�����
{
	cout<<nodenumber-1<<endl;//nodepositionÿ��ָ����һ�����ÿռ䣬��ʵ��������Ҫ��һ
}
void ALGraph::showtotaledgenumber()//��ʾ�ߵ��ܸ���
{
	cout<<edgenumber<<endl;
}
int ALGraph::findnode(int nodedata)//����Ƿ����
{
	row=0;//��ʵ���ݵ�ַ��1��nodenumber-1
	while((row<nodenumber) && (Graph[row].getheaddata()!=nodedata))//��û�������û���ҵ�ʱ
		row++;
    if(row>=nodenumber)//û���ҵ�ʱ
		row=-1;
	return row;
}
void ALGraph::insertmanynodes(int data)//һ�β���һ�����ʹ�õĲ����㺯�������������ݵ�����
{
	if(findnode(data)==-1)
	{
	    Graph[nodenumber].inserthead(data); //�������������´��
		nodenumber++;						//����������һ
	}
   else
		cout<<data<<"����Ѵ��ڣ�����ʧ��!!!"<<endl;
}
void ALGraph::insertonenode(int data)//������
{
//	int pos;
	if(findnode(data)==-1)
	{
	    Graph[nodenumber].inserthead(data);/////////�˴�û�б�֤��������ȷ��λ���Ͻ������������
	nodenumber++;
/*
	//int tempdata=data;
	//linklist
	i=1;//�ӵ�һ�������𣬲���С��data�ĸ���
	while (Graph[i].getheaddata()<data) //����½������Ӧ���õ���ȷλ��
			i++;							//������i����Ϊ��ȷ����λ��
		
		
		
		for (pos=nodenumber;pos<=i;pos--)
			Graph[pos]=Graph[pos-1];
		Graph[pos-1].inserthead(data);

			nodenumber++;
		//Graph=doquickSort(Graph[], nodenumber) 
*/
	}
   else
		cout<<data<<"����Ѵ��ڣ�����ʧ��!!!"<<endl;
}

int ALGraph::deletenode(int data)//ɾ�����
{
		cout<<"ɾ����㹦����δ�ṩ����������β���!!!"<<endl;
/*
���Ҹ�Ԫ���Ƿ����
�ҵ���Ԫ�����ڵ��У�����¼���±�
��ʼɾ��������صı���Ϣ������ͬʱ����
���ܱ�����ȥ�ü�������ֵ
�ӵ�һ�п�ʼ ����ɨ��
    ��������ָ���β��ָ�� �ҵ����±�������� һ��ɾ�� ÿ��ɾ��ʱ�ߵļ�����������һ
ѭ����ɺ󣬰�ɾ������������������һ��
�ܽ�������һ
*/
	return 1; 
}

void ALGraph::insertedge(int startpoint,int endpoint)
{
	Node* searchp=Graph[startpoint].find(endpoint);
	if(searchp==NULL||searchp->data!=endpoint)
	{
    	Graph[startpoint].insert(endpoint,Graph[startpoint].findsmallernum(endpoint)+1);
		//�ҵ���ȷλ�ã�����ߵ���Ϣ������
		edgenumber++;
	}
	else
		cout<<"�ñ��Ѵ��ڣ�����ʧ��!!!"<<endl;
}
int ALGraph::deleteedge(int startpoint,int endpoint)
{
	if(Graph[startpoint].del(endpoint)==true)
	{
		cout<<"ɾ���߳ɹ���"<<endl;
		edgenumber--;
	return 1;
	}
	else
	{
		cout<<"�ñ߲����ڣ�����ʧ��!!!"<<endl;
	return -1;
	}
}
Node *ALGraph::findedge(int startpoint,int endpoint) //����startpoint��endpoint֮��ı�        
{           
	return Graph[startpoint].find(endpoint);        
}
void ALGraph::searchnext(int data)//����data�����ڽ��
{
	int *adjvexdataarray;
	if(Graph[findnode(data)].length==1)
	{
		cout<<data<<"û�����ڽ��!!!"<<endl;
	}
	else
	{
		adjvexdataarray=Graph[findnode(data)].nodetoarraydata();
		cout<<data<<"�����ڽ��Ϊ��";
		for(int i=1;i<adjvexdataarray[0];i++)
			cout<<Graph[adjvexdataarray[i]].getheaddata()<<"  ";
		cout<<endl;
		delete[] adjvexdataarray;
	}
}
void ALGraph::DFSTraverse()//������ȱ������
{
	int *flag=new int [nodenumber];	//��㱻���ʱ�־��0��ʾδ�����ʣ�1��ʾ�ѷ���
	for(i=1;i<nodenumber;i++)	//��־λ�����ʼ����ȫ����ֵΪ0
		flag[i]=0; 
	int	*stackarray=new int [nodenumber+1];//����·�������飬��ջ������
	for(i=0;i<nodenumber;i++)//��ʼ״̬ȫ����ֵΪ-1
	{
		stackarray[i]=-1;
	}
	for(i=1;i<nodenumber;i++)		//ÿһ����㶼��Ϊ��ʼ���һ�Σ�ȷ������ͨͼҲ������ɱ���
		if(flag[i]==0)
			TDFSTraverse(i,flag,stackarray);
}
////////////////////////////////////////////////////////////////////////////////////
void ALGraph::TDFSTraverse(int row,int flag[], int stackarray[])//������ȱ�������
{
		int *adjvexdataarray1;	//�ڽӱ���Ϣ����ת���ɵ�����
	int nextnum;			//��һ���ڽӵ�ı��
	int visitednum=1;		//�ѷ��ʽ��ĸ���
    //if(row==-1) return;
	stackarray[0]=1;		//0�������д�ŷ��ʹ��Ľ���������˴�Ԥ��Ϊ1���������ʽ��������Ҫ��һ
	while(row!=-1 && stackarray[0]<nodenumber)//����������ڲ����ѷ��ʵĽ������û�е����ܽ������ѭ��
	{
		if(flag[row]==0)							//���û���ʣ��ͷ���
		{
			cout<<Graph[row].getheaddata()<<"  ";	//�Ѹñ�Ŷ�Ӧ�Ľ�������
			stackarray[stackarray[0]]=row;          //����·����Ϣ
	        stackarray[0]++;                        //stackarray[0]-1Ϊ����ѷ��ʽ�����
			flag[row]=1;
		}
		adjvexdataarray1=Graph[row].nodetoarraydata();//�������������ڽӽ����Ϣת�������飬��ַ��1��ʼ
		///////////////
		//cout<<"������ÿ��ÿһ�н����Ϣת��Ϊ��������Ϣ"<<endl;
		//for(i=1;i<nodenumber;i++)
		//	cout<<adjvexdataarray1[i]<<endl;
		//cout<<"ÿһ�н����Ϣת��Ϊ��������Ϣ����"<<endl;
		///////////////
		nextnum=1;									 //��ʼ�����һ�����ڽ��	                       
	    row=Graph[row].getnextnode(nextnum);		 //��ȡ���ڽ���Ӧ�ڽ�������е��к�
		while(flag[row]==1 && row!=-1 && stackarray[0]<nodenumber)//����ý�㱻���ʹ��������һ���ڽӵ�
			row=adjvexdataarray1[nextnum++];			 //ֱ���ҵ�һ��û�б����ʹ��Ľ���� 
		
		
		//TDFSTraverse(row,flag,stackarray);//���µ�һ�н��룬�ݹ���ɱ�������
		visitednum=stackarray[0]-1;                  //��¼�ѷ������ݸ���
		if(stackarray[0]<nodenumber && row==-1)      //���û�����꣬ͬʱ���ڽ�㶼�������
		{   visitednum--;							 //��ʼ���ݹ���	
			row=stackarray[visitednum];				 //�ӱ����·���л��˵���һ���ѷ��ʽ��
		}
   }
}
/*
void ALGraph::TDFSTraverse(int row,int flag[])//������ȱ�������
{
	int *adjvexdataarray;	//�ڽӱ���Ϣ����ת���ɵ�����
	int nextnum;			//��һ���ڽӵ�ı��
	int visitednum=1;		//�ѷ��ʽ��ĸ���
	int	*stackarray=new int [nodenumber+1];//����·�������飬��ջ������
	for(int i=0;i<nodenumber;i++)//��ʼ״̬ȫ����ֵΪ-1
	{
		stackarray[i]=-1;
	}
	stackarray[0]=1;			//0�������д�ŷ��ʹ��Ľ���������˴�Ԥ��Ϊ1���������ʽ��������Ҫ��һ
	while(row!=-1 && stackarray[0]<nodenumber)//����������ڲ����ѷ��ʵĽ������û�е����ܽ������ѭ��
	{
	    if(flag[row]==0)							//���û���ʣ��ͷ���
		{
			cout<<Graph[row].getheaddata()<<"  ";	//�Ѹñ�Ŷ�Ӧ�Ľ�������
			stackarray[stackarray[0]]=row;          //����·����Ϣ
	        stackarray[0]++;                        //stackarray[0]-1Ϊ����ѷ��ʽ�����
			flag[row]=1;
		}
		adjvexdataarray=Graph[row].nodetoarraydata();//�������������ڽӽ����Ϣת�������飬��ַ��1��ʼ
		nextnum=1;									 //��ʼ�����һ�����ڽ��	                       
	    row=Graph[row].getnextnode(nextnum);		 //��ȡ���ڽ���Ӧ�ڽ�������е��к�
		while(flag[row]==1 && row!=-1 && stackarray[0]<nodenumber)//����ý�㱻���ʹ��������һ���ڽӵ�
			row=adjvexdataarray[nextnum++];			 //ֱ���ҵ�һ��û�б����ʹ��Ľ���� 
		visitednum=stackarray[0]-1;                  //��¼�ѷ������ݸ���
		if(stackarray[0]<nodenumber && row==-1)      //���û�����꣬ͬʱ���ڽ�㶼�������
		{   visitednum--;							 //��ʼ���ݹ���	
			row=stackarray[visitednum];				 //�ӱ����·���л��˵���һ���ѷ��ʽ��
		}
   }
}
*/

//////////////////////////////////////////////////////////////////////////////////
void ALGraph::BFSTraverse()//������ȱ������
{
	int *flag=new int [nodenumber];	//��㱻���ʱ�־��0��ʾδ�����ʣ�1��ʾ�ѷ���
	for(int i=1;i<nodenumber;i++)	//��־λ�����ʼ����ȫ����ֵΪ0
		flag[i]=0; 
	for(i=1;i<nodenumber;i++)		//ÿһ����㶼��Ϊ��ʼ���һ�Σ�ȷ������ͨͼҲ������ɱ���
		if(flag[i]==0)
			TBFSTraverse(i,flag);
}
void ALGraph::TBFSTraverse(int row,int flag[])//������ȱ����ݹ麯��
{
	int *adjvexdataarray;
    if(flag[row]==0)  //��row�н��룬�����ŵ�row������Ŀǰ���µ���㣬��־λΪ0��ʾ����û�б�����
	{
		cout<<Graph[row].getheaddata()<<"  ";	//ȡ������ʾ��һ������еĽ����
	    flag[row]=1;							//��ת��־λ
	}
	adjvexdataarray=Graph[row].nodetoarraydata();//��row�н���������ؽ����Ϣ����һ����ʱ����
   	for(int i=1;i<adjvexdataarray[0];i++)    //0�ŵ�ַ��Ϊ��رߵ���������һ�����ʲ��ҽ���
	{
		if(flag[adjvexdataarray[i]]==0)     //����û�б����ʣ������ʾ
		{
			cout<<Graph[adjvexdataarray[i]].getheaddata()<<"  ";
			flag[adjvexdataarray[i]]=1;
			queue.enqueue(adjvexdataarray[i]);
		}
    }
	if( (row=queue.dequeue())!=-1)//���в�Ϊ�գ����Ӳ�������һ�������������
	{
		TBFSTraverse(row,flag);//���µ�һ�н��룬�ݹ���ɱ�������
	}
}
////////////////////////////////////////////
//���洦����󣺽����
class interfacebase
{
private:
	ALGraph graphnow;	//ͼ�����ʵ����
public:
	void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"=================================="<<endl;
    cout<<"      ͼ���ڽӱ�����ʾ          "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.�ֹ�����һ��ͼ					 "<<endl;
	cout<<"2.����Ĭ�����ݽ���ͼ				 "<<endl;
    cout<<"3.��ʾͼ�ڽӱ���ʾ������ͱ���	 "<<endl;
    cout<<"4.����ĳ�������ڽ��			 "<<endl;
    cout<<"5.���һ�����                    "<<endl;
    cout<<"6.ɾ��һ�����			         "<<endl;
    cout<<"7.���һ����						 "<<endl;
	cout<<"8.ɾ��һ����						 "<<endl;
    cout<<"a.������ȱ���ͼ					 "<<endl;
    cout<<"s.������ȱ���ͼ					 "<<endl;
    cout<<"0.�˳�							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
	char choice,yesno;			//�����û�ѡ��˵�ѡ��
	int  nodestart,nodeend;		//����߻�ɾ���ߵ������յ�
	int  removenode;			//����ɾ�����
	int  mark;					//����һ����־λ������ɾ����ʹ��
    cout<<"������ѡ�";
    cin>>choice;
    switch(choice)
    {
    case '1':
		cout<<"================"<<endl;
		if(build==1)
		{
        	cout<<"Σ�ղ�����ԭ�����ݽ���ɾ��!��ȷ����?ȷ����(Y||y)��!���������!"<<endl;
			cin>>yesno;
			if(yesno!='y' && yesno!='Y')
			{
				cout<<"�Ѿ�ȡ������ͼ!"<<endl;
				break;
			}
		}
		graphnow.inputdata();
		build=1;
		cout<<"================"<<endl;
        break;
	case '2':
		if(build==1)
		{
        	cout<<"Σ�ղ�����ԭ�����ݽ���ɾ��!��ȷ����?ȷ����(Y||y)��!���������!"<<endl;
			cin>>yesno;
			if(yesno!='y' && yesno!='Y')
			{
				cout<<"�Ѿ�ȡ������ͼ!"<<endl;
				break;
			}
		}
		graphnow.autocreatgraph();
		build=1;
		cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		cout<<"================"<<endl;
					//cout<<endl<<"������ȱ�������Ϊ :"<<endl;//����ʹ��
					//graphnow.DFSTraverse();
					//cout<<endl<<"������ȱ�������Ϊ :"<<endl;
					//graphnow.BFSTraverse();
					//cout<<endl;
        break;
    case '3':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		cout<<"��ǰ������Ϊ :";
	    graphnow.showtotalnodenumber();
		cout<<"��ǰͼ�ı���Ϊ :";
	    graphnow.showtotaledgenumber();
		cout<<"================"<<endl;
        break;
	case '4':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;	
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		int node;
		cout<<"����������: ";
			cin>>node;
			if(graphnow.findnode(node)==-1)      //����
				cout<<"�˽�㲻����"<<endl;
			else
			{
				graphnow.searchnext(node);
			}
		cout<<"================"<<endl;
		break;
	case '5':
        if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		cout<<"������Ҫ����Ľ�� : ";
		cin>>node;
		if(graphnow.findnode(node)==-1)  
		{
			graphnow.insertonenode(node);
			cout<<"������ɹ���"<<endl;
			cout<<"��ǰͼ���ڽӱ�����:"<<endl;
			graphnow.showgraph();
		}
		else 
			cout<<"�ý���Ѵ���!����ʧ��!!!"<<endl;
        cout<<"================"<<endl;
		break;
    case '6':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		cout<<"������Ҫɾ���Ľ����: ";
		cin>>removenode;
		cout<<"Σ�ղ���!��ȷ����?ȷ����(Y||y)��!���������!"<<endl;
		cin>>yesno;
		if(yesno=='y'||yesno=='Y')
		{			 
			mark=graphnow.deletenode(removenode);
			if(mark==1)
			{
				cout<<"���"<<removenode<<"�Ѿ���ɾ��!"<<endl;
				cout<<"��ǰͼ���ڽӱ�����:"<<endl;
				graphnow.showgraph();
			}
		}
		else
			cout<<"���β����Ѿ�����!!!";
		cout<<"================"<<endl;
        break;
    case '7':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		cout<<"������Ҫ����ߵ������յ�: "<<endl;
			cin>>nodestart>>nodeend;
			if(graphnow.findnode(nodestart)==-1 || graphnow.findnode(nodeend)==-1)
				cout<<"������д�!�����ʧ��!!!"<<endl;
			else
			{
				graphnow.insertedge(graphnow.findnode(nodestart),graphnow.findnode(nodeend));
				cout<<"��ǰͼ���ڽӱ�����:"<<endl;
				graphnow.showgraph();
			}
		cout<<"================"<<endl;	
		break;
	case '8':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
        cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
		cout<<"������Ҫɾ�������ӵ��������: "<<endl;
		cin>>nodestart>>nodeend;
		if(graphnow.findnode(nodestart)==-1||graphnow.findnode(nodeend)==-1)
			cout<<"������д�!ɾ����ʧ��!!!"<<endl;
		else
		{
			cout<<"Σ�ղ���!��ȷ����?ȷ����(Y||y)��!���������!"<<endl;
			cin>>yesno;
			if(yesno=='y'||yesno=='Y')
			{
				mark=graphnow.deleteedge(graphnow.findnode(nodestart),graphnow.findnode(nodeend));
				if (mark==1)
					cout<<"�ӽ��"<<nodestart<<"��"<<"���"<<nodeend<<"�ı��ѱ�ɾ��!"<<endl;
				cout<<"��ǰͼ���ڽӱ�����:"<<endl;
				graphnow.showgraph();
			}
			else
			cout<<"���β����Ѿ�����!!!";
		}
		cout<<"================"<<endl;
		break;
	case '9':
		//graphnow.inigraph();
		break;
	case 'a':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
        cout<<"================"<<endl;
		cout<<"Լ���ӵ�һ����㿪ʼ������"<<endl;//������ͼ��Ч��
		cout<<"������ȱ�������Ϊ :"<<endl;	
					graphnow.DFSTraverse();
		cout<<endl;
		cout<<"================"<<endl;
        break;
    case 's':
		if(build==0)
		{
			cout<<"================"<<endl;
			cout<<"ͼδ���������β���ʧ��!!!"<<endl;
			cout<<"================"<<endl;
		    break;
		}
		cout<<"================"<<endl;
		cout<<"��ǰͼ���ڽӱ�����:"<<endl;
        graphnow.showgraph();
        cout<<"================"<<endl;
		cout<<"Լ���ӵ�һ����㿪ʼ������"<<endl;//�Է���ͨͼ��Ч��������ͼ��Ч��
		cout<<"������ȱ�������Ϊ :"<<endl;
					graphnow.BFSTraverse();
		cout<<endl;
		cout<<"================"<<endl;
        break;
    case '0':
		cout<<"��ѡ�����˳���ллʹ��..."<<endl;
        system("pause");
        exit(1);
    default:
        cout<<"�����д�����������..."<<endl;
    }
}
int main(void) //���������
{

	system("color f0");
    system("cls");
    interfacebase interfacenow;
	build=0;
    while (1)
    {
        interfacenow.showmenu();
        interfacenow.processmenu();
        system("pause");
        system("cls");
    }
    return 0;
}//����������
