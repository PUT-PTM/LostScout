#include "main.h"
#include "config.h"

#include "background.h"

Background::Background(){
	Config mConf;

	fX = 0;
	fY = 0;
	fYspeed = 1.5;
	fDirY = 1;
	fImage = al_load_bitmap("Img/starFG.png");
	fWidth = al_get_bitmap_width(fImage);
	fHeight = al_get_bitmap_height(fImage);
	

	bX = 0;
	bY = 0;
	bYspeed = 0.5;
	bDirY = 1;
	bImage = al_load_bitmap("Img/starBG.png");
	bWidth = al_get_bitmap_width(bImage);
	bHeight = al_get_bitmap_height(bImage);
	
}

Background::~Background(){
	al_destroy_bitmap(fImage);
	al_destroy_bitmap(bImage);
}

void Background::update(){
	Config mConf;
	bY += bYspeed * bDirY;
	if(bY >= mConf.getHeight()){
		bY = 0;
	}


	fY += fYspeed * fDirY;
	if(fY >= mConf.getHeight()){
		fY = 0;
	}
}
void Background::show(){
	Config mConf;

	al_draw_bitmap(bImage, bX, bY, 0);
	if(bY + bHeight >0){
		al_draw_bitmap(bImage, bX, bY - bHeight, 0);
	}


	al_draw_bitmap(fImage, fX, fY, 0);
	if(fY + fHeight >0){
		al_draw_bitmap(fImage, fX, fY - fHeight, 0);
	}
}