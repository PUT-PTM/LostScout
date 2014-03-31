class Enemy;
class Player;
class Bitmap;
class Upgrade;

class Wave{
private:
	bool ready;
	bool bossAlive;
	int count;

	void zerg(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade);
	void terran(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade);
	void protoss(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade);
public:

	Wave();
	void wyzwalacz(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade);

	bool getReady();
	void setReady(int ready);
	bool getBossAlive();
	void setBossAlive(int bossAlive);
};