#include "Basket.h"
#include <conio.h>

struct Basket* initialize_basket(float balance)
{
	struct Basket* tmp = NULL;
	if (!(tmp = (struct Basket*)malloc(sizeof(struct Basket))))
	{
		perror("Cannot allocate memory!\n");
		clear_everything();
		exit(-3);
	}
	tmp->head = tmp->tail = NULL;
	tmp->balance = balance;
	return tmp;
}

void clear_basknodes(struct Basket* basket)
{
	struct BaskNode* current = basket->head;
	while (current)
	{
		struct BaskNode* next = current->next;
		current = del_node(current);
		current = next;
	}
	basket->head = basket->tail = NULL;
}

void cancel_all_orders(struct Basket* basket)
{
	struct BaskNode* current = basket->head;
	while (current)
	{
		current->data->amount_of_copies += current->discs_to_buy;/*возвращение забронированных дисков*/
		current = current->next;
	}
	clear_basknodes(basket);
	puts("Orders cleared!");
}

struct Basket* delete_basket(struct Basket* basket)
{
	if (!basket)
		return NULL;
	if (!basket->head)
	{
		free(basket);
		return NULL;
	}
	if (!basket->tail)
	{
		basket->head = del_node(basket->head);
		free(basket);
		return NULL;
	}

	clear_basknodes(basket);
	free(basket);
	return NULL;
}

struct BaskNode* new_node(const char* mdname, const char* mname, const char* aname)
{
	struct BaskNode* tmp = NULL;
	if (!(tmp = (struct BaskNode*)malloc(sizeof(struct BaskNode))))
	{
		perror("Cannot allocate memory!\n");
		clear_everything();
		exit(-3);
	}
	if (!(tmp->mus_dir_name = (char*)malloc(strlen(mdname) * sizeof(char) + 1)))
	{
		perror("Cannot allocate memory!\n");
		clear_everything();
		exit(-3);
	}
	if (!(tmp->mus_name = (char*)malloc(strlen(mname) * sizeof(char) + 1)))
	{
		perror("Cannot allocate memory!\n");
		clear_everything();
		exit(-3);
	}
	if (!(tmp->album_name = (char*)malloc(strlen(aname) * sizeof(char) + 1)))
	{
		perror("Cannot allocate memory!\n");
		clear_everything();
		exit(-3);
	}
	strcpy(tmp->mus_dir_name, mdname);
	strcpy(tmp->mus_name, mname);
	strcpy(tmp->album_name, aname);

	return tmp;
}

struct BaskNode* del_node(struct BaskNode* tmp)
{
	free(tmp->mus_dir_name);
	free(tmp->mus_name);
	free(tmp->album_name);
	free(tmp);
	/*не нужно освобождать память для Song * data, мы её не выделяли*/
	return NULL;
}

void add_to_basket(struct Basket* basket, const char* mdname, const char* mname, const char* aname, struct Song* data, int to_buy)
{
	if (!basket->head)
	{
		basket->head = new_node(mdname, mname, aname);
		basket->head->next = basket->tail;
		basket->head->prev = NULL;

		basket->head->discs_to_buy = to_buy;
		basket->head->price = data->price;
		basket->head->data = data;
		data->amount_of_copies -= to_buy;/*эти копии не уходят из магазина, а просто бронируются*/
	}
	else if (!basket->tail)
	{
		basket->tail = new_node(mdname, mname, aname);
		basket->tail->prev = basket->head;
		basket->tail->next = NULL;
		basket->head->next = basket->tail;

		basket->tail->discs_to_buy = to_buy;
		basket->tail->price = data->price;
		basket->tail->data = data;
		data->amount_of_copies -= to_buy;/*эти копии не уходят из магазина, а просто бронируются*/
	}
	else
	{
		struct BaskNode* tmp = new_node(mdname, mname, aname);
		tmp->discs_to_buy = to_buy;
		tmp->price = data->price;
		tmp->data = data;
		basket->tail->next = tmp;
		tmp->prev = basket->tail;
		tmp->next = NULL;
		basket->tail = tmp;
		data->amount_of_copies -= to_buy;/*эти копии не уходят из магазина, а просто бронируются*/
	}
}

void pay(struct Basket* basket)
{
	if (!basket || !basket->head)
	{
		puts("Nothing to pay for.");
		return;
	}

	/*check for pay-ability*/
	struct BaskNode* current = basket->head;
	float fullprice = 0;
	while (current)
	{
		fullprice += current->price * current->discs_to_buy;
		current = current->next;
	}
	if (fullprice > basket->balance)
	{
		puts("You can't afford that!");
		printf("Full price: %6.2f$\nYour balance: %6.2f$\n", fullprice, basket->balance);
		return;
	}
	/*else*/
	printf("\nFull price: %6.2f$\nYour balance: %6.2f$\nRemaining balance: %6.2f$\n", fullprice, basket->balance, (basket->balance - fullprice));
	printf("\nWould you like to buy it? (Yes/No): ");
	char choice[256] = { 0 };
	rewind(stdin);
	gets(choice);
	trim(choice);
	while (strcmp(to_lower_case(choice), "yes") && strcmp(to_lower_case(choice), "no"))
	{
		puts("Bad input.\nWould you like to buy it? (Yes/No): ");
		gets(choice);
		trim(choice);
	}
	strcpy(choice, to_lower_case(choice));/*"yes", "no"*/

	if (!strcmp(choice, "yes"))
	{
		current = basket->head;
		while (current)
		{
			saledSongsCounter += current->discs_to_buy;
			generalDiscsAmount -= current->discs_to_buy;
			current = current->next;
		}
		basket->balance -= fullprice;
		profit += fullprice;
		puts("Payment succesfull!");
		clear_basknodes(basket);
		puts("Basket cleared.");
		int c = getch();
	}
	else
	{
		puts("Ok. Maybe next time.\nPress any key to continue...");
		int c = getch();
	}
}

void add_balance(struct Basket* basket)
{
	if (!basket)
	{
		puts("No basket initialized!");
		return;
	}
	puts("Would you like to add some money to your balance?(Press [y] key if yes)");
	int c = getch();
	if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
	{
		printf("How much money would you like to add?($): ");
		float money = 0;
		while (scanf("%f", &money) != 1 || money <= 0)
		{
			puts("Bad input.");
			printf("How much money would you like to add?($): ");
			rewind(stdin);
		}
		rewind(stdin);
		printf("Current balance: %6.2f\n", basket->balance);
		puts("Adding...");
		basket->balance += money;
		printf("Added %6.2f$ to your balance.\nCurrent balance: %6.2f$\n", money, basket->balance);
		c = getch();
	}
	else
	{
		puts("Ok. Maybe next time.\nPress any key to continue...");
		int c = getch();
	}
}

void show_basket_info(struct Basket* basket)
{
	if (!basket || !basket->head)
	{
		puts("No items here.");
		return;
	}
	puts("*******************BASKET INFO**********************");
	struct BaskNode* current = basket->head;
	while (current)
	{
		printf("Musical direction: %s\nMusician: %s\nAlbum: %s\nSong: %s\nPrice: %2.2f$\nDiscs to buy: %d\n\n", 
					 current->mus_dir_name, current->mus_name, current->album_name, current->data->name, current->price, 
					 current->discs_to_buy);
		current = current->next;
	}
}