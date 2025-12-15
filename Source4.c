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

typedef struct _polynom* Position;

int readFromFile(Position, char*);
Position createElement();
Position add(Position, Position);
int print(Position);
void freePolynomial(Position);
Position multiply(Position, Position);


int main() {
	Position head1 = createElement();
	head1->next = NULL;

	Position head2 = createElement();
	head2->next = NULL;

	char file1[LEN];
	char file2[LEN];

	printf("Enter first polynomial file name: ");
	scanf("%s", file1);

	printf("Enter second polynomial file name: ");
	scanf("%s", file2);


	readFromFile(head1, file1);
	printf("First Polynomial:");
	print(head1->next);

	readFromFile(head2, file2);
	printf("Second Polynomial:");
	print(head2->next);

	Position sum = add(head1->next, head2->next);
	printf("Sum Polynomial: \n");
	print(sum);

	Position product = multiply(head1->next, head2->next);
	printf("Product Polynomial:\n");
	print(product);

	freePolynomial(head1);
	freePolynomial(head2);
	freePolynomial(sum);
	freePolynomial(product);

	return 0;

}

Position createElement() {
	Position newElement = (Position)malloc(sizeof(Polynom));

	if (newElement == NULL) {
		printf("Allocation failed. Exiting ...");
		return -1;
	}

	return newElement;
}

int readFromFile(Position head, char* filename) {
	FILE* fp = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File not open.\n");
		return -1;
	}

	int val, exp;
	Position current = head;

	while (!feof(fp)) {
		Position newPolynomial = createElement();
		fscanf(fp, " %d %d", &val, &exp);

		newPolynomial->value = val;
		newPolynomial->exp = exp;
		newPolynomial->next = NULL;

		while (current->next != NULL && exp < current->next->exp) {
			current = current->next;
		}
		if (current->next != NULL && current->next->exp == exp) {
			current->next->value += val;
			free(newPolynomial);
		}
		else {
			newPolynomial->next = current->next;
			current->next = newPolynomial;
		}
		current = head;
	}
	fclose(fp);
	return 0;
}

Position add(Position head1, Position head2) {
	Position result = createElement();

	result->next = NULL;
	Position temp = result;

	while (head1 != NULL && head2 != NULL) {
		Position new = createElement();
		
		if (head1->exp == head2->exp) {
			new->value = head1->value + head2->value;
			new->exp = head1->exp;
			head1 = head1->next;
			head2 = head2->next;
		}
		else if (head1->exp > head2->exp) {
			new->value = head1->value;
			new->exp = head1->exp;
			head1 = head1->next;
		}
		else {
			new->value = head2->value;
			new->exp = head2->exp;
			head2 = head2->next;
		}
		new->next = NULL;
		temp->next = new;
		temp = temp->next;
	}

	Position remaining;

	if (head1 != NULL) {
		remaining = head1;
	}
	else {
		remaining = head2;
	}

	while (remaining != NULL) {
		Position new = createElement();

		new->value = remaining->value;
		new->exp = remaining->exp;
		new->next = NULL;
		temp->next = new;
		temp = temp->next;
		remaining = remaining->next;
	}

	return result->next;
}

Position multiply(Position head1, Position head2) {
	Position resultHead = createElement();
	Position current1 = head1;
	Position current2 = NULL;

	resultHead->next = NULL;

	while (current1 != NULL) {

		current2 = head2;

		while (current2 != NULL) {

			int value = current1->value * current2->value;
			int exponent = current1->exp + current2->exp;

			Position prev = resultHead;
			Position curr = resultHead->next;

			while (curr != NULL && curr->exp > exponent) {
				prev = curr;
				curr = curr->next;
			}

			if (curr != NULL && curr->exp == exponent) {
				curr->value += value;
			}
			else {
				Position newNode = createElement();
				newNode->value = value;
				newNode->exp = exponent;
				newNode->next = curr;
				prev->next = newNode;
			}

			current2 = current2->next;
		}

		current1 = current1->next;
	}

	return resultHead->next;
}



int print(Position head) {
	while (head != NULL) {
		printf(" %d*x^%d", head->value, head->exp);
		if (head->next != NULL) {
			printf(" +");
		}
		head = head->next;
	}
	printf("\n");
	return 0;
}

void freePolynomial(Position head) {
	Position temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}


