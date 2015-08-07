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
	
	int v0;												//������·������ʹ�õ����
	int *distance,*path;								//������·������ʹ�õľ��������·������

	char nodesarray[11];								//�̲��������������Ľ���������������
	int	 topologicalSort[maxvertices];					//�洢������������Ľ����
	int  InDegree[maxvertices];							//����ͼ���ж����������
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
	
	void datafordijkstra();								//Ϊ�����·������׼������
	void dijkstra(int v0,int distance[],int path[]);	//�����·������ĺ���
	void dodijkstra();									//�������·�����������
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
void graph::inputdata(void)
{
	int nodestart,nodeend,weight;//��ʼ�㡢��ֹ�㡢Ȩֵ
	Vertices.ClearList();//����������
	initializationofEdge(maxvertices); 
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
	cout<<"����:1 2 10 ��ʾ�����һ����(��1�Ž�㵽2�Ž�㣬ȨֵΪ10)!:"<<endl;
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
	delete[] nodearray;
	build=1;
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
////////////////
void graph::datafordijkstra()//Ϊ�����·������׼������
{
	Vertices.ClearList();				//����������
	initializationofEdge(maxvertices); 	//�������ʼ��
	inputnodenum=6;						//�����				
	inputedgenum=8;						//����
	//                     0   1   2   3   4   5
	char defaultnodes[6]={'a','b','c','d','e','f'};//�������
	for(i=0;i<inputnodenum;i++)			
	{		
		insertVertices(defaultnodes[i]);//�ѽ�����洢�ṹ				
	}		    													           
	insertEdge(0,2,10);					//�ѱߵ���Ϣ����洢�ṹ
	insertEdge(0,4,30);
	insertEdge(0,5,100);
	insertEdge(1,2,5);
	insertEdge(2,3,50);
	insertEdge(3,5,10);
	insertEdge(4,3,20);
	insertEdge(4,5,60);
	build=1;
}
void graph::dodijkstra()//�������·�����������
{
	int *distance;
	inputnodenum=numofVertices();			//ȡ�ؽ�����
	distance=new int[inputnodenum];			//��������
	path=new int[inputnodenum];				//·������
	cout<<"���濪ʼ��ĳ����㵽����������̾���..."<<endl;
	cout<<"���������ţ�"<<0<<"~"<<inputnodenum-1<<endl;//��ʾ�������
	cin>>v0;//�������
	if(v0>=0 && v0<=inputnodenum)			//����Ų�����ȷ
	{
		dijkstra(v0,distance,path);			//����ʵ�����·������
		cout<<"�ӽ��"<<getvalue(v0)<<"��������������̾���Ϊ:"<<endl;
		for(i=0;i<inputnodenum;i++)
			if(distance[i]==10000)
				cout<<"�����"<<getvalue(i)<<"����̾���Ϊ: ��"<<endl;
			else
				cout<<"�����"<<getvalue(i)<<"����̾���Ϊ:"<<distance[i]<<endl;
		cout<<endl;
		cout<<"Ѱ��·������:"<<endl;
		cout<<"�ӽ��"<<getvalue(v0)<<"��������������·������һ�����Ϊ:"<<endl;
		for(i=0;i<inputnodenum;i++)
		{
			if(path[i]!=-1)
				cout<<"�����"<<getvalue(i)<<"����һ�����Ϊ:"<<getvalue(path[i])<<endl;
		}
	}
	else
	{
	cout<<"�Բ���!����������!���������������"<<endl;
	}
}
void graph::dijkstra(int v0,int distance[],int path[])
//�����·����������������㡢�������顢·������
{
	int inputnodenum;	
	inputnodenum=numofVertices();			//ȡ�ؽ�����
	int *mark=new int[inputnodenum];		//��־λ����
	int mindis,nextnode;					//���·������һ�����
	int i,j;								//ѭ������
	for(i=0;i<inputnodenum;i++)				//��ʼ��
	{
		distance[i]=getweight(v0,i);		//��һ�־��������¼����ʼ�㵽�������е�ı�Ȩֵ
		mark[i]=0;							//���б�־λ����
		if(i!=v0 && distance[i]<maxweight)	//�����ʼ�����Եִ�ĳ�����
			path[i]=v0;						//��Ѹý�����ȷ���·������
		else
			path[i]=-1;						//-1�����·����ͨ
	}
	mark[v0]=1;								//�����ı�־λ��תΪ1
	for(i=1;i<inputnodenum;i++)				//�ڻ�û���ҵ����·���Ľ�㼯����ѡȡ��̾�����nextnode
	{
		mindis=maxweight;					//����Լ����С����Ϊ�����
		for(j=0;j<=inputnodenum;j++)		//ɨ���������е�
		{
			if(mark[j]==0 && distance[j]<mindis)//���û�н������·���Ҿ���С����С����
			{
				nextnode=j;					//��¼���α߶���ĵ�
				mindis=distance[j];			//��¼�������·��
			}
		}
		if(mindis==maxweight)				//��������·��ʱ�㷨����
		{
			return;
		}
		mark[nextnode]=1;//��ǽ��nextnode�Ѿ��ŵ����ҵ����·���ĵļ�����
		for(j=0;j<inputnodenum;j++)//�޸Ľ��v0�������Ľ����̵ľ���
		{
			if(mark[j]==0 && getweight(nextnode,j)<maxweight			
				&& distance[nextnode]+getweight(nextnode,j)<distance[j])//�����µ����·��
			{
				distance[j]=distance[nextnode]+getweight(nextnode,j);   //ˢ�����·��
				path[j]=nextnode;										//�Ѹõ����·��
			}
		}
	}
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
    cout<<"      ͼ�����·��������ʾ        "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.�ֹ�����ͼ  					 "<<endl;
	cout<<"2.����Ĭ�����ݽ���ͼ 		     "<<endl;
    cout<<"3.�þ�����ʽ��ʾͼ				 "<<endl;
    cout<<"4.������·������				 "<<endl;
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
		graphnow.datafordijkstra();
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
		graphnow.dodijkstra();
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

