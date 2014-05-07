#include "main.h"
#include "config.h"
#include "player.h"
#include "bitmap.h"
#include "text.h"
Text::Text(){
	versionInfo = al_load_font("arial.ttf", 10, 0);
	font16 = al_load_font("Starcraft.ttf", 16, 0);
	font12 = al_load_font("arial.ttf", 12, 0);
	font36 = al_load_font("arial.ttf", 36, 0);
	font24 = al_load_font("arial.ttf", 24, 0);
	font12s = al_load_font("arial.ttf", 13, 0);
	font24sc = al_load_font("Starcraft.ttf", 48, 0);
}
Text::~Text(){
	al_destroy_font(font16);
	al_destroy_font(font12);
	al_destroy_font(font36);
	al_destroy_font(font24);
	al_destroy_font(font12s);
	al_destroy_font(font24sc);
	al_destroy_font(versionInfo);
}

void Text::viewVersion(){
	Config mConf;
	al_draw_textf(versionInfo, al_map_rgb(190,190,190), 630, 468, ALLEGRO_ALIGN_RIGHT, "Wersja gry: %04i , %s ", mConf.getBuild(), mConf.getStatus().c_str());

}

void Text::viewInfo(){
	//Config mConf;
	//al_draw_textf(font16, al_map_rgb(255,0,0), 20, mConf.getHeight() - 20, 0, "To jest wersja %s", mConf.getStatus().c_str());
}

void Text::viewScore(int wynik, int live, int killed, int left, int shoots){
	al_draw_textf(font12s, al_map_rgb(255,255,255), 30, 5, 0, "Wynik : %i     Pozostale zycia : %i     Zabici : %i     Pominieci : %i      Strzalow : %i", wynik, live, killed, left, shoots);
}
void Text::viewScoreMulti(Player mPlayer1, Player mPlayer2){			
	al_draw_textf(font12s, al_map_rgb(0,255,0), 30, -2, 0, "Player 1 =   Wynik : %i     Pozostale zycia : %i     Zabici : %i       Strzalow : %i", mPlayer1.getScore(),  mPlayer1.getLives(), mPlayer1.getNrKilled(), mPlayer1.getNrShoots());
	al_draw_textf(font12s, al_map_rgb(255,255,0), 30, 10, 0, "Player 2 =   Wynik : %i     Pozostale zycia : %i     Zabici : %i       Strzalow : %i", mPlayer2.getScore(),  mPlayer2.getLives(), mPlayer2.getNrKilled(), mPlayer2.getNrShoots());
	al_draw_textf(font12s, al_map_rgb(255,255,255), 500, 4, 0, "Pominieci : %i", mPlayer1.getNrLeft());
}
void Text::cziter(){
	al_draw_textf(font12s, al_map_rgb(255,0,0), 40, 50, 0, "CZITER!");
	al_draw_textf(font12s, al_map_rgb(255,0,0), 550, 50, 0, "CZITER!");
	al_draw_textf(font12s, al_map_rgb(255,0,0), 40, 420, 0, "CZITER!");
	al_draw_textf(font12s, al_map_rgb(255,0,0), 550, 420, 0, "CZITER!");
}
void Text::viewBigScore(int wynik){
	Config mConf;
	
	al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2, ALLEGRO_ALIGN_CENTER , "Wynik koncowy: %i", wynik);
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 40, ALLEGRO_ALIGN_CENTER , "Wcisnij 'R' by zagrac ponownie");
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 70, ALLEGRO_ALIGN_CENTER , "Wcisnij 'ENTER' by zapisac wynik");
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 100, ALLEGRO_ALIGN_CENTER , "Wcisnij 'Esc' by przejsc do menu");
}
void Text::viewBigScore(int wynik1, int wynik2){
	Config mConf;
	
	al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, 70, ALLEGRO_ALIGN_CENTER , "Wynik koncowy");
	al_draw_textf(font24, al_map_rgb(0,255,0), mConf.getWidth() / 2, 120, ALLEGRO_ALIGN_CENTER , "Player 1:         %i", wynik1);
	al_draw_textf(font24, al_map_rgb(255,255,0), mConf.getWidth() / 2, 160, ALLEGRO_ALIGN_CENTER , "Player 2:         %i", wynik2);
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 90, ALLEGRO_ALIGN_CENTER , "Wcisnij 'R' by zagrac ponownie");
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 120, ALLEGRO_ALIGN_CENTER , "Wcisnij 'ENTER' by zapisac wynik");
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 150, ALLEGRO_ALIGN_CENTER , "Wcisnij 'Esc' by przejsc do menu");
}

void Text::viewBigScoreArc(int wynik){
	Config mConf;
	
	al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2, ALLEGRO_ALIGN_CENTER , "Wynik koncowy: %i", wynik);
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 70, ALLEGRO_ALIGN_CENTER , "Wcisnij 'R' by zagrac ponownie");
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 100, ALLEGRO_ALIGN_CENTER , "Wcisnij 'Esc' by przejsc do menu");
}
void Text::viewBigScoreArc(int wynik1, int wynik2){
	Config mConf;
	
	al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, 70, ALLEGRO_ALIGN_CENTER , "Wynik koncowy");
	al_draw_textf(font24, al_map_rgb(0,255,0), mConf.getWidth() / 2, 120, ALLEGRO_ALIGN_CENTER , "Player 1:         %i", wynik1);
	al_draw_textf(font24, al_map_rgb(255,255,0), mConf.getWidth() / 2, 160, ALLEGRO_ALIGN_CENTER , "Player 2:         %i", wynik2);
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 120, ALLEGRO_ALIGN_CENTER , "Wcisnij 'R' by zagrac ponownie");
	al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, mConf.getHeight() / 2 + 150, ALLEGRO_ALIGN_CENTER , "Wcisnij 'Esc' by przejsc do menu");
}
void Text::saved(){
	Config mConf;
	al_draw_textf(font24, al_map_rgb(80,80,80), mConf.getWidth() / 2, mConf.getHeight() / 2 + 70, ALLEGRO_ALIGN_CENTER , "Wcisnij 'ENTER' by zapisac wynik");
}
void Text::timer(Player & mPlayer){
	Config mConf;
	al_draw_textf(font12, al_map_rgb(255,255,255), 300, mConf.getHeight() - 20, 0, "Timer: %i    Stage: %i     SubStage: %i", mPlayer.getTimer(), mPlayer.getStage(), mPlayer.getSubStage());
}

void Text::drawHP(int maxHP, int hp, int x, int y){
	if(hp > 0){
		al_draw_textf(font12, al_map_rgb(100,100,100), x, y, ALLEGRO_ALIGN_CENTER, "%i/%i", hp, maxHP);
	} else {
		al_draw_textf(font12, al_map_rgb(200,0,0), x, y, ALLEGRO_ALIGN_CENTER, "0/%i", maxHP);
	}

}
void Text::drawUI(Bitmap &mBitmap){
	al_draw_bitmap(mBitmap.overlay, 0, 0, 0);

}
void Text::countDown(Player & mPlayer){
	Config mConf;
	al_draw_textf(font24sc, al_map_rgb(255,0,0), mConf.getWidth() / 2, mConf.getHeight() / 2, ALLEGRO_ALIGN_CENTER, "%i", mPlayer.getRestTime() /60 + 1);

}
void Text::pause(){
	Config mConf;
	al_draw_textf(font24sc, al_map_rgb(255,0,0), mConf.getWidth() / 2, mConf.getHeight() / 2, ALLEGRO_ALIGN_CENTER, "Pauza");
	al_draw_textf(font16, al_map_rgb(255,0,0), mConf.getWidth() / 2, mConf.getHeight() / 2 + 50, ALLEGRO_ALIGN_CENTER, "Wcisnij 'P'");
}

void Text::nextPhase(Player &mPlayer){
	Config mConf;
	al_draw_textf(font24sc, al_map_rgb(255,0,0), mConf.getWidth() / 2, mConf.getHeight() / 2 - 50, ALLEGRO_ALIGN_CENTER, "Faza %i", mPlayer.getStage());
}