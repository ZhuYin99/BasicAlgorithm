/*
��Ŀ��
����һ�������һ�����֣��������в�����������ʹ�����ǵĺ�������������Ǹ����֡�
*/
//����һ  
//O��N��  
Pair findSum(int *s,int n,int x)     
{     
    //sort(s,s+n);   ������������ģ��Ǿ������ź���O��N*logN��     
      
    int *begin=s;     
    int *end=s+n-1;     
      
    while(begin<end)    //��ͷ�бƣ��������ָ������ɨ�跨���ܾ���ķ�����O��N��    
    {     
        if(*begin+*end>x)     
        {     
            --end;     
        }     
        else if(*begin+*end<x)     
        {     
            ++begin;     
        }     
        else    
        {     
            return Pair(*begin,*end);     
        }     
    }     
      
    return Pair(-1,-1);     
}     
  
//�������±�д��  
//�����  
//copyright@ zhedahht && yansha  
//July��updated��2011.05.14��  
bool find_num(int data[], unsigned int length, int sum, int& first_num, int& second_num)  
{     
    if(length < 1)  
        return true;  
      
    int begin = 0;  
    int end = length - 1;  
      
    while(end > begin)  
    {  
        long current_sum = data[begin] + data[end];  
          
        if(current_sum == sum)  
        {  
            first_num = data[begin];  
            second_num = data[end];  
            return true;  
        }  
        else if(current_sum > sum)  
            end--;  
        else  
            begin++;  
    }  
    return false;  
}  