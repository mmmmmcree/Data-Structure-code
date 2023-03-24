# include<stdio.h>
# include<stdlib.h>
/*
功能：对单向列表进行增删操作时，将单向列表转为链表，对链表进行增删操作，再将链表转为单向列表
作用：简化单向列表增加元素与删除元素的操作，同时保留单向列表查找元素的便利性
*/
# define ERROR 0
# define PASS 1

typedef int ELETYPE;

typedef struct Node
{
    int data;
    struct Node* next;
}LinkList;

typedef struct Array
{
    ELETYPE* arr;
    int length;
}Array;

LinkList array_to_LinkList(ELETYPE *arr, int n){
    LinkList* head = (LinkList*)malloc(sizeof(LinkList));
    head->data = n;
    head->next = NULL;
    LinkList* tail =  NULL;
    for (int i = 0; i < n; i++)
    {
        LinkList* p = (LinkList*)malloc(sizeof(LinkList));
        p->data = arr[i];
        p->next = NULL;
        if (i == 0)
        {
            head->next = p;
            tail = p;
        }
        else
        {
            tail->next = p;
            tail = tail->next;
        }
    }
    return *head;
}

ELETYPE* LinkList_to_array(LinkList head){
    ELETYPE len = head.data;
    ELETYPE *a = (ELETYPE*)malloc(sizeof(ELETYPE) * len);
    for (int i = 0; i < len; i++)
    {
        a[i] = head.next->data;
        head.next = head.next->next;
    }
    return a;
}

int add_element(LinkList *head, int index, ELETYPE element){
    if (index > head->data)
    {
        printf("index out of range");
        return ERROR;
    }
    head->data +=1;
    LinkList* r = head->next;
    for (int i = 0; i < index - 1; i++)
    {
        r = r->next;
    }
    LinkList *p = (LinkList*)malloc(sizeof(LinkList));
    p->next = r->next;
    r->next = p;
    p->data = element;
    return PASS;
}

int delete_element(LinkList *head, int index){
    if (index > head->data)
    {
        printf("index out of range");
        return ERROR;
    }
    head->data -=1;
    LinkList* r = head->next;
    for (int i = 0; i < index - 1; i++)
    {
        r = r->next;
    }
    LinkList *p = r->next;
    r->next = r->next->next;
    free(p);
    return PASS;
}

int change_element(LinkList *head, int index, ELETYPE element){
    if (index > head->data)
    {
        printf("index out of range");
        return ERROR;
    }
    LinkList* r = head->next;
    for (int i = 0; i < index; i++)
    {
        r = r->next;
    }
    r->data = element;
    return PASS;
}

void print_LinkList(LinkList head){
    printf("The length of the LinkList: %d [", head.data);
    while (head.next != NULL)
    {
        if (head.next->next == NULL)
        {
            printf("%d]\n", head.next->data);
            break;
        }
        printf("%d, ", head.next->data);
        head.next = head.next->next;
    }
}

void print_Array(Array a){
    printf("The length of the Array: %d [", a.length);
    for (int i = 0; i < a.length - 1; i++)
    {
        printf("%d, ", a.arr[i]);
    }
    printf("%d]\n", a.arr[a.length - 1]);
}

int add_elment_array(Array *a, int index, ELETYPE element){
    if (index > a->length || index < 0)
    {
        printf("Index out of range!\n");
        return ERROR;
    }
    ELETYPE** p = &a->arr;
    LinkList head = array_to_LinkList(*p, a->length);
    a->length += 1;
    add_element(&head, index, element);
    *p = LinkList_to_array(head);
    return PASS;
}

int delete_elment_array(Array *a, int index){
    if (index > a->length || index < 0)
    {
        printf("Index out of range!\n");
        return ERROR;
    }
    ELETYPE** p = &a->arr;
    LinkList head = array_to_LinkList(*p, a->length);
    a->length -= 1;
    delete_element(&head, index);
    *p = LinkList_to_array(head);
    return PASS;
}

void main(){
    ELETYPE arr[6] = {1, 2, 3, 4, 5, 6};
    Array a = {arr, 6};
    add_elment_array(&a, -11, 699);
    print_Array(a);
    delete_elment_array(&a, 2);
    print_Array(a);
}