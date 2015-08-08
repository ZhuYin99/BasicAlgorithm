/*
��Ŀ������
��������һ��������ĸ��ɵ��ַ���A��������һ���ַ���B���ַ�����B����ĸ�������һЩ��
ʲô���������Ĳ������С�ַ���B�����ĸ�ڴ��ַ���A�ﶼ�У�
*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//��������,ֻ��Դ�д��ĸ���ɸ���Ҫ��ı䣩
void countSort(char *oldArr,char *newArr){
	int count[26] = {0};
	int i,index;
	int lenOld = strlen(oldArr);
	int pos;
	memset(newArr,0,lenOld);//��newArrȫ����ֵΪ0
	for(i=0;i<lenOld;i++){
		pos = *(oldArr + i) - 'A';
		count[pos]++;
	}
	for(i=0;i<25;i++){
		count[i + 1] += count[i];
	}
	for(i=0;i<lenOld;i++){
		index = *(oldArr + i) - 'A';
		pos = count[index];
//		while(newArr[pos - 1] != 0){
//			pos--;
//		}
		newArr[pos - 1] = *(oldArr + i);
		count[index]--;
	}
}

//bit�������ö����Ƶ��������㣬���ִ�Сд
int contain_bit(char *longStr,char *shortStr){
	unsigned long bitLong = 0,bitShort = 0;
	while(*longStr){
		bitLong |= (unsigned long)(1l << (*longStr++ & 0x3f));//ȡ8λASCII���еĺ���λ����ȷ��һ����ĸ
	}
	while(*shortStr){
		bitShort |= (unsigned long)(1l << (*shortStr++ & 0x3f));//ȡ8λASCII���еĺ���λ����ȷ��һ����ĸ
	}
	return !((bitLong ^ bitShort) & bitShort);//�������������жϳ���˭ӵ�в�ͬ���ַ������������������ȷ��
}
//����hashTable��
int contain_hashTable(char *longStr,char *shortStr){
	int hash[52] = {0};
	int num = 0;
	int i = 0;
	//ɨ����ַ���
	for(i = 0;i < strlen(shortStr);i++){
		int index = shortStr[i] - 'A';
		if(hash[index] == 0){
			hash[index] = 1;
			num++;
		}
	}
	//ɨ�賤�ַ���
	for(i = 0;i < strlen(longStr);i++){
		int index = longStr[i] - 'A';
		if(hash[index] == 1){
			hash[index]  = 0;
			num--;
			if(num == 0){
				break;
			}
		}
	}
	if(num == 0){
		return 1;
	}else{
		return 0;
	}
}

//��������,���ܴ�������ַ���,��Ϊʹ�õ�unsigned long���
int contain_prime(char * stra, char * strb)
{
    int primeNumber[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
                           61, 67, 71, 73, 79, 83, 89, 97, 101};
    unsigned long bigNumber = 1; //too small for use.
    while (*stra)
    {
        bigNumber *= primeNumber[*stra - 'A'];
        stra++;
    }
    while (*strb)
    {
        if (0 != (bigNumber % primeNumber[*strb - 'A']))
        {
            break;
        }
        strb++;
    }
    if (*strb)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int contain_countSort(char *longStr,char *shortStr){
	int lenLong = strlen(longStr);
	int lenShort = strlen(shortStr);
	int i,j;
	char *longTmp = (char *)malloc(sizeof(char)*lenLong);
	char *shortTmp = (char *)malloc(sizeof(char)*lenShort);
	countSort(longStr,longTmp);
	countSort(shortStr,shortTmp);
	printf("���ַ��������%s\n",longTmp);
	printf("���ַ��������%s\n",shortTmp);
	for(i = 0,j = 0;i < lenLong && j < lenShort;){
		if(longTmp[i] == shortTmp[j]){
			j++;
			while(longTmp[i] == longTmp[i + 1]){
				i++;
			}
		}else if(longTmp[i] > shortTmp[j]){
			return 0;
		}else{
			i++;
		}
	}
	if(j == lenShort){
		return 1;
	}else{
		return 0;
	}
}

int main(){
	char longStr[50];
	char shortStr[50];
	sprintf(longStr,"ABCDFEGADCBHKJIAXCBADIKJIMNMXYZ");
	sprintf(shortStr,"CBADIKJIMNML");
	printf("���ü������򷨱Ƚϣ�\n");
	if(contain_countSort(longStr,shortStr)){
		printf("����\n");
	}else{
		printf("������\n");
	}
	printf("����bit����\n");
	if(contain_bit(longStr,shortStr)){
		printf("����\n");
	}else{
		printf("������\n");
	}
	printf("����hash����\n");
	if(contain_hashTable(longStr,shortStr)){
		printf("����\n");
	}else{
		printf("������\n");
	}

	printf("������������\n");
	if(contain_prime(longStr,shortStr)){
		printf("����\n");
	}else{
		printf("������\n");
	}

}