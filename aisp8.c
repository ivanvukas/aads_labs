#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

typedef struct numbers* position;
typedef struct numbers
{
    int val;
    position next;
} numbers;

int popStack(position head);
int readFromFile(position head);
int pushStack(position head, int result);

int main()
{
    position head = (position)malloc(sizeof(numbers));
    if (head == NULL)
    {
        printf("Neuspjela alokacija.\n");
        return 1;
    }
    head->next = NULL;

    if (readFromFile(head) != 0)
    {
        free(head);
        return 1;
    }

    free(head);
    return 0;
}


int readFromFile(position head)
{
    FILE* fp = fopen("postfiks.txt", "r");
    if (fp == NULL)
    {
        printf("Datoteka nije otvorena.\n");
        return 1;
    }

    char op;
    int val1, val2;

    while (fscanf(fp, " %c", &op) == 1)
    {
        if (isdigit(op))
        {
            int result = op - '0';

            if (pushStack(head, result) != 0)
            {
                fclose(fp);
                freeStack(head);
                return 1;
            }
        }
        else
        {
            val1 = popStack(head);
            val2 = popStack(head);

            if (val1 == INT_MIN || val2 == INT_MIN)
            {
                printf("Previse operanada.\n");
                fclose(fp);
                freeStack(head);
                return 1;
            }

            int result;

            switch (op)
            {
            case '+':
                result = val2 + val1;
                break;

            case '-':
                result = val2 - val1;
                break;

            case '*':
                result = val2 * val1;
                break;

            case '/':
                if (val1 == 0)
                {
                    printf("Dijeljenje s nulom.\n");
                    fclose(fp);
                    freeStack(head);
                    return 1;
                }
                result = val2 / val1;
                break;

            default:
                printf("Nepoznata operacija: %c\n", op);
                fclose(fp);
                freeStack(head);
                return 1;
            }

            if (pushStack(head, result) != 0)
            {
                fclose(fp);
                freeStack(head);
                return 1;
            }
        }
    }

    fclose(fp);

    if (head->next != NULL && head->next->next == NULL)
    {
        printf("Rezultat: %d\n", head->next->val);
        return 0;
    }

    printf("Greska: neispravan izraz.\n");
    freeStack(head);
    return 1;
}


int pushStack(position head, int result)
{
    position newEle = (position)malloc(sizeof(numbers));
    if (newEle == NULL)
    {
        printf("alokacija nije uspjesna");
        return INT_MIN;
    }

    newEle->next = head->next;
    head->next = newEle;
    newEle->val = result;

    return 0;
}

int popStack(position head)
{
    if (head->next == NULL)
    {
        printf("stack is empty");
        return INT_MIN;
    }

    position temp = head->next;
    head->next = temp->next;
    int tempVal = temp->val;
    free(temp);
    return tempVal;
}