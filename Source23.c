#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person {
    char firstName[20];
    char lastName[20];
    int yearOfBirth;
    struct _Person* next;
} Person;

typedef Person* Position;

Position createPerson();
int pushFront(Position);
int pushBack(Position);
int printList(Position);
int deleteCertainElement(Position);
int freeMemory(Position);
int findPersonByLastName(Position);
int addAfterElement(Position);
int addBeforeElement(Position);
int printListIntoFile(Position);
int readListFromFile(Position);
void fillData(Position);

int main() {
    Position head = (Position)malloc(sizeof(Person));
    if (head == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    head->next = NULL;

    int choice = -1;

    while (choice != 0) {
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (pushFront(head) != 0)
                printf("Error adding element to front.\n");
            break;

        case 2:
            if (pushBack(head) != 0)
                printf("Error adding element to back.\n");
            break;

        case 3:
            printList(head);
            break;

        case 4:
            findPersonByLastName(head);
            break;

        case 5:
            deleteCertainElement(head);
            break;

        case 6:
            if (addAfterElement(head) != 0)
                printf("Error adding element.\n");
            break;

        case 7:
            if (addBeforeElement(head) != 0)
                printf("Error adding element.\n");
            break;

        case 8:
            if (printListIntoFile(head) != 0)
                printf("Error writing to file.\n");
            break;

        case 9:
            if (readListFromFile(head) != 0)
                printf("Error reading from file.\n");
            break;

        case 0:
            freeMemory(head);
            free(head);
            return 0;
        }
    }
    return 0;
}

Position createPerson() {
    Position p = (Position)malloc(sizeof(Person));
    if (p == NULL)
        return NULL;
    p->next = NULL;
    return p;
}

void fillData(Position p) {
    scanf(" %s %s %d", p->firstName, p->lastName, &p->yearOfBirth);
}

int pushFront(Position head) {
    Position p = createPerson();
    if (!p) return 1;

    fillData(p);
    p->next = head->next;
    head->next = p;
    return 0;
}

int pushBack(Position head) {
    Position p = createPerson();
    if (!p) return 1;

    fillData(p);
    while (head->next)
        head = head->next;

    head->next = p;
    return 0;
}

int printList(Position head) {
    if (!head->next) {
        printf("Empty list.\n");
        return 1;
    }
    head = head->next;
    while (head) {
        printf("%s %s %d\n", head->firstName, head->lastName, head->yearOfBirth);
        head = head->next;
    }
    return 0;
}

int deleteCertainElement(Position head) {
    char fn[20], ln[20];
    scanf(" %s %s", fn, ln);

    Position prev = head;
    Position curr = head->next;

    while (curr) {
        if (!strcmp(curr->firstName, fn) && !strcmp(curr->lastName, ln)) {
            prev->next = curr->next;
            free(curr);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return 1;
}

int freeMemory(Position head) {
    Position tmp;
    while (head->next) {
        tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
    return 0;
}

int findPersonByLastName(Position head) {
    char ln[20];
    scanf(" %s", ln);

    head = head->next;
    while (head) {
        if (!strcmp(head->lastName, ln))
            printf("%s %s %d\n", head->firstName, head->lastName, head->yearOfBirth);
        head = head->next;
    }
    return 0;
}

int addAfterElement(Position head) {
    char fn[20], ln[20];
    scanf(" %s %s", fn, ln);

    while (head) {
        if (!strcmp(head->firstName, fn) && !strcmp(head->lastName, ln)) {
            Position p = createPerson();
            if (!p) return 1;
            fillData(p);

            p->next = head->next;
            head->next = p;
            return 0;
        }
        head = head->next;
    }
    return 1;
}

int addBeforeElement(Position head) {
    char fn[20], ln[20];
    scanf(" %s %s", fn, ln);

    Position prev = head;
    Position curr = head->next;

    while (curr) {
        if (!strcmp(curr->firstName, fn) && !strcmp(curr->lastName, ln)) {
            Position p = createPerson();
            if (!p) return 1;
            fillData(p);

            p->next = curr;
            prev->next = p;
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return 1;
}

int printListIntoFile(Position head) {
    FILE* fp = fopen("personsList.txt", "w");
    if (!fp) return 1;

    head = head->next;
    while (head) {
        fprintf(fp, "%s %s %d\n", head->firstName, head->lastName, head->yearOfBirth);
        head = head->next;
    }
    fclose(fp);
    return 0;
}

int readListFromFile(Position head) {
    FILE* fp = fopen("documentToReadFrom.txt", "r");
    if (!fp) return 1;

    while (!feof(fp)) {
        Position p = createPerson();
        if (!p) {
            fclose(fp);
            return 1;
        }

        if (fscanf(fp, " %s %s %d", p->firstName, p->lastName, &p->yearOfBirth) != 3) {
            free(p);
            break;
        }

        Position prev = head;
        Position curr = head->next;

        while (curr &&
            (strcmp(p->lastName, curr->lastName) > 0 ||
            (strcmp(p->lastName, curr->lastName) == 0 &&
             strcmp(p->firstName, curr->firstName) > 0))) {
            prev = curr;
            curr = curr->next;
        }

        p->next = curr;
        prev->next = p;
    }
    fclose(fp);
    return 0;
}
