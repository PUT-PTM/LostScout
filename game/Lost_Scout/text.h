class Player;
class Bitmap;

class Text {
private:
	ALLEGRO_FONT *versionInfo;
	ALLEGRO_FONT *font16;
	ALLEGRO_FONT *font12;
	ALLEGRO_FONT *font12s;
	ALLEGRO_FONT *font24;
	ALLEGRO_FONT *font36;
	ALLEGRO_FONT *font24sc;
public:
	Text();
	~Text();
	void viewVersion();
	void viewScore(int wynik, int live, int killed, int left, int shoots);
	void viewInfo();
	void viewBigScore(int wynik);
	void viewBigScoreArc(int wynik);
	void saved();
	void timer(Player & mPlayer);
	void drawHP(int maxHP, int hp, int x, int y);
	void drawUI(Bitmap &mBitmap);
	void countDown(Player & mPlayer);
	void pause();
	void nextPhase(Player &mPlayer);
};