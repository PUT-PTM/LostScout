#include "main.h"
#include "config.h"
#include "text.h"
#include "player.h"
#include "bitmap.h"
#include "upgrade.h"

Upgrade::Upgrade(){
	type = 1;
	uX = 0;
	uY = 0;
	imgX = 0;
	imgY = 0;
	live = false;
	ready = false;
	releseTime = 0;
}
Upgrade::~Upgrade(){
}


int Upgrade::getType(){ return type; }
void Upgrade::setType(int type){ this->type = type; }
int Upgrade::getX(){ return uX; }
void Upgrade::setX(int x){ this->uX = x; }
int Upgrade::getY(){ return uY; }
void Upgrade::setY(int y){ this->uY = y; }
bool Upgrade::getLive(){	return live;}
void Upgrade::setLive(bool live){this->live = live;}
bool Upgrade::getReady(){	return ready;}
void Upgrade::setReady(bool ready){this->ready = ready;}
int Upgrade::getReleseTime(){ return releseTime; }
void Upgrade::setReleseTime(int releseTime){ this->releseTime = releseTime; }

void Upgrade::show(Bitmap &mBitmap, Text & mText){
	switch(type){
		
	case 1:
		if(imgX != 0 || imgY != 0){
			imgX = al_get_bitmap_width(mBitmap.dmg);
			imgY = al_get_bitmap_height(mBitmap.dmg);
		}
		al_draw_bitmap(mBitmap.dmg, uX - imgX / 2, uY - imgY / 2, 0);
		break;
	case 2:
		if(imgX != 0 || imgY != 0){
			imgX = al_get_bitmap_width(mBitmap.life);
			imgY = al_get_bitmap_height(mBitmap.life);
		}
		al_draw_bitmap(mBitmap.life, uX - imgX / 2, uY - imgY / 2, 0);
		break;
	}
}
void Upgrade::update(Player &mPlayer){
	if(mPlayer.getTimer() - releseTime > 400)
		live = false;
}