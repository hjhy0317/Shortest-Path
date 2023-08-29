#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define infinity 99999  // infinity�� 99999�� ����

float distance(int a, int b, int c, int e)
{
	int x;
	float d;
	x = ((a - b) * (a - b) + (c - e) * (c - e));
	d = sqrt(x);  // d�� (a,b)�� (c,e) ������ �Ÿ�
	return d;
}


struct node  // ����ü node
{
	int x;
	float d; // d�� �Ÿ�
	struct node* next;  // ���� ��忡 ���� ���� ����
};


struct point  // data�� ����ü pointer
{
	int x;
	int y;
	struct node* linked_list;  // linked list�� ����� ��
}data[101];  // ���� ũ��� 101�� ����


struct heap  // heap ����ü
{
	int v;
	int Best;
}htr[101];  // ���� ũ��� 101�� ����


typedef struct heap heap;


void buildheap()  // heap tree�� ����� �Լ�
{
	int i;

	htr[1].v = 1;  // heap tree�� node 1 v���� 1
	data[1].x = htr[1].v;  // data�� heap node ����
	htr[1].Best = 0;  // heap tree�� node 1 Best���� 0

	for (i = 2; i <= 100; i++)
	{
		htr[i].v = i;  // heap tree�� node 2���� 100���� vertex�� �ڽ�
		data[i].x = htr[i].v;  // data�� heap node ����
		htr[i].Best = infinity;  // Best ���� infinity
	}

}


void per_down(int v, int size) // percolate down �Լ�
{
	int min = 0;
	int left;
	int right;
	heap temp;

	while (2 * v <= size)  // ���� ū node�� ũ�Ⱑ size���� ���� ���
	{
		right = v * 2 + 1;  
		left = v * 2;  
		if (right <= size)  // right�� size���� ���� ���
			if (htr[left].Best > htr[right].Best)  // ���� node > ������ node
				min = right;
			else min = left;
		else min = left;
		if (htr[min].Best < htr[v].Best)
		{
			temp = htr[v];
			htr[v] = htr[min];
			htr[min] = temp;
			v = min;  // �ּڰ��� heap tree���� switch
		}
		else break;
	}
}


heap del_min(int size)  // delete min �Լ�
{
	heap temp;

	temp = htr[1];
	htr[1] = htr[size];
	per_down(1, size);  // heap tree�� ���� ���� ��ġ�� node�� delete
	return temp;
}


struct node findmin(int n)  // node ���� �Ÿ� �� �ּڰ��� ã�� �Լ�
{

	double k = 13;  // �Ÿ��� 13�� ���� (k)
	struct node* minlist = data[n].linked_list, min;  // �ּ� �Ÿ� node ����

	while (minlist != NULL)
	{
		if (k > minlist->d)  // �ּ� node�� d�� 13���� ���� ���
		{
			k = minlist->d;  // �ּ� node�� d ���� ����
			min = *minlist;  // minlist�� �ּ� node�� update
		}
		minlist = minlist->next;
	}
	return min;
}


int main()
{
	int i;
	int j;
	int n;
	float d;
	struct node* adjacent, min;  // adjacent node

	printf("    point        adjacent      weight(distance)\n");
	printf("   (node)     (minimum node)  (minimum distance)\n(  x     y)   (  x     y)\n\n");

	for (i = 1; i <= 100; i++)
	{
		data[i].x = i;
		data[i].y = (i * i) % 100;  // y mod 100 (������)
	}

	for (i = 1; i <= 100; i++)
	{
		for (j = 1; j <= 100; j++)
		{
			d = distance(data[i].x, data[j].x, data[i].y, data[j].y);
			if (d > 0 && d <= 13)  // �Ÿ��� 13 ������ node�� adjacent�� ����
			{
				adjacent = (struct node*)malloc(sizeof(struct node));

				adjacent->x = j;
				adjacent->d = d;
				adjacent->next = NULL;
				adjacent->next = data[i].linked_list;
				data[i].linked_list = adjacent;
			}
		}
	}

	for (n = 1; n <= 100; n++)
	{
		min = findmin(n);
		printf("(%3d   %3d)   (%3d   %3d)           %.2f\n", n, data[n].y, min.x, data[min.x].y, min.d);
	}  // node, minimum weight, distance ���

}