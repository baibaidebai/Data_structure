#include<stdlib.h>
#include<stdio.h>
typedef struct Node *PtrToNode;
struct Node {
	int coe;//系数
	int fre;//指数
	PtrToNode Next;
};

//链表的创建
PtrToNode creatnode()
{
	//初始化链表头节点
	PtrToNode head = (PtrToNode)malloc(sizeof(Node));
	head->coe = 0;
	head->fre = 0;
	head->Next = NULL;
	return head;
}

//链表降序插入
PtrToNode insert(PtrToNode list, int coe, int fre) {
	// 创建一个新节点  
	PtrToNode newnode = (PtrToNode)malloc(sizeof(Node));
	if (newnode == NULL) {
		// 内存分配失败处理  
		return list;
	}
	newnode->coe = coe;
	newnode->fre = fre;
	newnode->Next = NULL;

	// 寻找插入位置，保持降序排列
	PtrToNode position = list;
	while (position->Next != NULL && position->Next->fre > fre) {
		position = position->Next;
	}

	// 插入新节点  
	newnode->Next = position->Next;
	position->Next = newnode;

	return list; // 返回头结点  
}

// 多项式相加
PtrToNode add(PtrToNode list1, PtrToNode list2)
{
	PtrToNode list = creatnode();
	PtrToNode last = list;
	PtrToNode p1 = list1->Next; // 指向第一个多项式的头节点
	PtrToNode p2 = list2->Next; // 指向第二个多项式的头节点
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->fre == p2->fre)
		{  // 指数相同
			int sum = p1->coe + p2->coe;
			if (sum != 0)
			{
				last->Next = (PtrToNode)malloc(sizeof(struct Node)); // 分配新节点
				last = last->Next;
				last->coe = sum;
				last->fre = p1->fre;
				last->Next = NULL;
			}
			p1 = p1->Next;
			p2 = p2->Next;
		}
		else if (p1->fre > p2->fre) 
		{  // 指数1 > 2
			last->Next = (PtrToNode)malloc(sizeof(struct Node)); // 分配新节点
			last = last->Next;
			last->coe = p1->coe;
			last->fre = p1->fre;
			last->Next = NULL;
			p1 = p1->Next;
		}
		else 
		{  // 指数1 < 2
			last->Next = (PtrToNode)malloc(sizeof(struct Node)); // 分配新节点
			last = last->Next;
			last->coe = p2->coe;
			last->fre = p2->fre;
			last->Next = NULL;
			p2 = p2->Next;
		}
	}

	// 判断两链表是否有剩余，防止链表节点数据的遗漏
	while (p1 != NULL) {  // 链表1有剩余
		last->Next = (PtrToNode)malloc(sizeof(struct Node)); // 分配新节点
		last = last->Next;
		last->coe = p1->coe;
		last->fre = p1->fre;
		last->Next = NULL;
		p1 = p1->Next;
	}
	while (p2 != NULL) {  // 链表2有剩余
		last->Next = (PtrToNode)malloc(sizeof(struct Node)); // 分配新节点
		last = last->Next;
		last->coe = p2->coe;
		last->fre = p2->fre;
		last->Next = NULL;
		p2 = p2->Next;
	}
	return list;
}

// 多项式的输出
void printnode(PtrToNode list) 
{
	PtrToNode p = list->Next;
	if (p == NULL) 
	{ // 如果链表为空，输出-1
		printf("-1");
		return;
	}
	int first = 1; // 标记是否为第一个输出的节点
	while (p != NULL) 
	{
		if (p->coe != 0) 
		{ // 系数不为0的项
			if (!first ) //不是第一项
			{
				printf("+");
			}
			if (p->fre == 0) 
			{ // 常数项
				printf("%d", p->coe);
			}
			else { // x^n项
				if (p->coe == 1) 
				{
					printf("x^%d", p->fre);
				}
				else if (p->coe == -1) 
				{
					printf("-x^%d", p->fre);
				}
				else 
				{
					printf("%dx^%d", p->coe, p->fre);
				}
			}
			first = 0; // 标记已经输出了第一个节点
		}
		p = p->Next;
	}
	printf("\n");
}

int main()//主函数
{
	int coe, fre;
	PtrToNode list1 = creatnode();
	scanf_s("%d %d", &coe, &fre);
	while (coe != 0 || fre != 0)
	{
		insert(list1, coe, fre);
		scanf_s("%d %d", &coe, &fre);
	}
	char ch;
	scanf_s("%c", &ch);
	scanf_s("%c", &ch);
	PtrToNode list2 = creatnode();
	scanf_s("%d %d", &coe, &fre);
	while (coe != 0 || fre != 0)
	{
		insert(list2, coe, fre);
		scanf_s("%d %d", &coe, &fre);
	}
	PtrToNode list=add(list1, list2);
	printnode(list);
	// 释放内存
	PtrToNode temp;
	while (list != NULL) {
		temp = list;
		list = list->Next;
		free(temp);
	}
	while (list1 != NULL) {
		temp = list1;
		list1 = list1->Next;
		free(temp);
	}
	while (list2 != NULL) {
		temp = list2;
		list2 = list2->Next;
		free(temp);
	};
	return 0;
}