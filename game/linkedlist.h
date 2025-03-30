#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include "movementhandler.h"

#define STRINGIZE_THIS(var) #var

typedef struct Node {
    Character* character;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

typedef struct {
    LinkedList** lists;
    int count;
} LinkedListCollection;

LinkedList* createList();

LinkedListCollection* createCollection(int count);

void push(LinkedList* list, Character* character);

Character pop(LinkedList* list, Character* character);

int isListEmptyOrDNE(LinkedList* list);

int isCharacterInList(LinkedList* list, Character* character);

#endif // LINKEDLIST_H