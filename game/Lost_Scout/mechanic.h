struct ALLEGRO_EVENT_QUEUE;

class Wave;
class Sound;
class Upgrade;

class Mechanic{
public:
void Fire(Bullet mBullet[], int max, Player &mPlayer);
void NewEnemy(Enemy mEnemy[], int max, Player &mPlayer, int level);
void TangoDown(Enemy mEnemy[], Bullet mBullet[], int maxE, int maxB, Player &mPlayer, Wave &mWave, Sound &mSound);
void PlayerColl(Enemy mEnemy[], int max, Player &mPlayer, Sound &mSound);
void Restart(Player &mPlayer, Enemy mEnemy[], Bullet mBullet[], Config &mConf);
void Restart(Player &mPlayer, Enemy mEnemy[], Bullet mBullet[], Config &mConf, int maxEnemy);
void TangoDown(Enemy mEnemy[], Bullet mBullet[], int maxE, int maxB, Player &mPlayer, Sound &mSound);

int getLevel(int& exit, ALLEGRO_EVENT_QUEUE *eventQueue, Bitmap &mBitmap, Sound &mSound);
int getPlayers(int& exit, ALLEGRO_EVENT_QUEUE *eventQueue, Bitmap &mBitmap, Sound &mSound);
void PlayerUpgrade(Upgrade &mUpgrade, Player &mPlayer, Sound &mSound);
};