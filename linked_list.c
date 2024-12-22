#include <stdio.h>
#include <stdlib.h>

// Node structure for Singly Linked List
typedef struct SinglyNode {
    int data;
    struct SinglyNode* next;
} SinglyNode;

// Node structure for Doubly Linked List
typedef struct DoublyNode {
    int data;
    struct DoublyNode* prev;
    struct DoublyNode* next;
} DoublyNode;

// Node structure for Circular Linked List
typedef struct CircularNode {
    int data;
    struct CircularNode* next;
} CircularNode;

// Functions for Singly Linked List
SinglyNode* insertSingly(SinglyNode* head, int data) {
    SinglyNode* newNode = (SinglyNode*)malloc(sizeof(SinglyNode));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

void displaySingly(SinglyNode* head) {
    SinglyNode* temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

SinglyNode* deleteSingly(SinglyNode* head, int key) {
    if (!head) return NULL;
    if (head->data == key) {
        SinglyNode* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    SinglyNode* current = head;
    while (current->next && current->next->data != key)
        current = current->next;
    if (current->next) {
        SinglyNode* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    return head;
}

// Functions for Doubly Linked List
DoublyNode* insertDoubly(DoublyNode* head, int data) {
    DoublyNode* newNode = (DoublyNode*)malloc(sizeof(DoublyNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = head;
    if (head) head->prev = newNode;
    return newNode;
}

void displayDoubly(DoublyNode* head) {
    DoublyNode* temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

DoublyNode* deleteDoubly(DoublyNode* head, int key) {
    if (!head) return NULL;
    if (head->data == key) {
        DoublyNode* temp = head;
        head = head->next;
        if (head) head->prev = NULL;
        free(temp);
        return head;
    }
    DoublyNode* current = head;
    while (current && current->data != key)
        current = current->next;
    if (current) {
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        free(current);
    }
    return head;
}

// Functions for Circular Linked List
CircularNode* insertCircular(CircularNode* tail, int data) {
    CircularNode* newNode = (CircularNode*)malloc(sizeof(CircularNode));
    newNode->data = data;
    if (!tail) {
        newNode->next = newNode;
        return newNode;
    }
    newNode->next = tail->next;
    tail->next = newNode;
    return newNode;
}

void displayCircular(CircularNode* tail) {
    if (!tail) return;
    CircularNode* temp = tail->next;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != tail->next);
    printf("(back to start)\n");
}

CircularNode* deleteCircular(CircularNode* tail, int key) {
    if (!tail) return NULL;
    CircularNode* current = tail->next;
    CircularNode* prev = tail;
    do {
        if (current->data == key) {
            if (current == tail && current->next == tail) {
                free(current);
                return NULL;
            }
            if (current == tail) tail = prev;
            prev->next = current->next;
            free(current);
            return tail;
        }
        prev = current;
        current = current->next;
    } while (current != tail->next);
    return tail;
}

// Additional utility functions to fill lines
void searchSingly(SinglyNode* head, int key) {
    int position = 0;
    SinglyNode* temp = head;
    while (temp) {
        if (temp->data == key) {
            printf("Key %d found at position %d in Singly Linked List\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Key %d not found in Singly Linked List\n", key);
}

void searchDoubly(DoublyNode* head, int key) {
    int position = 0;
    DoublyNode* temp = head;
    while (temp) {
        if (temp->data == key) {
            printf("Key %d found at position %d in Doubly Linked List\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Key %d not found in Doubly Linked List\n", key);
}

void searchCircular(CircularNode* tail, int key) {
    if (!tail) {
        printf("Circular Linked List is empty\n");
        return;
    }
    int position = 0;
    CircularNode* temp = tail->next;
    do {
        if (temp->data == key) {
            printf("Key %d found at position %d in Circular Linked List\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    } while (temp != tail->next);
    printf("Key %d not found in Circular Linked List\n", key);
}

void reverseSingly(SinglyNode** head) {
    SinglyNode *prev = NULL, *current = *head, *next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void reverseDoubly(DoublyNode** head) {
    DoublyNode *temp = NULL, *current = *head;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp) *head = temp->prev;
}

int main() {
    // Singly Linked List Operations
    SinglyNode* singlyHead = NULL;
    printf("Singly Linked List:\n");
    singlyHead = insertSingly(singlyHead, 10);
    singlyHead = insertSingly(singlyHead, 20);
    singlyHead = insertSingly(singlyHead, 30);
    displaySingly(singlyHead);
    searchSingly(singlyHead, 20);
    reverseSingly(&singlyHead);
    printf("Reversed: ");
    displaySingly(singlyHead);
    singlyHead = deleteSingly(singlyHead, 20);
    displaySingly(singlyHead);

    // Doubly Linked List Operations
    DoublyNode* doublyHead = NULL;
    printf("\nDoubly Linked List:\n");
    doublyHead = insertDoubly(doublyHead, 10);
    doublyHead = insertDoubly(doublyHead, 20);
    doublyHead = insertDoubly(doublyHead, 30);
    displayDoubly(doublyHead);
    searchDoubly(doublyHead, 20);
    reverseDoubly(&doublyHead);
    printf("Reversed: ");
    displayDoubly(doublyHead);
    doublyHead = deleteDoubly(doublyHead, 20);
    displayDoubly(doublyHead);

    // Circular Linked List Operations
    CircularNode* circularTail = NULL;
    printf("\nCircular Linked List:\n");
    circularTail = insertCircular(circularTail, 10);
    circularTail = insertCircular(circularTail, 20);
    circularTail = insertCircular(circularTail, 30);
    displayCircular(circularTail);
    searchCircular(circularTail, 20);
    circularTail = deleteCircular(circularTail, 20);
    displayCircular(circularTail);

    return 0;
}
