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
#include "musicas.h"

volatile char stop = 1;
volatile char but_flag;
volatile char selecao_flag = 0;
volatile char simbolo = 0;
volatile char desenha = 0;
volatile char troca = 0 ;
int led = 0;
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
		if (selecao_flag == 1){
			gfx_mono_draw_string("          ", 25,16, &sysfont);
			gfx_mono_draw_string("Mario", 45,16, &sysfont);
		}
		else if (selecao_flag == 2){
			gfx_mono_draw_string("           ", 25,16, &sysfont);
			gfx_mono_draw_string("Star Wars", 35,16, &sysfont);
		}
		else  if (selecao_flag == 3){
			gfx_mono_draw_string("          ", 25,16, &sysfont);
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

void set_buzzer(void){
	pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(void){
	pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

int  get_startstop(void){
	return pio_get(START_PIO, PIO_INPUT, START_PIO_IDX_MASK);
}

int  get_selecao(void){
	return pio_get(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK);
}

void atualiza_led(){
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

void buzzer_test(int freq){
	atualiza_led();
	int wait = 1E6/(freq);
	set_buzzer();
	delay_us(wait/2);
	clear_buzzer();
	delay_us(wait/2);
	led=!led;
}

void tela_inicial(){
	if (start){
		botao_play();
		barra_interativa();
	}
}
void tone(int freq, int time){
	int i = 0;
	// precisamos contar a quantidade de pulsos no tempo (dado em ms), logo basta converter o tempo para segundos e
	// multiplicar pela frequencia de oscilação, lembrando do casting para nao perder valor.
	double time_s = (double) time/1000;
	int count = (float)freq * time_s;
	while (i < count){
		buzzer_test(freq);
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

void init(void)
{
	board_init();
	// Initialize the board clock
	sysclk_init();
	// Init OLED
	gfx_mono_ssd1306_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_configure(LED1_PIO, PIO_OUTPUT_0, LED1_PIO_IDX_MASK, PIO_DEFAULT);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_configure(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK, PIO_DEFAULT);
	pmc_enable_periph_clk(LED3_PIO_ID);
	pio_configure(LED3_PIO, PIO_OUTPUT_0, LED3_PIO_IDX_MASK, PIO_DEFAULT);
	
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECAO_PIO_ID);
	
	//Inicializa PC8 como saída
	// POINTER, BITMASK, default level ,  pin configure open-drain , pull-up activate
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	
	pio_configure(START_PIO, PIO_INPUT, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(START_PIO, START_PIO_IDX_MASK, 60);
	
	pio_configure(SELECAO_PIO, PIO_INPUT, SELECAO_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(SELECAO_PIO, SELECAO_PIO_IDX_MASK, 60);
	
	pio_handler_set(START_PIO,
	START_PIO_ID,
	START_PIO_IDX_MASK,
	PIO_IT_RISE_EDGE,
	but_callback);
	
	pio_handler_set(SELECAO_PIO,
	SELECAO_PIO_ID,
	SELECAO_PIO_IDX_MASK,
	PIO_IT_RISE_EDGE,
	selecao_callback);
	
	// Ativa interrupção e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(START_PIO, START_PIO_IDX_MASK);
	pio_get_interrupt_status(START_PIO);
	
	pio_enable_interrupt(SELECAO_PIO, SELECAO_PIO_IDX_MASK);
	pio_get_interrupt_status(SELECAO_PIO);
	
	NVIC_EnableIRQ(START_PIO_ID);
	NVIC_SetPriority(START_PIO_ID, 4); // Prioridade 4
	NVIC_EnableIRQ(SELECAO_PIO_ID);
	NVIC_SetPriority(SELECAO_PIO_ID, 4); // Prioridade 4
}