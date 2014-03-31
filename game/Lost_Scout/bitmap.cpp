#include "main.h"
#include "config.h"
#include "bitmap.h"
Bitmap::Bitmap(){

	overlay = al_load_bitmap("Img/bg.png");

	overlord = al_load_bitmap("Img/overlord.png");
	avenger = al_load_bitmap("Img/avenger.png");
	mutalisk = al_load_bitmap("Img/mutalisk.png");
	queen = al_load_bitmap("Img/queen.png");
	guardian = al_load_bitmap("Img/guardian.png");
	devour = al_load_bitmap("Img/devour.png");

	dropship = al_load_bitmap("Img/dropship.png");
	wrath = al_load_bitmap("Img/wrath.png");
	scvessel = al_load_bitmap("Img/wessel.png");
	battlecruiser = al_load_bitmap("Img/battlecruiser.png");
	superbattlecruiser = al_load_bitmap("Img/sbattlecruiser.png");

	observer = al_load_bitmap("Img/observer.png");
	interceptor = al_load_bitmap("Img/interceptor.png");
	scout = al_load_bitmap("Img/scout.png");
	arbiter = al_load_bitmap("Img/arbiter.png");
	corsair = al_load_bitmap("Img/corsair.png");
	carrier = al_load_bitmap("Img/carrier.png");

	life = al_load_bitmap("Img/life.png");
	dmg = al_load_bitmap("Img/dmg.png");
}

Bitmap::~Bitmap(){
	al_destroy_bitmap(life);
	al_destroy_bitmap(dmg);

	al_destroy_bitmap(overlay);

	al_destroy_bitmap(overlord);
	al_destroy_bitmap(avenger);
	al_destroy_bitmap(mutalisk);
	al_destroy_bitmap(queen);
	al_destroy_bitmap(guardian);
	al_destroy_bitmap(devour);

	al_destroy_bitmap(dropship);
	al_destroy_bitmap(wrath);
	al_destroy_bitmap(scvessel);
	al_destroy_bitmap(battlecruiser);
	al_destroy_bitmap(superbattlecruiser);

	al_destroy_bitmap(observer);
	al_destroy_bitmap(interceptor);
	al_destroy_bitmap(scout);
	al_destroy_bitmap(arbiter);
	al_destroy_bitmap(corsair);
	al_destroy_bitmap(carrier);
}