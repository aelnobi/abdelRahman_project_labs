#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode QueueNode;
typedef struct LinkedList LinkedList;


struct QueueNode
{
    int data;
    QueueNode* next;
};
struct LinkedList
{
    QueueNode* front,*rear;
};

LinkedList* CreateQueue()
{
    LinkedList* lst = (LinkedList*)malloc(sizeof(LinkedList));
    lst->front = lst->rear = NULL;
    return lst;
}

QueueNode* CreateNode(int data)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void EnQueue(LinkedList* lst,int data)
{
    if(!lst)
        return;
    QueueNode* newNode = CreateNode(data);
    if(lst->front == NULL)
        {
            lst->front = lst->rear = newNode;
        }
    else{
            lst->rear->next = newNode;
            newNode->next = lst->front;
            lst->rear = newNode;
        }
}
int IsEmpty(LinkedList* lst)
{
    return (lst->front == NULL);
}
int Dequeue(LinkedList* lst, int* data)
{
    if(!lst || IsEmpty(lst))
        return 0;
    QueueNode* deleted = lst->front;
    * data = lst->front->data;
    lst->front = lst->front->next;
    if(lst->front)
        lst->rear->next = lst->front;
    else
        lst->rear = NULL;
    free(deleted);
    return 1;

}
void Peek(LinkedList* lst)
{
    if(!lst || lst->front == NULL){
        printf("No Peek \n");
        return;}
    printf("\nPeek is %d \n",lst->front->data);

}
void Display(LinkedList* lst)
{
    if(!lst || lst->front == NULL){
        printf("List is empty");
        return;}
    QueueNode* disp = lst->front;
    do{
            printf("%d ",disp->data);
            disp = disp->next;
        }while(disp != lst->front);
    printf("\n");
}


int main()
{
    LinkedList* myLst = CreateQueue();
    EnQueue(myLst,5);
    EnQueue(myLst,6);
    EnQueue(myLst,7);
    EnQueue(myLst,8);
    EnQueue(myLst,9);
    Display(myLst);
    int data;
    if(Dequeue(myLst,&data))
        printf("Popped data is %d",data);
    else
        printf("List is empty");
    Peek(myLst);
    Display(myLst);
    return 0;
}
