#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 20

typedef struct _polynom {
    int value;
    int exp;
    struct _polynom* next;
} Polynom;

typedef Polynom* Position;

int readFromFile(Position, char*);
Position createElement();
Position add(Position, Position);
Position multiply(Position, Position);
int print(Position);
void freePolynomial(Position);

int main() {
    Position head1 = createElement();
    if (head1 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head1->next = NULL;

    Position head2 = createElement();
    if (head2 == NULL) {
        printf("Memory allocation failed.\n");
        free(head1);
        return 1;
    }
    head2->next = NULL;

    char file1[LEN];
    char file2[LEN];

    scanf("%s", file1);
    scanf("%s", file2);

    if (readFromFile(head1, file1) != 0) {
        printf("Error reading first polynomial.\n");
        freePolynomial(head1);
        freePolynomial(head2);
        return 1;
    }

    if (readFromFile(head2, file2) != 0) {
        printf("Error reading second polynomial.\n");
        freePolynomial(head1);
        freePolynomial(head2);
        return 1;
    }

    printf("First polynomial:");
    print(head1->next);

    printf("Second polynomial:");
    print(head2->next);

    Position sum = add(head1->next, head2->next);
    if (sum == NULL) {
        printf("Error creating sum polynomial.\n");
        freePolynomial(head1);
        freePolynomial(head2);
        return 1;
    }

    printf("Sum polynomial:\n");
    print(sum);

    Position product = multiply(head1->next, head2->next);
    if (product == NULL) {
        printf("Error creating product polynomial.\n");
        freePolynomial(head1);
        freePolynomial(head2);
        freePolynomial(sum);
        return 1;
    }

    printf("Product polynomial:\n");
    print(product);

    freePolynomial(head1);
    freePolynomial(head2);
    freePolynomial(sum);
    freePolynomial(product);

    return 0;
}

Position createElement() {
    Position p = (Position)malloc(sizeof(Polynom));
    if (p == NULL)
        return NULL;
    p->next = NULL;
    return p;
}

int readFromFile(Position head, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        return 1;

    int val, exp;
    Position current = head;

    while (fscanf(fp, " %d %d", &val, &exp) == 2) {
        Position newPoly = createElement();
        if (newPoly == NULL) {
            fclose(fp);
            return 1;
        }

        newPoly->value = val;
        newPoly->exp = exp;
        newPoly->next = NULL;

        while (current->next != NULL && current->next->exp > exp)
            current = current->next;

        if (current->next != NULL && current->next->exp == exp) {
            current->next->value += val;
            free(newPoly);
        }
        else {
            newPoly->next = current->next;
            current->next = newPoly;
        }
        current = head;
    }

    fclose(fp);
    return 0;
}

Position add(Position p1, Position p2) {
    Position head = createElement();
    if (head == NULL)
        return NULL;

    Position tail = head;

    while (p1 && p2) {
        Position newNode = createElement();
        if (!newNode) {
            freePolynomial(head);
            return NULL;
        }

        if (p1->exp == p2->exp) {
            newNode->value = p1->value + p2->value;
            newNode->exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exp > p2->exp) {
            newNode->value = p1->value;
            newNode->exp = p1->exp;
            p1 = p1->next;
        }
        else {
            newNode->value = p2->value;
            newNode->exp = p2->exp;
            p2 = p2->next;
        }

        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }

    Position rest = (p1 != NULL) ? p1 : p2;

    while (rest) {
        Position newNode = createElement();
        if (!newNode) {
            freePolynomial(head);
            return NULL;
        }
        newNode->value = rest->value;
        newNode->exp = rest->exp;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        rest = rest->next;
    }

    Position result = head->next;
    free(head);
    return result;
}

Position multiply(Position p1, Position p2) {
    Position head = createElement();
    if (!head)
        return NULL;

    while (p1) {
        Position temp = p2;

        while (temp) {
            int val = p1->value * temp->value;
            int exp = p1->exp + temp->exp;

            Position prev = head;
            Position curr = head->next;

            while (curr && curr->exp > exp) {
                prev = curr;
                curr = curr->next;
            }

            if (curr && curr->exp == exp) {
                curr->value += val;
            }
            else {
                Position newNode = createElement();
                if (!newNode) {
                    freePolynomial(head);
                    return NULL;
                }
                newNode->value = val;
                newNode->exp = exp;
                newNode->next = curr;
                prev->next = newNode;
            }

            temp = temp->next;
        }
        p1 = p1->next;
    }

    Position result = head->next;
    free(head);
    return result;
}

int print(Position head) {
    if (!head) {
        printf("Empty polynomial.\n");
        return 1;
    }

    while (head) {
        printf(" %d*x^%d", head->value, head->exp);
        if (head->next)
            printf(" +");
        head = head->next;
    }
    printf("\n");
    return 0;
}

void freePolynomial(Position head) {
    Position tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
