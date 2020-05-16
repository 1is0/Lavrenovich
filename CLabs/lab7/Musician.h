#ifndef MUSICIAN_H
#define MUSICIAN_H
#include "Album.h"

/*********************************»—œŒÀÕ»≈“À‹**************************************/

extern void clear_everything();
extern const char* to_lower_case(char* s);
extern char compare(char* s1, char* s2);

typedef enum { SINGLE, GROUP } MusicianType;

struct Musician
{
	MusicianType mt;
	char* name;
	char* info;
	struct AlbumTree* albums;
};

struct MusicianTree
{
	struct MusicianTree* parent, * left, * right;
	struct Musician* data;
};

struct Musician* free_musician(struct Musician* a);
struct Musician* new_musician(const char* name, const char* info, MusicianType mt);
struct MusicianTree* insert_musician(struct MusicianTree* root, const char* name, const char* info, MusicianType mt);
struct MusicianTree* del_musician_tree(struct MusicianTree* tree);
struct Musician* find_mus_name(struct MusicianTree* root, const char* name);
void show_mus(struct MusicianTree* root);
void show_mus1(struct MusicianTree* root, float price);
void show_mus2(struct MusicianTree* root, int ncop);
#endif