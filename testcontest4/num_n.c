#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// �������� ��������� ������ ���������� ������
typedef struct Node 
{
    int data; // �������� ������
    struct Node* next; // ����� ��������� ������
}Cell;

// ������� ���������� ������
void insert(Cell** head_ref, int new_data) 
{
    // �������� ������ ��� ����� ����
    Cell* new_node;
    if (!(new_node = (Cell*)malloc(sizeof(Cell))))
        return 0;

    // ��������� �� ��������� ����
    Cell* last = *head_ref;
    // ��������� ������ ������ ����
    new_node->data = new_data;
    new_node->next = NULL;
    // ���� ������ ����, �� ����� ���� ���������� ������� ������
    if (*head_ref == NULL) 
    {
        *head_ref = new_node;
        return;
    }
    // ����� ���� ��������� ���� � ��������� ����� ���� � ����� ������
    while (last->next != NULL) 
        last = last->next;
    last->next = new_node;
    return;
}

void rearrangeList(Cell** head_ref) 
{   
    // ��������� �� ������ ������ ������������� �������
    Cell* even_positive_first = NULL;
    // ��������� �� ��������� ������ ������������� �������
    Cell* even_positive_last = NULL;
    // ������� ������� ������
    Cell* current = *head_ref;
    // ���������� ������� ������
    Cell* prev = NULL;

    // ���������� ��� �������� ������
    while (current != NULL) 
    {   
        // ���� ������� ������� ������ � �������������
        if (current->data > 0 && current->data % 2 == 0) 
        {   
            // ���� ��� ������ ������ ������������� �������
            if (even_positive_first == NULL) 
            {
                even_positive_first = current;
                even_positive_last = current;
            }

            // ����� ��������� ������� ������� � ����� ������ ������ ������������� ���������
            else 
            {
                even_positive_last->next = current;
                even_positive_last = even_positive_last->next;
            }

            // ������� ������� ������� �� ������� ������� ������
            if (prev != NULL)
                prev->next = current->next;
            if (*head_ref == current)
                *head_ref = current->next;
        }
        else
            prev = current;

        current = current->next;
    }

    // ���� ���� ������� ������ ������������� ��������, ������������ �� � ������ ������
    if (even_positive_first != NULL)
    {
        even_positive_last->next = *head_ref;
        *head_ref = even_positive_first;
    }
}

// ������� ������ ���� ��������� ������
void printList(Cell* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() 
{   
    setlocale(0, "");
    Cell* head = NULL;
    int num;

    printf("������� ����� ����� ������ (��� ���������� ������� ����� ������ ����� ����):\n");
    // ��������� ����� � ��������� �� � ������
    while (scanf("%d", &num) == 1)
        insert(&head, num);

    rearrangeList(&head);
    // ������� ��������� ������
    printf("�������������� ������:\n"); 
    printList(head);
    return 0;
}