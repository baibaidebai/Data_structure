#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义栈的节点
typedef struct SNode {
    char* data;
    int top;
    int base;
    int SteakSize;
} *Steak;

Steak CreateSteak(int SteakSize) // 创建栈
{
    Steak s = (Steak)malloc(sizeof(struct SNode));
    if (s == NULL) {
        printf("内存分配失败！");
        return NULL;
    }
    s->data = (char*)malloc(SteakSize * sizeof(char));
    if (s->data == NULL) {
        printf("内存分配失败！");
        free(s);
        return NULL;
    }
    s->SteakSize = SteakSize;
    s->base = 0;
    s->top = -1;
    return s;
}

bool IsEmpty(Steak s) // 判断栈空
{
    return s->top == -1;
}

bool IsFull(Steak s) // 判断栈满
{
    return s->top == s->SteakSize - 1;
}

bool Push(char data, Steak s) // 压入栈操作
{
    if (IsFull(s)) {
        printf("栈满");
        return false;
    }
    s->data[++s->top] = data;
    return true;
}

char Pop(Steak s) // 出栈操作
{
    if (IsEmpty(s)) {
        printf("栈空");
        return '\0';
    }
    return s->data[s->top--];
}

void ClearSteak(Steak s) // 清空
{
    s->top = -1;
}

char Take(Steak s) // 取栈顶元素
{
    if (IsEmpty(s)) {
        printf("栈空");
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
        printf("内存分配失败！");
        free(s->data);
        free(s);
        return 1;//反馈程序异常
    }

    for (int i = 0; i < n; i++)//将输入的两个序列存储进两个数组中
        scanf_s(" %c", &data[i],sizeof(char));
    for (int i = 0; i < n; i++)
        scanf_s(" %c", &simple[i],sizeof(char));
    //创建索引
    int dataIndex = 0;
    int i = 0;
    int l = 0;

    while (i < n) {
        if (!IsEmpty(s) && Take(s) == simple[i]) {//栈顶元素与示例元素相同
            print[l] = Pop(s);//记录到print数组中并弹出栈
            printIndex[l] = -1;
            i++;
            l++;
        }
        else if (dataIndex < n) {//数据索引小于n
            Push(data[dataIndex], s);
            printIndex[l] = 1;
            print[l] = data[dataIndex++];
            l++;
        }
        else {//数据索引大于等于n，则表示已经结束
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
