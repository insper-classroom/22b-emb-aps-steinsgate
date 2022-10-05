/*
 * musicas.c
 *
 * Created: 9/10/2022 4:40:21 PM
 *  Author: Matheus&Lister
 */ 

#include "musicas.h"

void start_struct(song *musica,int *melodia, int time, int size){
	musica->size = size;
	musica->tones = &melodia[0];
	musica->time = time;
}