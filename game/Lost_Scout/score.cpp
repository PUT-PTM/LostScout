
#include "main.h"
#include "config.h"
#include "sound.h"
#include "text.h"
#include "score.h"

void score(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue,  ALLEGRO_TIMER *timer, Bitmap & mBitmap){
	//Config mConf;
	Text mText;
	Sound mSound(mConf);
	cout << "Wyniki" << endl;
	bool end = false;
	ALLEGRO_FONT *font36 = al_load_font("Starcraft.ttf", 36, 0);
	ALLEGRO_FONT *font14 = al_load_font("Starcraft.ttf", 14, 0);
	ALLEGRO_FONT *font24 = al_load_font("Starcraft.ttf", 24, 0);

	fstream file;
	bool exist = false;
	int n = 0;
	file.open("score.txt", ios::in);
	Scor *tablica;
	if(file != 0){
		
		file >> n;
	}
	tablica = new Scor[n];
	if(file != 0){
		cout << "Zapisanych wyników: " << n << endl;
		
		for(int i = 0; i<n; i++){
			file >> tablica[i].nazwa;
			file >> tablica[i].wynik;
		}
		exist = true;
	}

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	mSound.menu();
	while(!end){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

		mText.drawUI(mBitmap);
		al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, 40, ALLEGRO_ALIGN_CENTER , "Najwyzsze wyniki");



		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode)	{
			case ALLEGRO_KEY_ENTER:
				end = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				end = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			end = true;
			exit = 1;
		}

		if(exist){
			for(int i = 0; i < n; i++){
				al_draw_textf(font14, al_map_rgb(180,180,180), 200, 100 + 25*i, ALLEGRO_ALIGN_LEFT , "%i. %s (%i)", i+1, tablica[i].nazwa.c_str(), tablica[i].wynik);
			}

		} else {
			al_draw_textf(font14, al_map_rgb(255,0,0), mConf.getWidth() / 2, 100 + 100, ALLEGRO_ALIGN_CENTER , "Brak pliku z wynikami");

		}

		al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 400, ALLEGRO_ALIGN_CENTER , "Powrot (Enter)");
		mText.viewInfo();
		mText.viewVersion();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
	al_destroy_font(font14);
	al_destroy_font(font24);
	al_destroy_font(font36);
	al_destroy_event_queue(eventQueue);
	delete [] tablica;
}

void saveScoreFile(string name, int score){

	fstream file;

	int n;
	file.open("score.txt", ios::in);

	if(file != 0){
		
		file >> n;
		cout << "Zapisanych wyników: " << n << endl;
		Scor *tablica = new Scor[n + 1];
		for(int i = 0; i<n; i++){
			file >> tablica[i].nazwa;
			file >> tablica[i].wynik;
		}
		tablica[n].wynik = score;
		tablica[n].nazwa = name;
		for(int i = 0; i < n+1; i++){
			for(int j = 0; j < n; j++){
				if(tablica[j].wynik < tablica[j+1].wynik){
					Scor buff;
					buff = tablica[j];
					tablica[j] = tablica[j+1];
					tablica[j+1] = buff;
				}
			}
		}
		file.close();

		fstream file2;
		file2.open("score.txt", ios::out | ios::trunc);

		if(file2.good()){

			if(n+1 <=10){
				file2 << n+1 << endl;
				for(int i = 0; i< n+1; i++){
					cout << i+1 << ". " << tablica[i].nazwa << " " << tablica[i].wynik << endl;
					file2 << tablica[i].nazwa << " " << tablica[i].wynik << endl;
				}
			} else {
				file2 << 10 << endl;
				for(int i = 0; i< 10; i++){
					cout << i+1 << ". " << tablica[i].nazwa << " " << tablica[i].wynik << endl;
					file2 << tablica[i].nazwa << " " << tablica[i].wynik << endl;
				}
		
			file2.close();
			}
		}
			delete [] tablica;
	} else {
		cout << "Brak pliku z wynikami! Tworzê..." << endl;
		file.open("score.txt", ios::out);
		file << "1" << endl;
		file << name << " " <<score << endl;
		file.close();
		cout << "Plik utworzony, pierwszy wynik zapisany" << endl;
	}
				

}