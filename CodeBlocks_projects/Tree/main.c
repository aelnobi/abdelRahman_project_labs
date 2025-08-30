#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
typedef struct Tree Tree;
typedef struct Stack Stack;
typedef struct StackNode StackNode;

struct Tree
{
    Node* root;
};
struct Node
{
    int data;
    Node* Left,* Right;
    int visited; // For the Display function optional to be used

};
struct StackNode
{
    Node* treeNode;
    StackNode* next;
};

struct Stack
{
    StackNode* top;
};

int IsEmpty(Stack* stk)
{
    return stk->top == NULL;

}

Stack* CreateStack()
{
    Stack* stk = (Stack*)malloc(sizeof(Stack));
    stk->top = NULL;
    return stk;
}

void Push(Stack* stk,Node* node)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->treeNode = node;
    newNode->next = stk->top;
    stk->top = newNode;
}
int Pop(Stack* stk, Node** outNode)
{
    if (IsEmpty(stk))
        return 0;

    StackNode* temp = stk->top;
    *outNode = temp->treeNode;
    stk->top = temp->next;
    free(temp);
    return 1;
}






Tree* CreateTree()
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

Node* CreateNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->Left = node->Right = NULL;
    return node;
}

void Add(Tree* tree,int data)
{
    Node* node = CreateNode(data);
    if(tree->root == NULL)
    {
        tree->root = node;
    }
    else
    {
        Node* current = tree->root;
        Node* parent = current;
        while(current!=NULL)
        {
            parent = current;
            if(data > current->data)
            {
                current = current->Right;
            }
            else
            {
                current = current->Left;
            }

        }
        if(data>parent->data)
            parent->Right = node;
        else
            parent->Left = node;
    }
}
Node* GetNodeByData(Tree* tree,int data)
{
    Node* current = tree->root;
    if(current == NULL)
        return NULL;
    else
    {
        while(current!=NULL)
        {
            if(current->data == data)
                return current;
            else if(current->data >=data)
                current = current->Left;
            else
                current = current->Right;
        }
    }
    return NULL;

}

Node* GetParent(Tree* tree, Node* node)
{
    Node* parent = tree->root;
    while(parent!=NULL)
    {
        if(parent->Left == node || parent->Right == node)
            return parent;
        if(parent->data > node->Left)
            parent = parent->Left;
        else
            parent = parent->Right;

    }
    return NULL;
}
 /*Implementation 1*/
//Node* GetMaxRight(Tree* tree, Node* node)
//{
//    if(tree->root == NULL)
//        return NULL;
//    Node* maxRight = node;
//    while(maxRight!=NULL)
//    {
//        if(maxRight->Right == NULL)
//            return maxRight;
//        maxRight = maxRight->Right;
//    }
//    return NULL;
//}

/*Implementation 2*/
Node* GetMaxRight(Tree* tree, Node* node)
{
    Node* current = tree->root;
    while(current->Right != NULL)
        current = current->Right;
    return current;
}

void Remove(Tree* tree, int data)
{
    Node* node = GetNodeByData(tree,data);

    if(node == NULL)
        return ;
    if(node == tree->root)
    {
        if(tree->root->Left == NULL && tree->root->Right == NULL)
        {
            tree->root = NULL;
        }
        else if(tree->root->Right == NULL)
        {
            tree->root = tree->root->Left;
        }
        else if (tree->root->Left == NULL)
        {
            tree->root = tree->root->Right;
        }
        else
        {
            Node* newRoot = tree->root->Left;
            Node* maxRight = GetMaxRight(tree,newRoot);
            maxRight->Right = tree->root->Right;
            tree->root = newRoot;
        }
    }
//    else
//    {
//        Node* parent = GetParent(tree,node);
//        if(node->Left == NULL && node->Right == NULL)
//            {
//                if(parent->Right == node)
//                    {
//                        parent->Right = NULL;
//                    }
//                else if(parent->Left == node)
//                    {
//                         parent->Left = NULL;
//                    }
//            }
//        else if (node->Right == NULL)
//            {
//                if(parent->Left == node){parent->Left = node->Left;}
//                else if(parent->Right == node){parent->Right = node->Left;}
//            }
//        else if (node->Left == NULL)
//            {
//                if(parent->Left == node){parent->Left = node->Right;}
//                else if(parent->Right == node){parent->Right = node->Right;}
//            }
//        else
//        {
//                /*First implementation*/
//                Node* newParent = node->Left;
//                Node* maxRight = GetMaxRight(parent);
//                maxRight->Right = node->Right;
//
//                if(parent->Left == node){parent->Left = newParent;}
//                else if(parent->Right == node){parent->Right = newParent;}
//
//        }
//    }
else
    {
        Node* parent = GetParent(tree,node);
        Node* newChild;
        if(node->Left == NULL && node->Right == NULL)
            {
                newChild = NULL;
            }
        else if (node->Right == NULL)
            {
                newChild = node->Left;
            }
        else if (node->Left == NULL)
            {
                newChild = node->Right;
            }
        else
        {
                /*First implementation*/
                Node* newParent = node->Left;
                Node* maxRight = GetMaxRight(tree,newparent);
                maxRight->Right = node->Right;

                newChild = newParent;

        }
                if(parent->Left == node){parent->Left = newChild;}
                else if(parent->Right == node){parent->Right = newChild;}
    }
}



//}Node* GetMaxRight(Tree* tree, Node* node) // Another Implementation
//{
//    if(tree->root == NULL)
//        return NULL;
//    Node* maxRight = node;
//    while(maxRight!=NULL){
//        if(maxRight->Right == NULL)
//            return maxRight;
//        maxRight = maxRight->Right;
//        }
//    return NULL;
//}

/*Recursion could be solved either using loop , or loop with Stack when i dont know how much nesting do i hacve*/

 /*Using Recurssion */
//void Display(Node* node)
//{
//    if(node == NULL)
//        return ;
//    Display(node->Left);
//    printf("%d ",node->data);
//    Display(node->Right);
//}

void Display(Node* root)
{
    Stack* stk =  CreateStack();
    Node* current = root;
    while(current != NULL || !IsEmpty(stk))
        {
            // Traverse left subTree
            while(current!=NULL)
                {
                    Push(stk,current);
                    current = current->Left;
                }
            // Pop and process
            Node* node;
            Pop(stk,&node);
            printf("%d ",node->data);
            current = node->Right;
        }
    // Clean up stack

};

int GetMaxDepth(Tree* tree); // i,e root is level 1 , after then level 2 ,3 --- The biggest path in the tree


int main()
{
    Tree* tree = CreateTree();
    Add(tree,50);
    Add(tree,40);
    Add(tree,45);
    Add(tree,60);
    Add(tree,30);
    Add(tree,70);
    Display(tree->root);
    return 0;
}
