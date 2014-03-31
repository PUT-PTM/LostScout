#include "main.h"
#include "config.h"

#include "player.h"
#include "enemy.h"
#include "bitmap.h"
#include "upgrade.h"

#include "wave.h"

Wave::Wave(){
	ready = false;
	bossAlive = true;
}

void Wave::wyzwalacz(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade){

	if(bossAlive == false){
		bossAlive = true;
		mPlayer.setStage(mPlayer.getStage() + 1);
		if(mPlayer.getStage() > 3){
			mPlayer.setStage(1);
			mPlayer.setRepeat(mPlayer.getRepeat() + 1);
		}
		mPlayer.setSubStage(1);
		mPlayer.setTimer(0);
		mPlayer.setRestTime(300);

	}

		switch(mPlayer.getStage()){
		case 1:
			if(mPlayer.getTimer() == 5){
				//1
				mPlayer.setSubStage(1);
				ready = false;
			}
			if(mPlayer.getTimer() == 500){
				//2
				mPlayer.setSubStage(2);
				ready = false;
			}
			if(mPlayer.getTimer() == 1500){
				//3
				mPlayer.setSubStage(3);
				ready = false;
			}
			if(mPlayer.getTimer() == 2100){
				//4 - medium boss
				mPlayer.setSubStage(4);
				ready = false;
			}
			if(mPlayer.getTimer() == 3200){
				//5 
				mPlayer.setSubStage(5);
				ready = false;
			}
			if(mPlayer.getTimer() == 4600){
				//6 boss
				mPlayer.setSubStage(6);
				ready = false;
			}
			break;
		case 2:
			if(mPlayer.getTimer() == 5){
				//1
				mPlayer.setSubStage(1);
				ready = false;
			}
			if(mPlayer.getTimer() == 500){
				//2
				mPlayer.setSubStage(2);
				ready = false;
			}
			if(mPlayer.getTimer() == 1500){
				//3
				mPlayer.setSubStage(3);
				ready = false;
			}
			if(mPlayer.getTimer() == 2100){
				//4 - medium boss
				mPlayer.setSubStage(4);
				ready = false;
			}
			if(mPlayer.getTimer() == 3200){
				//5
				mPlayer.setSubStage(5);
				ready = false;
			}
			if(mPlayer.getTimer() == 5000){
				//6 boss
				mPlayer.setSubStage(6);
				ready = false;
			}
			break;
		case 3:
			if(mPlayer.getTimer() == 5){
				//1
				mPlayer.setSubStage(1);
				ready = false;
			}
			if(mPlayer.getTimer() == 500){
				//2
				mPlayer.setSubStage(2);
				ready = false;
			}
			if(mPlayer.getTimer() == 1500){
				//3
				mPlayer.setSubStage(3);
				ready = false;
			}
			if(mPlayer.getTimer() == 2100){
				//4 - medium boss
				mPlayer.setSubStage(4);
				ready = false;
			}
			if(mPlayer.getTimer() == 3200){
				//5 
				mPlayer.setSubStage(5);
				ready = false;
			}
			if(mPlayer.getTimer() == 4600){
				//6 boss
				mPlayer.setSubStage(6);
				ready = false;
			}
			break;
		}


	if(ready == false){
		switch(mPlayer.getStage()){
		case 1:
			zerg(mEnemy, max, mPlayer, mBitmap, mUpgrade);
			break;
		case 2:
			terran(mEnemy, max, mPlayer, mBitmap, mUpgrade);
			break;
		case 3:
			protoss(mEnemy, max, mPlayer, mBitmap, mUpgrade);
			break;
		}
	}
}
bool Wave::getReady(){ return ready; }
void Wave::setReady(int ready){ this->ready = ready; }
bool Wave::getBossAlive(){ return bossAlive; }
void Wave::setBossAlive(int bossAlive){ this->bossAlive = bossAlive; }


void Wave::zerg(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade){
	Config mConf;
	switch(mPlayer.getSubStage()){
	case 1:
		// 5x Overlord
		count = 0;
		for(int i = 0; 5 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setType(1);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setHP(20 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(20 + mPlayer.getRepeat()*10);
				mEnemy[i].setCrashX(21);
				mEnemy[i].setCrashY(29);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.overlord));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.overlord));
				mEnemy[i].setRout(0);
				mEnemy[i].setMoveType(1);
				count++;
				switch(count){
				case 1:
					mEnemy[i].setX(mConf.getWidth() /2);
					mEnemy[i].setReleseTime(50);
					break;
				case 2:
					mEnemy[i].setX(mConf.getWidth() /2 -150);
					mEnemy[i].setReleseTime(150);
					break;
				case 3:
					mEnemy[i].setX(mConf.getWidth() /2 + 150);
					mEnemy[i].setReleseTime(200);
					break;
				case 4:
					mEnemy[i].setX(mConf.getWidth() /2 - 250);
					mEnemy[i].setReleseTime(250);
					break;
				case 5:
					mEnemy[i].setX(mConf.getWidth() /2 + 250);
					mEnemy[i].setReleseTime(300);
					break;
				}
			}
		}
		ready = true;
		break;


	case 2:
		// 20x Avenger
		count = 0;
		for(int i = 0; 20 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(2);
				mEnemy[i].setHP(5 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(5 + mPlayer.getRepeat()*10);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setX(0);
				mEnemy[i].setCrashX(12);
				mEnemy[i].setCrashY(12);
				mEnemy[i].setMoveType(2);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.avenger));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.avenger));
				count++;
				mEnemy[i].setReleseTime(450 + count*50);
			}
		}
		ready = true;
		break;

	case 3:
		// 15x Mutalisk
		count = 0;

		for(int i = 0; 15 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setHP(15 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(15 + mPlayer.getRepeat()*10);
				mEnemy[i].setType(3);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setReady(true);
				mEnemy[i].setCrashX(22);
				mEnemy[i].setCrashY(22);
				mEnemy[i].setMoveType(1);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.mutalisk));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.mutalisk));
				count++;
				switch(count){
					//lewo dó³
				case 1:
					mEnemy[i].setY(0);
					mEnemy[i].setX(100);
					mEnemy[i].setReleseTime(1500);
					break;
				case 2:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(60);
					mEnemy[i].setReleseTime(1500);
					break;
				case 3:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(140);
					mEnemy[i].setReleseTime(1500);
					break;
					//œrodek dó³
				case 4:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth()/2);
					mEnemy[i].setReleseTime(1600);
					break;
				case 5:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth()/2 - 40);
					mEnemy[i].setReleseTime(1600);
					break;
				case 6:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth()/2 + 40);
					mEnemy[i].setReleseTime(1600);
					break;
					//prawo dó³
				case 7:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth() -100);
					mEnemy[i].setReleseTime(1700);
					break;
				case 8:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() -140);
					mEnemy[i].setReleseTime(1700);
					break;
				case 9:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() - 60);
					mEnemy[i].setReleseTime(1700);
					break;
					//lewo góra
				case 10:
					mEnemy[i].setY(0);
					mEnemy[i].setX(200);
					mEnemy[i].setReleseTime(1800);
					break;
				case 11:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(160);
					mEnemy[i].setReleseTime(1800);
					break;
				case 12:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(240);
					mEnemy[i].setReleseTime(1800);
					break;
					//prawo góra
				case 13:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth() -200);
					mEnemy[i].setReleseTime(1800);
					break;
				case 14:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() -240);
					mEnemy[i].setReleseTime(1800);
					break;
				case 15:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() - 160);
					mEnemy[i].setReleseTime(1800);
					break;
				}
			}
		}
		ready = true;
		break;

	case 4:
		//Middleboss - queenka
		count = 0;
		for(int i = 0; 1 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(4);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setHP(500 + mPlayer.getRepeat()*100);
				mEnemy[i].setMaxHP(500 + mPlayer.getRepeat()*100);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setX(mConf.getWidth()/2);
				mEnemy[i].setCrashX(18);
				mEnemy[i].setCrashY(18);
				mEnemy[i].setMoveType(3);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.queen));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.queen));
				count++;
				mEnemy[i].setReleseTime(2100);
			}
		}
		ready = true;
		break;
	case 5:
		//Guardian x20;
		count = 0;
		for(int i = 0; 20 > count; i++){
			if(!mEnemy[i].getLive()){
				count++;
				if(count % 2 == 1){
					mEnemy[i].setX(100);
					mEnemy[i].setMoveType(4);
					mEnemy[i].setReleseTime(3150 + count*50);
				} else {
					mEnemy[i].setX(mConf.getWidth() - 100);
					mEnemy[i].setMoveType(5);
					mEnemy[i].setReleseTime(3150 + (count-1)*50);
				}
				mEnemy[i].setType(5);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setHP(25 + mPlayer.getRepeat()*15);
				mEnemy[i].setMaxHP(25 + mPlayer.getRepeat()*15);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setRout(0);
				mEnemy[i].setCrashX(25);
				mEnemy[i].setCrashY(15);
				
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.guardian));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.guardian));
				
				
			}
		}
		mUpgrade.setReady(true);
		mUpgrade.setType(1);
		mUpgrade.setReleseTime(3600);
		mUpgrade.setX(mConf.getWidth() / 2);
		mUpgrade.setY(50);
		ready = true;
		break;
	case 6:
		//EndBoss - Dev
		count = 0;

		for(int i = 0; 1 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(6);
				mEnemy[i].setHP(800 + mPlayer.getRepeat()*200);
				mEnemy[i].setMaxHP(800 + mPlayer.getRepeat()*200);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(mConf.getHeight() / 2);
				mEnemy[i].setX(mConf.getWidth());
				mEnemy[i].setCrashX(14);
				mEnemy[i].setCrashY(31);
				mEnemy[i].setMoveType(6);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.devour));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.devour));
				count++;
				mEnemy[i].setReleseTime(4600);
			}
		}
		mUpgrade.setReady(true);
		mUpgrade.setType(2);
		mUpgrade.setReleseTime(4800);
		mUpgrade.setX(mConf.getWidth() / 2);
		mUpgrade.setY(mConf.getHeight() / 3);
		ready = true;
		break;
	}

}
void Wave::terran(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade){
	Config mConf;
	switch(mPlayer.getSubStage()){
	case 1:
		// 5x DropShip
		count = 0;
		for(int i = 0; 5 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setType(11);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setHP(35 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(35 + mPlayer.getRepeat()*10);
				mEnemy[i].setCrashX(20);
				mEnemy[i].setCrashY(15);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.dropship));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.dropship));
				mEnemy[i].setRout(0);
				mEnemy[i].setMoveType(1);
				count++;
				switch(count){
				case 1:
					mEnemy[i].setX(mConf.getWidth() /2);
					mEnemy[i].setReleseTime(50);
					break;
				case 2:
					mEnemy[i].setX(mConf.getWidth() /2 -150);
					mEnemy[i].setReleseTime(150);
					break;
				case 3:
					mEnemy[i].setX(mConf.getWidth() /2 + 150);
					mEnemy[i].setReleseTime(200);
					break;
				case 4:
					mEnemy[i].setX(mConf.getWidth() /2 - 250);
					mEnemy[i].setReleseTime(250);
					break;
				case 5:
					mEnemy[i].setX(mConf.getWidth() /2 + 250);
					mEnemy[i].setReleseTime(300);
					break;
				}
			}
		}
		ready = true;
		break;
	case 2:
		// 20x Wrath
		count = 0;
		for(int i = 0; 20 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(12);
				mEnemy[i].setHP(25 + mPlayer.getRepeat()*5);
				mEnemy[i].setMaxHP(25 + mPlayer.getRepeat()*5);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setX(0);
				mEnemy[i].setCrashX(17);
				mEnemy[i].setCrashY(17);
				mEnemy[i].setMoveType(2);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.wrath));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.wrath));
				count++;
				mEnemy[i].setReleseTime(450 + count*50);
			}
		}
		ready = true;
		break;

	case 3:
		// 15x Wrath
		count = 0;

		for(int i = 0; 15 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setHP(25 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(25 + mPlayer.getRepeat()*10);
				mEnemy[i].setType(13);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setReady(true);
				mEnemy[i].setCrashX(17);
				mEnemy[i].setCrashY(17);
				mEnemy[i].setMoveType(1);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.wrath));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.wrath));
				count++;
				switch(count){
					//lewo dó³
				case 1:
					mEnemy[i].setY(0);
					mEnemy[i].setX(100);
					mEnemy[i].setReleseTime(1500);
					break;
				case 2:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(60);
					mEnemy[i].setReleseTime(1500);
					break;
				case 3:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(140);
					mEnemy[i].setReleseTime(1500);
					break;
					//œrodek dó³
				case 4:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth()/2);
					mEnemy[i].setReleseTime(1600);
					break;
				case 5:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth()/2 - 40);
					mEnemy[i].setReleseTime(1600);
					break;
				case 6:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth()/2 + 40);
					mEnemy[i].setReleseTime(1600);
					break;
					//prawo dó³
				case 7:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth() -100);
					mEnemy[i].setReleseTime(1700);
					break;
				case 8:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() -140);
					mEnemy[i].setReleseTime(1700);
					break;
				case 9:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() - 60);
					mEnemy[i].setReleseTime(1700);
					break;
					//lewo góra
				case 10:
					mEnemy[i].setY(0);
					mEnemy[i].setX(200);
					mEnemy[i].setReleseTime(1800);
					break;
				case 11:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(160);
					mEnemy[i].setReleseTime(1800);
					break;
				case 12:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(240);
					mEnemy[i].setReleseTime(1800);
					break;
					//prawo góra
				case 13:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth() -200);
					mEnemy[i].setReleseTime(1800);
					break;
				case 14:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() -240);
					mEnemy[i].setReleseTime(1800);
					break;
				case 15:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() - 160);
					mEnemy[i].setReleseTime(1800);
					break;
				}
			}
		}
		ready = true;
		break;

	case 4:
		//Middleboss - Science Vessel
		count = 0;
		for(int i = 0; 1 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(14);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setHP(800 + mPlayer.getRepeat()*100);
				mEnemy[i].setMaxHP(800 + mPlayer.getRepeat()*100);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setX(mConf.getWidth()/2);
				mEnemy[i].setCrashX(25);
				mEnemy[i].setCrashY(20);
				mEnemy[i].setMoveType(3);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.scvessel));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.scvessel));
				count++;
				mEnemy[i].setReleseTime(2100);
			}
		}
		ready = true;
		break;
	case 5:
		//Battlecruiser x20;
		count = 0;
		for(int i = 0; 20 > count; i++){
			if(!mEnemy[i].getLive()){
				count++;
				if(count % 2 == 1){
					mEnemy[i].setX(100);
					mEnemy[i].setMoveType(4);
					mEnemy[i].setReleseTime(3150 + count*50);
				} else {
					mEnemy[i].setX(mConf.getWidth() - 100);
					mEnemy[i].setMoveType(5);
					mEnemy[i].setReleseTime(3150 + (count-1)*50);
				}
				mEnemy[i].setType(15);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setHP(100 + mPlayer.getRepeat()*20);
				mEnemy[i].setMaxHP(100 + mPlayer.getRepeat()*20);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setRout(0);
				mEnemy[i].setCrashX(35);
				mEnemy[i].setCrashY(35);
				
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.battlecruiser));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.battlecruiser));
				
				
			}
		}
		mUpgrade.setReady(true);
		mUpgrade.setType(1);
		mUpgrade.setReleseTime(3600);
		mUpgrade.setX(mConf.getWidth() / 2);
		mUpgrade.setY(50);
		ready = true;
		break;
	case 6:
		//EndBoss - Super Battlecruiser
		count = 0;

		for(int i = 0; 1 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(16);
				mEnemy[i].setHP(1500 + mPlayer.getRepeat()*300);
				mEnemy[i].setMaxHP(1500 + mPlayer.getRepeat()*300);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(mConf.getHeight() / 2);
				mEnemy[i].setX(mConf.getWidth());
				mEnemy[i].setCrashX(70);
				mEnemy[i].setCrashY(70);
				mEnemy[i].setMoveType(6);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.superbattlecruiser));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.superbattlecruiser));
				count++;
				mEnemy[i].setReleseTime(5000);
			}
		}
		mUpgrade.setReady(true);
		mUpgrade.setType(2);
		mUpgrade.setReleseTime(5200);
		mUpgrade.setX(mConf.getWidth() / 2);
		mUpgrade.setY(mConf.getHeight() / 3);
		ready = true;
		break;
	}
}
void Wave::protoss(Enemy mEnemy[], int max, Player &mPlayer, Bitmap &mBitmap, Upgrade &mUpgrade){
	Config mConf;
	switch(mPlayer.getSubStage()){
	case 1:
		// 5x Observer
		count = 0;
		for(int i = 0; 5 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setType(21);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setHP(30 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(30 + mPlayer.getRepeat()*10);
				mEnemy[i].setCrashX(9);
				mEnemy[i].setCrashY(11);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.observer));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.observer));
				mEnemy[i].setRout(0);
				mEnemy[i].setMoveType(1);
				count++;
				switch(count){
				case 1:
					mEnemy[i].setX(mConf.getWidth() /2);
					mEnemy[i].setReleseTime(50);
					break;
				case 2:
					mEnemy[i].setX(mConf.getWidth() /2 -150);
					mEnemy[i].setReleseTime(150);
					break;
				case 3:
					mEnemy[i].setX(mConf.getWidth() /2 + 150);
					mEnemy[i].setReleseTime(200);
					break;
				case 4:
					mEnemy[i].setX(mConf.getWidth() /2 - 250);
					mEnemy[i].setReleseTime(250);
					break;
				case 5:
					mEnemy[i].setX(mConf.getWidth() /2 + 250);
					mEnemy[i].setReleseTime(300);
					break;
				}
			}
		}
		ready = true;
		break;
	case 2:
		// 20x Interceptor
		count = 0;
		for(int i = 0; 20 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(22);
				mEnemy[i].setHP(20 + mPlayer.getRepeat()*5);
				mEnemy[i].setMaxHP(20 + mPlayer.getRepeat()*5);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setX(0);
				mEnemy[i].setCrashX(8);
				mEnemy[i].setCrashY(6);
				mEnemy[i].setMoveType(2);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.interceptor));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.interceptor));
				count++;
				mEnemy[i].setReleseTime(450 + count*50);
			}
		}
		ready = true;
		break;

	case 3:
		// 15x scout
		count = 0;

		for(int i = 0; 15 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setHP(20 + mPlayer.getRepeat()*10);
				mEnemy[i].setMaxHP(20 + mPlayer.getRepeat()*10);
				mEnemy[i].setType(23);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setReady(true);
				mEnemy[i].setCrashX(13);
				mEnemy[i].setCrashY(13);
				mEnemy[i].setMoveType(1);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.scout));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.scout));
				count++;
				switch(count){
					//lewo dó³
				case 1:
					mEnemy[i].setY(0);
					mEnemy[i].setX(100);
					mEnemy[i].setReleseTime(1500);
					break;
				case 2:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(60);
					mEnemy[i].setReleseTime(1500);
					break;
				case 3:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(140);
					mEnemy[i].setReleseTime(1500);
					break;
					//œrodek dó³
				case 4:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth()/2);
					mEnemy[i].setReleseTime(1600);
					break;
				case 5:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth()/2 - 40);
					mEnemy[i].setReleseTime(1600);
					break;
				case 6:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth()/2 + 40);
					mEnemy[i].setReleseTime(1600);
					break;
					//prawo dó³
				case 7:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth() -100);
					mEnemy[i].setReleseTime(1700);
					break;
				case 8:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() -140);
					mEnemy[i].setReleseTime(1700);
					break;
				case 9:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() - 60);
					mEnemy[i].setReleseTime(1700);
					break;
					//lewo góra
				case 10:
					mEnemy[i].setY(0);
					mEnemy[i].setX(200);
					mEnemy[i].setReleseTime(1800);
					break;
				case 11:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(160);
					mEnemy[i].setReleseTime(1800);
					break;
				case 12:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(240);
					mEnemy[i].setReleseTime(1800);
					break;
					//prawo góra
				case 13:
					mEnemy[i].setY(0);
					mEnemy[i].setX(mConf.getWidth() -200);
					mEnemy[i].setReleseTime(1800);
					break;
				case 14:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() -240);
					mEnemy[i].setReleseTime(1800);
					break;
				case 15:
					mEnemy[i].setY(-40);
					mEnemy[i].setX(mConf.getWidth() - 160);
					mEnemy[i].setReleseTime(1800);
					break;
				}
			}
		}
		ready = true;
		break;

	case 4:
		//Middleboss - Arbiter
		count = 0;
		for(int i = 0; 1 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(24);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setHP(900 + mPlayer.getRepeat()*100);
				mEnemy[i].setMaxHP(900 + mPlayer.getRepeat()*100);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setX(mConf.getWidth()/2);
				mEnemy[i].setCrashX(18);
				mEnemy[i].setCrashY(16);
				mEnemy[i].setMoveType(3);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.arbiter));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.arbiter));
				count++;
				mEnemy[i].setReleseTime(2100);
			}
		}
		ready = true;
		break;
	case 5:
		//Corsair x20;
		count = 0;
		for(int i = 0; 20 > count; i++){
			if(!mEnemy[i].getLive()){
				count++;
				if(count % 2 == 1){
					mEnemy[i].setX(100);
					mEnemy[i].setMoveType(4);
					mEnemy[i].setReleseTime(3150 + count*50);
				} else {
					mEnemy[i].setX(mConf.getWidth() - 100);
					mEnemy[i].setMoveType(5);
					mEnemy[i].setReleseTime(3150 + (count-1)*50);
				}
				mEnemy[i].setType(25);
				mEnemy[i].setSpeed(2);
				mEnemy[i].setHP(55 + mPlayer.getRepeat()*15);
				mEnemy[i].setMaxHP(55 + mPlayer.getRepeat()*15);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(0);
				mEnemy[i].setRout(0);
				mEnemy[i].setCrashX(13);
				mEnemy[i].setCrashY(16);
				
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.corsair));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.corsair));
				
				
			}
		}
		mUpgrade.setReady(true);
		mUpgrade.setType(1);
		mUpgrade.setReleseTime(3600);
		mUpgrade.setX(mConf.getWidth() / 2);
		mUpgrade.setY(50);
		ready = true;
		break;
	case 6:
		//EndBoss - Carrier
		count = 0;

		for(int i = 0; 1 > count; i++){
			if(!mEnemy[i].getLive()){
				mEnemy[i].setRout(0);
				mEnemy[i].setType(26);
				mEnemy[i].setHP(1500 + mPlayer.getRepeat()*300);
				mEnemy[i].setMaxHP(1500 + mPlayer.getRepeat()*300);
				mEnemy[i].setSpeed(1);
				mEnemy[i].setReady(true);
				mEnemy[i].setY(mConf.getHeight() / 2);
				mEnemy[i].setX(mConf.getWidth());
				mEnemy[i].setCrashX(29);
				mEnemy[i].setCrashY(40);
				mEnemy[i].setMoveType(6);
				mEnemy[i].setImgX(al_get_bitmap_width(mBitmap.carrier));
				mEnemy[i].setImgY(al_get_bitmap_width(mBitmap.carrier));
				count++;
				mEnemy[i].setReleseTime(4600);
			}
		}
		mUpgrade.setReady(true);
		mUpgrade.setType(2);
		mUpgrade.setReleseTime(4800);
		mUpgrade.setX(mConf.getWidth() / 2);
		mUpgrade.setY(mConf.getHeight() / 3);
		ready = true;
		break;
	}
}
