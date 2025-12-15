#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define UPPER_LIMIT 100
#define LOWER_LIMIT 10

typedef struct numbers* position;
typedef struct numbers
{

    int ele;
    int priority;
    position next;
} numbers;

int pushStack(position head, int stackLen, int* counter);
int popStack(position head, int* counter);
int queuePush(position head);
int queuePop(position head);
int printList(position head);
int freeMemory(position head);

int main()
{
    srand(time(NULL));

    position head1 = (position)malloc(sizeof(numbers));
    if (head1 == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head1->next = NULL;

    position head2 = (position)malloc(sizeof(numbers));
    if (head2 == NULL)
    {
        printf("Memory allocation failed.\n");
        freeMemory(head1);
        return 1;
    }
    head2->next = NULL;

    int x;
    int stackLen = 0;
    printf("Unesite velicinu stoga:\n ");
    scanf("%d", &stackLen);
    int counter = 0;

    while (x != 0)
    {
        printf("Enter: \n 1) for pushing a number to stack: \n 2) for popping a number of stack \n 3) for pushing a number to queue \n 4) for popping a number from queue \n 5) for printing stack \n 6 for printing queue \n 0 for exting the program\n");
        scanf("%d", &x);

        int result;

        switch (x)
        {
        case 1:
            result = pushStack(head1, stackLen, &counter);
            break;

        case 2:
            result = popStack(head1, &counter);
            break;

        case 3:
            result = queuePush(head2);
            break;

        case 4:
            result = queuePop(head2);
            break;

        case 5:
            printList(head1);
            break;

        case 6:
            printList(head2);
            break;
        }
        if (result == 1)
        {
            printf("There was an ERROR!\n");
            freeMemory(head1);
            freeMemory(head2);
            return 1;
        }
    }

    freeMemory(head1);
    freeMemory(head2);

    return 0;
}

int pushStack(position head, int stackLen, int* counter)
{
    position newEle = (position)malloc(sizeof(numbers));
    if (newEle == NULL)
    {
        printf("alokacija nije uspjesna");
        return 1;
    }

    if (*counter >= stackLen)
    {
        printf("stack is full!!!");
        free(newEle);
        return 0;
    }

    int num = rand() % (UPPER_LIMIT + 1 - LOWER_LIMIT) + LOWER_LIMIT;

    newEle->next = head->next;
    head->next = newEle;
    newEle->ele = num;
    (*counter)++;

    return 0;
}

int popStack(position head, int* counter)
{
    if (head->next == NULL)
    {
        printf("stack is empty");
        return 1;
    }

    position temp = head->next;
    head->next = temp->next;
    free(temp);
    (*counter)--;
    return 0;
}

int queuePush(position head)
{
    position newEle = (position)malloc(sizeof(numbers));
    if (newEle == NULL)
    {
        printf("alokacija nije uspjesna");
        return 1;
    }
    int prio = rand() % (5 + 1 - 1) + 1;
    int num = rand() % (UPPER_LIMIT + LOWER_LIMIT - 1) + LOWER_LIMIT;
    if (head->next == NULL) {
        newEle->next = NULL;
        head->next = newEle;
        return 0;
    }
    newEle->ele = num;
    newEle->priority = prio;
    position previous = head;
    while (previous->next != NULL && previous->next->priority >= newEle->priority)
    {
        previous = previous->next;
    }
    newEle->next = previous->next;
    previous->next = newEle;

    return 0;
}

int queuePop(position head)
{
    if (head->next == NULL)
    {
        printf("Queue is empty\n");
        return 1;
    }

    position temp = head->next;
    head->next = temp->next;
    free(temp);
    return 0;
}

int printList(position head)
{
    if (head->next == NULL)
    {
        printf("the list is empty!");
        return 1;
    }

    position p = head->next;
    while (p != NULL)
    {
        printf("value: %d, priority: %d ", p->ele, p->priority);
        p = p->next;
    }

    printf("\n");
    return 0;
}

int freeMemory(position head)
{
    position p = head->next;
    while (p != NULL)
    {
        position temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
    return 0;
}