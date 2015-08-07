/*����������
ͼ����ع���ʵ�֣��洢�ṹʹ���ڽӾ���
*/
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit};	//���巵����Ϣ�嵥
int build;//���ڿ����Ƿ����ؽ�ͼ��Ϊ0ʱ��ʾ��һ�ν���ͼ��Ϊ1ʱ��ʾ�ؽ�ͼ
/************************************************************/
//˳����� ��ͼ�н����˳������洢���ͼ�н��Ķ�̬��ɾ����
const int MaxListSize=26;//Լ����˳������ֻ��26����ĸ
class SeqList
{
private:
	char node[MaxListSize];//����0���꣬��0-25������
	int size;
public:
	SeqList();
	~SeqList();
	int ListSize()const;
	int ListEmpty()const;
	int Find(char &item)const;
	char Getdata(int pos)const;
	void Insert(const char&item,int pos);
	int Delete(const int pos);
	void ClearList();
};
SeqList::SeqList()//˳���Ĺ��캯��
{
	size=0;
}
SeqList::~SeqList(){}//˳������������
int SeqList::ListSize()const//��˳���Ľ������ĺ���
{
	return size;
}
int SeqList::ListEmpty()const//�ж�˳����Ƿ�Ϊ�յĺ���
{
	if(size==0)
		return 1;
	else
		return 0;
}
int SeqList::Find(char &item)const//����ĳ�����ĺ���
{
	if(size==0)
	{
		return -1;
	}
	int i=0;
	while(i<size && item!=node[i]){i++;}
	if(i<size)
	{
		return i;
	}
	else return -1;
}
char SeqList::Getdata(int pos)const//��ȡĳ��λ�ý��ĺ���
{
	if(pos<0||pos>size-1)
	{
		cout<<"�Բ���!λ�ò���Խ�����!"<<endl;
		return(false);
	}
	return node[pos];
}
void SeqList::Insert(const char &item,int pos)//����һ����㵽˳�����
{
	int i;
	if(size==MaxListSize)
	{
		cout<<"˳��������޷�����!"<<endl;
		return;
	}
	else if(pos<0||pos>size)//���������һ��Ԫ���ұ��ǺϷ���
	{
		cout<<"�Բ���!λ�ò���Խ�����!"<<endl;
		return;
	}
	else
	{
		for(i=size;i>pos;i--)
		{
			node[i]=node[i-1];
			cout<<node[i]<<"//////////////////"<<endl;
		}
		node[pos]=item;
		size++;
	}
}
//��˳�����ɾ��һ�����
int SeqList::Delete(const int pos)
{
	if(size==0)
	{
		cout<<"˳����ѿ��޷�ɾ��!"<<endl;
		return 0;
	}
	else if(pos<0||pos>size-1)
	{
		cout<<"�Բ���!λ�ò���Խ�����!"<<endl;
		return 0;
	}
	else
	{
		char temp=node[pos];
		for(int i=pos;i<size-1;i++)
		{
			node[i]=node[i+1];
		}
		size--;
		return 1;
	}
}
void SeqList::ClearList()//��������˳���
{
	size=0;
}
/***************************************************************************/
//�����ࣺ���ͼ�Ĺ�����ȱ���
const int maxsize=100;
//������ѭ�����е���
class SeqQueue
{
private:
	char queuedata[maxsize];//��������Ԫ�ظ���
	int  front;//����һ������ָ��
	int  rear;//����һ����βָ��
	int  count;//Ԫ�ظ���������
public:
	SeqQueue(void);//���캯��
	~SeqQueue(){};//��������
	int  isempty()const{return front==rear;}
	void enqueue(const char&item);//Ԫ����Ӻ���
	char dequeue();//���Ӻ���
	void showseq();//��������
	void getfront();//����ͷ���ĺ���
};
SeqQueue::SeqQueue()
{
	front=0;//ͷβָ���ռһ���ռ䣬��ô�ܵĿ��Դ����Ԫ�صĸ���Ϊmaxsize-1
	rear =0;
	count=0;//��������ʼΪ0
}
void SeqQueue::enqueue(const char&item)
{
	if(front==(rear+1)%maxsize)//������������
	{
		cout<<"�Բ���!��������!�޷����!"<<endl;
	}
	else
	{
		queuedata[rear]=item;//����Ԫ�شӶ�β���
		rear=(rear+1)%maxsize;//��β�ȼ�һ��ȡģ
		count++;//��������һ
	}
}
char SeqQueue::dequeue()
{
	if(count==0)//����Ϊ�յ�����
	{
		cout<<"�Բ���!�����ѿ�!�޷�ɾ��!"<<endl;
		return false;
	}
	else
	{
		char datatemp=queuedata[front];//����Ԫ�شӶ�ͷ����
		front=(front+1)%maxsize;//��ͷ����
		count--;//Ԫ�ظ�����һ
		return datatemp;
	}
}
void SeqQueue::showseq()
{
	cout<<"����ȫ��Ԫ������:"<<endl;
	for(int i=front;i!=rear;)//���ײ�δ�洢Ԫ�ع�Ҫ��front��ʼ����
	{
		cout<<" "<<queuedata[i];
		i=(i+1)%maxsize;
	}
	cout<<endl;
	cout<<"��ǰԪ�ظ���Ϊ: "<<count<<endl;
	cout<<endl;
}
void SeqQueue::getfront()
{
	if(count==0)//����Ϊ�յ�����
	{
		cout<<"�Բ���!�����ѿ�!"<<endl;
		return;
	}
	else
	{
		cout<<"��ͷ��Ԫ�ص�ֵΪ :"<<queuedata[front]<<endl;
	}
}
/////////////
//ͼ��
const int maxvertices=26;//������������ֵΪ26 
const int maxweight=10000;//���������֮�䲻���ڱ�ʱ�����������10000��ģ��
class graph
{
private:
	int i,j;											//ѭ������
	int flag;											//��־λ
	int inputnodenum,inputedgenum;							//����Ľ�����������
	int numofedges;										//��¼�ߵ�����
	char *nodearray;									//������ʱʹ�õ�һά����
	SeqList Vertices;									//ͼ�Ľ����Ϣ��������һ�����Ա�
	int Edge[maxvertices][maxvertices];					//ͼ�ı���Ϣ,ʹ����һ����ά���飬��һ������ 
	

	char nodesarray[11];								//�̲��������������Ľ���������������
	int	 topologicalSort[maxvertices];					//�洢������������Ľ����
	int  Indegree[maxvertices];							//����ͼ���ж����������
	int  deleflag[maxvertices];							//������߼�ɾ������
public:
	graph(const int size=maxvertices);					//ͼ�Ĺ��캯��
	~graph(){};											//ͼ����������
	void initializationofEdge(int size);				//�ߵ��ڽӾ����ʼ�� 
    void inputdata(void);								//�ֹ���������
	void autocreatgraph();								//����Ĭ������
	void showgraph();									//��ʾͼ���ڽӾ���
	void showVertex();									//��ʾͼ�Ľ��
	int  graphempty()const{return Vertices.ListEmpty();}//�ж�ͼ�Ƿ�Ϊ��
	int  numofVertices(){return Vertices.ListSize();}	//��ͼ�Ľ�����
	int  numofEdges(void){return numofedges;}			//��ͼ�ı���
	char getvalue(const int i);							//��ȡͼĳ������ֵ
	int  getweight(const int nodestart,const int nodeend);//���������֮��ıߵ�Ȩֵ
	void insertVertices(const char& vertices);			//��ͼ�����һ�����
	int  deleteVertex(const int v);						//ɾ��һ�����
	int  insertEdge(const int nodestart,const int nodeend,int weight);//���һ����
	int  deleteEdge(const int nodestart,const int nodeend);//ɾ��һ����
	int  getfirstneighbor(const int v);//Ϊʵ��ͼ�ı��������붨�����ȡ���һ�����ڽ��ĺ���
	int  getnextneighbor(const int nodestart,const int nodeend);//��ȡ����һ�����ڽ��ĺ���
	void depthfirstsearch(const int v,int visited[],void visit(char item));//������ȱ���
	void breadthfirstsearch(const int v,int visited[],void visit(char item));//������ȱ���
	

	void initopological();								//�������򻷾���ʼ��
	void datafortopological();							//Ϊ��������׼������
	void topological();									//����������
};
graph::graph(const int size)//ͼ�Ĺ��캯��
{
	initializationofEdge(maxvertices); 
}
void graph::initializationofEdge(int size)  //�ߵ��ڽӾ����ʼ��
{
	for(int i=0;i<size;i++)//�ڽӾ���ĳ�ʼ��
	{
		for(int j=0;j<size;j++)
			if(i==j)
			{
				Edge[i][j]=0;//������ͬ���֮��ıߵ�ȨֵΪ0
			}
			else
				Edge[i][j]=maxweight;//��ʼ״̬��ͬ���֮�䲻���ڱߣ�Ȩֵ�������10000����ʾ
	}
	numofedges=0;//��ʼ״̬�ߵ�����Ϊ0
}
void graph::showgraph()//ͼ����ʾ����
{
	for(i=0;i<Vertices.ListSize();i++)//���ڽӾ�����ģ��ͼ�ıߵ������Ϣ
	{
		for(j=0;j<Vertices.ListSize();j++)
		{
			if(getweight(i,j)==maxweight)
				cout<<setw(5)<<"��";//��ʾ�������֮��û�б�
			else
				cout<<setw(5)<<getweight(i,j);
		}
		cout<<endl;
	}
}
void graph::showVertex()//��ʾͼ�Ľ��
{
	for(i=0;i<Vertices.ListSize();i++)//��ʾ����
		cout<<setw(5)<<i;
	cout<<endl;
	for(i=0;i<Vertices.ListSize();i++)//��ʾ����
		cout<<setw(5)<<Vertices.Getdata(i);
	cout<<endl;
}
char graph::getvalue(const int i)//��ȡͼ��ĳ������ֵ
{
	if(i<0||i>Vertices.ListSize())
	{
		cout<<"�Բ������Խ�����!"<<endl;
		return false;
	}
	else
		return Vertices.Getdata(i);//����˳���Ĳ������Ŀ��
}
int graph::getweight(const int nodestart,const int nodeend)//���������֮��ıߵ�Ȩֵ
{
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"�Բ������Խ�����!"<<endl;
		return false;
	}
	else
		return Edge[nodestart][nodeend];
}
void graph::insertVertices(const char& vertices)//���һ�����
{
	Vertices.Insert(vertices,Vertices.ListSize());//Ϊ�˼򵥰���ӽ�����˳�������λ��
}
int graph::deleteVertex(const int v)//ɾ��һ�����
{
	for(int i=0;i<Vertices.ListSize();i++)//ɾ������������������������ȫ���ı�����ɾ��
		for(int j=0;j<Vertices.ListSize();j++)
		{
			if(i==v||j==v && Edge[i][j]>0 && Edge[i][j]<maxweight)
			{
				Edge[i][j]=maxweight;
				numofedges--;
			}
		}
	int flag=Vertices.Delete(v);
	if(flag==1)//�ṩһ����־λΪ����ĵ��÷���
		return 1;
	else
		return 0;
}
int graph::insertEdge(const int nodestart,const int nodeend,int weight)//���һ����
{
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"�Բ������Խ�����!"<<endl;
		return 0;
	}
	else
	{
		Edge[nodestart][nodeend]=weight;
		numofedges++;
		return 1;
	}
}
int graph::deleteEdge(const int nodestart,const int nodeend)//ɾ��һ����
{
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"�Բ������Խ�����!"<<endl;
		return 0;
	}
	else
	{
		Edge[nodestart][nodeend]=maxweight;
	    numofedges--;
		return 1;
	}
}
int graph::getfirstneighbor(const int v)//��ȡ���һ�����ڽ��
{
	if(v<0||v>Vertices.ListSize())
	{
		cout<<"�Բ������Խ�����!"<<endl;
		return false;
	}
	else
	{
		for(int col=0;col<=Vertices.ListSize();col++)
		{
			if(Edge[v][col]>0 && Edge[v][col]<maxsize)
				return col;//���������ڵĽ�㷵�����±�
		}
		return -1;//���򷵻�-1
	}
}
int graph::getnextneighbor(const int nodestart,const int nodeend)//��ȡ����һ���ڽӱ�
{//�ҽ��nodestart��<nodestart,nodeend>�ڽӱߵ���һ���ڽӱ�
	if(nodestart<0||nodestart>Vertices.ListSize()||nodeend<0||nodeend>Vertices.ListSize())
	{
		cout<<"�Բ������Խ�����!"<<endl;
		return false;
	}
	else
	{//ʹcolΪnodeend+1���Ѱ�ҵı���nodestart��<nodestart,nodeend>�ڽӱߵ���һ���ڽӱ�
		for(int col=nodeend+1;col<=Vertices.ListSize();col++)
		{
			if(Edge[nodestart][col]>0&&Edge[nodestart][col]<maxsize)
				return col;
		}
		return -1;
	}
}
void graph::depthfirstsearch(const int startpoint,int visited[],void visit(char item))//������ȱ���
{
	int neighborpoint;
	visit(getvalue(startpoint));//���ʽ��startpoint
	visited[startpoint]=1;//��ǽ��startpoint�Ѿ�������
	neighborpoint=getfirstneighbor(startpoint);//����startpoint�ĵ�һ���ڽӽ��
	while(neighborpoint!=-1)//���ڽӽ�����ʱѭ��
	{
		if(!visited[neighborpoint])
			depthfirstsearch(neighborpoint,visited,visit);//�Խ��startpoint�ݹ�
		neighborpoint=getnextneighbor(startpoint,neighborpoint);
		//���neighborpointΪ<startpoint,neighborpoint>�ڽӱߵ���һ���ڽӽ��
	}
}
void graph::breadthfirstsearch(const int startpoint,int visited[],void visit(char item))//������ȱ���
{
	char getqueuehead,neighborpoint;
	SeqQueue queue;
	visit(getvalue(startpoint));//���ʳ�ʼ���startpoint
	visited[startpoint]=1;//���startpoint�Ѿ�����
	queue.enqueue(startpoint);//���startpoint���
	while(!queue.isempty())//����1�������зǿ�ʱ����ִ��
	{
		getqueuehead=queue.dequeue();//����ȡ��ͷ���getqueuehead
		neighborpoint=getfirstneighbor(getqueuehead);//���ͷ���ĵ�һ���ڽӽ��neighborpoint
		while(neighborpoint!=-1)//����2�������neighborpoint���������ִ�� ���򷵻ز���1
		{
			if(!visited[neighborpoint])//�����neighborpoint��δ������
			{
				visit(getvalue(neighborpoint));//���ʽ��neighborpoint
				visited[neighborpoint]=1;//���neighborpoint�Ѿ�����
				queue.enqueue(neighborpoint);//���neighborpoint���
			}
			neighborpoint=getnextneighbor(getqueuehead,neighborpoint);
			//����startpoint,neighborpoint����һ���ڽӽ��Ϊneighborpoint ���ز���2
		}
	}
}
void printchar(char item)
{
	cout<<setw(5)<<item;
}
void graph::initopological()//�������򻷾���ʼ��
{
	Vertices.ClearList();					//����������
	initializationofEdge(maxvertices); 	
	for(j=0;j<maxvertices;j++)				//��ʼ��������顢������顢ɾ����־����
	{
	   topologicalSort[j]=0;
	   Indegree[j]=0;						//�����±�ͳ����ȣ��������
	   deleflag[j]=0;
	}
}
void graph::inputdata(void)
{
	int nodestart,nodeend,weight;//��ʼ�㡢��ֹ�㡢Ȩֵ
	cout<<"������ӽ����Ϣ!"<<endl;
	cout<<"----------------"<<endl;
	cout<<"�����������(С�� "<<maxvertices<<"):";
	cin>>inputnodenum;
    nodearray=new char[inputnodenum];//�����ַ�����
	cout<<"������"<<inputnodenum<<"�����(����Ascii���ַ�)���ո������������Ϻ�س�:"<<endl;
	for(i=0;i<inputnodenum;i++)
		{
			cin>>nodearray[i];
			insertVertices(nodearray[i]);	
		}
	cout<<inputnodenum<<"������Ѿ���ӳɹ���!�ַ��ĵ�Ĭ�ϱ����:"<<endl;
	for(i=0;i<inputnodenum;i++)//��ʾ��Ӧ����	
		cout<<setw(5)<<i;
	cout<<endl;
	for(i=0;i<inputnodenum;i++)//��ʾ�������ַ�
		cout<<setw(5)<<nodearray[i];
	cout<<endl<<endl;
	cout<<"������ӱ���Ϣ!"<<endl;
	cout<<"---------------"<<endl;
	cout<<"���������: ";
	cin>>inputedgenum;
	cout<<"����:1 2 1 ��ʾ�����һ����(��1�Ž�㵽2�Ž�㣬ȨֵΪ1)!:"<<endl;
	for(i=0;i<inputedgenum;i++)
	{
		cout<<"������ӵ�"<<i+1<<"���ߵ���Ϣ: "<<endl;
	    cin>>nodestart>>nodeend>>weight;
        flag=insertEdge(nodestart,nodeend,weight);
		if(flag==1)
			cout<<"��"<<nodestart<<"�Ž��"<<"��"<<nodeend<<"�Ž��֮���Ѿ������ȨֵΪ"
			    <<weight<<"��һ����!"<<endl<<endl;
	}
	cout<<"ͼ�Ѿ�����!"<<endl;
	//delete[] nodearray;
	build=1;
}
////////////////
void graph::datafortopological()//Ϊ��������׼�����ݣ��޻�����ͼ
{
	inputnodenum=11;						//�̲ķ����Ľ�����
	inputedgenum=13;						//�̲ķ����ı���

	nodesarray[0]='a';
	nodesarray[1]='b';
	nodesarray[2]='c';
	nodesarray[3]='d';
	nodesarray[4]='e';
	nodesarray[5]='f';
	nodesarray[6]='g';
	nodesarray[7]='h';
	nodesarray[8]='i';
	nodesarray[9]='j';
	nodesarray[10]='k';
	for(i=0;i<inputnodenum;i++)//���������������			
		insertVertices(nodesarray[i]);				

	insertEdge(0,2,1);//�̲ķ���ʵ�ʱߵ���Ϣ�����������Եִ�ʱ��������λ������Ϊ1
	insertEdge(0,3,1);
	insertEdge(1,3,1);
	insertEdge(1,4,1);
	insertEdge(2,5,1);
	insertEdge(3,5,1);
	insertEdge(4,6,1);
	insertEdge(5,7,1);
	insertEdge(6,8,1);
	insertEdge(6,9,1);
	insertEdge(7,10,1);
	insertEdge(8,10,1);
	insertEdge(9,10,1);
	build=1;
}
void graph::topological()
{
	int tempcount;						//��ʱ������
	for(j=0;j<inputnodenum;j++)			//�����н�����ȣ���ÿһ�п�ʼɨ�裬Ȼ����һ�н���
	{
		tempcount=0;					//������ʱ��������¼ÿһ����1�ĸ���
		for(i=0;i<inputnodenum;i++)		//������ɨ��
			if(getweight(i,j)==1)
				tempcount++;			//����ͨ������ȼ�1
		Indegree[j]=tempcount;			//ÿһ��ͳ����Ϻ�������������±�λ��
	}
	cout<<endl<<"���н���������:"<<endl;//��ʾ�����Ϣ
	for(j=0;j<inputnodenum;j++)
		cout<<nodesarray[j]<<"=>"<<Indegree[j]<<"  ";
	cout<<endl;
	tempcount=0;//������ʱ��������¼�߼�ɾ����ĸ�����ͬʱ���õ��ڽ�������������������±���Ʊ���
	for(i=0;i<inputnodenum;i++)//��ÿһ����㿪ʼ���
		if((Indegree[i]==0) && (deleflag[i]==0))//���Ϊ0��ɾ�����Ϊ0�Ķ���
		{
			topologicalSort[tempcount]=i;//��������������
			tempcount++;                 //��������1��ͬʱΪ�±�
			for(j=0;j<inputnodenum;j++)  //�߼���ɾ���õ��ÿһ��ɨ��һ��
				if(getweight(i,j)==1)    //������ָ��еĸ���ԭ��Ϊ1
					Indegree[j]--;       //����������н��ý�����ȼ�1
			deleflag[i]=1;               //��ɾ����������н��ý��ɾ����Ƿ�תΪ1
		}
	if(tempcount==inputnodenum)//���ȫ����㶼�������������У�˵��������ͼû�л�·
	{ 
		cout<<endl<<"����ͼ����������Ϊ��"<<endl;//�����������
		for(i=0;i<inputnodenum;i++) 
			if(i==inputnodenum-1)
				cout<<"["<<nodesarray[topologicalSort[i]]<<"]";//���һ�����
			else 
				cout<<"["<<nodesarray[topologicalSort[i]]<<"]"<<"��";//�м���
		cout<<endl;
	}
	else
		cout<<"������ͼ�������������У��л�·����!"<<endl;

} 
////////////////
//���洦����󣺽����
class interfacebase
{
private:
	int i;							//ѭ������
	int nodestart,nodeend,weight;	//��ʼ�㡢��ֹ�㡢Ȩֵ
	int flag;						//��־λ
    graph graphnow;					//ͼ�����ʵ����
public:
	void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"=================================="<<endl;
    cout<<"      ͼ��������������ʾ        "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.�ֹ�����ͼ  					 "<<endl;
	cout<<"2.����Ĭ�����ݽ���ͼ 		     "<<endl;
    cout<<"3.�þ�����ʽ��ʾͼ				 "<<endl;
	cout<<"4.���������������				 "<<endl;
    cout<<"0.�˳�							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
    char choice,yesno;			//�����û�ѡ��˵�ѡ��
	//char newnode;
	//int *visited;
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
		graphnow.initopological();
		graphnow.inputdata();
		cout<<"================"<<endl;
        break;
	case '2':
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
		graphnow.initopological();
		graphnow.datafortopological();
		cout<<"����Ĭ�����ݳɹ�!!!"<<endl;
		cout<<"��ǰͼ������ͽ������:"<<endl;
		graphnow.showVertex();
		cout<<"��ǰͼ���ڽӾ�������:"<<endl;
        graphnow.showgraph();
		cout<<"================"<<endl;
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
		cout<<"��ǰͼ������ͽ������:"<<endl;
		graphnow.showVertex();
		cout<<"��ǰͼ���ڽӾ�������:"<<endl;
        graphnow.showgraph();
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
		cout<<"��ǰͼ������ͽ������:"<<endl;
		graphnow.showVertex();
		cout<<"��ǰͼ���ڽӾ�������:"<<endl;
        graphnow.showgraph();
		graphnow.topological();
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

