/*
��n������֮������绰ͨ�����������ѷ�����������ʡǮ��
����㷨Ϊ���ڿ��ܼ����������·��ѡȡn-1����������ͨn-1�����У�
��ʹ��Ͷ�ʴﵽ����С����
�������ڽӾ���Ϊ�洢�ṹ���Խ��ż��(A,B)����ʽ�����С�������ıߡ�
������Ʋ��������Сд��ת��Ϊ��д��
*/
//======================================================================================
//���ܣ���С�������������㷨
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;
enum  returninfo{success,wrong,fail,error};  //�������������
const int Maxsize=26;                       //�����ڽӾ��������ޣ��˴�����ĸ����
float MGraph[Maxsize][Maxsize]={0};         //�ڽӾ����ʼ��Ϊ0
int	  flag[Maxsize]={0};                    //��ʼ����־λȫ��Ϊ0
int   delflag[Maxsize]={0};                 //��ʼ���Ѿ�ɾ�����ı�־λΪ0
int   nodenumber=10,deletenumber=0;         //nodenumber��������deletenumber��ɾ�����ĸ���
int	  datamark=0;							//��־Ŀǰ�Ƿ��Ѿ���ͼ�����ݣ�0Ϊû�н���
//�����
class node     //����һ��node������ʾ�ߵ���Ϣ
{
public:
	node(char initpointstart,char initpointend,float initweight,node *initnext=NULL);
	node(node *initnext=NULL);//���캯�����أ�Ϊͷ����ʡ�ռ�
	~node();
	void display(void);		//��ʾ�ߵĽ���Լ�Ȩֵ��Ϣ
	char pointstart;		//�ߵ���㡾Լ��ASCII��С��
	char pointend;			//�ߵ��յ㡾Լ��ASCII���
	float weight;			//�ߵ�Ȩֵ
	node *next;				//��̽��ָ��
};
node::node(char initpointstart,char initpointend,float initweight,node *initnext)
{
	pointstart=initpointstart;
	pointend=initpointend;
	weight=initweight;
	next=initnext;
}
node::node(node *initnext)
{
	next=initnext;
}
node::~node()
{}
void node::display(void)
{
	cout<<"   ("<<pointstart<<","<<pointend<<")="<<weight<<endl;//����Ϊ�ߵ���㡢�յ㡢Ȩֵ
}
//������
class linklist     //��������linklist��
{
	friend class interfacebase;
	friend class minispantree;
private:
	node *headp;
	int number;    //ͳ��ÿ�������н��ĸ���
public:
	linklist();                                        //���캯��
	~linklist();									   //��������
	void clearlist(void);                              //�������
	bool empty(void) const;                            //�ж��Ƿ����
};
linklist::linklist()                 //���캯��
{
	headp=new node;                  //�����½�㣬��Ϊͷ���
	headp->next=NULL;                //ͷ���ĵ�ַ��Ԥ��Ϊ�յ�ַ
	number=0;                        //���������㣬������ʼʱû��ʵ������
}
linklist::~linklist()                //��������
{
    clearlist();                     //ɾ���������ݣ��ͷ����н��
	delete headp;                    //��ͷ���Ҳ�ͷŵ�
	number=0;                        //���������㣬������ʼʱû��ʵ������
}
void linklist::clearlist(void)       //�������
{
	node *searchp=headp->next,*followp=headp;    //��ʼ������ָ��
    while(searchp!=NULL)
	{
		followp=searchp;
		searchp=searchp->next;
		delete followp;
	}
	headp->next=NULL;              //���������һ����㣬����ͷ��㣬����������Ϊ��
	number=0;                      //������Ҳ����
}
bool linklist::empty(void)const   //�Ƿ����
{
	if(number==0)
		return true;
	else
		return false;
}
//��С��������
class minispantree
{
public:
	minispantree();
	~minispantree();
	bool readfile();				//���ļ�����
	void traveral(void);			//��ʾ��ǰ�ڽӾ���
	returninfo nodeinsdel(void);	//������ɾ����
	returninfo edgeinsdel(void);	//�ߵ���ɾ����
	returninfo edgemodify(void);	//�޸ıߵ�Ȩֵ
	void failflag(void);			//��ʾ��־λ��Ϣ
	char letterchange(char nodenameofedge);	//Сд��ĸ���ɴ�д��Ϣ
	returninfo kruskal();			//kruskal�㷨
	returninfo prim();				//prim�㷨
protected:
	linklist list[4];
	//0��1�±��ʾprim�㷨��ʼ����������,2��3�±��ʾkruskal�㷨�ĳ�ʼ����������
};
minispantree::minispantree(){}
minispantree::~minispantree(){}
bool minispantree::readfile()     //���ļ�����
{
	char choice;
	choice='0';
	cout<<endl<<"��ѡ��ͬ���ļ���"<<endl;
	cout<<"	1������Ĭ������"<<endl
		<<"	2���й�����㲻���γ���ͨͼ��Ĭ������"<<endl
		<<"	3�����ظ����ݵ�Ĭ������"<<endl
		<<"	4������г���Χ�����Ĭ������"<<endl
		<<"	5�������û������������ļ����ļ���Լ��Ϊ��graphdata.txt��"<<endl
		<<"	6���˳�"<<endl<<"��ѡ��";

	/*do
	{
		cin>>choice;
    }while(choice<'1'&&choice>'6');
	*/
	
	while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4'&&choice!='5'&&choice!='6')
		cin>>choice;
    
	fstream in;
	switch(choice)    //�����û���ѡ�������Ӧ�Ĳ���
	{
	case '1':
		cout<<endl<<"����������Ĭ�����ݣ����Բ�����С������������"<<endl;
		in.open("graphdata01.txt");
		break;
	case '2':
		cout<<endl<<"�����й�������Ĭ�����ݣ������γ���ͨͼ��"<<endl;
		in.open("graphdata02.txt");
		break;
	case '3':
		cout<<endl<<"�������ظ����ݵ�Ĭ�����ݣ���ͬ���ݺ������Ч��"<<endl;
		in.open("graphdata03.txt");
		break;
	case '4':
		cout<<endl<<"�����㳬��Χ�����Ĭ�����ݣ����Գ���Χ��㣡"<<endl;
		in.open("graphdata04.txt");
		break;
	case '5':
		cout<<endl<<"�����û������������ļ����ļ���Լ��Ϊ��graphdata.txt��"<<endl;
		in.open("graphdata.txt");
		break;
	case '6':
		{cout<<endl<<"���Ѿ�ѡ��������ļ���"<<endl;
		return false;
		}
	default:
		break;
	}
	if(!in)
		return false;
    else
	{
		int row,col,edgenumber,edgenumbernow;		//�����ꡢ�����ꡢ�ߵĸ�������ʱ����������
		float edgeweight;							//Ȩֵ
		char nodenameofedge[5];						//nodenameofedgeΪ�ߵ���Ϣ���ַ����飬����Ϊ5
		for(row=0;row<Maxsize;row++)				//ÿ�����¿�ʼ������Ҫ��ʼ������������ֵ
			for(col=0;col<Maxsize;col++)
				MGraph[row][col]=0;
		deletenumber=0;                             //ɾ�����������
		for(col=0;col<nodenumber;col++)
			delflag[col]=0;                         //ɾ������־λ����
		in>>nodenumber;								//����ͼ�Ľ������
	    in>>edgenumber;								//����ͼ�ı�����
		edgenumbernow=edgenumber;					//����һ����ʱ����������
		while(edgenumbernow!=0)						//����ߴ��ڣ���������Ϣ��Ȩֵ	
		{
			in>>nodenameofedge>>edgeweight;			//nodenameofedge��ʽ����Ϊ<AB>=
			nodenameofedge[1]=letterchange(nodenameofedge[1]);	//����0Ϊ�����ţ�����1Ϊ��һ����ĸ
			nodenameofedge[2]=letterchange(nodenameofedge[2]);  //����2Ϊ�ڶ�����ĸ����ת��Ϊ��д
			row=nodenameofedge[1]-'A';				//����������
			col=nodenameofedge[2]-'A';				//����������
			if(row<nodenumber && col<nodenumber )
			{
				MGraph[row][col]=edgeweight;			//���ڽӾ���������Ӧ����
				MGraph[col][row]=edgeweight;			//����ͼ�����жԳƵ�λ��ͬʱ��ֵ	
			}
			edgenumbernow--;//������������һ��Ϊ�������δ�����׼��
		}
	}
	in.close();    //�ر����ļ�
	return true;
}
void minispantree::traveral(void)
{
	int i,j;
	char inode='A';
	cout<<"    ��";
	for(i=0;i<nodenumber;i++)
		cout<<setw(6)<<setiosflags(ios::right)<<inode++;
	inode='A';     //���¸�ֵ
	cout<<endl<<"������";
	for(i=0;i<nodenumber;i++)
		cout<<"������";
	for(i=0;i<nodenumber;i++)
	{
		cout<<endl<<"  "<<setw(2)<<inode++<<"��";
		for(j=0;j<nodenumber;j++)
		{
			if(delflag[i]==1 || delflag[j]==1)      //ɾ����
				cout<<setw(6)<<setiosflags(ios::right)<<"�|";
			else if(i!=j && MGraph[i][j]==0)  //�ޱ�
				cout<<setw(6)<<setiosflags(ios::right)<<"��";
			else
				cout<<setw(6)<<setiosflags(ios::right)<<MGraph[i][j];
		}
		cout<<endl<<"    ��";
	}
	cout<<endl<<endl<<"����ܰ��ʾ��������ʾΪ �| �ı�ʾ�õ㱻ɾ������������ʾ��"<<endl<<endl;
}
returninfo minispantree::nodeinsdel(void)  //�����Ϣ����ɾ����
{
	char inode;
	int row,col,choice;
	cout<<"	1�����ӽ�����"<<endl<<"	2��ɾ��������"<<endl<<"	3���˳�"<<endl<<"��ѡ��";
	cin>>choice;
	if(choice==1)
	{
		cout<<"������ѡ�����������У� ";
		delflag[nodenumber]=1;
		nodenumber++;
		for(row=0;row<nodenumber;row++)
			if(delflag[row]==1)
				cout<<setw(5)<<char(row+'A');
		cout<<endl<<endl<<"	��ѡ��";
		cin>>inode;
		inode=letterchange(inode);      //�������ݼ��
		if(inode==0)					//���������д�
			return error;
		if(delflag[inode-'A']!=1)		//û��������ȷ
			return error;
		nodenumber--;
		delflag[nodenumber]=0;             //���»ص�0
		if(inode-'A'==nodenumber)
		{	nodenumber++; deletenumber++;}      //����������Ϊ��������nodenumber++
		delflag[inode-'A']=0;			//��ֵ0
		deletenumber--;
	}
	else if(choice==2)
	{
		cout<<"������ѡ���ɾ������У� ";
		for(row=0;row<nodenumber;row++)
			if(delflag[row]==0)
				cout<<setw(5)<<char(row+'A');
			cout<<endl<<endl<<"	��ѡ��";
			cin>>inode;
			inode=letterchange(inode);   //�������ݼ��
			if(inode==0)                 //���������д�
				return error;
			if(delflag[inode-'A']==1)    //û��������ȷ
				return error;
			deletenumber++;                   //��ɾ�����deletenumber++
			delflag[inode-'A']=1;        //��ֵ1
			for(row=0;row<nodenumber;row++)  //ɾ�����ϵı�ȫ��Ϊ0
				for(col=0;col<nodenumber;col++)
					if(col==inode-'A' || row==inode-'A')
						MGraph[row][col]=0;
	}
	else
		return fail;     //�˳�
	return success;
}
returninfo minispantree::edgeinsdel(void)  //����Ϣ����ɾ����
{
	char nodenamestart,nodenameend;
	int  row,col,choice;
	float weight;
	cout<<"	1�����ӱ���Ϣ����"<<endl<<"	2��ɾ������Ϣ����"<<endl<<"	3���˳�"<<endl<<"��ѡ��";
	cin>>choice;
	if(choice==1)
	{
		cout<<"���������ӱ߶�Ӧ�Ľ�����ƣ���ʽ��A B ���ո�ֿ�������";
		cin>>nodenamestart>>nodenameend;
		nodenamestart=letterchange(nodenamestart);     //�������ݼ��
		nodenameend=letterchange(nodenameend);
		if(nodenamestart==0 || nodenameend==0) //������������
			return error;
		row=nodenamestart-'A';
		col=nodenameend-'A';
		if(delflag[row]==1 || delflag[col]==1)  //�����Ƿ����
			return error;
		if(MGraph[row][col]!=0)
		{
			cout<<"��ǰ�˱ߵ�Ȩֵ�ǣ�"<<MGraph[row][col]<<endl;
			return fail;
		}
		cout<<"������ñߵ�Ȩֵ��";
		cin>>weight;
		MGraph[row][col]=weight;         //���ڽӾ���������Ӧ����
		MGraph[col][row]=weight;
	}
	else if(choice==2)
	{
		cout<<"������ɾ���߶�Ӧ�Ľ�����ƣ���ʽ��A B ���ո�ֿ�������";
		cin>>nodenamestart>>nodenameend;
		nodenamestart=letterchange(nodenamestart);     //�������ݼ��
		nodenameend=letterchange(nodenameend);
		if(nodenamestart==0 || nodenameend==0) //������������
			return error;
		row=nodenamestart-'A';
		col=nodenameend-'A';
		if(delflag[row]==1 || delflag[col]==1)  //�����Ƿ����
			return error;
		if(MGraph[row][col]==0)
			return fail;
		MGraph[row][col]=0;         //���ڽӾ���������Ӧ����
		MGraph[col][row]=0;
	}
	else
		return fail;     //�˳�
	return success;
}
returninfo minispantree::edgemodify()  //�޸ıߵ�Ȩֵ��Ϣ
{
	char nodenamestart,nodenameend,choice;
	float edgeweight;
	int row,col;
	cout<<"���������޸ı߶�Ӧ�Ľ�����ƣ���ʽ��A B ���ո�ֿ�������";
	cin>>nodenamestart>>nodenameend;
	nodenamestart=letterchange(nodenamestart);    //�������ݼ��
	nodenameend=letterchange(nodenameend);
	if(nodenamestart==0 || nodenameend==0) //������������
		return error;
	row=nodenamestart-'A';
	col=nodenameend-'A';
	if(delflag[row]==1 || delflag[col]==1)  //�����Ƿ����
		return error;
	if(MGraph[row][col]==0)    //���ñ��Ƿ����
		return error;
	cout<<"��ǰ�˱ߵ�Ȩֵ�ǣ�"<<MGraph[row][col]<<endl;
	cout<<"ȷ��Ҫ�����޸���Y/y����";
	cin>>choice;
	if(choice=='Y' || choice=='y')
	{
		cout<<"��������Ҫ�����趨��Ȩֵ��";
		cin>>edgeweight;
		MGraph[row][col]=edgeweight;         //���ڽӾ���������Ӧ����
		MGraph[col][row]=edgeweight;
	}
	else
		return fail;
	return success;
}
void minispantree::failflag(void) //��ʾ��־λ�õ���Ϣ
{
	int i;
	cout<<"������";
	for(i=0;i<nodenumber;i++)
		cout<<"�Щ�";
	cout<<"��"<<endl;
	cout<<"����㩦";
	for(i=0;i<nodenumber;i++)
		cout<<char(i+'A')<<" ��";
	cout<<endl<<"������";
	for(i=0;i<nodenumber;i++)
		cout<<"�੤";
	cout<<"��"<<endl;
	cout<<"����־��";
	for(i=0;i<nodenumber;i++)
	{
		if(delflag[i]==1)
			cout<<"�|��";
		else
			cout<<flag[i]<<" ��";
	}
	cout<<endl<<"������";
	for(i=0;i<nodenumber;i++)
		cout<<"�ة�";
	cout<<"��"<<endl<<endl;
}
char minispantree::letterchange(char nodenameofedge) //����������ĸ��Ϣ�����Сд����д��
{
	if(nodenameofedge>='a' && nodenameofedge<='a'+nodenumber-1)
		return char(nodenameofedge-32);    //Сд����д
	else if(nodenameofedge>='A' && nodenameofedge<='A'+nodenumber-1)
		return nodenameofedge;         //��д�򲻸�
	else
		return 0;            //��ʾ����������д�
}
returninfo minispantree::prim()     //prim�㷨
{
	//list[4]������0��1�����ʾprim�㷨�ĳ�ʼ��������ս������
	list[0].clearlist();//ÿ�ε����㷨ǰ����ʼ�������������
	list[1].clearlist();  
	char beginnode;//����������
	node *newnode,*searchp,*followp,*listrear;//�½�㡢����ָ�롢β��ָ�롢β��ָ��
	int i,j;//ѭ������
	int nodeflag=0;//����־λ
  	for(i=0;i<nodenumber;i++)     //��־λ����
		flag[i]=0;
	cout<<"�������淶Χ��������ʼ������ơ�A-"<<char('A'+nodenumber-1)<<"����";
	cin>>beginnode;
	beginnode=letterchange(beginnode);    //Сдת���ɴ�д
	if(beginnode==0) //������������
		return error;
	i=int(beginnode-'A');//���������������
    flag[i]=1;       //�Ѹ���Ŵ������ʼ��ı�־λ��תΪ1
	while(list[1].number!=nodenumber-1-deletenumber)
	{
		for(j=0;j<nodenumber;j++)
			if(MGraph[i][j]!=0)    //i�̶����䣬�������е���ȫ����һ��
			//����ڽӾ�����Ȩֵ��Ϊ0,��Ѹñ߼ӵ�������
			{
				newnode=new node(i+'A',j+'A',MGraph[i][j]);//����д�����Ӧ�Ľ������Ȩֵ
				if(list[0].empty()) //�����ʱ����Ϊ��
				{
					newnode->next=NULL;
					list[0].headp->next=newnode;
					list[0].number++;
				}
				else
				{
					//����������Ѿ����ڵĻ������������
					searchp=list[0].headp->next;//��������ָ��
					followp=list[0].headp;      //����β��ָ�� 
					while(searchp!=NULL && searchp->weight<MGraph[i][j])//�������У�����ȷλ��
					{
						followp=searchp;
						searchp=searchp->next;
					}
					while(searchp!=NULL && searchp->weight==MGraph[i][j])//������Ȩֵ���ʱ
					{
						if(searchp->pointstart==i+'A' && searchp->pointend==j+'A')//����յ�Ҳ��ͬ
						{
							nodeflag=1;
							delete newnode;//�ͷ��½��
							break;
						}
						searchp=searchp->next;//�����ƶ�ָ��
					}
					if(followp!=NULL && nodeflag==0)
					{
						newnode->next=followp->next;//�����½�㵽������
						followp->next=newnode;
						list[0].number++;			//��������һ
						nodeflag=0;					//���¹���
					}
				}
			}
		if(list[0].number==0 )
		{	if(delflag[i]==1)
			{
				cout<<endl<<"������Ľ�� "<<char(i+'A')<<" �ѱ�ɾ��!"<<endl;
				cout<<endl<<"����ܰ��ʾ��"<<endl
					<<"	1.��־ֵΪ0��ʾΪ��δѡ��Ľ���Ⱥ��"<<endl
					<<"	2.��־ֵΪ1��ʾ�ѱ�ѡ��Ľ��Ⱥ��"<<endl
					<<"	3.��־ֵΪ �| ��ʾ��ɾ�����Ⱥ��"<<endl<<endl;
				failflag();          //��ʾ��־λ��Ϣ
				return error;
			}
			cout<<endl<<"����ܰ��ʾ��"<<endl
				<<"	1.��־ֵΪ0��ʾΪ��δѡ��Ľ���Ⱥ��"<<endl
				<<"	2.��־ֵΪ1��ʾ�ѱ�ѡ��Ľ��Ⱥ��"<<endl
				<<"	3.��־ֵΪ �| ��ʾ��ɾ�����Ⱥ��"<<endl<<endl;
			failflag();          //��ʾ��־λ��Ϣ
			return fail;
		}
		searchp=list[0].headp->next;	//ȡ��ǰlist[0]������Ȩֵ��С�ı�
		while(searchp->next!=NULL && 
			flag[int(searchp->pointstart-'A')]+flag[int(searchp->pointend-'A')]==2)
		//��ʱsearchp�漰�ߵ������յ������ѡ���У����������򹹳ɻ�·��
		{
			list[0].headp->next=searchp->next;
			delete searchp;  //�ͷſռ�
			searchp=list[0].headp->next;//������������ָ��
		}
		//��ʱsearchpָ��һ����Ч�ߣ�������뵽list[1]�У����ҽ���������ѡ����
		i=flag[int(searchp->pointstart-'A')]<flag[int(searchp->pointend-'A')]?
			(searchp->pointstart-'A'):(searchp->pointend-'A');//ѡȡС�߱�־λ
		flag[i]=1;
		newnode=new node(searchp->pointstart,searchp->pointend,searchp->weight);//�������ݴ�����
		newnode->next=NULL;
		if(list[1].empty()) //�����ʱΪ��
		{
			list[1].headp->next=newnode;
			listrear=newnode;//����һ�������β��ָ������ÿ�β���������λ����
		}
		else
		{
			listrear->next=newnode;//���������һ�����
			listrear=newnode;//�ƶ�β��ָ�룬Ϊ��һ�ι�����׼��
		}
		list[1].number++;
	}
	for(i=0;i<nodenumber;i++)//ɨ���ж��Ƿ�Ϊ��С��������ȫ����־λΪ1��ɹ�����С��������������ͨ
		if(flag[i]!=1 && delflag[i]==0)   //����״̬��ȫ����־λΪ1�������ܹ�����С������
		{
			cout<<endl<<"����ܰ��ʾ��"<<endl
				<<"	1.��־ֵΪ0��ʾΪ��δѡ��Ľ���Ⱥ��"<<endl
				<<"	2.��־ֵΪ1��ʾ�ѱ�ѡ��Ľ��Ⱥ��"<<endl
				<<"	3.��־ֵΪ �| ��ʾ��ɾ�����Ⱥ��"<<endl<<endl;
			failflag();          //��ʾ��־λ��Ϣ
			return fail;
		}
	float total=0;					//��Ȩֵ����
	searchp=list[1].headp->next;	//�Խ���������ɨ��
	while(searchp!=NULL)			//��ʾ��С��������Ϣ
	{
		searchp->display();			//��ʾ��ǰ�ߵ���Ϣ
		total+=searchp->weight;		//�ۼ���С��������Ȩֵ
		searchp=searchp->next;
	}
	cout<<endl<<"��С����������ȨֵΪ��"<<total<<endl;//��ʾ��Ȩֵ
	return success;
}
returninfo minispantree::kruskal() //kruskal�㷨
{
	char nodenamestart,nodenameend;				//�ߵĿ�ʼ����������������
	node *newnode,*searchp,*followp,*listrear;	//�½�㡢����ָ�롢β��ָ�롢����β��ָ��
	int mark=0;									//mark��־��¼��ǰ��������ĸ��߼�
	int noderow,nodecol,tempvalue,tempbigger;	//����Ӧ���С��У���ʱ�洢ʹ�õı���������
	int nodeflag;						//��־�������Ƿ���Խ�����С��������Ϊ1���룬Ϊ0ʧ��
	int i,j,k;							//ѭ��������
	for(k=0;k<nodenumber;k++)			//�Ƿ��Ѿ�������С�������ı�־λȫ������
		flag[k]=0;
	list[2].clearlist();				//ÿ�ο�ʼʱ����ʼ��������ս���������
	list[3].clearlist();  
	//list[4]��2��3�����ʾkruskal�㷨�ĳ�ʼ��������ս������
	for(i=0;i<nodenumber-1;i++)//ɨ���ڽӾ��������н�������к���
		for(j=i+1;j<nodenumber;j++)//�������ȷ������������Ǿ�������з�0��Ȩֵ
		{
			if(MGraph[i][j]!=0) //�������Ȩֵ�漰�����������Ȩֵ���ݼ��뵽�����С���Ȩֵ�������С�
			{
				nodenamestart=i+'A';//����Ascii���������ת���ɽ����
				nodenameend=j+'A';  //����Ascii���������ת���ɽ����
				newnode=new node(nodenamestart,nodenameend,MGraph[i][j]);
				//�����½�㣬�ѱ��漰����������Ȩֵ����
				if(list[2].empty()) //�����ʱ����Ϊ�գ�����Ϊ��һ��������
				{
					newnode->next=NULL;
					list[2].headp->next=newnode;
				}
				else
				{
					followp=list[2].headp;
					searchp=list[2].headp->next;
					while(searchp!=NULL && searchp->weight<MGraph[i][j])//Ϊ�˱�֤��������ȷλ��
					{
						followp=searchp;
						searchp=searchp->next;
					}
					newnode->next=searchp;//�ҵ������������Ȩֵ��С��������
					followp->next=newnode;
				}
				list[2].number++;//������������������һ
			}
		}
	//���潫�������������а��մ�С����Ĵ���ѡ����С�������Ϸ��ı�
	searchp=list[2].headp->next;//��������ָ��
	while(searchp!=NULL && list[3].number!=nodenumber-1)//������û������Ҳ����ı�������ʱ��������
	{
		nodeflag=1; //ÿ�ο�ʼ��������Ϊ1�����赱ǰ����ǿ��Լ�����С��������
		noderow=searchp->pointstart-'A';//�ѵ�ǰ���Ľ������Ϊԭ�ڽӾ����е�������
		nodecol=searchp->pointend-'A';  //�ѵ�ǰ�յ�Ľ������Ϊԭ�ڽӾ����е�������
		if(flag[noderow]+flag[nodecol]==0)  //�������Ϊ0��˵����������㶼���Խ�����С������
		{
			flag[noderow]=++mark;//ÿ���µı߼��Ͽ�ʼʱ��־λ��������1�������жϸ�ͼ�Ƿ�����ͨͼ
			flag[nodecol]=mark;
		}
		else if(flag[noderow]*flag[nodecol]==0) //ֻ��һ��Ϊ0
		{
			tempvalue=(flag[noderow]>flag[nodecol])?flag[noderow]:flag[nodecol]; //ѡ������ֵ
			flag[noderow]=tempvalue;//Ŀ���Ǳ��ֽ��뵱ǰ�ı߼���
			flag[nodecol]=tempvalue;
		}
		else if(flag[noderow]*flag[nodecol]!=0) //�������Ϊ0����������������
		{
			if(flag[noderow]==flag[nodecol]) //��־λ������ȣ�˵����һ���߼��У�Ҳ���ǻ�����������
				nodeflag=0;                   //�������ͨ����־λ��תΪ0��ɣ�����ֻ����һ�����
			else      //���߶���Ϊ0�Ҳ���ȣ�˵����ʼʱ����һ���߼��У�������ͨ�ˣ���Ҫ�ϲ��߼�����ȡСֵ
			{
				tempvalue=(flag[noderow]<flag[nodecol])?flag[noderow]:flag[nodecol]; //׼��С�ı�־λ
				tempbigger=(flag[noderow]>flag[nodecol])?flag[noderow]:flag[nodecol];//��¼��ı�־λ
				for(k=0;k<nodenumber;k++)//���б�־λɨ�裬���ڴ��־λ��ȫ��ˢ��ΪС�ı�־λ
					if(flag[k]==tempbigger)
						flag[k]=tempvalue;
			}
		}
		else     //�������������������д�����ʾ���н��ı�־
		{
			return error;
		}
		if(nodeflag==1)//��ʾ�����������С������������
		{
			//���˽����ӵ�����״̬�����С�β�巨��
			newnode=new node(searchp->pointstart,searchp->pointend,searchp->weight);
			newnode->next=NULL;
			if(list[3].empty()) //�����ʱ����Ϊ�գ�����Ϊ��һ��������
			{
				list[3].headp->next=newnode;
				listrear=newnode;//����һ�������β��ָ������ÿ�β���������λ����
			}
			else
			{
				listrear->next=newnode;//���������һ�����
				listrear=newnode;//�ƶ�β��ָ�룬Ϊ��һ�ι�����׼��
			}
			list[3].number++;//��������һ
		}
		searchp=searchp->next;//����������һ����㣬�����㹻ʱ����ֹͣ
	}
	for(k=0;k<nodenumber;k++)//ɨ���ж��Ƿ�Ϊ��С��������ȫ����־λΪ1��ɹ�����С��������������ͨ
		if(flag[k]!=1 && delflag[k]==0)   //ֻҪ����һ������־λ��Ϊ1���Ҳ��Ǳ�ɾ���Ľ�㣬��ʧ��
		{
			cout<<endl<<"����ܰ��ʾ��"<<endl<<"	1.��־ֵΪ0��ʾΪ������㣻"
				<<endl<<"	2.��־ֵΪ��0����ȵı�ʾ�����Ľ�㼯�ϣ�"
				<<endl<<"	3.��־ֵΪ �| ��ʾ��ɾ����㼯�ϡ�"<<endl<<endl;
			failflag();				//��ʾ��־λ��Ϣ
			return fail;			//ֱ���˳�
		}
	float total=0;//��Ȩֵ�ۼ�������
	searchp=list[3].headp->next;//��������ָ��
	while(searchp!=NULL)//��ʾ�����С�������ı�
	{
		searchp->display();//ÿһ����������ֵ���������
		total+=searchp->weight;//��Ȩֵ�ۼ�
		searchp=searchp->next;//�ƶ���������ָ��
	}
	cout<<endl<<"��С����������ȨֵΪ��"<<total<<endl;//��ʾ��Ȩֵ
	return success;
}

//������
class interfacebase
{
private:
	minispantree listonface;  //����һ������listonface
public:
	void clearscreen(void);
	void showmenu(void);
	int  userchoice(void);
	void processmenu(char choice);
};
void interfacebase::clearscreen(void)
{
    system("cls");
}
void interfacebase::showmenu(void)
{
  	cout<<"   �绰ͨ������С������������ʾ�˵�  "<<endl;
    cout<<"====================================="<<endl;
    cout<<"1.�ļ���ȡ��㡢�ߺ�Ȩֵ��Ϣ			"<<endl;
    cout<<"2.���ӻ�ɾ�����						"<<endl;
	cout<<"3.���ӻ�ɾ����						"<<endl;
    cout<<"4.�޸�Ȩֵ							"<<endl;
    cout<<"5.��ʾ��ǰ�ڽӾ���					"<<endl;
	cout<<"6.Prim�㷨(����ķ�㷨)				"<<endl;
	cout<<"7.Kruskal�㷨(��³˹�����㷨)		"<<endl;
    cout<<"8.��������							"<<endl;
	cout<<"====================================="<<endl;
}
int interfacebase::userchoice(void)
{	char choice;
	cout<<"����������ѡ��";
	cin>>choice;
	return choice;
}
void interfacebase::processmenu(char choice)
{
	int returnvalue;

	switch(choice)    //�����û���ѡ�������Ӧ�Ĳ���
	{
	case '1':
		if(!listonface.readfile())
		{
		cout<<endl<<endl<<"�������ļ�����ļ����������������..."<<endl;
		break;
		}
		else
		{
			cout<<"�ɹ������ļ��еĽ�㡢�ߺ�Ȩֵ����Ϣ!�����ڽӾ������£�"<<endl<<endl;
			listonface.traveral();                 //��ʾ�ڽӾ���
			datamark=1;
			cout<<endl<<endl<<"������ɣ������������..."<<endl;
		}
		break;
	case '2':
		returnvalue=listonface.nodeinsdel();
		if(returnvalue==fail)
			cout<<endl<<endl<<"�ɹ��˳��������!�밴���������..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"����������д�����ʧ��!�밴���������..."<<endl;
		else
		{
			cout<<endl<<endl<<"�����ɹ�!�밴���������..."<<endl;
			datamark=1;
		}
		break;
	case '3':
		if(datamark==0)
		{
			cout<<endl<<"Ŀǰû��ͼ����Ϣ���޷�����!�밴���������..."<<endl;
			break;
		}
		returnvalue=listonface.edgeinsdel();
		if(returnvalue==fail)
			cout<<endl<<endl<<"�ɹ��˳��������!�밴���������..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"����������д�����ʧ��!�밴���������..."<<endl;
		else
			cout<<endl<<endl<<"�����ɹ�!�밴���������..."<<endl;
		break;
	case '4':
		if(datamark==0)
		{
			cout<<endl<<"Ŀǰû��ͼ����Ϣ���޷�����!�밴���������..."<<endl;
			break;
		}
		returnvalue=listonface.edgemodify();
		if(returnvalue==fail)
			cout<<endl<<endl<<"�ɹ��˳��������!�밴���������..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"����������д�!�밴���������..."<<endl;
		else
			cout<<endl<<endl<<"�����ɹ�!�밴���������..."<<endl;
		break;
	case '5':
		if(datamark==0)
		{
			cout<<endl<<"Ŀǰû��ͼ����Ϣ���޷�����!�밴���������..."<<endl;
			break;
		}
		cout<<endl<<endl<<"��ǰϵͳ�е��ڽӾ�����Ϣ���£�"<<endl<<endl;
		listonface.traveral();
		cout<<endl<<endl<<"��Ϣ��ʾ�ɹ�!�밴���������..."<<endl;
		break;
	case '6':
		if(datamark==0)
		{
			cout<<endl<<"Ŀǰû��ͼ����Ϣ���޷�����!�밴���������..."<<endl;
			break;
		}
		cout<<endl<<"��ѡ����Prim�㷨��"<<endl;
		returnvalue=listonface.prim();
		if(returnvalue==error)
			cout<<endl<<endl<<"�����д�����ʧ��!�밴���������..."<<endl;
		else if(returnvalue==fail)
			cout<<endl<<endl<<"������С������������������!�밴���������..."<<endl;
		else
			cout<<endl<<endl<<"Prim�㷨�ɹ�!�밴���������..."<<endl;
		break;
	case '7':
		if(datamark==0)
		{
			cout<<endl<<"Ŀǰû��ͼ����Ϣ���޷�����!�밴���������..."<<endl;
			break;
		}
		cout<<endl<<"��ѡ����Kruskal�㷨��"<<endl;
		returnvalue=listonface.kruskal();
		if(returnvalue==fail)
			cout<<endl<<endl<<"������С������������������!�밴���������..."<<endl;
		else if(returnvalue==error)
			cout<<endl<<endl<<"�����д�����ʧ��!�밴���������..."<<endl;
		else
			cout<<endl<<endl<<"Kruskal�㷨�ɹ�!�밴���������..."<<endl;
		break;
	case '8':
				cout<<endl<<endl<<"���Ѿ��ɹ��˳���ϵͳ����ӭ�ٴ�ʹ��!!!"<<endl;
		        exit(0);
	default:
				cout<<endl<<endl<<"�Բ���������Ĺ��ܱ���д�!����������!!!"<<endl;
		    	break;
	}
}
int main(void)                     //���������
{
	char choice;
	system("color f0");
	interfacebase interfacenow;
	interfacenow.clearscreen();
    while (1)
	{
  		interfacenow.showmenu();
		choice=interfacenow.userchoice();
		interfacenow.processmenu(choice);
		getch();
		interfacenow.clearscreen();
    }
    return 0;
}//����������
