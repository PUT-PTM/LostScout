struct ALLEGRO_BITMAP;
struct ALLEGRO_EVENT_QUEUE;
class Bitmap;
class Sound;

class Player{
private:
	int dmg;
	int lives;
	int x, y;
	int crash_x, crash_y;
	int speed;
	int score;

	int imgX, imgY;
	ALLEGRO_BITMAP *player;

	int nrShoot, nrKilled, nrLeft;

	int stage;
	int substage;
	int repeat;

	int timer;

	int restTime;

public:
	int getDmg();
	void setDmg(int dmg);
	int getLives();
	void setLives(int life);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getCrashX();
	void setCrashX(int CrashX);
	int getCrashY();
	void setCrashY(int CrashY);

	int getRestTime();
	void setRestTime(int restTime);

	int getStage();
	void setStage(int stage);
	int getSubStage();
	void setSubStage(int subStage);
	int getRepeat();
	void setRepeat(int repeat);

	void zeroStats();
	void incNrShoots();
	void incNrKilled();
	void incNrLeft();
	int getNrShoots();
	int getNrKilled();
	int getNrLeft();

	int getScore();
	void setScore(int score);

	Player();
	~Player();

	void up();
	void down();
	void left();
	void right();

	void show();

	void saveScore( ALLEGRO_EVENT_QUEUE *eventQueue, Bitmap & mBitmap, Sound &mSound);

	void incTimer();
	int getTimer();
	void setTimer(int timer);


	void move(); // KOD DO STMa
};