#include "main.h"
#include "player.h"
#include "bitmap.h"
#include "enemy.h"
#include "config.h"
#include "text.h"


Enemy::Enemy(){


	enemy = al_load_bitmap("Img/enemy.png");
	imgX = al_get_bitmap_width(enemy);
	imgY = al_get_bitmap_height(enemy);
	type = 0;
	rout = 0;
	live = false;
	hp = 1;
}
Enemy::~Enemy(){
	al_destroy_bitmap(enemy);
}


int Enemy::getHP(){ return hp; }
void Enemy::setHP(int hp){ this->hp = hp; }
int Enemy::getMaxHP(){ return maxHP; }
void Enemy::setMaxHP(int maxHP){ this->maxHP = maxHP; }
int Enemy::getType(){ return type; }
void Enemy::setType(int type){ this->type = type; }
int Enemy::getRout(){ return rout; }
void Enemy::setRout(int rout){ this->rout = rout; }
int Enemy::getX(){ return eX; }
void Enemy::setX(int x){ this->eX = x; }
int Enemy::getY(){ return eY; }
void Enemy::setY(int y){ this->eY = y; }
int Enemy::getWaveLeft(){ return waveLeft; }
void Enemy::setWaveLeft(int waveLeft){ this->waveLeft = waveLeft; }
bool Enemy::getLive(){	return live;}
void Enemy::setLive(bool live){this->live = live;}
bool Enemy::getReady(){	return ready;}
void Enemy::setReady(bool ready){this->ready = ready;}
void Enemy::setSpeed(int speed){this->espeed = speed;}
int Enemy::getCrashX(){ return crash_x; }
void Enemy::setCrashX(int CrashX){ this->crash_x = CrashX; }
int Enemy::getCrashY(){ return crash_y; }
void Enemy::setCrashY(int CrashY){ this->crash_y = CrashY; }
int Enemy::getReleseTime(){ return releseTime; }
void Enemy::setReleseTime(int releseTime){ this->releseTime = releseTime; }
int Enemy::getMoveType(){ return moveType; }
void Enemy::setMoveType(int moveType){ this->moveType = moveType; }
void Enemy::setImgX(int imgX){ this->imgX = imgX; }
void Enemy::setImgY(int imgY){ this->imgY = imgY; }

void Enemy::show(Bitmap &mBitmap, Text & mText){
	mText.drawHP(maxHP, hp, eX, eY - imgY / 2 );
	switch(type){
		
	case 0:
		al_draw_bitmap(enemy, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 1:
		al_draw_bitmap(mBitmap.overlord, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 2:
		al_draw_bitmap(mBitmap.avenger, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 3:
		al_draw_bitmap(mBitmap.mutalisk, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 4:
		al_draw_bitmap(mBitmap.queen, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 5:
		al_draw_bitmap(mBitmap.guardian, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 6:
		al_draw_bitmap(mBitmap.devour, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 11:
		al_draw_bitmap(mBitmap.dropship, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 12:
	case 13:
		al_draw_bitmap(mBitmap.wrath, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 14:
		al_draw_bitmap(mBitmap.scvessel, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 15:
		al_draw_bitmap(mBitmap.battlecruiser, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 16:
		al_draw_bitmap(mBitmap.superbattlecruiser, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 21:
		al_draw_bitmap(mBitmap.observer, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 22:
		al_draw_bitmap(mBitmap.interceptor, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 23:
		al_draw_bitmap(mBitmap.scout, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 24:
		al_draw_bitmap(mBitmap.arbiter, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 25:
		al_draw_bitmap(mBitmap.corsair, eX - imgX / 2, eY - imgY / 2, 0);
		break;
	case 26:
		al_draw_bitmap(mBitmap.carrier, eX - imgX / 2, eY - imgY / 2, 0);
		break;

	}
}
void Enemy::show(){
	al_draw_bitmap(enemy, eX - imgX / 2, eY - imgY / 2, 0);
}
void Enemy::update(Player &mPlayer){
	Config mConf;
		eY += espeed;
		if(eY > mConf.getHeight()){
			live = false;
			mPlayer.incNrLeft();
		}
}
void Enemy::updateWave(Player &mPlayer){
	Config mConf;
	switch(moveType){
	case 1:
		eY += espeed;
		if(eY > mConf.getHeight()){
			live = false;
			mPlayer.incNrLeft();
		}
		break;
	case 2:
		if(eX < mConf.getWidth() / 2){
			eY += espeed;
			eX += espeed;
		} else {
			eY -= espeed;
			eX += espeed;
		}
		if(eY < 0 && eX > mConf.getWidth()){
			live = false;
			mPlayer.incNrLeft();
		}
		break;
	case 3:
		switch(rout){
		case 0:
			eY += espeed;
			if(eY > mConf.getHeight() / 3)
				rout = 1;
			break;
		case 1:
			eX -= espeed;
			if(eX < mConf.getWidth() / 6)
				rout = 2;
			break;
		case 2:
			eX += espeed;
			if(eX > (5 * mConf.getWidth()) / 6)
				rout = 3;
			break;
		case 3:
			eX -= espeed;
			if(eX < mConf.getWidth() / 2)
				rout = 4;
			break;
		case 4:
			eY += espeed;
			if(eY > mConf.getHeight()){
				live = false;
				mPlayer.incNrLeft();
			}
			break;
		}
		break;
	case 4:
		//Guardian dó³ - prawo
		switch(rout){
		case 0:
			eY += espeed;
			if(eY > 3* mConf.getHeight() / 4)
				rout = 1;
			break;
		case 1:
			eX += espeed;
			eY -= espeed;
			if(eY < mConf.getHeight() / 6)
				rout = 2;
			break;
		case 2:
			eY += espeed;
			if(eY > mConf.getHeight()){
				live = false;
				mPlayer.incNrLeft();
			}
			break;

		}
		break;

	case 5:
		//Guardian dó³ - prawo
		switch(rout){
		case 0:
			eY += espeed;
			if(eY > 3* mConf.getHeight() / 4)
				rout = 1;
			break;
		case 1:
			eX -= espeed;
			eY -= espeed;
			if(eY < mConf.getHeight() / 6)
				rout = 2;
			break;
		case 2:
			eY += espeed;
			if(eY > mConf.getHeight()){
				live = false;
				mPlayer.incNrLeft();
			}
			break;
		}
		break;
	case 6:
		//Endboss Dev
		switch(rout){
		case 0:
			eX -= espeed;
			if(eX < mConf.getWidth() / 6)
				rout = 1;
			break;
		case 1:
			eX += espeed;
			eY -= espeed;
			if(eY < mConf.getHeight() / 6)
				rout = 2;
			break;
		case 2:
			eX += espeed;
			eY += espeed;
			if(eY > 2 * mConf.getHeight() / 3){
				rout = 0;
			}
			break;
		case 3:
			eX -= espeed;
			if(eX < mConf.getWidth() / 8){
				rout = 4;
			}
			break;
		case 4:
			eX += espeed;
			if(eX < 7*mConf.getWidth() / 8){
				rout = 3;
			}
			break;

		}
		break;
	}
}
