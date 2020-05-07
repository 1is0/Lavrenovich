#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Node 
{
	int value; 
	struct Node* next; 
  struct	Node* prev;
};

struct Number//represents a big number to be stored
{
	struct Node* head;
	struct Node* tail;
};

struct Node* new_digit(void)
{
	struct Node* d = (struct Node*)malloc(sizeof(struct Node));
	d->value = 0;
	return d;
}

struct Number* new_num(void)//new big number, initially it's 1
{
	struct Number* n = (struct Number*)malloc(sizeof(struct Number));
	n->head = new_digit();
	n->tail = new_digit();
	struct Node* d = (struct Node*)malloc(sizeof(struct Node));
	d->value = 1;
	n->head->next = d;
	d->prev = n->head;
	n->tail->prev = d;
	d->next = n->tail;
	return n;
}

void move(struct Number* num)
{
	struct Node* current = num->tail->prev;
	while (current != num->head)//moving digits to the left
	{
		if (current->prev == num->head && current->value >= 10)
		{
			struct Node* d = new_digit();
			d->value += current->value / 10;
			current->value %= 10;
			num->head->next = d;
			d->prev = num->head;
			current->prev = d;
			d->next = current;
			current = current->prev;
			continue;
		}
		current->prev->value += current->value / 10;
		current->value %= 10;
		current = current->prev;
	}
	current = num->head->next;
	while (current->value == 0)//getting rid of leading 0's
	{
		struct Node* tmp = current;
		if (current->next == num->tail)//leaving only one 0
			break;
		num->head->next = current->next;
		current->next->prev = num->head;
		free(tmp);
		current = num->head->next;
	}
}

void multiply2(struct Number* num)
{
	struct Node* current = num->tail->prev;
	while (current != num->head)
	{
		current->value *= 2;
		current = current->prev;
	}
	move(num);
}

void divide2(struct Number* num, int* r)
{
	struct Node* current = num->head->next;
	if (current->next == num->tail)//only 1 digit
	{
		*r = current->value % 2;
		current->value /= 2;
		return;
	}

	int cur = 0, carry = 0;
	while (current != num->tail)
	{
		cur = current->value + carry * 10;
		current->value = cur / 2;
		carry = cur % 2;
		current = current->next;
	}
	*r = carry;
	move(num);//get rid of leading nulls
}

void minus(struct Number* n1, struct Number* n2)
{
	int carry = 0;
	struct Node *a = n1->tail->prev, *b = n2->tail->prev;
	while(b != n2->head || carry) {
		a->value -= carry + ((b != n2->head) ? b->value : 0);
		carry = (a->value < 0);// 1 if <0, else 0 
		if (carry)  
			a->value += 10;
		a = a->prev;
		b = b->prev;
	}
	move(n1);//getting rid of leading nulls
}

struct Number* to_bin(struct Number* n)
{
	struct Number* bin_n = new_num();
	int* r = (int*)malloc(sizeof(int));

	divide2(n, r);
	bin_n->head->next->value = *r;
	while (n->head->next->value != 0)
	{
		divide2(n, r);
		struct Node* d = new_digit();
		d->value = *r;//new digit to bin_n
		struct Node* n1 = bin_n->head;
		struct Node* n2 = bin_n->head->next;
		//put d in between head and head->next
		d->prev = n1;
		d->next = n2;
		n1->next = d;
		n2->prev = d;
		//no memory leak
	}
	free(r);
	return bin_n;
}

char is_perfect(struct Number* bin_n)
{
	//in perfect numbers, in binary form they have n of leading 1's and then n-1 0's
	struct Node* current = bin_n->head->next;
	if (current->value == 0)
	{
		perror("Something went wrong...\n");
		return 0;
	}
	int n0 = 0, n1 = 0;
	while (current->value != 0)
	{
		n1++;
		current = current->next;
	}
	while (current != bin_n->tail)
	{
		if (current->value == 0)
			n0++;
		else
			break;
		current = current->next;
	}
	if (current != bin_n->tail)//did not reach end of bin_n
		return 0;

	printf("\n%d 1's followed by %d 0's\n", n1, n0);
	return (n1 == n0 + 1);//or here we did
}

void print_info(struct Number* num, const char* s)
{
	struct Node* tmp;
	int n1 = 0;
	printf(s);
	tmp = num->head->next;
	while (tmp != num->tail)
	{
		printf("%d", tmp->value);
		tmp = tmp->next;
		n1++;
	}
	printf("\n\ndigits: %d\n\n", n1);
}

struct Number* del_num(struct Number* n)
{
	//fish rots from the head
	struct Node* current = n->head->next;
	while (current != n->tail)
	{
		free(current->prev);
		current = current->next;
	}
	//then get rid of its tail
	free(current);
	return NULL;
}

int main(void)
{
	/* 
	2^19936 * (2^19937 - 1) = 2^19936 * (2^19936 * 2 - 1) =
	= 2^19936 * (2^19936 + 2^19936 - 1) =[n=19936]= 2^n * (2^n + 2^n - 1) =
	= 2^(2n) + 2^(2n) - 2^n = 2^(2n+1) - 2^n;
	*/
	const int n = 19936;
	struct Number* num1 = new_num();
	for (int i = 0; i < 2 * n + 1; i++)
		multiply2(num1);
	print_info(num1, "\nnum1=");
	//now we have 2^(2n+1) in num1
	struct Number* num2 = new_num();
	for (int i = 0; i < n; i++)
		multiply2(num2);
	print_info(num2, "\nnum2=");
	//now we have 2^n in num2

	//let's do num1 -= num2
	minus(num1, num2);//works
	printf("\nAfter num1 - num2:\n");
	print_info(num1, "\nnum1=");
	print_info(num2, "\nnum2=");

	//and make it binary-looking
	struct Number* bin_n = to_bin(num1);
	print_info(bin_n, "\nBinary representation of num1:\n");

	//let's see if num1 is perfect
	if (is_perfect(bin_n))
		printf("\n\nWow, it's actually perfect!\n");
	else
		printf("\n\nNah, just a regular one.\n");

	//cleaning memory
	num1 = del_num(num1);
	num2 = del_num(num2);
	bin_n = del_num(bin_n);

	getchar();
	return 0;
}