#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include <string.h>

char is_scope(char c)
{
	if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
		return 1;
	return 0;
}

int main(void)
{
	FILE* f = fopen("input.txt", "r");
	if (!f)
	{
		perror("Unable to open the file. ");
		exit(-1);
	}
	else
	{
		int c;
		//()[]{}
		char* scopes;
		if ((scopes = (char*)calloc(sizeof(f), sizeof(char))) == NULL)
		{
			perror("Memory allocation error. ");
			exit(-1);
		}

		int len = 0;
 		while ( (c = fgetc(f)) != EOF)
		{
			//this code is executable
			if (!is_scope(c))
				continue;
			//so 'c' IS a scope
			if (!len)
			{
				scopes[len++] = c;
				continue;
			}
			if ( (scopes[len - 1] == '(' && c == ')') || (scopes[len - 1] == '[' && c == ']') || (scopes[len - 1] == '{' && c == '}') )
				scopes[len--] = '\0';
			else
				scopes[len++] = c;
		}
		free(scopes);
		fclose(f);
		if (len)
			printf("Wrong.");
		else
			printf("Right!");
	}
	getchar();
	return 0;
}