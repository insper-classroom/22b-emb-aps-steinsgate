#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "songs.h"

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

volatile char stop = 1;
volatile char but_flag;
volatile char selecao_flag = 0;
int led = 0;

void init(void);
void set_buzzer(void);
void clear_buzzer(void);
int  get_startstop(void);
int  get_selecao(void);
void buzzer_test(int freq);
void tone(int freq, int time);
void play(int melodia[], int time, int notes);
void barra_interativa(void);
void botao_play(void);
void botao_pause(void);


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
	int wait = 1E6/(freq);
	set_buzzer();     
	delay_us(wait/2);                    
	clear_buzzer();   
	delay_us(wait/2);
	led=!led;
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

void play(int melodia[], int time, int notes){
		int wholenote = (60000 * 4) / time;
		int divider = 0;
		
		for(int i=140;i>=0;i-=2){
			gfx_mono_draw_rect(i, 5, 2, 5, GFX_PIXEL_CLR);
		}
		
		for (int thisNote = 0; thisNote < notes * 2 && !stop; thisNote = thisNote + 2) {
			gfx_mono_draw_rect(100*thisNote / (2*notes) + 30 , 5, 2, 5, GFX_PIXEL_SET);
			divider = melodia[thisNote + 1];
			int noteDuration = (wholenote) / abs(divider);
			if (divider < 0) {
				noteDuration *= 1.5;
			}
			if  (melodia[thisNote] != 0){
				tone(melodia[thisNote], noteDuration*0.9);
				delay_ms(noteDuration/2);
			}
			else{
				delay_ms(noteDuration);
			}
		}
}

void barra_interativa(void){
	for(int i=40;i<=120;i+=2){
		
		gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_SET);
		delay_ms(10);
		
	}
	for(int i=120;i>=40;i-=2){
		
		gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_CLR);
		delay_ms(10);
		
	}
}

void botao_play(void){
	gfx_mono_generic_draw_vertical_line(2, 10, 25,GFX_PIXEL_SET);
	gfx_mono_generic_draw_line(2,10,17,20,GFX_PIXEL_SET);
	gfx_mono_generic_draw_line(2,30,17,20,GFX_PIXEL_SET);
}

void botao_pause(void){
	gfx_mono_generic_draw_vertical_line(2, 17, 10,GFX_PIXEL_SET);
	gfx_mono_generic_draw_vertical_line(8, 17, 10,GFX_PIXEL_SET);
}

void but_callback(void)
{
	stop = !stop;
	but_flag = 1;
}

void selecao_callback(void)
{
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
	gfx_mono_draw_string("         ", 25,16, &sysfont);
	gfx_mono_draw_string("Inicie", 45,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		if (stop){
			gfx_mono_draw_filled_rect(2,8,20,23,GFX_PIXEL_CLR);
			botao_play();
		}
		else{
			gfx_mono_draw_filled_rect(2,8,20,23,GFX_PIXEL_CLR);
			botao_pause();
		}
		if (but_flag){
			if (selecao_flag == 1){
				play(mario,time_mario,notes_mario);
			}
			else if(selecao_flag ==2){
				play(starwars,time_starwars,notes_starwars);
			}
			else if(selecao_flag ==3){
				play(godfather,time_godfather,notes_godfather);
			}
			but_flag = 0;
		}
		if (!get_selecao()){
			if (selecao_flag == 1){
				gfx_mono_draw_string("          ", 25,16, &sysfont);
				gfx_mono_draw_string("Star Wars", 30,16, &sysfont);
				
			}
			else if (selecao_flag == 2){
				gfx_mono_draw_string("           ", 25,16, &sysfont);
				gfx_mono_draw_string("Godfather", 35,16, &sysfont);
				
			}
			else  if (selecao_flag == 3){
				gfx_mono_draw_string("          ", 25,16, &sysfont);
				gfx_mono_draw_string("Mario", 45,16, &sysfont);
			}
			
			
		}		
	}
}
