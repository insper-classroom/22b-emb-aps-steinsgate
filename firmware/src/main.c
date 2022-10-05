#include <asf.h>


#include "mario.h"
#include "starwars.h"
#include "godfather.h"
#include "play.h"
#include "musicas.h"
#include "pinos.h"
#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"


int main (void)
{
	init();
	gfx_mono_draw_string("Inicie", 45,16, &sysfont);
	song mario;
	song star_wars;
	song godfather;
	start_struct(&mario,mario_song,time_mario,notes_mario);
	start_struct(&star_wars,starwars_song,time_starwars,notes_starwars);
	start_struct(&godfather,godfather_song,time_godfather,notes_godfather);
	song musicas[] = {mario, star_wars, godfather};

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		tela_inicial();
		desenha_play();
		toca_musica(musicas);
		escreve_musica();
	}
}
