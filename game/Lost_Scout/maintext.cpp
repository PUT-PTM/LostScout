#include "main.h"
#include "config.h"
void mainText(Config mC){
	ALLEGRO_FONT *font16 = al_load_font("Starcraft.ttf", 16, 0);
	ALLEGRO_FONT *versionInfo = al_load_font("arial.ttf", 10, 0);
   

   
	al_draw_text(font16, al_map_rgb(255,0,0), 0, 0, 0, "To jest wersja preAlpha");
	cout << mC.getStatus();
	al_draw_textf(versionInfo, al_map_rgb(150,150,150), 630, 468, ALLEGRO_ALIGN_RIGHT, 
	   "Wersja gry: %04i , %s ", mC.getBuild(), mC.getStatus());

}