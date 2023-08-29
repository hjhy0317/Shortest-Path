#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define infinity 99999  // infinity를 99999로 설정

float distance(int a, int b, int c, int e)
{
	int x;
	float d;
	x = ((a - b) * (a - b) + (c - e) * (c - e));
	d = sqrt(x);  // d는 (a,b)와 (c,e) 사이의 거리
	return d;
}


struct node  // 구조체 node
{
	int x;
	float d; // d는 거리
	struct node* next;  // 다음 노드에 대한 정보 저장
};


struct point  // data의 구조체 pointer
{
	int x;
	int y;
	struct node* linked_list;  // linked list로 연결된 값
}data[101];  // 저장 크기는 101로 설정


struct heap  // heap 구조체
{
	int v;
	int Best;
}htr[101];  // 저장 크기는 101로 설정


typedef struct heap heap;


void buildheap()  // heap tree를 만드는 함수
{
	int i;

	htr[1].v = 1;  // heap tree의 node 1 v값은 1
	data[1].x = htr[1].v;  // data와 heap node 연결
	htr[1].Best = 0;  // heap tree의 node 1 Best값은 0

	for (i = 2; i <= 100; i++)
	{
		htr[i].v = i;  // heap tree의 node 2부터 100까지 vertex는 자신
		data[i].x = htr[i].v;  // data와 heap node 연결
		htr[i].Best = infinity;  // Best 값은 infinity
	}

}


void per_down(int v, int size) // percolate down 함수
{
	int min = 0;
	int left;
	int right;
	heap temp;

	while (2 * v <= size)  // 가장 큰 node의 크기가 size보다 작은 경우
	{
		right = v * 2 + 1;  
		left = v * 2;  
		if (right <= size)  // right가 size보다 작은 경우
			if (htr[left].Best > htr[right].Best)  // 왼쪽 node > 오른쪽 node
				min = right;
			else min = left;
		else min = left;
		if (htr[min].Best < htr[v].Best)
		{
			temp = htr[v];
			htr[v] = htr[min];
			htr[min] = temp;
			v = min;  // 최솟값과 heap tree값을 switch
		}
		else break;
	}
}


heap del_min(int size)  // delete min 함수
{
	heap temp;

	temp = htr[1];
	htr[1] = htr[size];
	per_down(1, size);  // heap tree의 가장 위에 위치한 node를 delete
	return temp;
}


struct node findmin(int n)  // node 간의 거리 중 최솟값을 찾는 함수
{

	double k = 13;  // 거리는 13을 기준 (k)
	struct node* minlist = data[n].linked_list, min;  // 최소 거리 node 설정

	while (minlist != NULL)
	{
		if (k > minlist->d)  // 최소 node의 d가 13보다 작은 경우
		{
			k = minlist->d;  // 최소 node의 d 값을 기준
			min = *minlist;  // minlist로 최소 node를 update
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
		data[i].y = (i * i) % 100;  // y mod 100 (나머지)
	}

	for (i = 1; i <= 100; i++)
	{
		for (j = 1; j <= 100; j++)
		{
			d = distance(data[i].x, data[j].x, data[i].y, data[j].y);
			if (d > 0 && d <= 13)  // 거리가 13 이하인 node를 adjacent로 설정
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
	}  // node, minimum weight, distance 출력

}