//������ʽ
#include<windows.h>
#include<iostream>
#include<iomanip>
#include<sstream>						//�ṩstringstream�Ĺ���
#include<assert.h>							
using namespace std;
enum returninfo {success,fail,overflow,underflow,nolchild,norchild,nofather,havesonl,havesonr,
                 haveason,havetwosons,range_error,quit
                };									//���巵����Ϣ�嵥
#define expmaxsize 50								//�������鳤��
char defaultexp[]="12/6*(3*2+5)";					//Ĭ�ϱ��ʽ
bool startbuild;									//��־λ���ж��Ƿ��ǵ�һ��������ʽ
//ջ����//
template<class StackItemType>
class CStack
{
   private:
	   struct StackNode
	   {
	       StackItemType item;
		   StackNode* next;
	   };
	   StackNode* topPtr;
   public:
	   CStack();
	   CStack(const CStack &aStack);
	   ~CStack();
	   bool isEmpty() const;
	   void push(StackItemType newItem);
	   bool pop();
	   bool pop(StackItemType &stackTop);
	   bool getTop(StackItemType &stackTop) const;
		                                 
};
template<class StackItemType>
CStack<StackItemType>::CStack():topPtr(NULL)
{}
template<class StackItemType>
CStack<StackItemType>::CStack(const CStack &aStack)
{
   if(aStack.topPtr==NULL)
	   topPtr=NULL;
   else
   {
       topPtr=new StackNode;
	   assert(topPtr!=NULL);
	   topPtr->item=aStack.topPtr->item;
	   StackNode* newPtr=topPtr;
	   for(StackNode* origPtr=aStack.topPtr->next;origPtr!=NULL;origPtr=origPtr->next)
	   {
	       newPtr->next=new StackNode;
		   assert(newPtr->next!=NULL);
		   newPtr=newPtr->next;
		   newPtr->item=origPtr->item;
	   }
   }
}
template<class StackItemType>
CStack<StackItemType>::~CStack()
{
   while(!isEmpty())
	   pop();
}
template<class StackItemType>
bool CStack<StackItemType>::isEmpty()const
{
   return topPtr==NULL;
}
template<class StackItemType>
void CStack<StackItemType>::push(StackItemType newItem)
{
   StackNode* newPtr=new StackNode;
   assert(newPtr!=NULL);
   newPtr->item=newItem;
   newPtr->next=topPtr;
   topPtr=newPtr;
}
template<class StackItemType>
bool CStack<StackItemType>::pop()
{
   if(!isEmpty())
   {
      StackNode* temp=topPtr;
	  topPtr=topPtr->next;
	  temp->next=NULL;
	  delete temp;
	  temp=NULL;
	  return true;
   }
   else
	  return false;
}
template<class StackItemType>
bool CStack<StackItemType>::pop(StackItemType &stackTop)
{
   if(!isEmpty())
   {
      stackTop=topPtr->item;
	  StackNode* temp=topPtr;
	  topPtr=topPtr->next;
	  temp->next=NULL;
	  delete temp;
	  temp->next=NULL;
	  return true;
   }
   else
	  return false;
}
template<class StackItemType>
bool CStack<StackItemType>::getTop(StackItemType &stackTop)const
{
   if(!isEmpty())
   {
	   stackTop=topPtr->item;
	   return true;
   }
   else
	   return false;
}
//����������//
class calculator
{
private:
    char answer;
    stringstream buff;							//���������ַ���
	char infixexp[expmaxsize];					//�洢���ʽ�ַ����и���ʽ
	char postfixexp[expmaxsize];				//�洢���ʽ�ַ��������ʽ
public:
    calculator() {};
    ~calculator() {};
	returninfo inputexp(int choice);			//������ѧ���ʽ����Ĭ�ϻ��������
	void showinfixexp();						//��ʾ��ѧ���ʽ
	void showpostfixexp();						//��ʾ��׺���ʽ
	int  precedence(char op);					//��������������ȼ�
	bool change();								//����׺���ʽת��Ϊ��׺���ʽ
	bool compute();								//�����׺���ʽpostfixexp��ֵ
};
returninfo calculator::inputexp(int choice)  //������ѧ���ʽ
{
	if(startbuild==0)
        startbuild=1;
    else
    {
		cout<<"��ȫ��ʾ�� ԭ��ѧ���ʽ�Ѿ��������������Ὣ���ƻ�!"<<endl;
        cout<<"��ȷ�ϼ������д˲���  (Y|y):";
        cin>>answer;
        if(answer=='Y'||answer=='y')
        {
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
            strcpy(infixexp,defaultexp);
        }
        else
        {
            cout<<"�����ü���������ѧ���ʽ���ַ�����ʽ (ע����Ӣ�����뷨)��"<<endl;
            cout<<"������6.3*(1.2+2.5)-9*2"<<endl;
            cout<<"ע�⣺����ʱ�ݲ�֧�ָ������磺-9/3"<<endl;
            cout<<"������Ϸ���ѧ���ʽ���ַ�����ʽ��"<<endl;
            cin>>infixexp;//�ַ�����
        }
    }
    buff << infixexp;					//�����ַ�����
	return success;
}
void calculator::showinfixexp()
{
    cout<<infixexp<<endl;
}
void calculator::showpostfixexp()
{
    cout<<postfixexp<<endl;
}
int calculator::precedence(char op)//��������������ȼ�
{
    switch(op)
	{
	   case '+':
	   case '-':
		   return 1;//�Ӽ�ͬ��Ϊ1
	   case '*':
	   case '/':
		   return 2;//�˳�ͬ��Ϊ2
	   case '@':
	   case '(':
	   default:
		   return 0;//����Ϊ0
	}
}
bool calculator::change()//����׺���ʽתΪ��׺���ʽ
{
   CStack<char> charstack;//�����ݴ��������ջ���Ա��ڰ����ȼ�������������postfixexp��
   charstack.push('@');   //����@��ջ�ף���������͵����ȼ�0
   int posi=0;               //ɨ��infixexp��ָʾpostfixexp�Ĵ����ַ���λ��
   int posj=0;
   //����ɨ��infixexp��׺���ʽ�е��ַ�
   char charnow=infixexp[posi];
   while(charnow!='\0')//���ʽû�н���ʱһֱ��
   {
       if(charnow==' ')        //���ڿո����κδ���
	       charnow=infixexp[++posi];
 	   else if(charnow=='(')   //����'('��ֱ�ӽ�ջ
	   {
		   charstack.push(charnow);
		   charnow=infixexp[++posi];
	   }
	   else if(charnow==')')   //����')'��ʹ�����ڵ���ͣ����ջ�е���������γ�ջ��д��postfixexp
	   {
           char topitem;
		   if(!charstack.pop(topitem))
		   {
			   cout<<endl<<"������������ʱջ�ѿ�!"<<endl;
			   return false;
		   }
		   while((topitem!='(')&&(topitem!='@'))
		   {
		       postfixexp[posj++]=topitem;
			   charstack.pop(topitem);
		   }
		   if(topitem=='@')
		   {
			   cout<<endl<<"���ʽ����: ���Ų�ƥ�� !"<<endl;
			   return false;
		   }
		   charnow=infixexp[++posi];
	   }
	   //���������������ʹ�ݴ���ջ���Ĳ�����charnow���ȼ����������ջ��д��postfixexp
	   else if((charnow=='+')||(charnow=='-')||(charnow=='*')||(charnow=='/'))
	   {
	       char topitem;
		   if(!charstack.getTop(topitem))
		   {
			   cout<<endl<<"����ȡ��������ʱ��ȡջ��ʱջ�ѿ�!"<<endl;
			   return false;
		   }
		   while(precedence(topitem)>=precedence(charnow))
		   {   //����precedence()��������������ȼ�
			   postfixexp[posj++]=topitem;
			   charstack.pop();
		       if(!charstack.getTop(topitem))
			   {
				   cout<<endl<<"����ȡջ��ʱջ�ѿ�!"<<endl;			   
				   return false;
			   }			   
		   }
		   charstack.push(charnow);
		   charnow=infixexp[++posi];
	   }
	   else//����ֵ��ÿһλ����postfixexp 
	   {
	       if((charnow<'0'||charnow>'9') && charnow!='.')//�������֣�Ҳ����С����
		   {
			   cout<<endl<<"���ʽ���� :���ַǷ�����������ֵķ���!"<<endl;
			   return false;
		   }
		   else
		   {
		       while((charnow>='0'&&charnow<='9')||(charnow=='.'))
			   { 
			       postfixexp[posj++]=charnow;
				   charnow=infixexp[++posi];				   
			   }
		   }
		   postfixexp[posj++]=' ';//ÿ�����ֺ���Ÿ��ո�
	   }
   }
   //infixexp�������
   //���ݴ���ջ�е������������ջ��д��postfixexp
   charstack.pop(charnow);
   while(charnow!='@')
   {
       if(charnow=='(')
	   {
		   cout<<endl<<"���ʽ����: ���Ų�ƥ�� !"<<endl;
		   return false;
	   }
	   else
	   {
	       postfixexp[posj++]=charnow;
		   charstack.pop(charnow);
	   }
   }
   postfixexp[posj++]='\0';
   return true;
}
bool calculator::compute()//�����׺���ʽpostfixexp��ֵ
{
   CStack<double> doublestack;//�ø�ջ�洢���������м���
   double partinteger,partdecimal;  //���ڱ��渡������partintegerΪ�������֣�partdecimalΪС������
   double topX,topY;          //����ÿ��������������������
   int posi=0;                   //���ڱ�����׺���ʽ
   while(postfixexp[posi])
   {
       if(postfixexp[posi]==' ')//�����ո�������
	   {
	       posi++;
		   continue;
	   }
	   switch(postfixexp[posi])
	   {
	       case '+'://��ջ������Ԫ�صļӷ����͸���partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"���ʽ���� !"<<endl;
				   return false;
			   }
			   partinteger=topX+topY;
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   case '-'://��ջ������Ԫ�صļ��������partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"���ʽ���� !"<<endl;
				   return false;
			   }
			   partinteger=topY-topX;
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   case '*'://��ջ������Ԫ�صĳ˷���������partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"���ʽ���� !"<<endl;
				   return false;
			   }
			   partinteger=topX*topY;
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   case '/'://��ջ������Ԫ�صĳ������̸���partinteger
			   if(!(doublestack.pop(topX) && doublestack.pop(topY)))
			   {
				   cout<<endl<<"���ʽ���� !"<<endl;
				   return false;
			   }
			   if(topX!=0.0)
				   partinteger=topY/topX;
			   else
			   {
			       cout<<endl<<"���ʽ���� : ����Ϊ0 !"<<endl;
				   return false;
			   }
			   posi++;
			   doublestack.push(partinteger);
			   break;
		   default:
			   //����partinteger����ɨ�赽���������ֵ�ֵ
			   partinteger=0;										//��׼Ϊ0
			   while(postfixexp[posi]>=48 && postfixexp[posi]<=57)	//�����ַ��Ƿ�Ϊ�ַ�����
			   {
			       partinteger=partinteger*10+postfixexp[posi]-48;  //�ַ�����ת�����������֣���ʵ�ֶ�λ��
				   posi++;											//ѭ���ƶ�����һ���ַ�
			   }
			   //����partdecimal����ɨ�赽��С�����ֵ�ֵ
			   if(postfixexp[posi]=='.')							//һ������С���㣬�������С������
			   {
			       partdecimal=0;									//��׼Ϊ0
				   posi++;											//С������һλ
				   double tentimes=10.0;
				   while(postfixexp[posi]>=48 && postfixexp[posi]<=57)
				   {
				       partdecimal=partdecimal+(postfixexp[posi]-48)/tentimes;
					   posi++;
					   tentimes*=10;
				   }
				   partinteger+=partdecimal;	//���������ֺ�С�����ֺ���һ��			   			   
			   }
			   doublestack.push(partinteger);
	   }
   }
   if(doublestack.isEmpty())
   {
	   cout<<endl<<"���ʽ���� !"<<endl;
	   return false;
   }
   doublestack.pop(partinteger);
   if(doublestack.isEmpty())
   {
	   cout<<endl<<"�������ǣ�"<<endl<<partinteger<<endl<<endl;
	   return true;
   }
   else
   {
	   cout<<endl<<"���ʽ���� !"<<endl;
	   return false;
   }
}
//�������
class interfacebase
{
private:
    calculator calculatornow;			//���ݽṹ�����ʵ����
public:
    void showmenu(void);
    void processmenu(void);
};
void interfacebase::showmenu(void)
{
    cout<<"        ������ʽ������ʾ        "<<endl;
    cout<<"=================================="<<endl;
    cout<<"1.����Ĭ�ϱ��ʽ                  "<<endl;
    cout<<"2.��������                        "<<endl;
    cout<<"3.������ʽ                      "<<endl;
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
        returnvalue=calculatornow.inputexp(1);
        if(returnvalue==fail)
            cout<<"�Ѿ�ȡ���������ʽ!"<<endl;
        else if(returnvalue==success)
        {
            cout<<"��ǰ���ʽ�ַ���Ϊ: "<<endl;
            calculatornow.showinfixexp();
            cout<<"���ʽ�����ɹ�!"<<endl;
        }
        cout<<"================"<<endl;
        break;
    case '2'://2.���ü�������
        cout<<"================"<<endl;
        returnvalue=calculatornow.inputexp(2);
        if(returnvalue==fail)
            cout<<"�Ѿ�ȡ���������ʽ!"<<endl;
        else if(returnvalue==success)
        {
            cout<<"��ǰ���ʽ�ַ���Ϊ: "<<endl;
            calculatornow.showinfixexp();
            cout<<"���ʽ�����ɹ�!"<<endl;
        }
        cout<<"================"<<endl;
        break;
     case '3'://3.������ʽ
        cout<<"================"<<endl;
		cout<<"��ǰ���ʽ�ַ���Ϊ: "<<endl;
        calculatornow.showinfixexp();
		if(calculatornow.change()==1)
		{
			cout<<endl<<"��Ӧ�ĺ�׺���ʽ��"<<endl;
			calculatornow.showpostfixexp();
			cout<<"������ʽ��ʼ... "<<endl;
			calculatornow.compute();
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