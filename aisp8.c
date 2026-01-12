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
    if (readFromFile(head) != 0)
    {
        free(head);
        return 1;
    }
    return 0;
}

int readFromFile(position head)
{
    FILE* fp;

    fp = fopen("postfiks.txt", "r");

    if (fp == NULL)
    {
        printf("datoteka je prazna");
        return 1;
    }
    char op;
    int val1 = INT_MIN, val2 = INT_MIN;
    while ((fscanf(fp, " %c", &op) != EOF))
    {
        if (isdigit(op))
        {
            int result = op - '0';
            pushStack(head, result);
        }
        else
        {
            val1 = popStack(head);
            val2 = popStack(head);
            if (val1 == INT_MIN || val2 == INT_MIN)
            {
                printf("Too many operands!!");
                return 1;
            }
            int result;
            switch (op)
            {
            case '+':
                result = val1 + val2;
                break;
            case '-':
                result = val2 - val1;
                break;
            case '*':
                result = val1 * val2;
                break;
            case '/':
                if (val1 != 0)
                {
                    result = val2 / val1;
                }
                else
                {
                    printf("Greska: deljenje sa nulom\n");
                    result = 0;
                }
                pushStack(head, result);
                break;
            default:
                printf("Nepoznata operacija: %c\n", op);
                continue;
            }
            pushStack(head, result);
        }
    }

    fclose(fp);

    if (head->next != NULL && head->next->next == NULL)
    {
        printf("Rezultat: %d\n", head->next->val);
    }
    else
    {
        printf("Greska: neispravan izraz\n");
    }
    return 0;
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