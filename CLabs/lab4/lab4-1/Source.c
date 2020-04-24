#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void swap(char* c1, char* c2)
{
	char swp = *c1;
	*c1 = *c2;
	*c2 = swp;
}

void reverse(char* s)
{
	int n = strlen(s);
	for (int i = 0; i < n / 2; i++)
		swap(&s[i], &s[n - i - 1]);
}

int main(void)
{
	printf("Enter your text (press \\ on new line to end input):\n");

	char** text = (char**)malloc(255 * sizeof(char*));
	for (int i = 0; i < 30; i++)
		text[i] = (char*)malloc(256 * sizeof(char));

	int count = 0;
	while (count < 30)
	{
		char ch = _getche();
		if (ch == '\\')
			break;
		else
			ungetc(ch, stdin);
		gets_s(text[count++], 255);
	}

	char* str, separator[] = " .,?!;:\\()<>{}[]";
	char** text_rev = (char**)malloc(1024 * sizeof(char*));//1024 words max
	int rev_count = 0;

	printf("\nYour new text:\n");
	for (int i = 0; i < count; i++)
	{
		str = strtok(text[i], separator);
		while (str)
		{
			reverse(str);
			text_rev[rev_count] = (char*)malloc(256 * sizeof(char));
			strcpy(text_rev[rev_count++], str);
			str = strtok(NULL, separator);
		}
		printf("\n");
	}
	for (int i = rev_count - 1; i >= 0; i--)
		printf("%s ", text_rev[i]);


	for (int i = 0; i < 30; i++)
		free(text[i]);
	free(text);

	for (int i = 0; i < rev_count; i++)
		free(text_rev[i]);
	free(text_rev);

	return 0;
}