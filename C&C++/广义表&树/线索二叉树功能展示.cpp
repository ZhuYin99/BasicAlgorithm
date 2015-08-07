//�����������Ĺ���չʾ
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<sstream>							//�ṩstringstream�Ĺ���
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };					//���巵����Ϣ�嵥
#define Maxsize 100									//����ĳ���
char defaultbtree[]="ab#d##ce#f###";				//Ĭ���ȸ���������������
bool startbuild;									//����Ƿ����½���������Ϊ0ʱ���½���Ϊ1���Ѿ�����
class threadnode
{
public:
    char data;
    int ltag,rtag;
    threadnode *lchild, *rchild;
    threadnode(const char item):data(item),lchild(NULL),rchild(NULL),
        ltag(0),rtag(0) {}
};
class threadtree
{
private:
    char btreedata[Maxsize];						//�洢�ȸ�������Լ�����ַ�����ʽ���ڹ���������
    char answer;
    stringstream buff;								//���������ַ���
protected:
    threadnode *root;
    void creatbtree(threadnode *&nodenow);			//�ݹ齨��������	
    void buildinorderthread(threadnode *current,threadnode *&pre);//�����и�����
    threadnode *parent(threadnode *nodenow);		//���Ҹ��׽��
public:
    threadtree() {};
    ~threadtree() {};
    returninfo inputbtree(int choice);				//�������ݣ����� 1��Ĭ�� 2����������
    void showbtreedata();							//������������ʾ��ǰ��������
    threadnode *first(threadnode *current);			//���и������µĵ�һ��
    threadnode *last(threadnode  *current);			//���и������µ����һ��
	threadnode *prior(threadnode *current);			//���и������µ���һ��
    threadnode *next(threadnode  *current);			//���и������µ���һ��
    returninfo  buildinorderthread();				//�����и����������������
    void preorder(void (*visit)(threadnode *searchp));  //�����������µ��ȸ�����
    void inorder (void  (*visit)(threadnode *searchp)); //�����������µ��и�����
    void postorder(void (*visit)(threadnode *searchp)); //�����������µĺ������
};
returninfo threadtree::inputbtree(int choice)  //������ַ����������Ӵ洢������
{
	if(startbuild==0)
        startbuild=1;
    else
    {
		cout<<"��ȫ��ʾ�� ԭ�������Ѿ��������������Ὣ��������ȫ���ƻ�!"<<endl;
        cout<<"��ȷ�ϼ������д˲���  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
            //�˴�Ӧ�ð�ԭ�����������н��ռ��ͷſռ䣬�˴�û�д���
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
            strcpy(btreedata,defaultbtree);
        }
        else
        {
            cout<<"�����ü����������������������ַ�����ʽ (ע����Ӣ�����뷨)��"<<endl;
            cout<<"������abc##de#g##f###"<<endl;
            cout<<"������Ϸ��Ķ���������������ַ�����ʽ��"<<endl;
            cin>>btreedata;//�ַ�����
        }
    }
    buff << btreedata;					//�����ַ�����
    creatbtree(root);					//����������
	return success;
}
//��ʾ�ַ�����
void threadtree::showbtreedata()
{
    cout<<btreedata<<endl;
}
//������*currentΪ�����и��������������и������µĵ�һ�����
threadnode *threadtree::first(threadnode  *current)
{
    threadnode *searchp = current;
    while(searchp->ltag == 0)
        searchp = searchp->lchild;  //�����½�㣨��һ����Ҷ��㣩
    return searchp;
}
//������*currentΪ�����и��������������и������µ����һ�����
threadnode *threadtree::last(threadnode *current)
{
    threadnode *searchp = current;
    while(searchp->rtag == 0)
        searchp = searchp->rchild;  //�����½�㣨��һ����Ҷ��㣩
    return searchp;
}
//�������и������������н��current���и��µ��������
threadnode *threadtree::prior(threadnode *current)
{
    threadnode *searchp = current->lchild;
    if(current->ltag == 0)
        return last(searchp);
    else
        return searchp;
}
//�������и������������н��current���и��µĺ�̽��
threadnode *threadtree::next(threadnode *current)
{
    threadnode *searchp = current->rchild;
    if(current->rtag == 0)
        return first(searchp);	//�������������и��µ�һ�����
    else
        return searchp;			// rtag=1��searchpָ����������ĺ�̽�㣬ֱ�ӷ���
}

//�����и������Զ����������и�������
returninfo threadtree::buildinorderthread()
{
    threadnode *pre = NULL;
    if(root!=NULL)
    {
        buildinorderthread(root,pre);
        pre->rchild= NULL;
        pre->rtag = 1;
    }
    return success;
}
//���и��������������󸸽��
threadnode *threadtree::parent(threadnode *nodenow)
{
    threadnode* searchp;
    if(nodenow == root) 
		return NULL;
    for(searchp = nodenow; searchp->ltag==0; searchp = searchp->lchild);
    if(searchp->lchild!=NULL)
    {
        for(searchp = searchp->lchild; searchp->lchild!=nodenow && searchp->rchild!=nodenow; 
		searchp=searchp->rchild);
    }
    else
    {
        for(searchp = nodenow; searchp->rtag==0; searchp=searchp->rchild);
        for(searchp=searchp->rchild; searchp->lchild!=nodenow && searchp->rchild!=nodenow; 
		searchp=searchp->lchild);
    }
    return searchp;
}
//ͨ���ȸ��ݹ����������������
void threadtree::creatbtree(threadnode *&nodenow)
{
    char charnow;							//���嵱ǰ�ַ�
    if(buff>>charnow)						//���뵱ǰ�ַ�
    {
        if(charnow!='#')					//������ǿն��ӷ��ţ���ʼ�������
        {
            nodenow=new threadnode(charnow);//����ռ�
            nodenow->data=charnow;			//�ַ�������������
            creatbtree(nodenow->lchild);	//�ݹ齨����������
            creatbtree(nodenow->rchild);	//�ݹ齨����������
        }
        else
            nodenow = NULL;
    }
}
//ͨ���и��ݹ�������Զ���������������
void threadtree::buildinorderthread(threadnode *current,threadnode *&pre)
{
    if(current == NULL) return;
    buildinorderthread(current->lchild,pre);				//�ݹ����������
    if(current->lchild == NULL)								//û���������ʼ��������
    {
        current->lchild = pre;
        current->ltag = 1;
    }
    if(pre!=NULL && pre->rchild == NULL)					//û���Ҷ�����ʼ��������
    {
        pre->rchild = current;
        pre->rtag = 1;
    }
    pre = current;
    buildinorderthread(current->rchild,pre);				//�ݹ����������
}
//��ʾ��ǰ������ݣ����������ڶ����У�Ϊ����ĺ�����Ϊ����ʹ��
void print(threadnode* nodenow)
{
    cout << nodenow->data<<"  ";
}
//���и�������������ʵ���ȸ�����
void threadtree::preorder(void(*visit)(threadnode *searchp))
{
    threadnode *searchp=root;
    while(searchp!= NULL)
    {
        visit(searchp);									//���ʸ����
        if(searchp->ltag == 0)							//������Ů����Ϊ���
            searchp = searchp->lchild;
        else if(searchp->rtag == 0)						//������Ů����Ϊ���
            searchp = searchp ->rchild;
        else
        {
            while (searchp!=NULL && searchp->rtag == 1)	// �غ���������
                searchp = searchp->rchild;			// ֱ��������Ů�Ľ��
            if (searchp!=NULL)							//��ʱ����rtag=0
                searchp = searchp->rchild;			//����Ů��Ϊ���
        }
    }
}
//���и�������������ʵ���и�����
void threadtree::inorder(void(*visit)(threadnode *searchp))
{
    threadnode *searchp;
    for(searchp = first(root); searchp != NULL; searchp = next(searchp))
        visit(searchp);									//����������Ϊ�и��������и������ͺܼ�
}
//���и�������������ʵ�ֺ��������
void threadtree::postorder(void(*visit)(threadnode *searchp))
{
    threadnode *workingp,*searchp;						
    workingp = root;									//���ù���ָ��workingp���Ӹ���㿪ʼ
	while(workingp->ltag == 0 || workingp ->rtag ==0)	//�����Ҷ���ʱ�������ӽ�����ƶ�
    {
        if(workingp->ltag == 0) 
			workingp = workingp->lchild;
        else 
		if(workingp->rtag == 0) 
			workingp = workingp->rchild;
    }
    visit(workingp);									//���ʵ�ǰ����ָ����ָ���
	while((searchp=parent(workingp)) != NULL)			//��������ָ��searchpÿ�δӹ���ָ�븸��㿪ʼ			
    {
        if(searchp->rchild == workingp || searchp->rtag == 1)
            workingp = searchp;
        else
        {
            workingp = searchp->rchild;
            while(workingp->ltag == 0 || workingp->rtag == 0)
            {
                if(workingp->ltag ==0) workingp = workingp->lchild;
                else if(workingp->rtag ==0) workingp = workingp->rchild;
            }
        }
        visit(workingp);								//���ʵ�ǰ����ָ����ָ���
    }
}
//���洦����󣺽����
class interfacebase
{
private:
    threadtree threadtreenow;			//���ݽṹ�����ʵ����
public:
    void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"        ����������������ʾ   heqinghqocsh       "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.��һ�����뷨��Ĭ���ȸ��ַ���    "<<endl;
    cout<<"2.�ڶ������뷨�������ȸ��ַ���    "<<endl;
    cout<<"3.�и����������������ֱ���        "<<endl;
    cout<<"0.�˳�							 "<<endl;
    cout<<"=================================="<<endl;
}
void interfacebase::processmenu()
{
    char choice;				//�����û�ѡ��˵�ѡ��
    int  returnvalue;			//������Ϣ����
    cout<<"������ѡ�";
    cin>>choice;
    switch(choice)
    {
    case '1'://1.����Ĭ������
        cout<<"================"<<endl;
        returnvalue=threadtreenow.inputbtree(1);
        if(returnvalue==fail)
            cout<<"�Ѿ�ȡ������������!"<<endl;
        else if(returnvalue==success)
        {
            cout<<"��ǰ����������������ַ���Ϊ: "<<endl;
            threadtreenow.showbtreedata();
            cout<<"�����������ɹ�!"<<endl;
        }
        cout<<"================"<<endl;
        break;
    case '2'://2.���ü�������
        cout<<"================"<<endl;
        returnvalue=threadtreenow.inputbtree(2);
        if(returnvalue==fail)
            cout<<"�Ѿ�ȡ������������!"<<endl;
        else if(returnvalue==success)
        {
            cout<<"��ǰ����������������ַ���Ϊ: "<<endl;
            threadtreenow.showbtreedata();
            cout<<"�����������ɹ�!"<<endl;
        }
        cout<<"================"<<endl;
        break;
     case '3'://3.���и��������������ϱ���
        cout<<"================"<<endl;
		cout<<"��ǰ����������������ַ���Ϊ: "<<endl;
		threadtreenow.showbtreedata();
        cout<<"================"<<endl;
		cout<<"��ʼ����������"<<endl;
        returnvalue=threadtreenow.buildinorderthread();
        
		if(returnvalue==fail)
            cout<<"�и�������ʧ��!"<<endl;
        else if(returnvalue==success)
		{	
            cout<<"�и��������ɹ�!"<<endl;
			cout<<"================"<<endl;
			cout<<"�ȸ����������";
			threadtreenow.preorder(print);
			cout<<endl;
			cout<<"�и����������";
			threadtreenow.inorder(print);
			cout<<endl;
			cout<<"������������";
			threadtreenow.postorder(print);
			cout<<endl;
        
		}
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
    startbuild=0;
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

