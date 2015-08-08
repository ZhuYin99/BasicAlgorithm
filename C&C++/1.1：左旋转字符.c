#include <stdio.h>
#include <string.h>
/*
����ʱ�䣺2015-8-6  by��heqinghqocsh
*/
/*��Ŀ������
	�����ַ���������ת���������ַ���ǰ������ɸ��ַ��ƶ����ַ�����β����
	����ַ���abcdef����ת2λ�õ��ַ���cdefab����ʵ���ַ�������ת�ĺ�����
	Ҫ��Գ���Ϊn���ַ���������ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)�� 				
*/

//������λ��(���Ӷ�ΪO(m*n))
void violenceShift1(char * arr, int n)
{
    size_t tmpLen = strlen(arr);//ע��˳��Ȱ���������('/0')
    char tmpChar;
    int i, j;
    if (n >= 0)//��n����0ʱ��Ϊ����ת��������ߵ�n���ַ��Ƶ�ĩβ��
    {
		while(n--){
			tmpChar = *arr;//�����һ���ַ�
			for(i = 0; i < tmpLen; i++){
				*(arr + i) = *(arr + i + 1);
			}
			*(arr + tmpLen - 1) = tmpChar;
		}
    }
    else//��nС��0ʱ��Ϊ����ת�������ұߵ�n���ַ��Ƶ���ͷ��
    {
		while(n++){
			tmpChar = *(arr + tmpLen -1);//��һ����Ϊ�ַ����ԡ�/0����βҪռһλ
			for(i = tmpLen - 1; i > 0; i--){
				*(arr + i) = *(arr + i - 1);
			}
			*arr = tmpChar;
		}
    }
}
//ָ����λ��(���Ӷ�ΪO(m+n))
void leftShift2(char * arr, int len, int n)
{
    int i;
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
    while (p1 + n - 1 < tmpLen)//�ж��Ƿ�Խ��
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    while (p1 < tmpLen)//��p1С���ַ����ĳ���ʱҪ����β��
    {
        tmpChar = *(arr + p1);
        for (i = p1; i > p0; i--)
        {
            *(arr + i) = *(arr + i - 1);
        }
        *(arr + p0) = tmpChar;
        p0++;
        p1++;
    }
}

//ָ����λ��,β�������õݹ�
void leftShift3(char * arr, int len, int n)
{
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
    while (p1 + n - 1 < tmpLen)
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    if (p1 < tmpLen)
    {
        leftShift2(arr + p0, len - p0, n);
    }
}

//ָ����λ��,�ݹ�
void leftShift4(char * arr, int len, int n)
{
    size_t tmpLen = len;
    int p0 = 0;
    int p1 = n;
    char tmpChar;
	int i;
    while (p1 < tmpLen)
    {
        tmpChar = *(arr + p0);
        *(arr + p0) = *(arr + p1);
        *(arr + p1) = tmpChar;
        p0++;
        p1++;
    }
    i = n - tmpLen%n;
    if (i != 0 && p0 != tmpLen - 1)//���һ��������֤i=n(��tmplen%n=0)ʱ��©��
    {
        leftShift4((arr + p0), n, i);
    }
}

//������ת��
/*
˼·����һ���ַ����ֳ������֣�X��Y�������֣����ַ����϶��巴ת�Ĳ���X^T��
����X�������ַ���ת���磬X="abc"����ôX^T="cba"������ô���ǿ��Եõ�����Ľ��ۣ�(X^TY^T)^T=YX��
��Ȼ������Ϳ���ת��Ϊ�ַ����ķ�ת�������ˡ�ok,����abcdef ���������˵����Ҫ��def��ת��abc��ǰͷ
����ôֻҪ������3������������ɣ�
1�����ȷ�Ϊ�����֣�X:abc��Y:def��
2��X->X^T��abc->cba�� Y->Y^T��def->fed��
3��(X^TY^T)^T=YX��cbafed->defabc����������ת��
*/
void myinvert(char * start, char * end)
{
    char tmpChar;
    while (start < end)
    {
        tmpChar = *start;
        *start = *end;
        *end = tmpChar;
        start++;
        end--;
    }
}
void leftShift5(char * arr, int len, int n)
{
    myinvert(arr, arr + n - 1);
    myinvert(arr + n, arr + len - 1);
    myinvert(arr, arr + len - 1);
}
int gcd(int m, int n)
{
    int r;
    while ((r = m % n))
    {
        m = n;
        n = r;
    }
    return n;
}
//����ѭ����λ��
void leftShift6(char * arr, int len, int n)
{
    int group = gcd(len, n);
    char tmpChar;
    int x = len / group;
    int i, j;
    for (i = 0; i < group; i++)
    {
        tmpChar = *(arr + i);
        for (j = 0; j < x - 1; j++)
        {
            *(arr + (i + (j * n)) % len) = *(arr + (i + (j * n) + n) % len);
        }
        *(arr + (i + (j * n)) % len) = tmpChar;
    }
}
int main()
{
    char str[50];
    sprintf(str, "abcdefghijk");
    printf("ԭʼ�ַ���Ϊ :%s\t����ΪΪ :%d\n", str, strlen(str));
    printf("\n");
    violenceShift1(str, 2);
    printf("������λ��������2λ�� :%s\n", str);
    violenceShift1(str, -2);
    printf("������λ��������2λ�� :%s\n", str);
    violenceShift1(str, 3);
    printf("������λ��������3λ�� :%s\n", str);
    violenceShift1(str, strlen(str) - 3);
    printf("������λ��������3λ�� :%s\n", str);
    printf("\n");

    leftShift2(str, strlen(str), 3);
    printf("ָ����λ��������3λ�� :%s\n", str);
    leftShift2(str, strlen(str), strlen(str) - 3);
    printf("ָ����λ��������3λ�� :%s\n", str);
    leftShift2(str + 2, strlen(str) - 2, 2);
    printf("ָ����λ�����ӵ���λ��ʼ����2λ�� :%s\n", str);
    leftShift2(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("ָ����λ�����ӵ���λ��ʼ����2λ�� :%s\n", str);
    printf("\n");


    leftShift3(str, strlen(str), 3);
    printf("ָ����λ����β���õݹ飩 :%s\n", str);
    leftShift3(str, strlen(str), strlen(str) - 3);
    printf("ָ����λ����β���õݹ飩 :%s\n", str);
    leftShift3(str + 2, strlen(str) - 2, 2);
    printf("ָ����λ����β���õݹ飩 :%s\n", str);
    leftShift3(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("ָ����λ����β���õݹ飩 :%s\n", str);
    printf("\n");

    leftShift4(str, strlen(str), 3);
    printf("ָ����λ�����õݹ飩 :%s\n", str);
    leftShift4(str, strlen(str), strlen(str) - 3);
    printf("ָ����λ�����õݹ飩 :%s\n", str);
    leftShift4(str + 2, strlen(str) - 2, 2);
    printf("ָ����λ�����õݹ飩 :%s\n", str);
    leftShift4(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("ָ����λ�����õݹ飩 :%s\n", str);
    printf("\n");

    leftShift5(str, strlen(str), 3);
    printf("������ת�� :%s\n", str);
    leftShift5(str, strlen(str), strlen(str) - 3);
    printf("������ת�� :%s\n", str);
    leftShift5(str + 2, strlen(str) - 2, 2);
    printf("������ת�� :%s\n", str);
    leftShift5(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("������ת�� :%s\n", str);
    printf("\n");

    leftShift6(str, strlen(str), 3);
    printf("����ѭ����λ�� :%s\n", str);
    leftShift6(str, strlen(str), strlen(str) - 3);
    printf("����ѭ����λ�� :%s\n", str);
    leftShift6(str + 2, strlen(str) - 2, 2);
    printf("����ѭ����λ�� :%s\n", str);
    leftShift6(str + 2, strlen(str) - 2, strlen(str) - 2 - 2);
    printf("����ѭ����λ�� :%s\n", str);
    printf("\n");


    return 0;
}