//
//  main.c
//  removeUntil()
//
//  Created by Brandon Chen on 30/3/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

//CX1007 Data Structures
//Week 11 Solutions (Stack and Queques)

////////////////////////////////////////////////////////////

//#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>

//////////////////////////////////   linked list //////////////////////////////////////////////

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
    int size;
    ListNode *head;
    ListNode *tail;
} LinkedList;

////////////////////////////////// stack    //////////////////////////////////////////////

typedef struct stack{
    LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////

typedef struct _queue{
    LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////
void printList(ListNode *head);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);



//////////////////////////////////////////////////

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);



//////////////////////////////////////////////////

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////////////

void removeUntil(Stack *s, int value);

//////////////////////////////////////////////////////////////////
/////

int main()
{
    
    Stack s;
    s.ll.head=NULL;
    s.ll.size=0;
    int item;
    
    printf("Enter a list of numbers for a stack, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        push(&s, item);
    scanf("%*s");
    printf("\nBefore removeUntil() is called:\n");
    printList(s.ll.head);
    
    printf("Enter an integer value for removeUntil()\n");
    scanf("%d",&item);
    removeUntil(&s,item);
    printf("\nAfter removeUntil() was called:\n");
    printList(s.ll.head);
    
    //free dynamic memory is omitted here!
    return 0;
    
}



////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
    insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
    int item;
    
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
}

int peek(Stack *s){
    return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
    if ((s->ll).size == 0)
        return 1;
    return 0;
}


////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item){
    insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
    int item;
    item = ((q->ll).head)->item;
    removeNode(&(q->ll), 0);
    return item;
}

int isEmptyQueue(Queue *q){
    if ((q->ll).size == 0)
        return 1;
    return 0;
}



////////////////////////////////////////////////////////////////////////////////

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}


ListNode * findNode(LinkedList *ll, int index){
    
    ListNode *temp;
    
    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;
    
    temp = ll->head;
    
    if (temp == NULL || index < 0)
        return NULL;
    
    while (index > 0){
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }
    
    return temp;
}

int insertNode(LinkedList *ll, int index, int value){
    
    ListNode *pre, *cur;
    
    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;
    
    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->tail = ll->head;
        ll->head->item = value;
        ll->head->next = cur;
        ll->size++;
        return 0;
    }
    
    // Inserting as new last node
    if (index == ll->size){
        pre = ll->tail;
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        ll->tail = pre->next;
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }
    
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(ll, index-1)) != NULL){
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        
        if (index == ll->size)
            ll->tail = pre->next;
        
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }
    
    return -1;
}

int removeNode(LinkedList *ll, int index){
    
    ListNode *pre, *cur;
    
    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;
    
    // If removing first node, need to update head pointer
    if (index == 0){
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--;
        
        if (ll->size == 0)
            ll->tail = 0;
        
        return 0;
    }
    
    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(ll, index-1)) != NULL){
        
        // Removing the last node, update the tail pointer
        if (index == ll->size - 1){
            ll->tail = pre;
            free(pre->next);
            pre->next = NULL;
        }
        else{
            cur = pre->next->next;
            free(pre->next);
            pre->next = cur;
        }
        ll->size--;
        return 0;
    }
    
    return -1;
}





////////////////////////////////////////////////////////////////
//Question 1

void removeUntil(Stack *s, int value){
    while ((s->ll).head->item != value) {
        if ((s->ll).head->next == NULL)
            break;
        pop(s);
    }
}

