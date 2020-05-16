#include "Album.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Album* free_album(struct Album* a)
{
	free(a->name);
	a->name = NULL;
	a->songs = del_song_tree(a->songs);
	free(a);
	a = NULL;
	return NULL;
}

struct Album* new_album(const char* name)
{
	struct Album* tmp = NULL;
	if (!(tmp = (struct Album*)malloc(sizeof(struct Album))))
	{
		perror("Cannot allocate memory.");
		clear_everything();
		exit(-3);
	}
	char* tname = NULL;
	if (!(tname = (char*)malloc(strlen(name) * sizeof(char) + 1)))
	{
		perror("Cannot allocate memory.");
		clear_everything();
		exit(-3);
	}

	strcpy(tname, name);

	tmp->songs = NULL;
	tmp->name = tname;
	return tmp;
}

struct AlbumTree* insert_album(struct AlbumTree* root, const char* name)
{
	if (root == NULL)// tree is empty
	{
		if (!(root = (struct AlbumTree*)malloc(sizeof(struct AlbumTree))))
		{
			perror("Unable to allocate memory!\n");
			exit(-3);
		}
		root->data = new_album(name);
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
			root->left = insert_album(root->left, name);// идем по левой части дерева
			root->left->parent = root;
		}
		else
		{
			root->right = insert_album(root->right, name);// идем по правой части
			root->right->parent = root;
		}
	}
	return root;
}

struct AlbumTree* del_album_tree(struct AlbumTree* tree)
{
	if (!tree)
		return NULL;
	if (tree->left)
		tree->left = del_album_tree(tree->left);
	if (tree->right)
		tree->right = del_album_tree(tree->right);

	tree->data = free_album(tree->data);
	free(tree);
	return NULL;
}

struct Album* find_album_name(struct AlbumTree* root, const char* name)
{
	struct Album* tmp = NULL;
	if (root)
	{
		char s1[256] = { 0 }, s2[256] = { 0 };
		strcpy(s1, to_lower_case(root->data->name));
		strcpy(s2, to_lower_case(name));

		if (strcmp(s1, s2))// not found
		{
			if (compare(s1, s2)) // если наш проверяемый символ находится в алфавите до символа из узла, то
				tmp = find_album_name(root->left, name);// идем по левой части дерева
			else
				tmp = find_album_name(root->right, name);// идем по правой части
		}
		else
			tmp = root->data;
	}

	return tmp;
}

void show_albums(struct AlbumTree* root)
{
	if (!root)
		return;
	if (root->left)
		show_albums(root->left);


	printf("Name: ");
	puts(root->data->name);
	puts("\n***********************SONGS*******************\n");
	show_songs(root->data->songs);
	printf("\n");

	if (root->right)
		show_albums(root->right);
}

void show_albums1(struct AlbumTree* root, float price)
{
	if (!root)
		return;
	if (root->left)
		show_albums1(root->left, price);


	printf("Name: ");
	puts(root->data->name);
	puts("\n***********************SONGS*******************\n");
	show_songs1(root->data->songs, price);
	printf("\n");

	if (root->right)
		show_albums1(root->right, price);
}

void show_albums2(struct AlbumTree* root, int ncop)
{
	if (!root)
		return;
	if (root->left)
		show_albums2(root->left, ncop);


	printf("Name: ");
	puts(root->data->name);
	puts("\n***********************SONGS*******************\n");
	show_songs2(root->data->songs, ncop);
	printf("\n");

	if (root->right)
		show_albums2(root->right, ncop);
}