#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node* pNext;
}node;

node* createNode(int value)
{
    node* newNode = (node*)malloc(sizeof(node));

    newNode->value = value;
    newNode->pNext = NULL;

    return newNode;
}

void push_front(node **array, int value)
{
    node* newNode = NULL;

    newNode = createNode(value); 
    if (*array == NULL)
    {
        *array = newNode;
    }
    else{
        newNode -> pNext = *array; 
        *array = newNode;
    }
}

void push_back(node** array, int value)
{
    node* newNode = NULL;
    node* temp = *array;  

    newNode = createNode(value); 

    if (*array == NULL)  
    {
        *array = newNode;
    }
    else               
    {
        while (temp->pNext != NULL) 
        {
            temp = temp -> pNext;    
        }
        temp->pNext = newNode;    
    }
}

void pop_front(node **array)
{
    node* pDelete = NULL;

    if (*array == NULL)
    {
        printf("No element !!!\n");
    }
    else{
        pDelete = *array;  
        (*array) = (*array) -> pNext;  // 
    }

    free(pDelete);
}

void pop_back(node** array)
{
    node *pTemp = *array;
    node *pDelete = NULL;

    if (pTemp == NULL)
    {
        printf("No element in list!!!\n");
    }
    else if(pTemp -> pNext == NULL)
    {
        pDelete = (*array);
        (*array) = NULL;
    }
    else if (pTemp -> pNext -> pNext != NULL)
    {
        while (pTemp -> pNext -> pNext != NULL)  
        {
            pTemp = pTemp -> pNext;
        }
        pDelete = pTemp -> pNext;
        pTemp ->pNext = NULL;
    }

    free(pDelete);
}

void insert(node **array, int value, int pos)
{
    node* newNode, *pTemp, *pHead;
    int i = 1;

    newNode = createNode(value);
    pTemp = *array;

    if (pos == 0)
    {
        newNode -> pNext = *array;
        *array = newNode;
    }
    else
    {
        while ((pTemp -> pNext != NULL) && (pos != i))
        {
            i ++;
            pTemp = pTemp -> pNext;
        }
        newNode -> pNext = pTemp -> pNext;
        pTemp -> pNext = newNode; 
    }
}

void delete_list(node **array, int pos)
{
    node *pTemp = *array;
    node *pDelete = NULL;
    int i = 0;

    if (pos == 0)
    {
        pDelete = *array;
        *array = (*array)->pNext; 
    }
    else
    {
        while ((pTemp != NULL) && (pos - 1 != (i)))
        {
            i ++;
            pTemp = pTemp -> pNext;
        }

        pDelete = pTemp -> pNext;

        pTemp -> pNext = pDelete -> pNext; 
    }

    free(pDelete);
}



int front(node *array)
{
    return array -> value;
}

int back(node *array)
{
    while(array -> pNext != NULL)
    {
        array = array -> pNext;
    }

    return array -> value;
}



void display_list(node *array)
{
    node *temp = array;
    int i = 0;

    if (temp == NULL)
    {
        printf("No element in list!!!\n");
    }
    
    while (temp != NULL)
    {
        printf("value of index %d : %d\n", i, temp -> value);
        temp = temp ->pNext;
        i ++;
    }
    
}


int get(node* array, int pos)
{
    int i = 0;
 
    while (array->pNext != NULL && pos != i)
    {
        array = array->pNext;
        i++;
    }

    if (pos != i)
    {
        printf("Error: List has less element\n");
        return 0;
    }

    int value = array->value;
    return value;
}


int size(node *array)
{
    int i = 0; 

    while (array != NULL)
    {
        i++;
        array = array->pNext;
    }

    return i;
}



bool empty(node *array)
{
    bool bitVal = false;

    if (array == NULL)
    {
        bitVal = true;
    }
    else
    {
        bitVal = false;
    }
    
    return bitVal;
}



int main()
{
    node* list = NULL;

    push_back(&list, 2);  /* 2 */

    push_back(&list, 7);  /* 2, 7 */

    push_front(&list, 3); /* 3, 2, 7*/

    push_front(&list, 5); /* 5, 3, 2, 7*/

    pop_front(&list);
    insert(&list, 12, 2); /* 5, 3, 12, 2, 7*/

    delete_list(&list, 0); /*3, 12, 2, 7*/
    delete_list(&list, 2); /*3, 12, 7*/
    printf("Size of list: %d\n", size(list));

    display_list(list);

    printf("\n");
    printf("Value of index 2: %d\n", get(list, 2));
    printf("Value of index 3: %d\n", get(list, 3));

	return 0;
}


