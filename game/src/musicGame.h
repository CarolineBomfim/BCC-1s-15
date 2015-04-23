#ifndef _MUSIC_H_
#define _MUSIC_H_

typedef struct _music {
	int nBlocos;
	int ***music;
}music;
music alocaMusic(int total);
music readFileMusic(char *file);
void freeMusic(music musica);
#endif
