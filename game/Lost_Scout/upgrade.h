class Upgrade{
private:
	int type;
	int uX;
	int uY;
	int imgX;
	int imgY;
	bool live;
	bool ready;
	int releseTime;
public:
	Upgrade();
	~Upgrade();
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	bool getLive();
	void setLive(bool live);
	int getType();
	void setType(int type);
	bool getReady();
	void setReady(bool ready);
	int getReleseTime();
	void setReleseTime(int releseTime);

	void show(Bitmap &mBitmap, Text & mText);
	void update(Player &mPlayer);
};