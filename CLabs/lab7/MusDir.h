#ifndef MUSDIR_H
#define MUSDIR_H
#include "Musician.h"
/*********************************Ã”« Õ¿œ–¿¬À≈Õ»≈**********************************/
extern void clear_everything();
extern const char* to_lower_case(char* s);
extern char compare(char* s1, char* s2);

struct MusDir
{
	char* name;
	char* info;
	struct MusicianTree* musicians;
};

struct MusDirTree
{
	struct MusDirTree* parent, * left, * right;
	struct MusDir* data;
};

struct MusDir* free_mus_dir(struct MusDir* a);
struct MusDir* new_mus_dir(const char* name, const char* info);
struct MusDirTree* insert_mus_dir(struct MusDirTree* root, const char* name, const char* info);
struct MusDirTree* del_mus_dir_tree(struct MusDirTree* tree);
struct MusDir* find_md_name(struct MusDirTree* root, const char* name);
void show_md(struct MusDirTree* root);
void show_md1(struct MusDirTree* root, float price);
void show_md2(struct MusDirTree* root, int ncop);
#endif
