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
	}//生成随机数
}

void Merge(SSTable& ST , int low, int mid, int high)//low和high均为下标
{
	ElemType *B;
	B = (ElemType*)malloc(sizeof(ElemType) * ST.TableLen);//分配数组B空间
	int i, j, k;
	for (k = low; k <= high; k++)//从low的位置开始
	{
		B[k] = ST.elem[k];//复制到B数组中
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)//k不断+1
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
	while (i <= mid)//后面已经排完
	{
		ST.elem[k++] = B[i++];
	}
	while (j <= high)//前面已经排完
	{
		ST.elem[k++] = B[j++];
	}
}
//合并

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
//归并排序

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
	printf("\n---------归并排序---------\n");
	MergeSort(ST, 0, 9);
	ST_print(ST);
	return 0;
}