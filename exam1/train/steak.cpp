#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ����ջ�Ľڵ�
typedef struct SNode {
    char* data;
    int top;
    int base;
    int SteakSize;
} *Steak;

Steak CreateSteak(int SteakSize) // ����ջ
{
    Steak s = (Steak)malloc(sizeof(struct SNode));
    if (s == NULL) {
        printf("�ڴ����ʧ�ܣ�");
        return NULL;
    }
    s->data = (char*)malloc(SteakSize * sizeof(char));
    if (s->data == NULL) {
        printf("�ڴ����ʧ�ܣ�");
        free(s);
        return NULL;
    }
    s->SteakSize = SteakSize;
    s->base = 0;
    s->top = -1;
    return s;
}

bool IsEmpty(Steak s) // �ж�ջ��
{
    return s->top == -1;
}

bool IsFull(Steak s) // �ж�ջ��
{
    return s->top == s->SteakSize - 1;
}

bool Push(char data, Steak s) // ѹ��ջ����
{
    if (IsFull(s)) {
        printf("ջ��");
        return false;
    }
    s->data[++s->top] = data;
    return true;
}

char Pop(Steak s) // ��ջ����
{
    if (IsEmpty(s)) {
        printf("ջ��");
        return '\0';
    }
    return s->data[s->top--];
}

void ClearSteak(Steak s) // ���
{
    s->top = -1;
}

char Take(Steak s) // ȡջ��Ԫ��
{
    if (IsEmpty(s)) {
        printf("ջ��");
        return '\0';
    }
    return s->data[s->top];
}

int main() {
    int n;
    scanf_s("%d", &n);
    Steak s = CreateSteak(n);
    if (s == NULL) {
        return 1;
    }

    char* data = (char*)malloc((n + 1) * sizeof(char));
    char* simple = (char*)malloc((n + 1) * sizeof(char));
    char* print = (char*)malloc((2*n + 1) * sizeof(char));
    char* printIndex = (char*)malloc((2 * n + 1) * sizeof(char));
    if (data == NULL || simple == NULL || print == NULL || printIndex == NULL) {
        printf("�ڴ����ʧ�ܣ�");
        free(s->data);
        free(s);
        return 1;//���������쳣
    }

    for (int i = 0; i < n; i++)//��������������д洢������������
        scanf_s(" %c", &data[i],sizeof(char));
    for (int i = 0; i < n; i++)
        scanf_s(" %c", &simple[i],sizeof(char));
    //��������
    int dataIndex = 0;
    int i = 0;
    int l = 0;

    while (i < n) {
        if (!IsEmpty(s) && Take(s) == simple[i]) {//ջ��Ԫ����ʾ��Ԫ����ͬ
            print[l] = Pop(s);//��¼��print�����в�����ջ
            printIndex[l] = -1;
            i++;
            l++;
        }
        else if (dataIndex < n) {//��������С��n
            Push(data[dataIndex], s);
            printIndex[l] = 1;
            print[l] = data[dataIndex++];
            l++;
        }
        else {//�����������ڵ���n�����ʾ�Ѿ�����
            break;
        }
    }

    if (!IsEmpty(s)) {
        printf("0\n");
    }
    else{
        printf("1\n");
        for (int k = 0; k < l; k++) {
            printf("%c", print[k]);
            if (printIndex[k] == -1)
                printf("_out ");
            else
                printf("_in ");
        }
    }

    free(data);
    free(simple);
    free(print);
    free(printIndex);
    free(s->data);
    free(s);

    return 0;
}
