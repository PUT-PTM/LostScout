#ifndef MAIN_H
	#include <iostream>
	#include <locale.h>
	#include <stdio.h>
	#include <string>
	#include <cstdlib>
	#include <fstream> 

	#include <allegro5/allegro.h>
	#include <allegro5/allegro_font.h>
	#include <allegro5/allegro_ttf.h>
	#include <allegro5/allegro_primitives.h>
	#include <allegro5/allegro_image.h>
	#include <allegro5/allegro_audio.h>
	#include <allegro5/allegro_acodec.h>
	using namespace std; 
#endif

	class Bitmap;
	class Config;
	void game(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, Bitmap & mBitmap);
	int menu(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, Bitmap & mBitmap);
	void score(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, Bitmap & mBitmap);
	void arcade(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, Bitmap & mBitmap);

	void saveScoreFile(string name, int score);