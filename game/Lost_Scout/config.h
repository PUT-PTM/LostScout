#ifndef MAIN_H
	#include <iostream>
	#include <locale.h>
	#include <stdio.h>
	#include <string>
	#include <allegro5/allegro.h>
	#include <allegro5/allegro_font.h>
	#include <allegro5/allegro_ttf.h>
	#include <allegro5/allegro_primitives.h>

	using namespace std; 
#endif
class Config{
public:
	int getBuild();
	bool gameOver;	
	const int getWidth();
	const int getHeight();
	const int getFPS();
	const int getSamples();
	const int getMaxBullet();
	const int getMaxEnemy();

	const int getArcadeEnemyEasy();
	const int getArcadeEnemyMedium();
	const int getArcadeEnemyHard();
	const int getArcadeEnemyBrutal();

	string getStatus();
	Config();
	~Config();

	bool mute;
private:
	int build;
	string status;
	const static int width = 640;
	const static int Height = 480;
	const static int fps = 60;
	const static int maxBullet = 20;
	const static int maxEnemy = 40;

	const static int samples = 20;

	const static int arcadeEnemyEasy = 20;
	const static int arcadeEnemyMedium = 50;
	const static int arcadeEnemyHard = 100;
	const static int arcadeEnemyBrutal = 150;
};
