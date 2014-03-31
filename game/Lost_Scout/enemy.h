
struct ALLEGRO_BITMAP;
class Player;
class Bitmap;
class Text;

class Enemy{
private:
	int hp, maxHP;
	int type;
	int waveLeft;
	int rout;
	int eX;
	int eY;
	int crash_x, crash_y;
	int espeed;
	bool live;
	bool ready;
	int imgX, imgY;
	int releseTime;
	int moveType;
	ALLEGRO_BITMAP *enemy;
public:
	Enemy();
	~Enemy();
	int getHP();
	void setHP(int hp);
	int getMaxHP();
	void setMaxHP(int maxHP);
	int getType();
	void setType(int type);
	int getRout();
	void setRout(int rout);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getWaveLeft();
	void setWaveLeft(int waveLeft);
	bool getLive();
	void setLive(bool live);
	bool getReady();
	void setReady(bool ready);
	void setSpeed(int speed);
	int getCrashX();
	void setCrashX(int CrashX);
	int getCrashY();
	void setCrashY(int CrashY);
	int getReleseTime();
	void setReleseTime(int releseTime);
	int getMoveType();
	void setMoveType(int moveType);
	void setImgX(int imgX);
	void setImgY(int imgY);

	void show();
	void show(Bitmap &mBitmap, Text & mText);
	void update(Player &mPlayer);
	void updateWave(Player &mPlayer);
};