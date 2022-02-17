#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;
typedef struct {
	ElemType* elem;
	int TableLen;
}SSTable;

void ST_Init(SSTable& ST,int len)
{
	ST.TableLen = len;
	ST.elem = (ElemType*)malloc(sizeof(ElemType) * ST.TableLen);
	int i;
	srand(time(NULL));
	for (i = 0; i < ST.TableLen; i++)
	{
		ST.elem[i] = rand() % 100;
	}//���������
}

void Merge(SSTable& ST , int low, int mid, int high)//low��high��Ϊ�±�
{
	ElemType *B;
	B = (ElemType*)malloc(sizeof(ElemType) * ST.TableLen);//��������B�ռ�
	int i, j, k;
	for (k = low; k <= high; k++)//��low��λ�ÿ�ʼ
	{
		B[k] = ST.elem[k];//���Ƶ�B������
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)//k����+1
	{
		if (B[i] <= B[j])
		{
			ST.elem[k] = B[i++];
		}
		else
		{
			ST.elem[k] = B[j++];
		}
	}
	while (i <= mid)//�����Ѿ�����
	{
		ST.elem[k++] = B[i++];
	}
	while (j <= high)//ǰ���Ѿ�����
	{
		ST.elem[k++] = B[j++];
	}
}
//�ϲ�

void MergeSort(SSTable& ST , int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(ST, low, mid);
		MergeSort(ST, mid + 1, high);
		Merge(ST, low, mid, high);
	}
}
//�鲢����

void ST_print(SSTable ST)
{
	int i;
	for (i = 0; i < ST.TableLen; i++)
	{
		printf("%3d", ST.elem[i]);
	}
	printf("\n");
}

int main()
{
	SSTable ST;
	ST_Init(ST,10);
	ST_print(ST);
	printf("\n---------�鲢����---------\n");
	MergeSort(ST, 0, 9);
	ST_print(ST);
	return 0;
}