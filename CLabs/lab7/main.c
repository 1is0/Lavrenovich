#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

#include "MusDir.h"
#include "Musician.h"
#include "Album.h"
#include "Song.h"
#include "Basket.h"

struct MusDirTree* MusicalDirections = NULL;/*главное дерево, в котором хранится весь каталог*/
struct Basket* Basket = NULL;/*корзина с балансом*/
float profit = 0;
int saledSongsCounter = 0;
int generalDiscsAmount = 0;

void trim(char* s)
{
	if (!strlen(s))
		return;
	
	if (s[0] == ' ')/*trim left*/
	{
		int k = 0;
		while (s[k] == ' ') 
			k++;
		if (k == strlen(s))/*fully spaced string*/
		{
			s[0] = '\0';
			return;
		}
		else
			for (int i = 0; i < strlen(s) - k + 1; i++)
				s[i] = s[i + k];
	}

	if (s[strlen(s) - 1] == ' ')/*trim right*/
	{
		int i;
		for (i = strlen(s); s[i - 1] == ' '; i--)		;/*просто отсчёт*/
		s[i] = '\0';
	}
}

void clear_string(char* s)
{
	if (s)
		s[0] = '\0';
}

const char* to_lower_case(char* s)//работает заебись
{
	static char tmp[256];
	clear_string(tmp);
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		tmp[i] = tolower(s[i]);
	tmp[n] = '\0';
	return tmp;
}

const char* get_text_info(FILE* f)
{
	static char tmp[10000] = {0};
	clear_string(tmp);
	if (f)
	{
		char str[100];
		while (!feof(f))
		{
			fgets(str, 99, f);
			strcat(tmp, str);
		}
	}
	return tmp;
}

char compare(char* s1, char* s2)//алфавитное сравнение
{
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
}

void clear_everything()/*в случае чего-то непридвиденного очистить всё*/
{
	MusicalDirections = del_mus_dir_tree(MusicalDirections);
	Basket = delete_basket(Basket);
}

void load_database()
{
	char path[BUFSIZ];
	GetCurrentDirectory(BUFSIZ, path);
	strcat(path, "\\MusDirections");

	/*добавление из файлов*/
	FILE* fMusDirs = NULL;
	char pathMusDirs[BUFSIZ] = { 0 };
	strcpy(pathMusDirs, path);
	strcat(pathMusDirs, "\\MusDirections.txt");/*pathMusDirs = "...\MusDirections.txt"*/

	fMusDirs = fopen(pathMusDirs, "r");
	while (!feof(fMusDirs))/*проход по папкам музыкальных направлений*/
	{
		/*works*/
		char sMusDirFolder[BUFSIZ] = { 0 };
		strcpy(sMusDirFolder, path);
		strcat(sMusDirFolder, "\\");

		char folderName0[41] = { 0 };
		fgets(folderName0, 40, fMusDirs);/*first folder HipHop*/
		if (folderName0[strlen(folderName0) - 1] == '\n')
			folderName0[strlen(folderName0) - 1] = '\0';

		strcat(sMusDirFolder, folderName0);
		strcat(sMusDirFolder, "\\");

		char sMDInfoPath[BUFSIZ] = { 0 };
		strcpy(sMDInfoPath, sMusDirFolder);
		strcat(sMDInfoPath, "Info.txt");
		FILE* fMDInfo = fopen(sMDInfoPath, "r");/*reading from Info.txt*/
		MusicalDirections = insert_mus_dir(MusicalDirections, folderName0, get_text_info(fMDInfo));
		fclose(fMDInfo);
		/*works*/


		char pathMusicians[BUFSIZ] = { 0 };
		strcpy(pathMusicians, sMusDirFolder);
		strcat(pathMusicians, "Musicians.txt");
		FILE* fMusicians = fopen(pathMusicians, "r");
		while (!feof(fMusicians))
		{
			char sMusiciansFolder[BUFSIZ] = { 0 };
			strcpy(sMusiciansFolder, sMusDirFolder);

			char folderName1[41] = { 0 };
			fgets(folderName1, 40, fMusicians);
			if (folderName1[strlen(folderName1) - 1] == '\n')
				folderName1[strlen(folderName1) - 1] = '\0';

			strcat(sMusiciansFolder, folderName1);
			strcat(sMusiciansFolder, "\\");

			char sMInfoPath[BUFSIZ] = { 0 };
			strcpy(sMInfoPath, sMusiciansFolder);
			strcat(sMInfoPath, "Info.txt");
			FILE* fMInfo = fopen(sMInfoPath, "r");/*reading from Info.txt*/
			char musType[10] = { 0 };
			fgets(musType, 9, fMInfo);
			/*найти нужный MusDir, где хранится MusicianTree musicians через folderName0*/
			struct MusDir* currentMusDir = find_md_name(MusicalDirections, folderName0);
			if (!strcmp(musType, "SINGLE\n"))
				currentMusDir->musicians = insert_musician(currentMusDir->musicians, folderName1, get_text_info(fMInfo), SINGLE);
			else
				currentMusDir->musicians = insert_musician(currentMusDir->musicians, folderName1, get_text_info(fMInfo), GROUP);
			fclose(fMInfo);



			char pathAlbums[BUFSIZ] = { 0 };
			strcpy(pathAlbums, sMusiciansFolder);
			strcat(pathAlbums, "Albums.txt");
			FILE* fAlbums = fopen(pathAlbums, "r");
			while (!feof(fAlbums))
			{
				char sAlbumsFolder[BUFSIZ] = { 0 };
				strcpy(sAlbumsFolder, sMusiciansFolder);

				char folderName2[41] = { 0 };
				fgets(folderName2, 40, fAlbums);
				if (folderName2[strlen(folderName2) - 1] == '\n')
					folderName2[strlen(folderName2) - 1] = '\0';

				strcat(sAlbumsFolder, folderName2);
				strcat(sAlbumsFolder, "\\");

				struct Musician* currentMusician = find_mus_name(currentMusDir->musicians, folderName1);
				currentMusician->albums = insert_album(currentMusician->albums, folderName2);


				char pathSongs[BUFSIZ] = { 0 };
				strcpy(pathSongs, sAlbumsFolder);
				strcat(pathSongs, "Songs.txt");
				FILE* fSongs = fopen(pathSongs, "r");
				while (!feof(fSongs))
				{
					char songTextPath[BUFSIZ] = { 0 };
					strcpy(songTextPath, sAlbumsFolder);

					char songName[41] = { 0 };
					fgets(songName, 40, fSongs);
					if (songName[strlen(songName) - 1] == '\n')
						songName[strlen(songName) - 1] = '\0';

					strcat(songTextPath, songName);
					strcat(songTextPath, ".txt");

					FILE* fSongText = fopen(songTextPath, "r");
					struct Album* currentAlbum = find_album_name(currentMusician->albums, folderName2);
					/*rework*/
					char tmpstr[20] = { 0 };
					fgets(tmpstr, 19, fSongs);
					if (tmpstr[strlen(tmpstr) - 1] == '\n')
						tmpstr[strlen(tmpstr) - 1] = '\0';
					int amountOfDiscs = atoi(tmpstr);
					clear_string(tmpstr);
					fgets(tmpstr, 19, fSongs);
					float price = strtof(tmpstr, NULL);

					currentAlbum->songs = insert_song(currentAlbum->songs, songName, get_text_info(fSongText), price, amountOfDiscs);
					generalDiscsAmount += amountOfDiscs;
					fclose(fSongText);
				}
				fclose(fSongs);
				printf("\t\t");
				puts(sAlbumsFolder);
			}
			fclose(fAlbums);
			printf("\t");
			puts(sMusiciansFolder);
		}
		fclose(fMusicians);
		puts(sMusDirFolder);
	}
	fclose(fMusDirs);
}

void clear_screen()
{
	int n;
	for (n = 0; n < 20; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");
}

/*functions used in menu*/
void show_whole_catalog()
{
	clear_screen();
	puts("****************************CATALOG*******************************\n\n");
	show_md(MusicalDirections);
	puts("Press any key to continue...");
	int c = getch();
}

void make_report()
{
	clear_screen();
	FILE* fReport = fopen("Report.txt", "w");
	fprintf(fReport, "REPORT\nSaled songs: %d\nGeneral profit: %6.2f$\nDiscs remain: %d", saledSongsCounter, profit, generalDiscsAmount);
	fclose(fReport);
	puts("Report successfully made!\nPress any key to continue...");
	int c = getch();
}

void show_all_lesseq_than_price(float price)
{
	clear_screen();
	printf("Less than price: %6.2f", price);
	puts("****************************FOUND*******************************\n\n");
	show_md1(MusicalDirections, price);
	puts("Press any key to continue...");
	int c = getch();
}

void show_all_has_enough_copies(int ncopies)
{
	clear_screen();
	printf("More than %d copies  ", ncopies);
	puts("****************************FOUND*******************************\n\n");
	show_md2(MusicalDirections, ncopies);
	puts("Press any key to continue...");
	int c = getch();
}

void find_and_add()/*finding and adding step by step*/
{
	clear_screen();
	printf("Would you like to add another order to your basket? (Yes/No): ");
	char ans[100] = { 0 };
	gets(ans);
	trim(ans);
	while (strcmp(to_lower_case(ans), "yes") && strcmp(to_lower_case(ans), "no"))
	{
		printf("Bad input.\nWould you like to add another order to your basket? (Yes/No): ");
		gets(ans);
		trim(ans);
	}

	if (!strcmp(to_lower_case(ans), "yes"))
	{
		/********************STEP 1***********************/
		printf("Input the musical direction: ");
		char mdname[100] = { 0 };
		gets(mdname);
		trim(mdname);
		struct MusDir* currMD = NULL;
		currMD = find_md_name(MusicalDirections, mdname);
		while (!currMD)
		{
			printf("No such musical direction.\nPress [y] key if you'd like to retry...\n");
			int c = getch();
			if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
			{
				printf("Input the musical direction: ");
				gets(mdname);
				trim(mdname);
				currMD = find_md_name(MusicalDirections, mdname);
			}
			else
				break;
		}
		if (!currMD)/*прерывание ввода*/
		{
			printf("Ok. Maybe next time.\nPress any key to continue...");
			int c = getch();
			return;
		}
		/********************STEP 2***********************/
		printf("\nChosen musical direction: %s\n", currMD->name);
		printf("Input the musician: ");
		char mname[100] = { 0 };
		gets(mname);
		trim(mname);
		struct Musician* currMusician = NULL;
		currMusician = find_mus_name(currMD->musicians, mname);
		while (!currMusician)
		{
			printf("No such musician in this musical direction.\nPress [y] key if you'd like to retry...\n");
			int c = getch();
			if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
			{
				printf("Input the musical direction: ");
				gets(mname);
				trim(mname);
				currMusician = find_mus_name(currMD->musicians, mname);
			}
			else
				break;
		}
		if (!currMusician)/*прерывание ввода*/
		{
			printf("Ok. Maybe next time.\nPress any key to continue...");
			int c = getch();
			return;
		}
		/********************STEP 3***********************/
		printf("\nChosen musician: %s\n", currMusician->name);
		printf("Input the album you want: ");
		char aname[100] = { 0 };
		gets(aname);
		trim(aname);
		struct Album* currAlbum = NULL;
		currAlbum = find_album_name(currMusician->albums, aname);
		while (!currAlbum)
		{
			printf("No such album in this musician section, maybe we'll have it later.\nPress [y] key if you'd like to retry...\n");
			int c = getch();
			if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
			{
				printf("Input the album you want: ");
				gets(aname);
				trim(aname);
				currAlbum = find_album_name(currMusician->albums, aname);
			}
			else
				break;
		}
		if (!currAlbum)/*прерывание ввода*/
		{
			printf("Ok. Maybe next time.\nPress any key to continue...");
			int c = getch();
			return;
		}
		/***************STEP 4 (FINAL)*******************/
		printf("\nChosen album: %s\n", currAlbum->name);
		printf("Input the song you want: ");
		char sname[100] = {0};
		gets(sname);
		trim(sname);
		struct Song* currSong = NULL;
		currSong = find_song_name(currAlbum->songs, sname);
		if (currSong && !currSong->amount_of_copies)
		{
			printf("Sorry, we have no discs left with this song. Press any key to proceed...\n");
			currSong = NULL;
			int c = getch();
		}
		while (!currSong)
		{
			printf("No such song in this album. Probably it's either not even there or we're out of discs.\nPress [y] key if you'd like to retry...\n");
			int c = getch();
			if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
			{
				printf("Input the song you want: ");
				gets(sname);
				trim(sname);
				currSong = find_song_name(currAlbum->songs, sname);
			}
			else
				break;
			if (currSong && !currSong->amount_of_copies)
			{
				printf("Sorry, we have no discs left with this song. Press any key to proceed...\n");
				currSong = NULL;
				int c = getch();
			}
		}
		if (!currSong)
		{
			printf("Ok. Maybe next time.\nPress any key to continue...");
			int c = getch();
			return;
		}

		/********************ADDING STEP***********************/
		puts("****************ORDER INFO***********************");
		printf("Musical Direction Name: %s\n", currMD->name);
		printf("Musician Name: %s\n", currMusician->name);
		printf("Album Name: %s\n", currAlbum->name);
		printf("Song Name: %s\n", currSong->name);
		printf("Price: %2.2f\nDiscs left: %d\n", currSong->price, currSong->amount_of_copies);
		printf("How much discs would you like to order?: ");
		int ncopies = -1;
		while (scanf("%d", &ncopies) != 1 || ncopies <= 0 || ncopies > currSong->amount_of_copies)
		{
			printf("Bad input. It has to be between 1 and %d.\nHow much discs would you like to order?: ", currSong->amount_of_copies);
			rewind(stdin);
		}
		puts("Ok. We will add this order to your basket.");
		add_to_basket(Basket, currMD->name, currMusician->name, currAlbum->name, currSong, ncopies);
		puts("Successfully added!\nPress any key to continue...");
		int c = getch();
	}
	else
	{
		printf("Ok. Maybe next time.\nPress any key to continue...");
		int c = getch();
	}
}

void make_payment()
{
	clear_screen();
	show_basket_info(Basket);
	puts("Would you like to make a payment?(Press [y] key if yes)\n");
	int c = getch();
	if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
		pay(Basket);
	else
	{
		puts("Ok. Maybe next time. Press any key to continue...\n");
		int c = getch();
	}
}

void clear_basket()
{
	clear_screen();
	show_basket_info(Basket);
	puts("Would you like to cancel all the orders?(Press [y] key if yes)\n");
	int c = getch();
	if ((char)c == 'y' || (char)c == 'Y' || (char)c == 'н' || (char)c == 'Н')
		cancel_all_orders(Basket);
	else
	{
		puts("Ok. Maybe next time. Press any key to continue...\n");
		int c = getch();
	}
}

void menu()
{
	int c = ' ';
	while (c != '0')
	{
		clear_screen();
		puts("************************MENU*************************");
		puts("(1)Show whole catalog");
		puts("(2)Make report");
		puts("(3)Show all songs less than price X");
		puts("(4)Show all songs more than X copies");
		puts("(5)Add new order to the Basket");
		puts("(6)Make payment for all orders");
		puts("(7)Cancel all the orders");
		puts("(8)Version");
		puts("(9)Add some money");
		puts("(0)Exit");
		printf("\nYour current balance: %6.2f$", Basket->balance);
		switch (c = getch())
		{
		case '1': 
			show_whole_catalog();
			break;
		case '2':
			make_report();
			break;
		case '3':
			clear_screen();
			printf("Input desired price: ");
			float price = 0;
			while (scanf("%f", &price) != 1 || price <= 0 || price >= 10)
			{
				rewind(stdin);
				puts("Bad input. Choose between 0.01 and 9.99.");
				printf("Input desired price: ");
			}
			rewind(stdin);
			show_all_lesseq_than_price(price);
			break;
		case '4': 
			clear_screen();
			printf("Input desired number of copies: ");
			int ncop = 0;
			while (scanf("%d", &ncop) != 1 || ncop <= 0 || ncop > 100000)
			{
				rewind(stdin);
				puts("Bad input. Choose between 1 and 100K.");
				printf("Input desired number of copies: ");
			}
			rewind(stdin);
			show_all_has_enough_copies(ncop);
			break;
		case '5': 
			find_and_add();
			break;
		case '6': 
			make_payment();
			break;
		case '7': 
			clear_basket();
			break;
		case '8': 
			clear_screen();
			puts("Designed by: Lavrenovich A. E., 953502\nVersion: 1.0_raw");
			int a = getch();
			break;
		case '9':
			clear_screen();
			add_balance(Basket);
			break;
		default: ;/*exit or show menu again*/
		}
	}
}

//********************************ПРОГРАММА******************************************
int main(void)
{
	char* locale = setlocale(LC_ALL, "");
	setlocale(LC_NUMERIC, "C");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	load_database();
	Basket = initialize_basket(150.45);/*balance = value*/

	menu();

	clear_everything();
	//int c = getch();
	return 0;
}