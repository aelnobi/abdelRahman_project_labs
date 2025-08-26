#include <stdio.h>
#include <stdlib.h>

typedef struct Stack Stack;
typedef struct LinkedList LinkedList;

struct Stack
{
    int data;
    Stack* next;
};

struct LinkedList
{
    Stack* top;
};

LinkedList* CreateStack()
{
    LinkedList* stk = (LinkedList* )malloc(sizeof(LinkedList));
    stk->top = NULL;
    return stk;
}

Stack* CreateNode(int data)
{
    Stack* stk = (Stack*)malloc(sizeof(Stack));
    stk->data = data;
    stk->next = NULL;
    return stk;
}


void Push(LinkedList* lst,int data)
{
    Stack* newNode = CreateNode(data);
    if(lst->top == NULL)
        lst->top = newNode;
    else
        {
            newNode->next = lst->top;
            lst->top = newNode;
        }
}


int Pop (LinkedList* lst, int* data)
{
    if(lst->top == NULL)
        return 0;
    Stack* deleted = lst->top;
    *data = deleted->data;
    lst->top = lst->top->next;
    free(deleted);
    return 1;

}
void Display(LinkedList* lst)
{
    Stack* disp = lst->top;
    while(disp!=NULL)
        {
            printf("%d ",disp->data);
            disp = disp->next;
        }
    printf("\n");
}
void Destroy(LinkedList*lst)
{
    Stack* curr = lst->top;
    while(curr!=NULL)
        {
            Stack* next = curr->next;
            free(curr);
            curr = next;
        }
    free(lst);
    printf("Destroy succedded");
}

int main()
{
    LinkedList* lst = CreateStack();
    Push(lst,5);
    Push(lst,6);
    Push(lst,7);
    Display(lst);
    int num;
    if(Pop(lst,&num))
        printf("%d\n",num);
    else
        printf("List is empty");
    Display(lst);
    Destroy(lst);
    return 0;
}
