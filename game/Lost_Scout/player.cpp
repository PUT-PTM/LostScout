#include "main.h"
#include "config.h"
#include "text.h"
#include "sound.h"
#include "bitmap.h"
#include "player.h"

#include "_STM.h"
Player::Player(bool drugi){
	this->drugi = drugi;
	if(!drugi)
		player = al_load_bitmap("Img/player.png");
	else
		player = al_load_bitmap("Img/player2.png");
	imgX = al_get_bitmap_width(player);
	imgY = al_get_bitmap_height(player);
	dmg = 10;
	lives = 3;
	Config mConf;
	if(!drugi)
		x = mConf.getWidth() / 2 + 30;
	else
		x = mConf.getWidth() / 2 - 30;
	y = 2* mConf.getHeight() /3;
	speed = 7;
	crash_x = 16;
	crash_y = 17;
	score = 0;
	nrKilled = 0;
	nrLeft = 0;
	nrShoot = 0;
	stage = 1;
	substage = 1;
	repeat = 0;

	timer = 0;
	restTime = 0;
}

Player::~Player(){
	//al_destroy_bitmap(player);
}

void Player::up(){
	y -= speed;
	if(y < 0 + 55){
		y = 55;
	}
}
void Player::down(){
	Config mConf;
	y += speed;
	if(y > mConf.getHeight() - 50){
		y = mConf.getHeight() -50;
	}
}

void Player::left(){
	x -= speed;
	if(x < 0 + 50){
		x = 50;
	}
}
void Player::right(){
	Config mConf;
	x += speed;
	if(x > mConf.getWidth() - 55){
		x = mConf.getWidth() -55;
	}
}

int Player::getDmg(){ return dmg; }
void Player::setDmg(int dmg){ this->dmg = dmg; }
int Player::getLives(){ return lives; }
void Player::setLives(int lives){ this->lives = lives; }
int Player::getX(){ return x; }
void Player::setX(int x){ this->x = x; }
int Player::getY(){ return y; }
void Player::setY(int y){ this->y = y; }
int Player::getScore(){ return score; }
void Player::setScore(int score){ this->score = score; }
int Player::getCrashX(){ return crash_x; }
void Player::setCrashX(int CrashX){ this->crash_x = CrashX; }
int Player::getCrashY(){ return crash_y; }
void Player::setCrashY(int CrashY){ this->crash_y = CrashY; }

int Player::getRestTime(){ return restTime; }
void Player::setRestTime(int restTime){ this->restTime = restTime; }

int Player::getStage(){ return stage; }
void Player::setStage(int stage){ this->stage = stage; }
int Player::getSubStage(){ return substage; }
void Player::setSubStage(int subStage){ this->substage = subStage; }
int Player::getRepeat(){ return repeat; }
void Player::setRepeat(int repeat){ this->repeat = repeat; }

void Player::show(){
	al_draw_bitmap(player, x - imgX / 2, y - imgY / 2, 0);
}

void Player::saveScore(int &exit, ALLEGRO_EVENT_QUEUE *eventQueue, Bitmap & mBitmap, Sound &mSound){

	Config mConf;
	ALLEGRO_FONT *font24 = al_load_font("Starcraft.ttf", 16, 0);
	ALLEGRO_FONT *font20 = al_load_font("Starcraft.ttf", 16, 0);

	bool end = false;
	string name;
	Text mText;
while(!end){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);
		mText.drawUI(mBitmap);
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){ 
			switch(ev.keyboard.keycode)	{
			case ALLEGRO_KEY_ESCAPE:
				mSound.click();
				end = true;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				if(!name.empty())
					name.pop_back();
				break;
			case ALLEGRO_KEY_ENTER:
				mSound.click();
				saveScoreFile(name, getScore());

				cout << "Zapisano wynik " << getScore() << " dla " << name << endl;
				end = true;
				break;



			}
			if(!end){
				char key = ev.keyboard.keycode + 96;
				if(key > 96 && key < 123){
					name = name + key;
				}
			}
		}
		
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			end = true;
			exit = 1;
		}

		al_draw_textf(font24, al_map_rgb(180,180,180), mConf.getWidth() /2, 80, ALLEGRO_ALIGN_CENTER, "Wynik: %i ", score);
		al_draw_textf(font24, al_map_rgb(180,180,180), mConf.getWidth() /2, 150, ALLEGRO_ALIGN_CENTER, "Podaj twoje imie: ", score);
		al_draw_textf(font24, al_map_rgb(180,180,180), mConf.getWidth() /2, 180, ALLEGRO_ALIGN_CENTER, "%s", name.c_str());
		mText.viewInfo();
		mText.viewVersion();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
	al_destroy_font(font20);
	al_destroy_font(font24);
	
}

	void Player::zeroStats(){
		nrShoot = 0;
		nrKilled = 0;
		nrLeft = 0;
	}
	void Player::incNrShoots(){
		nrShoot++;
	}
	void Player::incNrKilled(){
		nrKilled++;
	}
	void Player::incNrLeft(){
		nrLeft++;
	}

	int Player::getNrShoots(){
		return nrShoot;
	}
	int Player::getNrKilled(){
		return nrKilled;
	}
	int Player::getNrLeft(){
		return nrLeft;
	}


	void Player::incTimer(){ timer++; }
	int Player::getTimer(){ return timer; }
	void Player::setTimer(int timer){ this->timer = timer;}

	////// KOD DO STMa
	void Player::move( char * buffer){
		USHORT	ByteNumber;
		CHAR	ReceivedByte;
		/*for (ByteNumber=0; ByteNumber < 4; ByteNumber++)
		{
			//Get a byte.
			ReceivedByte = buffer[ByteNumber];
			//Display it.
			cout << (int)ReceivedByte <<", ";
		}*/
		Config mConf;

		cout << (int)buffer[1] << "   " << (int)buffer[2] << "   " << (int)buffer[3] << endl;

		x = x + buffer[1]/3;
		if(x > mConf.getWidth() - 55){
					x = mConf.getWidth() -55;
		} else if(x < 0 + 50){
					x = 50;
		}
		y = y + buffer[2]/3;
		if(y > mConf.getHeight() - 50){
					y = mConf.getHeight() -50;
		} else if(y < 0 + 55){
					y = 55;
		}

	}
	////// KOD DO STMa