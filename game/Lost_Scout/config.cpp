#include "main.h"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "config.h"
Config::Config(){
	build = 1856;
	status = "Alpha in dev";
	gameOver = false;
	mute = false;
}
Config::~Config(){
}
int Config::getBuild(){
	return build;
}
string Config::getStatus(){
	return status;
}
const int Config::getWidth(){
	return width;
}
const int Config::getHeight(){
	return Height;
}
const int Config::getFPS(){
	return fps;
}
const int Config::getMaxBullet(){
	return maxBullet;
}
const int Config::getMaxEnemy(){
	return maxEnemy;
}

const int Config::getArcadeEnemyEasy(){ return arcadeEnemyEasy; }
const int Config::getArcadeEnemyMedium(){ return arcadeEnemyMedium; }
const int Config::getArcadeEnemyHard(){ return arcadeEnemyHard; }
const int Config::getArcadeEnemyBrutal(){ return arcadeEnemyBrutal; }

const int Config::getSamples(){ return samples; }