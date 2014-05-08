#include "main.h"
#include "config.h"
#include "sound.h"
#include "text.h"
#include "bitmap.h"

int menu (Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, Bitmap & mBitmap){
	cout << "Menu" << endl;

	//Config mConf;
	Text mText;
	Sound mSound(mConf);
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	bool end = false;
	al_start_timer(timer);	
	ALLEGRO_FONT *font36 = al_load_font("Starcraft.ttf", 36, 0);
	ALLEGRO_FONT *font24 = al_load_font("Starcraft.ttf", 24, 0);

	int wybor = 1;
	int max = 4;

	mSound.menu();

	while(!end){
		mText.drawUI(mBitmap);
		al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, 40, ALLEGRO_ALIGN_CENTER , "Zagubiony Scout");

		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);


		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode)	{
			case ALLEGRO_KEY_UP:
				mSound.point();
				wybor--;
				break;
			case ALLEGRO_KEY_DOWN:
				mSound.point();
				wybor++;
				break;
			case ALLEGRO_KEY_ENTER:
				mSound.click();
				al_rest(0.35);
				end = true;
				break;
			case ALLEGRO_KEY_M:
				mSound.muteSound(mConf);
				if(mConf.mute == false)
					mSound.menu();
				break;
			case ALLEGRO_KEY_ESCAPE:
				mSound.click();
				al_rest(0.35);
				wybor = 0;
				end = true;
				break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			wybor = 0;
			end = true;
			exit = 1;
		}

		if(wybor <=0 && !end){
			wybor = max;
		}
		if(wybor > max){
			wybor = 1;
		}

		if(wybor == 1){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 200, ALLEGRO_ALIGN_CENTER , "Start gry");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 200, ALLEGRO_ALIGN_CENTER , "Start gry");
		}
		if(wybor == 2){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 250, ALLEGRO_ALIGN_CENTER , "Tryb arcade");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 250, ALLEGRO_ALIGN_CENTER , "Tryb arcade");
		}
		if(wybor == 3){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 300, ALLEGRO_ALIGN_CENTER , "Najlepsze wyniki");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 300, ALLEGRO_ALIGN_CENTER , "Najlepsze wyniki");
		}
		if(wybor == 4){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 350, ALLEGRO_ALIGN_CENTER , "Wyjscie z gry");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 350, ALLEGRO_ALIGN_CENTER , "Wyjscie z gry");
		}
		mText.viewInfo();
		mText.viewVersion();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
	al_destroy_font(font24);
	al_destroy_font(font36);
	return wybor;
}
