#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int PRN;
    char name[50];
    struct Node *next;
};

struct Node *head = NULL, *tail = NULL;

struct Node *createNode(int PRN, char name[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->PRN = PRN;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

void addPresident(int PRN, char name[])
{
    struct Node *newNode = createNode(PRN, name);
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

void addSecretary(int PRN, char name[])
{
    struct Node *newNode = createNode(PRN, name);
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void addMember(int PRN, char name[], int afterPRN)
{
    struct Node *newNode = createNode(PRN, name);
    struct Node *temp = head;
    while (temp != NULL && temp->PRN != afterPRN)
    {
        temp = temp->next;
    }
    if (temp != NULL)
    {
        newNode->next = temp->next;
        temp->next = newNode;
        if (temp == tail)
        {
            tail = newNode;
        }
    }
}

void deletePresident()
{
    if (head != NULL)
    {
        struct Node *temp = head;
        head = head->next;
        if (head == NULL) // List is now empty
            tail = NULL;
        free(temp);
    }
}

void deleteSecretary()
{
    if (head == NULL)
        return;
    
    if (head == tail) // Only one node in the list
    {
        free(head);
        head = tail = NULL;
    }
    else
    {
        struct Node *temp = head;
        while (temp->next != tail)
        {
            temp = temp->next;
        }
        free(tail);
        tail = temp;
        tail->next = NULL;
    }
}

void deleteMember(int PRN)
{
    if (head == NULL)
        return;

    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp != NULL && temp->PRN != PRN)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL)
    {
        if (prev != NULL)
        {
            prev->next = temp->next;
            if (temp == tail) // Update tail if deleting the last node
                tail = prev;
        }
        else
        {
            head = temp->next;
            if (head == NULL) // List is now empty
                tail = NULL;
        }
        free(temp);
    }
}

void display()
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("PRN: %d, Name: %s\n", temp->PRN, temp->name);
        temp = temp->next;
    }
}

int countMembers()
{
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void reverse()
{
    struct Node *prev = NULL, *current = head, *next = NULL;
    tail = head; // Update tail to the current head
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

int main()
{
    addPresident(1, "John");
    addMember(2, "Alice", 1);
    addMember(3, "Bob", 2);
    addSecretary(4, "Charlie");

    printf("Members of the club:\n");
    display();

    printf("\nTotal members: %d\n", countMembers());

    deletePresident();
    deleteSecretary();

    printf("\nAfter deleting president and secretary:\n");
    display();

    reverse();
    printf("\nAfter reversing the list:\n");
    display();

    return 0;
}
