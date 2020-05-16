#ifndef BASKET_H
#define BASKET_H
#include "MusDir.h"
#include "Musician.h"
#include "Album.h"
#include "Song.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern float profit;
extern int saledSongsCounter;
extern int generalDiscsAmount;
extern const char* to_lower_case(char*);
extern void trim(char* s);

struct BaskNode
{
	struct BaskNode* prev, * next;
	struct Song* data;
	int discs_to_buy;
	float price;
	char* mus_dir_name, * mus_name, * album_name;
};

struct Basket
{
	float balance;
	struct BaskNode* head, * tail;
};

struct BaskNode* new_node(const char* mdname, const char* mname, const char* aname);
struct BaskNode* del_node(struct BaskNode* tmp);
void clear_basknodes(struct Basket* basket);
void cancel_all_orders(struct Basket* basket);
void add_balance(struct Basket* basket);

struct Basket* initialize_basket(float balance);
struct Basket* delete_basket(struct Basket* basket);
void add_to_basket(struct Basket* basket, const char* mdname, const char* mname, const char* aname, struct Song* data, int to_buy);
void pay(struct Basket* basket);
void show_basket_info(struct Basket* basket);

#endif