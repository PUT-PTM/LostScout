struct ALLEGRO_BITMAP;
class Bitmap{
public:
	Bitmap();
	~Bitmap();
	ALLEGRO_BITMAP *overlord;
	ALLEGRO_BITMAP *avenger;
	ALLEGRO_BITMAP *mutalisk;
	ALLEGRO_BITMAP *queen;
	ALLEGRO_BITMAP *guardian;
	ALLEGRO_BITMAP *devour;
	ALLEGRO_BITMAP *overlay;

	ALLEGRO_BITMAP *dropship;
	ALLEGRO_BITMAP *wrath;
	ALLEGRO_BITMAP *scvessel;
	ALLEGRO_BITMAP *battlecruiser;
	ALLEGRO_BITMAP *superbattlecruiser;

	ALLEGRO_BITMAP *observer;
	ALLEGRO_BITMAP *interceptor;
	ALLEGRO_BITMAP *scout;
	ALLEGRO_BITMAP *arbiter;
	ALLEGRO_BITMAP *corsair;
	ALLEGRO_BITMAP *carrier;

	ALLEGRO_BITMAP *life;
	ALLEGRO_BITMAP *dmg;
};