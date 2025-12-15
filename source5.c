#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct numbers* position;
typedef struct numbers
{
    int el;
    position next;
} numbers;

int createList(position head);
int printList(position head);
int intersection(position head1, position head2, position result);
int Union(position head1, position head2, position result);
int freeMemory(position head);

int main()
{
    position head1 = (position)malloc(sizeof(numbers));
    if (head1 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head1->next = NULL;

    position head2 = (position)malloc(sizeof(numbers));
    if (head2 == NULL) {
        printf("Memory allocation failed.\n");
        free(head1);
        return 1;
    }
    head2->next = NULL;

    position head3Union = (position)malloc(sizeof(numbers));
    if (head3Union == NULL) {
        printf("Memory allocation failed.\n");
        free(head1);
        free(head2);
        return 1;
    }
    head3Union->next = NULL;

    position head3Intersection = (position)malloc(sizeof(numbers));
    if (head3Intersection == NULL) {
        printf("Memory allocation failed.\n");
        free(head1);
        free(head2);
        free(head3Union);
        return 1;
    }
    head3Intersection->next = NULL;

    if (createList(head1) != 0) {
        printf("Error creating first list\n");
        freeMemory(head1);
        freeMemory(head2);
        freeMemory(head3Union);
        freeMemory(head3Intersection);
        return 1;
    }

    if (createList(head2) != 0) {
        printf("Error creating second list\n");
        freeMemory(head1);
        freeMemory(head2);
        freeMemory(head3Union);
        freeMemory(head3Intersection);
        return 1;
    }

    printf("First list: ");
    printList(head1);
    printf("Second list: ");
    printList(head2);

    if (Union(head1, head2, head3Union) != 0) {
        printf("Error creating union\n");
        freeMemory(head1);
        freeMemory(head2);
        freeMemory(head3Union);
        freeMemory(head3Intersection);
        return 1;
    }

    if (intersection(head1, head2, head3Intersection) != 0) {
        printf("Error creating intersection\n");
        freeMemory(head1);
        freeMemory(head2);
        freeMemory(head3Union);
        freeMemory(head3Intersection);
        return 1;
    }

    printf("Union of lists: ");
    printList(head3Union);
    printf("Intersection of lists: ");
    printList(head3Intersection);

    freeMemory(head1);
    freeMemory(head2);
    freeMemory(head3Union);
    freeMemory(head3Intersection);

    return 0;
}

int createList(position head)
{
    char filename[20];
    printf("Enter file name: ");
    scanf(" %s", filename);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return 2;
    }

    int num;
    position current = head;

    while (fscanf(fp, " %d", &num) == 1)
    {
        position newList = (position)malloc(sizeof(numbers));
        if (newList == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(fp);
            return 1;
        }
        newList->el = num;

        while (current->next != NULL && current->next->el < num)
        {
            current = current->next;
        }

        newList->next = current->next;
        current->next = newList;
        current = head;
    }
    fclose(fp);
    return 0;
}

int printList(position head)
{
    if (head->next == NULL)
    {
        printf("List is empty!\n");
        return 1;
    }
    head = head->next;
    while (head != NULL)
    {
        printf("%d ", head->el);
        head = head->next;
    }
    printf("\n");
    return 0;
}

int intersection(position head1, position head2, position result)
{
    position current1 = head1->next;
    position current2 = head2->next;
    position currentResult = result;

    while (current1 != NULL && current2 != NULL)
    {
        if (current1->el == current2->el)
        {
            position newNode = (position)malloc(sizeof(numbers));
            if (newNode == NULL)
            {
                return 1;
            }
            newNode->el = current1->el;
            newNode->next = NULL;

            currentResult->next = newNode;
            currentResult = newNode;

            current1 = current1->next;
            current2 = current2->next;
        }
        else if (current1->el < current2->el)
        {
            current1 = current1->next;
        }
        else
        {
            current2 = current2->next;
        }
    }
    return 0;
}

int Union(position head1, position head2, position result)
{
    position current1 = head1->next;
    position current2 = head2->next;
    position currentResult = result;

    while (current1 != NULL && current2 != NULL)
    {
        position newNode = (position)malloc(sizeof(numbers));
        if (newNode == NULL)
        {
            return 1;
        }
        if (current1->el == current2->el)
        {
            newNode->el = current1->el;
            newNode->next = NULL;
            current1 = current1->next;
            current2 = current2->next;
        }
        else if (current1->el > current2->el)
        {
            newNode->el = current2->el;
            newNode->next = NULL;
            current2 = current2->next;
        }
        else
        {
            newNode->el = current1->el;
            newNode->next = NULL;
            current1 = current1->next;
        }
        currentResult->next = newNode;
        currentResult = newNode;
    }

    while (current1 != NULL) {
        position newNode = (position)malloc(sizeof(numbers));
        if (newNode == NULL) {
            return 1;
        }
        newNode->el = current1->el;
        newNode->next = NULL;
        currentResult->next = newNode;
        currentResult = newNode;
        current1 = current1->next;
    }

    while (current2 != NULL) {
        position newNode = (position)malloc(sizeof(numbers));
        if (newNode == NULL) {
            return 1;
        }
        newNode->el = current2->el;
        newNode->next = NULL;
        currentResult->next = newNode;
        currentResult = newNode;
        current2 = current2->next;
    }
    return 0;
}

int freeMemory(position head)
{
    position temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}