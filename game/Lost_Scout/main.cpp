#include "main.h"
#include "config.h"
#include "bitmap.h"

int main(){

	setlocale(LC_ALL,"polish");
	srand (time(NULL));
	Config mConf;
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	
	//FullScr
		//		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
				al_set_new_display_flags(ALLEGRO_RESIZABLE);
	//FullScr

	if(!al_init()) {
		cout << stderr << "failed to initialize allegro!\n";
		return -1;
	}
 
	display = al_create_display(mConf.getWidth(), mConf.getHeight());
	
	if(!display) {
		cout << stderr << "failed to create display!\n";
		return -1;
	}


	timer = al_create_timer(1.0 / mConf.getFPS());
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
 
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(mConf.getSamples());

	Bitmap mBitmap;

	bool end = false;
	while(!end){
	int what = menu(display, eventQueue, timer, mBitmap);



		switch(what){
		case 1:
			cout << "Game" << endl;
			game(display, eventQueue, timer, mBitmap);
			break;

		case 2:
			cout << "Arcade" << endl;
			arcade(display, eventQueue, timer, mBitmap);
			break;

		case 3:
			cout << "Score" << endl;
			score(display, eventQueue, timer, mBitmap);
			break;

		case 4:
		case 0:
			end = true;
			break;
		}
	}
	
	al_destroy_display(display);
	al_destroy_timer(timer);
	
	return 0;
}