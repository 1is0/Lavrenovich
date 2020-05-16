#include "MusDir.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct MusDir* free_mus_dir(struct MusDir* a)
{
	free(a->info);
	a->info = NULL;
	free(a->name);
	a->name = NULL;
	a->musicians = del_musician_tree(a->musicians);
	free(a);
	a = NULL;
	return NULL;
}

struct MusDir* new_mus_dir(const char* name, const char* info)
{
	struct MusDir* tmp = NULL;
	if (!(tmp = (struct MusDir*)malloc(sizeof(struct MusDir))))
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

	tmp->musicians = NULL;
	tmp->info = tinfo;
	tmp->name = tname;
	return tmp;
}

struct MusDirTree* insert_mus_dir(struct MusDirTree* root, const char* name, const char* info)
{
	if (root == NULL)// tree is empty
	{
		if (!(root = (struct MusDirTree*)malloc(sizeof(struct MusDirTree))))
		{
			perror("Unable to allocate memory!\n");
			exit(-3);
		}
		root->data = new_mus_dir(name, info);
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
			root->left = insert_mus_dir(root->left, name, info);// идем по левой части дерева
			root->left->parent = root;
		}
		else
		{
			root->right = insert_mus_dir(root->right, name, info);// идем по правой части
			root->right->parent = root;
		}
	}
	return root;
}

struct MusDirTree* del_mus_dir_tree(struct MusDirTree* tree)
{
	if (!tree)
		return NULL;
	if (tree->left)
		tree->left = del_mus_dir_tree(tree->left);
	if (tree->right)
		tree->right = del_mus_dir_tree(tree->right);

	tree->data = free_mus_dir(tree->data);
	free(tree);
	return NULL;
}

struct MusDir* find_md_name(struct MusDirTree* root, const char* name)
{
	struct MusDir* tmp = NULL;
	if (root)
	{
		char s1[256] = { 0 }, s2[256] = { 0 };
		strcpy(s1, to_lower_case(root->data->name));
		strcpy(s2, to_lower_case(name));

		if (strcmp(s1, s2))// not found
		{
			if (compare(s1, s2)) // если наш проверяемый символ находится в алфавите до символа из узла, то
				tmp = find_md_name(root->left, name);// идем по левой части дерева
			else
				tmp = find_md_name(root->right, name);// идем по правой части
		}
		else
			tmp = root->data;
	}

	return tmp;
}

void show_md(struct MusDirTree* root)
{
	if (!root)
		return;
	if (root->left)
		show_md(root->left);


	printf("Name: ");
	puts(root->data->name);
	printf("Info: ");
	puts(root->data->info);
	puts("\n***********************MUSICIANS*******************\n");
	show_mus(root->data->musicians);
	printf("\n");

	if (root->right)
		show_md(root->right);
}

void show_md1(struct MusDirTree* root, float price)
{
	if (!root)
		return;
	if (root->left)
		show_md1(root->left, price);

	printf("Name: ");
	puts(root->data->name);
	printf("Info: ");
	puts(root->data->info);
	puts("\n***********************MUSICIANS*******************\n");
	show_mus1(root->data->musicians, price);
	printf("\n");

	if (root->right)
		show_md1(root->right, price);
}

void show_md2(struct MusDirTree* root, int ncop)
{
	if (!root)
		return;
	if (root->left)
		show_md2(root->left, ncop);

	printf("Name: ");
	puts(root->data->name);
	printf("Info: ");
	puts(root->data->info);
	puts("\n***********************MUSICIANS*******************\n");
	show_mus2(root->data->musicians, ncop);
	printf("\n");

	if (root->right)
		show_md2(root->right, ncop);
}