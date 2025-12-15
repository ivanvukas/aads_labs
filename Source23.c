#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


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
void fillData(Position);
int printList(Position);
int deleteCertainElement(Position);
int freeMemory(Position);
int findPersonByLastName(Position);
void addAfterElement(Position);
void addBeforeElement(Position);
void printListIntoFile(Position);
void readListFromFile(Position);



int main() {
	Position head = (Position)malloc(sizeof(Person));
	if (head == NULL) {
		printf("Memory allocation for head element failed.\n");
		return -1;
	}

	head->next = NULL;

	int choice = -1;

	printf("Choose which action you want to do:\n");
	printf("number 1 for adding an element to the start of the list\n");
	printf("number 2 for adding an element to the end of the list\n");
	printf("number 3 for writing out the list\n");
	printf("number 4 for finding a person by its last name\n");
	printf("number 5 for deleting a certain element from the list\n");
	printf("number 6 for adding after a certain element\n");
	printf("number 7 for adding before a certain element\n");
	printf("number 8 for printing the list into a file\n");
	printf("number 9 for reading a sorted list from a file.\n");

	while (choice != 0) {
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			pushFront(head);
			break;
		case 2:
			pushBack(head);
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
			addAfterElement(head);
			break;
		case 7:
			addBeforeElement(head);
			break;
		case 8:
			printListIntoFile(head);
			break;
		case 9:
			readListFromFile(head);
			break;
		case 0:
			freeMemory(head);
			printf("Action finished. Memory freed.");
			return 0;
		}
		printf("Choose which action you want to do again, you can press 0 for exiting the program:\n");
	}
	
}

int pushFront(Position head) {
	Position newPerson = createPerson();
	if (newPerson == NULL) {
		printf("Memory allocation failed.\n");
		return -1;
	}
	fillData(newPerson);

	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

int pushBack(Position head) {
	Position newPerson = createPerson();
	if (newPerson == NULL) {
		printf("Memory allocation failed.\n");
		return -1;
	}
	fillData(newPerson);

	Position temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = newPerson;
	newPerson->next = NULL;

	return 0;
}

Position createPerson() {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL) {
		printf("Memory allocation failed.\n");
		return -1;
	}

	return newPerson;
}


void fillData(Position newPerson) {
	printf("Please insert the data for the new person.\n");

	printf("First name: ");
	scanf(" %s", newPerson->firstName);  

	printf("Last name: ");
	scanf(" %s", newPerson->lastName);

	printf("Year of birth: ");
	scanf("%d", &newPerson->yearOfBirth);

	newPerson->next = NULL;
}

int printList(Position head) {
	Position temp = head->next;

	if (head->next == NULL) {
		printf("Empty list.\n");
	}

	while (temp != NULL) {
		printf("%s %s, born in %d.\n", temp->firstName, temp->lastName, temp->yearOfBirth);
		temp = temp->next;

	}
	return 0;
}

int deleteCertainElement(Position head) {
	Position current = head;
	Position temp = NULL;

	char firstName[20];
	char lastName[20];

	printf("Insert first and last name of the person that you want to remove from the list: ");
	scanf(" %s %s", firstName, lastName);

	while (current != NULL) {
		if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0) {
			temp->next = current->next;
			free(current);
			printf("Person deleted.\n");
			return 0;
		}
		else {
			temp = current;
			current = current->next;
		}
	}
	return 0;
}

int freeMemory(Position head) {

	while (head->next != NULL) {
		Position temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}

int findPersonByLastName(Position head) {
	Position current = head;
	Position temp = NULL;
	char lastName[20];

	printf("Enter last Name that you're searching for: ");
	scanf(" %s", lastName);

	printf("Persons that fit your search: ");

	while (current != NULL) {
		if (strcmp(current->lastName, lastName) == 0) {
			printf("Name: %s, last name: %s, year of birth: %d ", current->firstName, current->lastName, current->yearOfBirth);
		}
		current = current->next;
	}
	return 0;
}

void addAfterElement(Position head) {
	Position current = head;
	Position temp = NULL;

	char firstName[20], lastName[20];
	printf("Enter first and last name after which you want to add another person: ");
	scanf(" %s %s", firstName, lastName);
	
	int matchingCounter = 0;

	while (current != NULL) {
		if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0) {
			Position newPerson = createPerson();
			fillData(newPerson);

			newPerson->next = current->next;
			current->next = newPerson;
			printf("Element added after %s %s.\n", current->firstName, current->lastName);
			matchingCounter++;
		}
		temp = current;
		current = current->next;
	}

	if (matchingCounter == 0) {
		printf("No elements matched your search.\n");
	}
}

void addBeforeElement(Position head) {
	Position current = head;
	Position temp = NULL;

	char firstName[20], lastName[20];
	printf("Enter first and last name before which you want to add another person: ");
	scanf(" %s %s", firstName, lastName);

	int matchingCounter = 0;

	while (current != NULL) {
		if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0) {
			Position newPerson = createPerson();
			fillData(newPerson);

			newPerson->next = current;
			temp->next = newPerson;
			printf("Element added before %s %s.\n", current->firstName, current->lastName);
			matchingCounter++;
		}
		temp = current;
		current = current->next;
	}

	if (matchingCounter == 0) {
		printf("No elements matched your search.\n");
	}
}

void printListIntoFile(Position head) {
	Position current = head->next;

	FILE* fp = NULL;
	fp = fopen("personsList.txt", "w");
	if (fp == NULL) {
		printf("Datoteka nije otvorena.\n");
		return -1;
	}

	while (current != NULL) {
		fprintf(fp, "%s %s %d", current->firstName, current->lastName, current->yearOfBirth);
		current = current->next;
	}
	fclose(fp);
}


void readListFromFile(Position head) {
	FILE* fp = NULL;
	fp = fopen("documentToReadFrom.txt", "r");
	if (fp == NULL) {
		printf("Datoteka nije otvorena.\n");
		return -1;
	}

	while (!feof(fp)) {
		Position newPerson = createPerson();
		fscanf(fp, " %s %s %d", newPerson->firstName, newPerson->lastName, &newPerson->yearOfBirth);

		Position temp = head;
		Position current = head->next;
		
		while (current != NULL) {
			if (strcmp(newPerson->lastName, current->lastName) < 0 || (strcmp(newPerson->lastName, current->lastName) == 0 && strcmp(newPerson->firstName, current->firstName) < 0)) {
				break;
			}
			temp = current;
			current = current->next;
		}
		newPerson->next = current;
		temp->next = newPerson;
	}


	fclose(fp);
}
