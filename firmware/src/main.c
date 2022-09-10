#include <asf.h>


#include "songs.h"
#include "play.h"
#include "musicas.h"
#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

void init(void);


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
	troca = 1;
	if (selecao_flag > 2){
		selecao_flag = 1;
		return;
	}
	selecao_flag++;
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

int main (void)
{
	init();
  // Escreve na tela um circulo e um texto
	//gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string("Inicie", 45,16, &sysfont);
	song mario;
	song star_wars;
	song godfather;
	start_struct(&mario,mario_song,time_mario,notes_mario);
	start_struct(&star_wars,starwars_song,time_starwars,notes_starwars);
	start_struct(&godfather,godfather_song,time_godfather,notes_godfather);


  /* Insert application code here, after the board has been initialized. */
	while(1) {
		if (start){
			botao_play();
			barra_interativa();
		}
		
		if (stop){
			if (!simbolo && desenha){
				gfx_mono_generic_draw_vertical_line(2, 10, 20,GFX_PIXEL_CLR);
				gfx_mono_generic_draw_vertical_line(12, 10, 20,GFX_PIXEL_CLR);
				botao_play();
				desenha = 0;
			}
		}
		if (but_flag){
			start = 0;
			if (selecao_flag == 1){
				play(mario);
			}
			else if(selecao_flag ==2){
				play(star_wars);
			}
			else if(selecao_flag ==3){
				play(godfather);
			}
			but_flag = 0;
		}
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
}
