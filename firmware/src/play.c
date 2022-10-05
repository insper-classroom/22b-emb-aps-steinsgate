/*
 * play.c
 *
 * Created: 9/10/2022 3:40:01 PM
 *  Author: Matheus&Lister
 */ 

#include "play.h"
#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "pinos.h"
#include "musicas.h"

volatile char stop = 1;
volatile char but_flag;
volatile char selecao_flag = 0;
volatile char simbolo = 0;
volatile char desenha = 0;
volatile char troca = 0 ;
int thisNote = 0;
int start = 1;


void toca_musica(song musicas[]){
	if (but_flag){
		start = 0;
		play(musicas[selecao_flag-1]);
		but_flag = 0;
	}
}
void but_callback(void)
{
	simbolo = !simbolo;
	stop = !stop;
	desenha = 1;
	but_flag = 1;
}

void selecao_callback(void)
{
	thisNote = 0;
	simbolo = 0;
	troca = 1;
	if (selecao_flag > 2){
		selecao_flag = 1;
		return;
	}
	selecao_flag++;
}

void desenha_play(){
	if (stop){
		if (!simbolo && desenha){
			limpa_botaopause();
			botao_play();
			desenha = 0;
		}
	}
}
void escreve_musica(){
	if (troca){
		gfx_mono_draw_string("          ", 25,16, &sysfont);
		if (selecao_flag == 1){
			gfx_mono_draw_string("Mario", 45,16, &sysfont);
		}
		else if (selecao_flag == 2){
			gfx_mono_draw_string("Star Wars", 35,16, &sysfont);
		}
		else  if (selecao_flag == 3){
			gfx_mono_draw_string("Godfather", 35,16, &sysfont);
		}
		troca = 0;
	}
}

void botao_pause(void){
	gfx_mono_generic_draw_vertical_line(2, 10, 20,GFX_PIXEL_SET);
	gfx_mono_generic_draw_vertical_line(12, 10, 20,GFX_PIXEL_SET);
}

void barra_interativa(void){
	for(int i=40;i<=120 && !troca;i+=2){
		gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_SET);
		delay_ms(10);
	}
	for(int i=120;i>=40 && !troca;i-=2){
		gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_CLR);
		delay_ms(10);
	}
}

void limpa_botaopause(){
	gfx_mono_generic_draw_vertical_line(2, 10, 20,GFX_PIXEL_CLR);
	gfx_mono_generic_draw_vertical_line(12, 10, 20,GFX_PIXEL_CLR);
}
void botao_play(void){
	gfx_mono_generic_draw_vertical_line(2, 10, 20,GFX_PIXEL_SET);
	gfx_mono_generic_draw_line(2,10,15,20,GFX_PIXEL_SET);
	gfx_mono_generic_draw_line(2,30,15,20,GFX_PIXEL_SET);
}



void atualiza_led(int led){
	if (led){
		pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
	}
	else{
		pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	}
}

void buzzer_test(int freq, int led){
	atualiza_led(led);
	int wait = 1E6/(freq);
	set_buzzer();
	delay_us(wait/2);
	clear_buzzer();
	delay_us(wait/2);
}

void tela_inicial(){
	if (start){
		botao_play();
		barra_interativa();
	}
}
void tone(int freq, int time){
	int i = 0;
	int led = 0;
	// precisamos contar a quantidade de pulsos no tempo (dado em ms), logo basta converter o tempo para segundos e
	// multiplicar pela frequencia de oscilação, lembrando do casting para nao perder valor.
	if (!freq){
		delay_ms(time);
		return;
	}
	double time_s = (double) time/1000;
	int count = (float)freq * time_s;
	while (i < count){
		led=!led;
		buzzer_test(freq, led);
		i++;
	}
}

void atualiza_simbolo(){
	if (simbolo){
		gfx_mono_generic_draw_vertical_line(2, 10, 20,GFX_PIXEL_CLR);
		gfx_mono_generic_draw_line(2,10,15,20,GFX_PIXEL_CLR);
		gfx_mono_generic_draw_line(2,30,15,20,GFX_PIXEL_CLR);
		botao_pause();
	}
}

void play(song musica){
	int wholenote = (60000 * 4) / musica.time;
	int divider = 0;
	if (!thisNote){
		atualiza_simbolo();
		for(int i=140;i>=0;i-=2){
			gfx_mono_draw_rect(i, 5, 2, 5, GFX_PIXEL_CLR);
		}
	}
	for (thisNote; thisNote < musica.size * 2 && !stop; thisNote = thisNote + 2) {
		gfx_mono_draw_rect(97*thisNote / (2*musica.size) + 30 , 5, 2, 5, GFX_PIXEL_SET);
		atualiza_simbolo();
		divider = musica.tones[thisNote + 1];
		int noteDuration = (wholenote) / abs(divider);
		if (divider < 0) {
			noteDuration *= 1.5;
		}
		if  (musica.tones[thisNote] != 0){
			tone(musica.tones[thisNote], noteDuration*0.9);
			delay_ms(noteDuration/2);
		}
		else{
			delay_ms(noteDuration);
		}
	}
}

