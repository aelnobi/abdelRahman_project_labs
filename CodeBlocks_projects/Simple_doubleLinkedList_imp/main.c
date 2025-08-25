#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;
typedef struct Node Node;


struct Node
{
    int data;
    Node* next,*prev;
};

struct LinkedList
{
    Node* Head,* Tail;
};

LinkedList* CreateLinkedList()
{
    LinkedList* lst = (LinkedList*)malloc(sizeof(LinkedList));
    lst->Head = lst->Tail = NULL;
    return lst;
}



Node* CreateNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = node->prev = NULL;
    return node ;

}
void AddFromLast(LinkedList* lst, int data)
{
    Node* newNode = CreateNode(data);
    if(lst->Head == NULL)
        {
            lst->Head = lst->Tail = newNode;
        }
    else
        {
            lst->Tail->next = newNode;
            newNode->prev = lst->Tail;
            lst->Tail = lst->Tail->next;
        }

}
void AddFromFirst(LinkedList* lst, int data)
{
    Node* newNode = CreateNode(data);
    if(lst->Head == NULL){
        lst->Head = lst->Tail = newNode;
        }
    else
        {
            lst->Head->prev = newNode;
            newNode->next = lst->Head;
            lst->Head = lst->Head->prev;
        }


}
Node* GetDataByNode(LinkedList* lst, int data)
{
    Node* getNode = lst->Head;
    while(getNode!=NULL)
        {
            if(getNode->data == data)
                return getNode;
            getNode = getNode->next;
        }
    return NULL;
}

void Remove(LinkedList* lst, int data)
{
    Node* deleted = GetDataByNode(lst,data);
    if(deleted == NULL)
        return;
    else if(deleted == lst->Head)
        {
              lst->Head = deleted->next;
              if(lst->Head)lst->Head->prev=NULL;
              else lst->Tail=NULL;


        }
    else if (deleted == lst->Tail)
        {

             lst->Tail = deleted->prev;
             if(lst->Tail)lst->Tail->next = NULL;
             else lst->Head = NULL;
        }
    else
        {
            deleted->prev->next = deleted->next;
            deleted->next->prev = deleted->prev;
        }
    free(deleted);
}



void Display(LinkedList* lst)
{
    Node* display = lst->Head;
    while(display!=NULL)
        {
            printf("%d ",display->data);
            display = display->next;
        }
    printf("\n");
}



int main()
{
    LinkedList* myLst = CreateLinkedList();
    AddFromLast(myLst,5);
    AddFromLast(myLst,6);
    AddFromLast(myLst,7);
    AddFromLast(myLst,8);
    Display(myLst);
    AddFromFirst(myLst,10);
    Display(myLst);
//    Remove(myLst,6);
//    Display(myLst);


    return 0;
}
