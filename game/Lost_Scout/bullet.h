
struct ALLEGRO_BITMAP;
class Player;

class Bullet{
private:
	int id;
	int bX;
	int bY;
	int bspeed;
	bool live;
	int imgX, imgY;

	ALLEGRO_BITMAP *bullet;
	ALLEGRO_BITMAP *bullet2;
	ALLEGRO_BITMAP *bullet3;
public:
	bool getLive();
	void setLive(bool live);
	int getX();
	void setX(int X);
	int getY();
	void setY(int Y);
	Bullet();
	~Bullet();
	void show(Player mPlayer);
	void update();


};