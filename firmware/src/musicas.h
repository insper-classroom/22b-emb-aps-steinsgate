/*
 * musicas.h
 *
 * Created: 9/10/2022 4:40:34 PM
 *  Author: Matheus
 */ 


#ifndef MUSICAS_H_
#define MUSICAS_H_

typedef struct {
	int size;
	int time;
	int *tones;
} song;

void start_struct(song *musica,int *melodia, int time, int size);

#endif /* MUSICAS_H_ */