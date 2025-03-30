#include "linkedlist.h"

// Function to create a new linked list
LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

// Function to create a collection of linked lists
LinkedListCollection* createCollection(int count) {
    LinkedListCollection* collection = (LinkedListCollection*)malloc(sizeof(LinkedListCollection));
    collection->count = count;
    collection->lists = (LinkedList**)malloc(count * sizeof(LinkedList*));
    for (int i = 0; i < count; i++) {
        collection->lists[i] = createList();
    }
    return collection;
}

// Function to push a character onto the list
void push(LinkedList* list, Character* character) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->next = list->head;
    list->head = newNode;
}

// Function to pop a character from the list
Character pop(LinkedList* list, Character* character) {
    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->character == character) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Removed character");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Character not found with state");
}

// Function to pop a character from the list
int isCharacterInList(LinkedList* list, Character* character) {
    if (isListEmptyOrDNE(list)) {
        return 0;
    }

    Node* current = list->head;
    Node* prev = NULL;
    
    while (current != NULL) {
        if (current->character == character) {
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    return 0;
}

int isListEmptyOrDNE(LinkedList* list) {
    return (list == NULL || list->head == NULL);
}
