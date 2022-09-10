/*
 * functions.h
 *
 * Created: 9/9/2022 12:56:10 AM
 *  Author: Matheus & Lister
 */ 

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "musics.h"

#define BUZZER_PIO        PIOA                 // periferico que controla o BUZZER
#define BUZZER_PIO_ID        ID_PIOA              // ID do periférico PIOA (controla BUZZER)
#define BUZZER_PIO_IDX       4                    // ID do BUZZER no PIO
#define BUZZER_PIO_IDX_MASK  (1 << BUZZER_PIO_IDX)   // Mascara para CONTROLARMOS o BUZZER

#define START_PIO PIOD
#define START_PIO_ID ID_PIOD
#define START_PIO_IDX 28
#define START_PIO_IDX_MASK (1u << START_PIO_IDX)

#define SELECAO_PIO PIOC
#define SELECAO_PIO_ID ID_PIOC
#define SELECAO_PIO_IDX 31
#define SELECAO_PIO_IDX_MASK (1u << SELECAO_PIO_IDX)

//LED1
#define LED1_PIO           PIOA                 // periferico que controla o LED
#define LED1_PIO_ID        ID_PIOA              // ID do periférico PIOC (controla LED)
#define LED1_PIO_IDX       0                   // ID do LED no PIO
#define LED1_PIO_IDX_MASK  (1 << LED1_PIO_IDX)   // Mascara para CONTROLARMOS o LED

//LED2
#define LED2_PIO           PIOC                 // periferico que controla o LED
#define LED2_PIO_ID        ID_PIOC              // ID do periférico PIOC (controla LED)
#define LED2_PIO_IDX       30                    // ID do LED no PIO
#define LED2_PIO_IDX_MASK  (1 << LED2_PIO_IDX)   // Mascara para CONTROLARMOS o LED

//LED3
#define LED3_PIO           PIOB                 // periferico que controla o LED
#define LED3_PIO_ID        ID_PIOB              // ID do periférico PIOC (controla LED)
#define LED3_PIO_IDX       2                    // ID do LED no PIO
#define LED3_PIO_IDX_MASK  (1 << LED3_PIO_IDX)   // Mascara para CONTROLARMOS o LED

extern volatile char stop;
extern volatile char but_flag;
extern volatile char selecao_flag;
extern volatile char simbolo;
extern volatile char desenha;
extern volatile char troca;
extern int led;
extern int thisNote;
extern int start;

void set_buzzer(void);
void clear_buzzer(void);
int  get_startstop(void);
int  get_selecao(void);
void buzzer_test(int freq);
void tone(int freq, int time);
void play(song musica);
void barra_interativa(void);
void botao_pause(void);
void botao_play(void);

#endif /* FUNCTIONS_H_ */