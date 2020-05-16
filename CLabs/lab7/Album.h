#ifndef ALBUM_H
#define ALBUM_H
#include "Song.h"
//*********************************¿À‹¡ŒÃ********************************************
extern void clear_everything();
extern const char* to_lower_case(char* s);
extern char compare(char* s1, char* s2);

struct Album
{
	char* name;
	struct SongTree* songs;
};

struct AlbumTree
{
	struct AlbumTree* parent, * left, * right;
	struct Album* data;
};

struct Album* free_album(struct Album* a);
struct Album* new_album(const char* name);
struct AlbumTree* insert_album(struct AlbumTree* root, const char* name);
struct AlbumTree* del_album_tree(struct AlbumTree* tree);
struct Album* find_album_name(struct AlbumTree* root, const char* name);
void show_albums(struct AlbumTree* root);
void show_albums1(struct AlbumTree* root, float price);
void show_albums2(struct AlbumTree* root, int ncop);
#endif