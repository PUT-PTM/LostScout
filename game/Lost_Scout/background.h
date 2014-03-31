struct ALLEGRO_BITMAP;

class Background{
private:
	float fX;
	float fY;
	float fYspeed;
	int fDirY;
	int fWidth;
	int fHeight;
	ALLEGRO_BITMAP *fImage;

	float bX;
	float bY;
	float bYspeed;
	int bDirY;
	int bWidth;
	int bHeight;
	ALLEGRO_BITMAP *bImage;
public:
	Background();
	~Background();

	void update();
	void show();
};