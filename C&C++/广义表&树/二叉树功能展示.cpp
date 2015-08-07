/*����������
      1. �������������ַ���(�������ʽ���á��������������������ݹ���)��
	  2. ������������ַ���(�������ʽ��������ʽ)��
	  3. ���������ֱ���(�ݹ����֡��ǵݹ����֡���α��������֣�ʹ�����Ա��߼��ṹ�����
	  4. ��������ȫ��������Ϣ��ʾ��
	  2. ���ӡ�ɾ���Ͳ������ݽ�㡣
	  3. �ṩ��ǰ����ָ���ת��(��������ӡ������Ҷ��ӡ��������׺��������������������Ҷ���)
*/

#include<windows.h>
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };					//���巵����Ϣ�嵥
#define Maxsize 100									//������������ĳ���
char defaultbtree1[]="a(b,c(,d))";					//Ĭ�Ϲ�������ݱ�ʾ�Ķ���������1
char defaultbtree2[]="a(b(c(d,e),f(,g)),h(i,j))";	//Ĭ�Ϲ�������ݱ�ʾ�Ķ���������2
class node
{
    friend class btree;//�����������Ԫ��
public:
    node(char initdata='0',int initdeep=0,node *initl=NULL,node *initr=NULL,
		node *initf=NULL,node *initn=NULL);
    ~node() {};
protected:
    char data;		//����������е����ݣ��˴�����Ϊ�ַ�
    int	 deep;		//���ö������������
    node *lchild;	//�����
    node *rchild;	//�Ҷ���
    node *father;	//���׽��
    node *next;		//�õ����������н��ʱָ����һ�����
};
node::node(char initdata,int initdeep,node *initl,node *initr,node *initf,node *initn)
{
    data=initdata;
    deep=initdeep;
    lchild=initl;
    rchild=initr;
    father=initf;
    next=initn;
}
class stackdata //����һ��stackdata�࣬�ڷǵݹ�����㷨����Ҫ
{
    friend class btree;
private:
    node *link;
    int  flag;
public:
    stackdata()  {};
    ~stackdata() {};
};
class btree  //����һ����������
{
private:
    char btreedata[Maxsize];		//������ַ�����
    char answer;					//���ڻش�˵�ѡ��
    node *root;						//ָ������λ�õ�ָ��
    node *workinp,*linkrear;		//����һ������ָ�룬β��ָ��
    int  btreecount;				//������������
    bool firstbracket;				//��ʾ�����ʱ�����һ�����ţ�Ϊ1�ǣ����0�Ͳ�����
	int  countnow;					//ÿһ����Ҫʹ�ü�����ʱ��ʱ�����ֵ
    int  leafcount;
    int  countall;
    int	 sondeep;					//�������ӽ��ʱ���浱ǰ���
public:
    btree(node *initrootp);
    btree()
    {
        root=NULL;
		firstbracket=1;
		countall=0;					//�ݹ麯���ڲ�ͳ�ƽ�����
		btreecount=0;               //������ͳ�ƺ�Ľ�����
    };
    ~btree() {};
    void initfirstbracket();		//�ѵ�һ�����ű�־λ�ָ���1
    returninfo createbtree(int choice); //���ݹ�����ַ������ɶ�������choice=1ΪĬ�����ݣ�2Ϊ��������
    returninfo createroot();		//������������
    void visit(node *searchp);      //���ʵ�ǰ���������
    void showbtreedata();			//������������ʾ��ǰ��������
    int  rgetcount(node *searchp);  //�ݹ�ͳ�ƶ������еĽ�����
    int  getcount();				//��¼�������еĽ�����
    returninfo changeworkinpp();    //������ָ��ָ������ӡ��Ҷ��ӻ��߸���
    returninfo findnode();			//���ҽ��
    returninfo addchild();          //��������ӻ����Ҷ���
    returninfo deletenode();        //ɾ�����
    returninfo getinformation();    //��ȡ����������Ҷ����Ϣ
    returninfo gliststravel(node *searchp);//�Թ����glists��ʾ�����������
    returninfo indenttravel(node *searchp);//�԰���indent��ʾ�����������
    returninfo preorder    (node *searchp);//�ݹ��ȸ�����
    returninfo inorder     (node *searchp);//�ݹ��и�����
    returninfo postorder   (node *searchp);//�ݹ�������
    returninfo nrpreorder  (node *searchp);//�ǵݹ��ȸ�����
    returninfo nrinorder   (node *searchp);//�ǵݹ��и�����
    returninfo nrpostorder (node *searchp);//�ǵݹ�������
    returninfo levelorder  (node *searchp);//��α���
};
////////////////////////////////////////////////////////////////////////////////////////ok
btree::btree(node *initrootp)
{
    root=initrootp;
    workinp=NULL;
}
void btree::initfirstbracket()//�ع�Ϊ��һ������Ϊ��
{
    firstbracket=1;
}
returninfo btree::createbtree(int choice)  //������ַ����������Ӵ洢������ 
{
    bool startbuild;//�ж��Ƿ���Կ�ʼ����������
    char charnow;
    node *newnode;
    startbuild=0;//��ʼĬ��Ϊ���ܽ���������
    if(root==NULL)
        startbuild=1;
    else
    {
        cout<<"��ȫ��ʾ�� ԭ�������Ѿ��������������Ὣ��������ȫ���ƻ�!"<<endl;
        cout<<"��ȷ�ϼ������д˲���  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
            //�˴�Ӧ�ð�ԭ�����������н��ռ��ú��������������������ͷſռ䣬��ʱû���ṩ
            startbuild=1;
        }
        else
        {
			return fail;
        }
    }
    if(startbuild==1)
    {
        if(choice==1)
        {
            cout<<endl<<"1.����1���򵥹����   2.����2�����ӹ����"<<endl;
            cin>>choice;
            if(choice==1)
                strcpy(btreedata,defaultbtree1);
            else if(choice==2)
                strcpy(btreedata,defaultbtree2);
            else
                return fail;
        }
        else
        {
            cout<<"������ʾ����������� (ע����Ӣ�����뷨)��"<<endl;
			cout<<"ע�⣺��λ������һ����ĸ!"<<endl;
            cout<<"��������a(b(c,d),d(,g)) ��"<<endl;
            cin>>btreedata;//�ַ�����
        }
        root=new node(btreedata[0],1);		//�ѵ�һ�����ݸ�����
        workinp=root;						//������ǰ����ָ��
        linkrear=root;						//��¼����β����Ϊ�ں�������½����׼��
        for(int i=1; btreedata[i]!='\0'; i++) //�ӵڶ�����������������Ϊֹ��ѭ������
        {
            charnow=btreedata[i];
            switch(charnow)
            {
            case '(':
                if(btreedata[i+1]==',')
                {
                    i=i+2; //�����������������������źͶ���
                    sondeep=workinp->deep+1;//����Ŀǰ�������
                    newnode=new node(btreedata[i],sondeep);
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
                    workinp->rchild=newnode; //�Ҷ���
                    newnode->father=workinp;
                    linkrear->next=newnode;//�Ӻ������
                    linkrear=newnode;//βָ�����
                    i++;//����һ��������һ���ַ�
                }
                else
                {
                    i++;//������һ�������ַ���
                    sondeep=workinp->deep+1;//����Ŀǰ�������
                    newnode=new node(btreedata[i],sondeep);
                    newnode->lchild=NULL;
                    newnode->rchild=NULL;
                    workinp->lchild=newnode; //�����
                    newnode->father=workinp;
                    linkrear->next=newnode;//�Ӻ������
                    linkrear=newnode;//βָ�����
                    workinp=workinp->lchild;//ָ����λ
                }
                break;
            case ',':
                i++; //������һ�������ַ���
                workinp=workinp->father;//ָ����λ
                sondeep=workinp->deep+1;//����Ŀǰ�������
                newnode=new node(btreedata[i],sondeep);
                newnode->lchild=NULL;
                newnode->rchild=NULL;
                workinp->rchild=newnode; //�Ҷ���
                newnode->father=workinp;
                linkrear->next=newnode;//�Ӻ������
                linkrear=newnode;//βָ�����
                workinp=workinp->rchild;//ָ����λ
                break;
            case ')':
                workinp=workinp->father;
                break;
            default:
                return fail;
                break;
            }
			linkrear->next=NULL;//ȷ�����������һ����������Ϊ��
        }
    }
    return success;
}
returninfo btree::createroot() //��������
{
    bool startinput;//�ж��Ƿ���Կ�ʼ��������
    char newrootdata;
    startinput=0;//��ʼĬ��Ϊ������������
    if(root==NULL)
        startinput=1;
    else
    {
        cout<<"��ȫ��ʾ�� ԭ�������Ѿ��������������Ὣ��������ȫ���ƻ�!"<<endl;
        cout<<"��ȷ�ϼ������д˲���  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
            //�˴�ԭ���������н��ռ��ú���������ͷſռ�û���ṩ
            startinput=1;
        }
        else
        {
            return fail;
        }
    }
    if(startinput==1)
    {
        cout<<"�������������������ݣ�";
        cin>>newrootdata;
        root=new node(newrootdata,1);	//�����������������ݲ��������Ϊ1
		root->lchild=NULL;				//����������ÿ�
        root->rchild=NULL;				//�Ҷ��������ÿ�
        root->father=NULL;				//���������ÿ�
        root->next  =NULL;				//��������һ����������ÿ�
        workinp=root;					//���ù���ָ��Ϊ��ǰ�����
        linkrear=root;					//��¼����β����Ϊ�ں�������½����׼��
        return success;
    }
    return success;
}
void btree::visit(node *searchp)		//��ʾ�������������
{
    cout<<setw(2)<<searchp->data;		//��ʾ��ȣ������Ҫ���޸�
}
void btree::showbtreedata()
{
    cout<<btreedata;
}
int btree::rgetcount(node *searchp)      //ͳ�ƶ������н�����
{
	if(searchp!=NULL)
    {
        countall++;						//countall���ڵݹ麯���ڲ���¼Ԫ�ظ���
        rgetcount(searchp->lchild);
        rgetcount(searchp->rchild);
    }
	return countall;
}
int btree::getcount()    //��¼�������еĽ�����
{
    countall=0;							//�ݹ麯����������������
	btreecount=rgetcount(root);			//btreecount������¼��ǰ������������Ԫ�ظ���
    return btreecount;
}
returninfo btree::changeworkinpp()//ת�ƹ���ָ��
{
    char subchoice;		//�Ӳ˵�ѡ�����
    if(root==NULL)
        return underflow;
    else
    {
        initfirstbracket();
		indenttravel(root);//����ʽ��ʾ������
        cout<<endl;
        cout<<"1.������ǰ����ָ����������"<<endl;
        cout<<"2.������ǰ����ָ������Ҷ���"<<endl;
        cout<<"3.�����������ĸ�              "<<endl;
        cout<<"4.������ǰ����ָ����ĸ���  "<<endl;
        cout<<"5.�����ƶ�����ָ�����        "<<endl;
        cout<<"��ѡ��";
        cin>>subchoice;
        switch(subchoice)
        {
        case '1' :        //���������
            if(workinp->lchild==NULL)
                return nolchild;
            else
                workinp=workinp->lchild;
            break;
        case '2' :       //�����Ҷ���
            if(workinp->rchild==NULL)
                return norchild;
            else
                workinp=workinp->rchild;
            break;
        case '3' :       //��������
            workinp=root;
            break;
        case '4' :       //��������
            if(workinp->father==NULL)
                return nofather;
            else
                workinp=workinp->father;
            break;
        case '5' :
            return quit;
            break;
        default:
            return fail;
            break;
        }
    }
    initfirstbracket();
	indenttravel(root);//����ʽ��ʾ������
    cout<<endl;
    return success;
}
returninfo btree::findnode() //���������㣬���õ��������
{
    node *searchp;
    char finddata,newdata;//��Ҫ���ҵ����ݡ��޸Ľ����Ҫ��������
    int flag=0;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    cout<<"��������Ҫ���ҵĽ�����ݣ�";//���ҽ��
    cin>>finddata;
    while(searchp!=NULL)//���ж����ͬ����ʱ��������ѯ���Ƿ�Ϊ��������
    {
        if(searchp->data==finddata)//�ж��Ƿ�͵�ǰָ���Ӧ������ͬ
        {
            cout<<endl<<"�ý�������Ϊ��";
            visit(searchp);
            if(searchp->lchild!=NULL)
            {
                cout<<endl<<"�ý�������Ϊ��";
                visit(searchp->lchild);
            }
            else
                cout<<endl<<"�ý���������!";
            if(searchp->rchild!=NULL)
            {
                cout<<endl<<"�ý���Ҷ���Ϊ��";
                visit(searchp->rchild);
            }
            else
                cout<<endl<<"�ý�����Ҷ���!"<<endl;
            cout<<endl<<"�ý�������Ƿ�Ϊ��Ҫ�ҵģ�(Y����y):";
            cin>>answer;
            if(answer=='Y'||answer=='y')
            {
                workinp=searchp;
                flag=1;
                break;
            }
            else
                cout<<endl<<"������Ҫ���ҵģ���������..."<<endl;
        }
        searchp=searchp->next;
    }
    if(flag==1)
    {
        cout<<endl<<"���ҵ��������Ϊ��";
        visit(searchp); 
		cout<<endl;
        cout<<endl<<"����Ҫ�޸ĸ�������(Y����y)";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
			cout<<"��������Ҫ�޸ĺ�������ݣ�";//����޸�
			cin>>newdata;
			searchp->data=newdata;
            cout<<"�޸ĳɹ�!";
		}
		else
			cout<<"�����޸�!";
        cout<<endl;
        cout<<"��ǰ����ָ���Ѿ�ָ�򱾴β��ҽ�����!"<<endl;
        return success;
    }
    else
        cout<<endl<<"Ҫ���ҵĽ������ "<<finddata<<" �����ڣ�"<<endl;
    return success;
}
returninfo btree::addchild()//���Ӷ���
{
    char  subchoice;
    char sondata;
    node *newnode;
    if(root==NULL)
        return underflow;
    else if(workinp->lchild!=NULL && workinp->rchild!=NULL  )
        return havetwosons;
	else
    {
        indenttravel(root);//����ʽ��ʾ������
        cout<<"1.���������"<<endl;
        cout<<"2.�����Ҷ���"<<endl;
        cout<<"3.�������β���"<<endl;
        cout<<"��ѡ��";
        cin>>subchoice;
        switch(subchoice)
        {
        case '1'://���������
            if(workinp->lchild!=NULL)
                return havesonl;
            else
            {
                cout<<"����������ӵ����ݣ�";
                cin>>sondata;
                sondeep=workinp->deep+1;//����Ŀǰ�������
                newnode=new node(sondata,sondeep);
                newnode->lchild=NULL;
                newnode->rchild=NULL;
                workinp->lchild=newnode;
                newnode->father=workinp;
                linkrear->next=newnode;//�Ӻ������
                linkrear=newnode;//βָ�����
            }
            break;
        case '2'://�����Ҷ���
            if(workinp->rchild!=NULL)
                return havesonr;
            else
            {
                cout<<"�������Ҷ��ӵ����ݣ�";
                cin>>sondata;
                sondeep=workinp->deep+1;//����Ŀǰ�������
                newnode=new node(sondata,sondeep);
                newnode->lchild=NULL;
                newnode->rchild=NULL;
                workinp->rchild=newnode;
                newnode->father=workinp;
                linkrear->next=newnode;//�Ӻ������
                linkrear=newnode;//βָ�����
            }
            break;
        case 3 :
            return quit;
            break;
        default:
            return fail;
            break;
        }
    }
    indenttravel(root);//����ʽ��ʾ������
    return success;
}

returninfo btree::deletenode()      //ɾ����㣬�漰���˵�����
{
    node *searchp,*followp,*usednode;
    if(root==NULL)
        return underflow;
    else if(workinp->lchild!=NULL || workinp->rchild!=NULL  )
        return haveason;
    cout<<"����ָ��ָ���������Ҷ�ӽ�㣺 "<<workinp->data<<"  ����ɾ������ȷ�ϣ�Y/y����";
    cin>>answer;
    if(answer!='Y' && answer!='y')
        return quit;
    usednode=workinp;				//��usednode����ɾ���
	if(usednode==root)				//����һ������ʱ
	{	
		delete usednode;			//�ͷſռ�
		root=NULL;					//�ָ���ָ��Ϊ��
		firstbracket=1;
		countall=0;					//�ݹ麯���ڲ�ͳ�ƽ�����
		btreecount=0;               //������ͳ�ƺ�Ľ�����
		return success;
	}
	else
	{
		workinp=workinp->father;	//����ָ��workinp�ع��丸�׽��
 		if(workinp->rchild==usednode)
			workinp->rchild=NULL;
		if(workinp->lchild==usednode)
			workinp->lchild=NULL;
    }
	searchp=root->next;				//��������ָ���ڵ�������Ѱ�ұ�ɾ��㣬����һ���������Ѿ�����
    followp=root;					//����β��ָ��������
	while (searchp!=usednode)
    {
        followp=searchp;			//β��ָ�����
        searchp=searchp->next;		//����ָ��ǰ��
    }
	if(usednode->next=NULL)			//��ɾ���Ϊ���һ�����
		followp->next=NULL;
	else
		followp->next=usednode->next;//��������ʱsearchp=usednode��������ָ��ɾ���
    delete usednode;//�ͷſռ�
    return success;
}
returninfo btree::getinformation()  //��ȡ����������Ҷ����Ϣ
{
    int countnow,btreedeep;
	node *searchp;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    gliststravel(root);//�������ʾ������
    cout<<endl;
    initfirstbracket();
    countnow=getcount();
    cout<<"������Ϊ��"<<countnow<<endl;
    btreedeep=0;
	searchp=root;
	while(searchp!=NULL)//�˴�ʹ���˵�����
    {
        btreedeep=(searchp->deep > btreedeep) ? searchp->deep : btreedeep;
        searchp=searchp->next;
    }
    cout<<"���Ϊ��    "<<btreedeep;
    
	if(root->next==NULL)
		cout<<endl<<"��������ֻ��һ�����,��: "<<root->data<<endl;
	else
	{
		cout<<endl<<"���з�Ҷ�ӽ��Ϊ��";
		searchp=root;
		while(searchp!=NULL)//�˴�ʹ���˵�����
		{
			if(searchp->lchild!=NULL || searchp->rchild!=NULL)
				visit(searchp);
			searchp=searchp->next;
		}
		cout<<endl;


		searchp=root;
		cout<<"����Ҷ�ӽ��Ϊ��  ";
		while(searchp!=NULL)//�˴�ʹ���˵�����
		{
			if(searchp->lchild==NULL && searchp->rchild==NULL)
				visit(searchp);
			searchp=searchp->next;
		}
		cout<<endl;
    }
	
	cout<<"================"<<endl;
    cout<<"�������ڽ����������н������Ϊ��";
    searchp=root;
    while(searchp!=NULL)//�˴�ʹ���˵�����
    {
        cout<<searchp->data<<"("<<searchp->deep<<")  ";
        searchp=searchp->next;
    }
    cout<<endl;
	return success;
}
returninfo btree::gliststravel(node *searchp)    //�Թ�����ʾ��������������ݹ飬�����ȸ�����
{
    if(firstbracket==1)
    {
        searchp=root;
        cout<<"�Թ�����ʾ����������������";
    }
    if(searchp!=NULL)
    {
		firstbracket=0;    
		cout<<searchp->data;
        if(searchp->lchild!=NULL||searchp->rchild!=NULL)
        {
            cout<<"(";
            gliststravel(searchp->lchild);//�ݹ鴦��������
            if(searchp->rchild!=NULL)
                cout<<",";
            gliststravel(searchp->rchild);//�ݹ鴦��������
            cout<<")";
        }
    }
    return success;
}

returninfo btree::indenttravel(node *searchp)  //������ʽ��ʽ������������ݹ��㷨
{
    if(firstbracket==1)
    {
        searchp=root;
        cout<<endl<<endl<<"������ʽ��ʽ��������������"<<endl<<endl;

    }
    if(searchp!=NULL)
    {
        {
            firstbracket=0; 
			cout<<setw(searchp->deep*3)<<" "<<searchp->deep<<"�ѩ�>";//�������ʾ������
            visit(searchp);
            if(searchp==workinp)
                cout<<"  <==�Ѵ˽��Ϊ��ǰ����ָ��λ��!";
            cout<<endl;
            indenttravel(searchp->lchild);
            if(searchp->lchild==NULL)
                cout<<setw(searchp->deep*3+3)<<" "<<searchp->deep+1<<"�ѩ�>����ӿ� "<<endl;
            indenttravel(searchp->rchild);
            if(searchp->rchild==NULL)
                cout<<setw(searchp->deep*3+3)<<" "<<searchp->deep+1<<"�ѩ�>�Ҷ��ӿ� "<<endl;
        }
    }
    return success;
}
///���ֵݹ�����������ȸ����и��ͺ��
returninfo btree::preorder(node *searchp)	//�ȸ��ݹ����
{
    		
	if(firstbracket==1)						//������ʾ��һ������
    {
        searchp=root;
        if(searchp==NULL)
            return underflow;
		firstbracket=0;						//�˺󶼲��ǵ�һ��������		
		countnow=getcount();				//��������ʹ�ý�����
        cout<<"�ݹ��ȸ���������� (";
    }
    if(searchp!=NULL)
    {

		visit(searchp);
		countnow--;
        
        if(countnow!=0)
            cout<<",";
        else
            cout<<")"<<endl;
        preorder(searchp->lchild);
        preorder(searchp->rchild);
    }
    return success;
}
returninfo btree::inorder(node *searchp)	//�и��ݹ����
{
    if(firstbracket==1)
    {
        searchp=root;
        if(searchp==NULL)
            return underflow;
        firstbracket=0;		
		countnow=getcount();				
        cout<<"�ݹ��и���������� (";
	}
    if(searchp!=NULL)
    {

		inorder(searchp->lchild);
        visit(searchp);
		countnow --;
		if(countnow!=0)
            cout<<",";
        else cout<<")"<<endl;
        inorder(searchp->rchild);
    }
    return success;
}
returninfo btree::postorder(node *searchp)	//����ݹ����
{
    if(firstbracket==1)
    {
        searchp=root;
        if(searchp==NULL)
            return underflow;
        firstbracket=0;		
		countnow=getcount();				
        cout<<"�ݹ������������ (";
	}
    if(searchp!=NULL)
    {

		postorder(searchp->lchild);
        postorder(searchp->rchild);
        visit(searchp);
        countnow --;
        if(countnow!=0)
            cout<<",";
        else cout<<")"<<endl;
    }
    return success;
}
//���ַǵݹ�����������ȸ����и��ͺ��
returninfo btree::nrpreorder(node *searchp)//�ǵݹ��ȸ�����
{
    node *stack[Maxsize],*pnow;		//����ջ��pnowָ�������ĳ�����ĵ�ַ
    int top;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    top=0;							//0�ŵ�ַ���ô����һ������
    pnow=searchp;
    cout<<"�ǵݹ��ȸ����������(";
	countnow=getcount();			
    while(!(pnow==NULL&&top==0))
    {
        while(pnow!=NULL)
        {
            visit(pnow);
			countnow--;
            if(countnow!=0)
                cout<<",";
            else
                cout<<")";
            if(top<Maxsize-1)//�򵥴�����һ��ջ���������
            {
                stack[top]=pnow;
                top++;
            }
            else
            {
                return overflow;
            }
            pnow=pnow->lchild;
        }
        if(top<=0) return success;
        else
        {
            top--;
            pnow=stack[top];
            pnow=pnow->rchild;
        }
    }
    cout<<endl;
    return success;
}
returninfo btree::nrinorder(node *searchp)//�ǵݹ��и�����
{
    node *stack[Maxsize],*pnow;
    int top;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    top=0;
    pnow=searchp;
    cout<<"�ǵݹ��и����������(";
	countnow=getcount();			
    while(!(pnow==NULL && top==0))
    {
        while(pnow!=NULL)
        {
            if(top<Maxsize-1)
            {
                stack[top]=pnow;
                top++;
            }
            else
            {
                return overflow;
            }
            pnow=pnow->lchild;
        }
        if(top<=0) return success;
        else
        {
            top--;
            pnow=stack[top];
            visit(pnow);
			countnow --;
			if(countnow!=0)
                cout<<",";
            else cout<<")";
			pnow=pnow->rchild;
        }
    }
    cout<<endl;
    return success;
}
returninfo btree::nrpostorder(node *searchp)//�ǵݹ�������
{
    stackdata stack[Maxsize];//�˴���ջ���ǽ�����ָ��һ����Ϣ�����Ƕ����Ϣ
    node *pnow;
    int top,sign;
    searchp=root;
    if(searchp==NULL)
        return underflow;
    top=-1;
    pnow=searchp;
    cout<<"�ǵݹ������������(";
	countnow=getcount();	
    while(!(pnow==NULL&&top==-1))
    {
        if(pnow!=NULL)
        {
            if(top<Maxsize-1)
            {
                top++;
                stack[top].link=pnow;
                stack[top].flag=1;
                pnow=pnow->lchild;
            }
            else
                return overflow;
        }
        else
        {
            pnow=stack[top].link;
            sign=stack[top].flag;
            top--;
            if(sign==1)
            {
                top++;
                stack[top].link=pnow;
                stack[top].flag=2;
                pnow=pnow->rchild;
            }
            else
            {
                countnow --;
                visit(pnow);
                if(countnow!=0)
                    cout<<",";
                else
                    cout<<")";
                pnow=NULL;
            }
        }
    }
    cout<<endl;
    return success;
}
returninfo btree::levelorder(node *searchp)//��α���
{
	node *queue[Maxsize];				//ע�⣺�����в���û�п��Ǽ��������
	int front,rear;						//��ͷ�Ͷ�β
    searchp=root;						//����ն�����
    if(searchp==NULL)
        return underflow;
	countnow=getcount();				//��������ʹ�ý�����
	front=-1;							//����ָ���ʼ��
    rear=0;
    queue[rear]=searchp;				//�Ѹ�������
	cout<<"��α�������� (";
    while(front!=rear)
    {
        front++;
        visit(queue[front]);			//���ʶ���Ԫ�ص�����
        countnow--;						//���δ������һ���Ѿ������ʵ�����
    	if(countnow!=0)					//����û�����������
            cout<<",";
        else
            cout<<")";					//���ݽ���ʱ���������
        if(queue[front]->lchild!=NULL)	//����ͷ���ݵ���������
        {
            rear++;
            queue[rear]=queue[front]->lchild;
        }
        if(queue[front]->rchild!=NULL)	//����ͷ���ݵ��Ҷ������
        {
            rear++;
            queue[rear]=queue[front]->rchild;
        }
    }
    cout<<endl;
    return success;
}
//���洦����󣺽����
class interfacebase
{
private:
    btree btreenow;			//���ݽṹ�����ʵ����
public:
    void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"   ����������洢������ʾ  ���ߣ�heqinghqocsh         "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.��һ�����뷨��Ĭ�Ϲ����		 "<<endl;
    cout<<"2.�ڶ������뷨��������������    "<<endl;
    cout<<"3.���������뷨���½�����(�������)"<<endl;
    cout<<"4.���Ӷ�������                    "<<endl;
    cout<<"5.ɾ��Ҷ�ӽ��������			 "<<endl;
    cout<<"6.�ƶ���ǰ����ָ��				 "<<endl;
	cout<<"7.���ҽ�㲢�޸Ľ����Ϣ		     "<<endl;
    cout<<"8.�ù���������ͬʱ��ʾ������  "<<endl;
    cout<<"9.���ֵݹ��ʽ����				 "<<endl;
    cout<<"a.���ַǵݹ��ʽ����			     "<<endl;
    cout<<"s.��α���						 "<<endl;
    cout<<"d.�鿴������Լ�Ҷ����Ϣ		     "<<endl;
    cout<<"0.�˳�							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
    char choice;				//�����û�ѡ��˵�ѡ��
    int  returnvalue;			//������Ϣ����
    int  countnow;				//Ŀǰ��ʵ�ʽ����
    node *rootnow=NULL;			//ָ�������Ϊ����ͱ���
    cout<<"������ѡ�";
    cin>>choice;
    switch(choice)
    {
    case '1'://1.����Ĭ������(�����ʽ)
        cout<<"================"<<endl;
        returnvalue=btreenow.createbtree(1);
		if(returnvalue==fail)
            cout<<"�Ѿ�ȡ������������!"<<endl;
		else
		if(returnvalue==success)
		{
			cout<<"��ǰ�����Ϊ: "<<endl;
			btreenow.showbtreedata();
			cout<<endl<<"�����������ɹ�!"<<endl;
        }
		cout<<"================"<<endl;
        break;
    case '2'://2.���ü�������(�����ʽ)
        cout<<"================"<<endl;
        returnvalue=btreenow.createbtree(2);//Ƕ������ʽ���������
		if(returnvalue==fail)
            cout<<"�Ѿ�ȡ������������!"<<endl;
		else
		if(returnvalue==success)
			cout<<"�����������ɹ�!"<<endl;
        cout<<"================"<<endl;
        break;
    case '3'://3.�½�����(����������������)
        cout<<"================"<<endl;
        returnvalue=btreenow.createroot();//��������
        if(returnvalue==fail)
            cout<<"�Ѿ�ȡ��������!"<<endl;
		else
		if(returnvalue==success)
			cout<<"���������ɹ�!"<<endl;
        cout<<"================"<<endl;
        break;
    case '4'://4.���Ӷ�������
        cout<<"================"<<endl;
        returnvalue=btreenow.addchild();//���Ӷ���
        if(returnvalue==underflow)
            cout<<"ע�⣺������Ŀǰû�и�!�޷�����..."<<endl;
        if(returnvalue==havetwosons)
            cout<<"�Բ��𣬸ý��ͬʱ������Ӻ��Ҷ���!�������Ӷ���!"<<endl;
        if(returnvalue==havesonl)
            cout<<"�Բ��𣬸ý��������ӣ��������Ӷ���!"<<endl;
        if(returnvalue==havesonr)
            cout<<"�Բ��𣬸ý�����Ҷ��ӣ��������Ӷ���!"<<endl;
        if(returnvalue==quit)
            cout<<"�������Ӷ��Ӳ����Ѿ�����!"<<endl;
        if(returnvalue==fail)
            cout<<"�Բ��𣬷�Χ������󣬱��β���ʧ��!"<<endl;
        if(returnvalue==success)
            cout<<"���Ӷ��ӳɹ�!"<<endl;
        cout<<"================"<<endl;
        break;
    case '5'://5.ɾ�����ݽ��
        cout<<"================"<<endl;
        cout<<"��ʾ������ɾ��Ҷ�ӽ�㣬�����һ�����������"<<endl;
        cout<<"Ҷ�ӽ��ɾ���ɹ���ǰ����ָ��ָ���丸�׽��!"<<endl;
		cout<<"����һ����ɾ���ɹ���ǰ����ָ��ָ���!"<<endl;
        returnvalue=btreenow.deletenode();//ɾ�����
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;
        if(returnvalue==haveason)
        {
            cout<<"�Բ��𣬵�ǰ����ָ����ָ���������һ�����ӣ��޷�ɾ��"<<endl;
            cout<<"����6�Ź����ƶ���ǰ����ָ���7�Ź���ȥ����ĳ��Ҷ�ӽ��!"<<endl;
        }
        if(returnvalue==quit)
            cout<<"��ʾ��ɾ���������Ѿ�����!"<<endl;
        if(returnvalue==success)
            cout<<"ɾ���������ɹ�!"<<endl;
        cout<<"================"<<endl;
        break;
    case '6'://6.�ı䵱ǰ����ָ��
        cout<<"================"<<endl;
        returnvalue=btreenow.changeworkinpp();//�ı乤��ָ��
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;
        if(returnvalue==nolchild)
            cout<<"�Բ��𣬸ý��û������ӣ����ܽ����ƶ�����!"<<endl;
        if(returnvalue==norchild)
            cout<<"�Բ��𣬸ý��û���Ҷ��ӣ����ܽ����ƶ�����!"<<endl;
        if(returnvalue==nofather)
            cout<<"�Բ��𣬸ý��û�и��ף����ܽ����ƶ�����!"<<endl;
        if(returnvalue==quit)
            cout<<"�����ƶ������Ѿ�����!"<<endl;
        if(returnvalue==fail)
            cout<<"�Բ��𣬷�Χ������󣬱��β���ʧ��!"<<endl;
        if(returnvalue==success)
            cout<<"��ǰ����ָ��ָ���ƶ��ɹ�!"<<endl;
        cout<<"================"<<endl;
        break;
	case '7'://12.���ҽ��
        cout<<"================"<<endl;
        returnvalue=btreenow.findnode();
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;
        else
            cout<<"���Ҳ������!..."<<endl;
        cout<<"================"<<endl;
        break;
    case '8'://7.��ʾ������(����������)
        cout<<"================"<<endl;
        countnow=btreenow.getcount();    //ͳ��Ŀǰ�Ľ�����
        if(countnow==0)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;
        else
        {
            btreenow.initfirstbracket();
			btreenow.gliststravel(rootnow);//�������ʾ������
            btreenow.initfirstbracket();
            btreenow.indenttravel(rootnow);//����ʽ��ʾ������
        }
        cout<<"================"<<endl;
        break;
    case '9'://8.���ֵݹ��ʽ����
        cout<<"================"<<endl;
        btreenow.initfirstbracket();   //�ع�Ϊ��һ������Ϊ��1
		returnvalue=btreenow.preorder(rootnow);  //�ݹ��ȸ�����
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;//ͬ���Ĵ���ֻ��ʾһ�Σ�Ϊ��࣬�ɹ�������ʾ
        btreenow.initfirstbracket();   
        returnvalue=btreenow.inorder(rootnow);	//�ݹ��и�����
        btreenow.initfirstbracket();
        returnvalue=btreenow.postorder(rootnow);//�ݹ�������
        cout<<"================"<<endl;
        break;
    case 'a'://9.���ַǵݹ��ʽ����
        cout<<"================"<<endl;
        returnvalue=btreenow.nrpreorder(rootnow);  //�ǵݹ��ȸ�����
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;//ͬ���Ĵ���ֻ��ʾһ�Σ�Ϊ��࣬�ɹ�������ʾ
        if(returnvalue==overflow)
            cout<<"ע�⣺ջ�ռ䲻��!�޷�����..."<<endl;
        returnvalue=btreenow.nrinorder(rootnow);	//�ǵݹ��и�����
        if(returnvalue==overflow)
            cout<<"ע�⣺ջ�ռ䲻��!�޷�����..."<<endl;
        returnvalue=btreenow.nrpostorder(rootnow);	//�ǵݹ�������
        if(returnvalue==overflow)
            cout<<"ע�⣺ջ�ռ䲻��!�޷�����..."<<endl;
        cout<<"================"<<endl;
        break;
    case 's'://10.��α���
        cout<<"================"<<endl;
        returnvalue=btreenow.levelorder(rootnow);//��α���
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;
        else
            cout<<"��α��������ɹ�!..."<<endl;
        cout<<"================"<<endl;
        break;
    case 'd'://11.�鿴������Լ�Ҷ����Ϣ
        cout<<"================"<<endl;
        returnvalue=btreenow.getinformation();
        if(returnvalue==underflow)
            cout<<"ע�⣺������ĿǰΪ��!�޷�����..."<<endl;
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
    while (1)
    {
        interfacenow.showmenu();
        interfacenow.processmenu();
        system("pause");
        system("cls");
    }
    return 0;
}//����������

