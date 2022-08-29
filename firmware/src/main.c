#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define BUZZER_PIO        PIOA                 // periferico que controla o LED
#define BUZZER_PIO_ID        ID_PIOA              // ID do periférico PIOC (controla LED)
#define BUZZER_PIO_IDX       4                    // ID do LED no PIO
#define BUZZER_PIO_IDX_MASK  (1 << BUZZER_PIO_IDX)   // Mascara para CONTROLARMOS o LED

void init(void);

void init(void)
{
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	//Inicializa PC8 como saída
	// POINTER, BITMASK, default level ,  pin configure open-drain , pull-up activate
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
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
  gfx_mono_draw_string("mundo", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);      // Coloca 1 no pino LED
		delay_ms(100);                           // Delay por software de 200 ms
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);    // Coloca 0 no pino do LED
		delay_ms(100);
	}
}
