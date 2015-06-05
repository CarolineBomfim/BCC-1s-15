#ifndef _MUSIC_H_
#define _MUSIC_H_

typedef struct _music {
	int nBlocos;
	char ***music;
}music;
music alocaMusic(int total);
music readFileMusic(global_var *global, char *file);
void freeMusic(music musica);
#endif
