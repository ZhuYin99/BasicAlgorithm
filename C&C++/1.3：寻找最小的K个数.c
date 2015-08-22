/*
��Ŀ����������n������Ѱ��������С��k����
*/
#include<stdio.h>
#include<stdlib.h>

#define MAX_NUM 100000  //������������ĸ������ֵ
#define K 10            //Ѱ����С����
#define NUM 20          //��data.txt �ж�ȡnum������

/*
�������ܣ������������Ȼ��д��data.txt�ļ���
*/
void random_num(){
	long num = 0;
	long i = 1;
	FILE *fp;
	fp = fopen("data.txt","w");
	if(fp == NULL){
		printf("�ļ���ʧ��!\n");
		return ;
	}
	printf("��������Ҫ������������ĸ�����<=%d��\n",MAX_NUM);
	scanf("%ld",&num);
	if(num > MAX_NUM){
		printf("����ĸ�������!");
		return;
	}
	srand((unsigned)time(NULL));
	for(i = 1;i <= num;i++){
		long temp = rand() % 100000;
		fprintf(fp,"%ld ",temp);
	}
	fclose(fp);
}

/*
��ӡǰk����
*/
void print_K(long a[],int k){
	int i = 1;
	printf("�����ǰk����Ϊ��\n");
	for(i = 1;i <= k;i++){
		printf("%ld  ",a[i]);
	}
	printf("\n");
}


/*
����������
*/
void swap(long *a,long *b){
	long tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
���������еķ��η���----�����Ԫ
*/
int partition_rand(long a[],int first,int last){
	int pivot = first + rand() % (last - first + 1);
	long key;
	swap(&a[first],&a[last]);

	key = a[first];
	while(first < last){
		while(first < last && a[last] >= key){
			last--;
		}
		swap(&a[first],&a[last]);
		while(first < last && a[first] <= key){
			first++;
		}
		swap(&a[first],&a[last]);
	}
	return first;
}

/*
���������з��η���-----�̶���Ԫ
*/
int partition(long a[],int first,int last){
	long key = a[first];
	while(first < last){
		while(first < last && a[last] >= key){
			last--;
		}
		swap(&a[first],&a[last]);
		while(first < last && a[first] <= key){
			first++;
		}
		swap(&a[first],&a[last]);
	}
	return first;
}

/*
���������㷨----�����Ԫ
*/
void quick_sort_rand(long a[],int first,int last){
	if(first < last){
		int pivot = partition_rand(a,first,last);
		quick_sort_rand(a,first,pivot - 1);
		quick_sort_rand(a,pivot + 1,last);
	}
}

/*
���������㷨----�̶���Ԫ
*/
void quick_sort(long a[],int first,int last){
	if(first < last){
		int pivot = partition(a,first,last);
		quick_sort(a,first,pivot - 1);
		quick_sort(a,pivot + 1,last);
	}
}

/*
��������ǰ�ĳ�ʼ��
*/

long* init(){
	long a[NUM + 1];
	int i = 1;
	FILE *fp = NULL;
	random_num();//���������
	
	fp = fopen("data.txt","r");
	if(fp == NULL){
		printf("�޷����ļ�data.txt!\n");
		return;
	}
	while((fscanf(fp,"%ld",&a[i])) != EOF && (i <= NUM)){
		i++;
	}
	printf("��data.txt�ļ��ж�ȡ��%d�����ǣ�\n",NUM);
	for(i = 1;i <= NUM;i++){
		if(i % 11 == 0){
			printf("\n");
		}
		printf("%ld ",a[i]);
	}
	printf("\n\n");
	fclose(fp);
	return a;
}

void main(){
	int first = 1;
	int last = NUM;
	long b[NUM + 1];
	long *a = init();
	memcpy(b,a,sizeof(a));
//	quick_sort_rand(b,first,last);
//	printf("ͨ���������������Ԫ���ҵ�����С�� %d ����Ϊ��\n",K);
//	print_K(b,K);

	quick_sort(b,first,last);
	printf("ͨ���������򣨹̶���Ԫ���ҵ�����С�� %d ����Ϊ��\n",K);
	print_K(b,K);
	


}