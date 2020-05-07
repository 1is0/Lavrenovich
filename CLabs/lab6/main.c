#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

struct Tree {
	struct Tree *parent, *left, *right;
	char* data;
};

char compare(char* s1, char* s2) {
	int len = (strlen(s1) < strlen(s2)) ? strlen(s1) : strlen(s2);
	for (int i = 0; i < len; i++)
		if (s1[i] < s2[i])
			return 0;
		else if (s1[i] > s2[i])
			return 1;
	if (strlen(s1) < strlen(s2))
		return 0;
	else
		return 1;
} // strings cannot be equal, it's worked out down in code

struct Tree* insert(struct Tree * root, char* s) {
	if (root == NULL) // tree is empty
	{
		if (!(root = (struct Tree*)malloc(sizeof(struct Tree)))) {
			perror("Unable to allocate memory!\n");
			exit(-3);
		}
		root->data = s;
		root->left = root->right = NULL;
		root->parent = NULL;
		return root;
	}

	if (compare(root->data, s))
	// если наш проверяемый символ находится в алфавите до символа из узла, то
	{
		root->left = insert(root->left, s); // идем по левой части дерева
		root->left->parent = root;
	}
	else 
	{
		root->right = insert(root->right, s); // идем по правой части
		root->right->parent = root;
	}
	
	return root;
}

void to_lower_case(char * s) {
	for (int i = 0; i < strlen(s); i++)
		s[i] = tolower(s[i]);
}

struct Tree* del_tree(struct Tree * tree) {
	if (!tree)
		return NULL;
	if (tree->left)
		tree->left = del_tree(tree->left);
	if (tree->right)
		tree->right = del_tree(tree->right);

	free(tree->data);
	free(tree);

	return NULL;
}

char is_palyndrom(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n / 2 + 1; i++)
		if (s[i] != s[n - i - 1])
			return 0;
	return 1;
}

void centered(struct Tree* tree) {
	if (!tree)
		return;
	centered(tree->left);
	if (is_palyndrom(tree->data))
		puts(tree->data);
	centered(tree->right);
}

char find(struct Tree* tree, char* data) {
	if (!tree)
		return 0;
	if (!strcmp(tree->data, data))
		return 1;
	return find(tree->left, data) || find(tree->right, data);
}

char fully_spaced(char* s) {
	for (int i = 0; i < strlen(s); i++)
		if (s[i] != ' ')
			return 0;
	return 1;
}

int main(void) {
	printf("Input your strings (string 'end' will terminate input):\n");
	char str[1024] = {0};
	struct Tree* tree = NULL;
	do {
		rewind(stdin);
		char* s;
		gets(str);
		

		to_lower_case(str);

		if (!strcmp(str, "end"))
			break;
		if (!strlen(str))
			continue; // simply pressed ENTER
		if (fully_spaced(str))
			continue; // consists of only spaces
		if (find(tree, str))
			continue;

		if (!(s = (char*)malloc(1024 * sizeof(char)))) {
			perror("Unable to allocate memory!\n");
			exit(-3);
		}
		strcpy(s, str);
		tree = insert(tree, s);
	}
	while (strcmp(str, "end"));

	printf("Our palyndroms in alphabetic order:\n");
	centered(tree);

	// MEMORY CLEANUP
	tree = del_tree(tree);
	getchar();
	return 0;
}
