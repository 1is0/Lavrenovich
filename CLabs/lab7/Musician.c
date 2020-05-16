#include "Musician.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Musician* free_musician(struct Musician* a)
{
	free(a->name);
	a->name = NULL;
	free(a->info);
	a->info = NULL;
	a->albums = del_album_tree(a->albums);
	free(a);
	a = NULL;
	return NULL;
}

struct Musician* new_musician(const char* name, const char* info, MusicianType mt)
{
	struct Musician* tmp = NULL;
	if (!(tmp = (struct Musician*)malloc(sizeof(struct Musician))))
	{
		perror("Cannot allocate memory.");
		clear_everything();
		exit(-3);
	}
	char* tname = NULL, * tinfo = NULL;
	if (!(tname = (char*)malloc(strlen(name) * sizeof(char) + 1)) || !(tinfo = (char*)malloc(strlen(info) * sizeof(char) + 1)))
	{
		perror("Cannot allocate memory.");
		clear_everything();
		exit(-3);
	}

	strcpy(tname, name);
	strcpy(tinfo, info);

	tmp->mt = mt;
	tmp->albums = NULL;
	tmp->info = tinfo;
	tmp->name = tname;
	return tmp;
}

struct MusicianTree* insert_musician(struct MusicianTree* root, const char* name, const char* info, MusicianType mt)
{
	if (root == NULL)// tree is empty
	{
		if (!(root = (struct MusicianTree*)malloc(sizeof(struct MusicianTree))))
		{
			perror("Unable to allocate memory!\n");
			exit(-3);
		}
		root->data = new_musician(name, info, mt);
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
			root->left = insert_musician(root->left, name, info, mt);// идем по левой части дерева
			root->left->parent = root;
		}
		else
		{
			root->right = insert_musician(root->right, name, info, mt);// идем по правой части
			root->right->parent = root;
		}
	}
	return root;
}

struct MusicianTree* del_musician_tree(struct MusicianTree* tree)
{
	if (!tree)
		return NULL;
	if (tree->left)
		tree->left = del_musician_tree(tree->left);
	if (tree->right)
		tree->right = del_musician_tree(tree->right);

	tree->data = free_musician(tree->data);
	free(tree);
	return NULL;
}

struct Musician* find_mus_name(struct MusicianTree* root, const char* name)
{
	struct Musician* tmp = NULL;
	if (root)
	{
		char s1[256] = { 0 }, s2[256] = { 0 };
		strcpy(s1, to_lower_case(root->data->name));
		strcpy(s2, to_lower_case(name));

		if (strcmp(s1, s2))// not found
		{
			if (compare(s1, s2)) // если наш проверяемый символ находится в алфавите до символа из узла, то
				tmp = find_mus_name(root->left, name);// идем по левой части дерева
			else
				tmp = find_mus_name(root->right, name);// идем по правой части
		}
		else
			tmp = root->data;
	}

	return tmp;
}

void show_mus(struct MusicianTree* root)
{
	if (!root)
		return;

	if (root->left)
		show_mus(root->left);

	printf("Name: ");
	puts(root->data->name);
	printf("Info: ");
	puts(root->data->info);
	puts((root->data->mt == SINGLE) ? "Type:\tSIGNLE" : "Type:\tGROUP");
	puts("\n***********************ALBUMS*******************\n");
	show_albums(root->data->albums);
	printf("\n");

	if (root->right)
		show_mus(root->right);
}

void show_mus1(struct MusicianTree* root, float price)
{
	if (!root)
		return;

	if (root->left)
		show_mus1(root->left, price);

	printf("Name: ");
	puts(root->data->name);
	printf("Info: ");
	puts(root->data->info);
	puts((root->data->mt == SINGLE) ? "Type:\tSIGNLE" : "Type:\tGROUP");
	puts("\n***********************ALBUMS*******************\n");
	show_albums1(root->data->albums, price);
	printf("\n");

	if (root->right)
		show_mus1(root->right, price);
}

void show_mus2(struct MusicianTree* root, int ncop)
{
	if (!root)
		return;

	if (root->left)
		show_mus2(root->left, ncop);

	printf("Name: ");
	puts(root->data->name);
	printf("Info: ");
	puts(root->data->info);
	puts((root->data->mt == SINGLE) ? "Type:\tSIGNLE" : "Type:\tGROUP");
	puts("\n***********************ALBUMS*******************\n");
	show_albums2(root->data->albums, ncop);
	printf("\n");

	if (root->right)
		show_mus2(root->right, ncop);
}