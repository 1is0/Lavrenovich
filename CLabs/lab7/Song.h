#ifndef SONG_H
#define SONG_H
/********************************* ќћѕќ«»÷»я****************************************/
extern void clear_everything();
extern const char* to_lower_case(char* s);
extern char compare(char* s1, char* s2);

struct Song
{
	char* name;
	char* text;
	float price;/*цена за диск*/
	int amount_of_copies;/*диски с каждой песней*/
};

struct SongTree
{
	struct SongTree* parent, * left, * right;
	struct Song* data;
};

struct Song* free_song(struct Song* a);
struct Song* new_song(const char* name, const char* text, float price, int amount);
struct SongTree* insert_song(struct SongTree* root, const char* name, const char* text, float price, int amount);
struct SongTree* del_song_tree(struct SongTree* tree);
struct Song* find_song_name(struct SongTree* root, const char* name);
void show_songs(struct SongTree* root);
void show_songs1(struct SongTree* root, float price);
void show_songs2(struct SongTree* root, int ncop);
#endif