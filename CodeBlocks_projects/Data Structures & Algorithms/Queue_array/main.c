#include <stdio.h>
#include <stdlib.h>

typedef struct Queue Queue;

struct Queue
{
    int front,rear,size;
    int* arr;
};
Queue* CreateQueue(int size)
{
    Queue* que = (Queue*)malloc(sizeof(Queue));
    que->front = que->rear = -1;
    que->size = size;
    que->arr = (int*)malloc(sizeof(int)*size);
    return que;
}

int IsFull(Queue* que)
{
    return que->front == ((que->rear+1) % que->size);
}


int IsEmpty(Queue* que)
{
    return (que->front) == -1;
}
void Enqueue(Queue* que,int data)
{
    if(!que || IsFull(que))
        return ;
    if(que->front == -1)
        que->front = 0;
    que->rear = (que->rear+1) % que->size;
    que->arr[que->rear] = data;
}
int Dequeue (Queue* que, int * data)
{
    if(!que || IsEmpty(que))
        return 0;
    *data = que->arr[que->front];
    if(que->front == que->rear)
        {
            que->front = que->rear =  -1;
        }
    else
        {
            que->front = (que->front+1) % que->size;
        }
    return 1;
}
void Display(Queue* que)
{
    if (!que || que->front == -1) {
        printf("Queue is empty\n");
        return;
    }

    int index = que->front;
    while (1) {
        printf("%d ", que->arr[index]);
        if (index == que->rear)
            break;
        index = (index + 1) % que->size;
    }
    printf("\n");
}


int main()
{
    Queue* myQue = CreateQueue(6);
    Enqueue(myQue,4);
    Enqueue(myQue,6);
    Enqueue(myQue,7);
    Enqueue(myQue,8);
    Enqueue(myQue,9);
    Enqueue(myQue,10);
    Display(myQue);
    int pop;
    if(Dequeue(myQue,&pop))
        printf("Popped data is %d\n ",pop);
    else
        printf("\nQueue is Empty");
    Display(myQue);
    return 0;
}
