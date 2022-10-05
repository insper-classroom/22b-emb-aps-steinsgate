/*
 * play.h
 *
 * Created: 9/10/2022 3:40:17 PM
 *  Author: Matheus&Lister
 */ 

#ifndef PLAY_H_
#define PLAY_H_
#include "musicas.h"
#include "pinos.h"


void botao_pause(void);
void buzzer_test(int freq);
void tone(int freq, int time);
void play(song musica);
void barra_interativa(void);
void botao_play(void);
void escreve_musica(void);
void limpa_botaopause(void);
void desenha_play(void);
void init(void);
void but_callback(void);
void selecao_callback(void);
void atualiza_led(void);
void atualiza_simbolo(void);
void tela_inicial(void);
void toca_musica(song musicas[]);

extern volatile char stop;
extern volatile char but_flag;
extern volatile char selecao_flag;
extern volatile char simbolo;
extern volatile char desenha;
extern volatile char troca;
extern int thisNote;
extern int start;

#endif /* PLAY_H_ */