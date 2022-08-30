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

#define TEMPO 200

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int melody[] = {

	// Super Mario Bros theme
	// Score available at https://musescore.com/user/2123/scores/2145
	// Theme by Koji Kondo
	
	
	NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
	NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

	
	REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
	REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
	REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
	NOTE_C5,2, REST,2,

	REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
	REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
	REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
	NOTE_C5,2, REST,2,

	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
	REST,1,
	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
	NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
	NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
	
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
	
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
	NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
	
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
	NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
	REST,1,

	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
	NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
	NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
	
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
	NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
	
	//game over sound
	NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
	NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
	NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,

};


int wholenote = (60000 * 4) / TEMPO;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int divider = 0, noteDuration = 0;

void init(void);
void set_buzzer(void);
void clear_buzzer(void);
int  get_startstop(void);
int  get_selecao(void);
void buzzer_test(int freq);
void tone(int freq, int time);


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
	int wait = 1E6/(freq);
	set_buzzer();     
	delay_us(wait/2);                           
	clear_buzzer();   
	delay_us(wait/2);
	
}

void tone(int freq, int time){
	 int i = 0;
	 // precisamos contar a quantidade de pulsos no tempo (dado em ms), logo basta converter o tempo para segundos e multiplicar pela frequencia de oscilação, lembrando do casting para nao perder valor.
	 int count = (double)freq * ((double) time/1000);
	 while (i < n){
		 buzzer_test(freq);
		 i++;
	 }
	
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
			gfx_mono_draw_string("           ", 50,16, &sysfont);
			gfx_mono_draw_string("Mario  ", 50,16, &sysfont);
			delay_ms(1000); 
			
			for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
				divider = melody[thisNote + 1];
				noteDuration = (wholenote) / abs(divider);
				if (divider < 0) {
					noteDuration *= 1.5; 
				}
				if  (melody[thisNote] == 0){
					// Wait for the specief duration before playing the next note.
					delay_ms(noteDuration);
				}
				else{
					tone(melody[thisNote], noteDuration*0.9);
					delay_ms(noteDuration*0.5);
				}
				
			}
		}
		if (!get_selecao()){
			gfx_mono_draw_string("teste", 50,16, &sysfont);
			delay_ms(1000); 
		}
		gfx_mono_draw_string("sim  ", 50,16, &sysfont);
		
	}
}
