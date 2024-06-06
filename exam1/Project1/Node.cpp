#include<stdlib.h>
#include<stdio.h>
typedef struct Node *PtrToNode;
struct Node {
	int coe;//ϵ��
	int fre;//ָ��
	PtrToNode Next;
};

//����Ĵ���
PtrToNode creatnode()
{
	//��ʼ������ͷ�ڵ�
	PtrToNode head = (PtrToNode)malloc(sizeof(Node));
	head->coe = 0;
	head->fre = 0;
	head->Next = NULL;
	return head;
}

//���������
PtrToNode insert(PtrToNode list, int coe, int fre) {
	// ����һ���½ڵ�  
	PtrToNode newnode = (PtrToNode)malloc(sizeof(Node));
	if (newnode == NULL) {
		// �ڴ����ʧ�ܴ���  
		return list;
	}
	newnode->coe = coe;
	newnode->fre = fre;
	newnode->Next = NULL;

	// Ѱ�Ҳ���λ�ã����ֽ�������
	PtrToNode position = list;
	while (position->Next != NULL && position->Next->fre > fre) {
		position = position->Next;
	}

	// �����½ڵ�  
	newnode->Next = position->Next;
	position->Next = newnode;

	return list; // ����ͷ���  
}

// ����ʽ���
PtrToNode add(PtrToNode list1, PtrToNode list2)
{
	PtrToNode list = creatnode();
	PtrToNode last = list;
	PtrToNode p1 = list1->Next; // ָ���һ������ʽ��ͷ�ڵ�
	PtrToNode p2 = list2->Next; // ָ��ڶ�������ʽ��ͷ�ڵ�
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->fre == p2->fre)
		{  // ָ����ͬ
			int sum = p1->coe + p2->coe;
			if (sum != 0)
			{
				last->Next = (PtrToNode)malloc(sizeof(struct Node)); // �����½ڵ�
				last = last->Next;
				last->coe = sum;
				last->fre = p1->fre;
				last->Next = NULL;
			}
			p1 = p1->Next;
			p2 = p2->Next;
		}
		else if (p1->fre > p2->fre) 
		{  // ָ��1 > 2
			last->Next = (PtrToNode)malloc(sizeof(struct Node)); // �����½ڵ�
			last = last->Next;
			last->coe = p1->coe;
			last->fre = p1->fre;
			last->Next = NULL;
			p1 = p1->Next;
		}
		else 
		{  // ָ��1 < 2
			last->Next = (PtrToNode)malloc(sizeof(struct Node)); // �����½ڵ�
			last = last->Next;
			last->coe = p2->coe;
			last->fre = p2->fre;
			last->Next = NULL;
			p2 = p2->Next;
		}
	}

	// �ж��������Ƿ���ʣ�࣬��ֹ����ڵ����ݵ���©
	while (p1 != NULL) {  // ����1��ʣ��
		last->Next = (PtrToNode)malloc(sizeof(struct Node)); // �����½ڵ�
		last = last->Next;
		last->coe = p1->coe;
		last->fre = p1->fre;
		last->Next = NULL;
		p1 = p1->Next;
	}
	while (p2 != NULL) {  // ����2��ʣ��
		last->Next = (PtrToNode)malloc(sizeof(struct Node)); // �����½ڵ�
		last = last->Next;
		last->coe = p2->coe;
		last->fre = p2->fre;
		last->Next = NULL;
		p2 = p2->Next;
	}
	return list;
}

// ����ʽ�����
void printnode(PtrToNode list) 
{
	PtrToNode p = list->Next;
	if (p == NULL) 
	{ // �������Ϊ�գ����-1
		printf("-1");
		return;
	}
	int first = 1; // ����Ƿ�Ϊ��һ������Ľڵ�
	while (p != NULL) 
	{
		if (p->coe != 0) 
		{ // ϵ����Ϊ0����
			if (!first ) //���ǵ�һ��
			{
				printf("+");
			}
			if (p->fre == 0) 
			{ // ������
				printf("%d", p->coe);
			}
			else { // x^n��
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
			first = 0; // ����Ѿ�����˵�һ���ڵ�
		}
		p = p->Next;
	}
	printf("\n");
}

int main()//������
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
	// �ͷ��ڴ�
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