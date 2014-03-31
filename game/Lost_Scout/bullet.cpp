#include "main.h"
#include "config.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
Bullet::Bullet(){
	bspeed = 10;
	live = false;
	bullet = al_load_bitmap("Img/bullet.png");
	bullet2 = al_load_bitmap("Img/bullet2.png");
	bullet3 = al_load_bitmap("Img/bullet3.png");
	imgX = al_get_bitmap_width(bullet);
	imgY = al_get_bitmap_height(bullet);
}
Bullet::~Bullet(){
	al_destroy_bitmap(bullet);
	al_destroy_bitmap(bullet2);
	al_destroy_bitmap(bullet3);
}

void Bullet::show(Player mPlayer){
	switch(mPlayer.getDmg()){
	case 10:
		al_draw_bitmap(bullet, bX - imgX / 2, bY - imgY / 2, 0);
		break;
	case 20:
		al_draw_bitmap(bullet2, bX - imgX / 2, bY - imgY / 2, 0);
		break;
	case 30:
		al_draw_bitmap(bullet3, bX - imgX / 2, bY - imgY / 2, 0);
		break;
	}
}

void Bullet::update(){
	Config mConf;
	bY -= bspeed;
	if(bY < 0)
		live = false;

}

bool Bullet::getLive(){	return live;}
void Bullet::setLive(bool live){this->live = live;}
int Bullet::getX(){return bX;}
void Bullet::setX(int x){this->bX = x;}
int Bullet::getY(){return bY;}
void Bullet::setY(int y){this->bY = y;}

