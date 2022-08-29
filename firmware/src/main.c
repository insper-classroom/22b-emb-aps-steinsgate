#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

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

void init(void);
void set_buzzer(void);
void clear_buzzer(void);
int  get_startstop(void);
int  get_selecao(void);
void buzzer_test(int freq);

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

void buzzer_test(int freq){
	int tempo = 100/(freq);
	set_buzzer();     
	delay_ms(tempo);                           
	clear_buzzer();   
	delay_ms(tempo);
	
}

void init(void)
{
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECAO_PIO_ID);
	
	//Inicializa PC8 como saída
	// POINTER, BITMASK, default level ,  pin configure open-drain , pull-up activate
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	
	pio_set_input(START_PIO, START_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(SELECAO_PIO, SELECAO_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(START_PIO, START_PIO_IDX_MASK, 1);
	pio_pull_up(SELECAO_PIO, SELECAO_PIO_IDX_MASK, 1);
}

int main (void)
{
	board_init();
	init();
	delay_init();

  // Init OLED
	gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string("sim", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		if (!get_startstop()){
			gfx_mono_draw_string("nao", 50,16, &sysfont);
			delay_ms(1000); 
		}
		if (!get_selecao()){
			gfx_mono_draw_string("kkk", 50,16, &sysfont);
			delay_ms(1000); 
		}
		gfx_mono_draw_string("sim", 50,16, &sysfont);
		
		buzzer_test(1);
		
	}
}
