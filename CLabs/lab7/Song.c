#include "Song.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

struct Song* free_song(struct Song* a)
{
	free(a->name);
	a->name = NULL;
	free(a->text);
	a->text = NULL;
	free(a);
	a = NULL;
	return NULL;
}

struct Song* new_song(const char* name, const char* text, float price, int amount)
{
	struct Song* tmp = NULL;
	if (!(tmp = (struct Song*)malloc(sizeof(struct Song))))
	{
		perror("Cannot allocate memory.");
		clear_everything();
		exit(-3);
	}
	char* tname = NULL, * ttext = NULL;
	if (!(tname = (char*)malloc(strlen(name) * sizeof(char) + 1)) || !(ttext = (char*)malloc(strlen(text) * sizeof(char) + 1)))
	{
		perror("Cannot allocate memory.");
		clear_everything();
		exit(-3);
	}

	strcpy(tname, name);
	strcpy(ttext, text);

	tmp->name = tname;
	tmp->text = ttext;
	tmp->price = price;
	tmp->amount_of_copies = amount;
	return tmp;
}

struct SongTree* insert_song(struct SongTree* root, const char* name, const char* text, float price, int amount)
{
	if (root == NULL)// tree is empty
	{
		if (!(root = (struct SongTree*)malloc(sizeof(struct SongTree))))
		{
			perror("Unable to allocate memory!\n");
			exit(-3);
		}
		root->data = new_song(name, text, price, amount);
		root->left = root->right = NULL;
		root->parent = NULL;
		return root;
	}
	char s1[256] = { 0 }, s2[256] = { 0 };
	strcpy(s1, to_lower_case(root->data->name));
	strcpy(s2, to_lower_case(name));

	if (strcmp(s1, s2))// not found
	{
		if (compare(s1, s2)) // если наш проверяемый символ находится в алфавите до символа из узла, то
		{
			root->left = insert_song(root->left, name, text, price, amount);// идем по левой части дерева
			root->left->parent = root;
		}
		else
		{
			root->right = insert_song(root->right, name, text, price, amount);// идем по правой части
			root->right->parent = root;
		}
	}
	return root;
}

struct SongTree* del_song_tree(struct SongTree* tree)
{
	if (!tree)
		return NULL;
	if (tree->left)
		tree->left = del_song_tree(tree->left);
	if (tree->right)
		tree->right = del_song_tree(tree->right);

	tree->data = free_song(tree->data);
	free(tree);
	return NULL;
}

struct Song* find_song_name(struct SongTree* root, const char* name)
{
	struct Song* tmp = NULL;
	if (root)
	{
		char s1[256] = { 0 }, s2[256] = { 0 };
		strcpy(s1, to_lower_case(root->data->name));
		strcpy(s2, to_lower_case(name));

		if (strcmp(s1, s2))// not found
		{
			if (compare(s1, s2)) // если наш проверяемый символ находится в алфавите до символа из узла, то
				tmp = find_song_name(root->left, name);// идем по левой части дерева
			else
				tmp = find_song_name(root->right, name);// идем по правой части
		}
		else
			tmp = root->data;
	}

	return tmp;
}

void show_songs(struct SongTree* root)
{
	if (!root)
		return;

	if (root->left)
		show_songs(root->left);

	printf("Name: ");
	puts(root->data->name);
	printf("Price: %2.2f$\n", root->data->price);
	printf("Amount of copies: %d\n", root->data->amount_of_copies);

	printf("Want to see text?");
	int c = getch();
	if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
	{
		printf("Text:\n");
		puts(root->data->text);
	}
	else
		printf("\n");
	printf("\n");

	if (root->right)
		show_songs(root->right);
}

void show_songs1(struct SongTree* root, float price)
{
	if (!root)
		return;

	if (root->left)
		show_songs1(root->left, price);

	if (root->data->price <= price) {
		printf("Name: ");
		puts(root->data->name);
		printf("Price: %2.2f$\n", root->data->price);
		printf("Amount of copies: %d\n", root->data->amount_of_copies);
		int c = getch();
		printf("\n");
	}

	if (root->right)
		show_songs1(root->right, price);
}

void show_songs2(struct SongTree* root, int ncop)
{
	if (!root)
		return;

	if (root->left)
		show_songs2(root->left, ncop);

	if (root->data->amount_of_copies >= ncop) {
		printf("Name: ");
		puts(root->data->name);
		printf("Price: %2.2f$\n", root->data->price);
		printf("Amount of copies: %d\n", root->data->amount_of_copies);
		int c = getch();
		printf("\n");
	}

	if (root->right)
		show_songs2(root->right, ncop);
}