#include "main.h"
#include "config.h"
#include "bullet.h"
#include "wave.h"
#include "enemy.h"
#include "player.h"
#include "upgrade.h"
#include "sound.h"
#include "bitmap.h"
#include "mechanic.h"
#include "text.h"

#include "_STM.h"
void Mechanic::Fire(Bullet mBullet[], int max, Player &mPlayer){
	for( int i = 0; i < max; i++){

		if(!mBullet[i].getLive()){

			mBullet[i].setX(mPlayer.getX());
			mBullet[i].setY(mPlayer.getY());
			mBullet[i].setLive(true);
			mPlayer.incNrShoots();
			break;

		}
	}
}

void Mechanic::NewEnemy(Enemy mEnemy[], int max, Player &mPlayer, int level){
	Config mConf;
	for(int i = 0; i < max; i++)
	{
		if(!mEnemy[i].getLive())
		{		
			if(rand() % 500 == 0)
			{
				switch(level){
				case 1:
					mEnemy[i].setSpeed(1);
					break;
				case 2:
					mEnemy[i].setSpeed(2);
					break;
				case 3:
					mEnemy[i].setSpeed(3);
					break;
				case 4:
					mEnemy[i].setSpeed(6);
				}

				mEnemy[i].setLive(true);
				mEnemy[i].setX(50 + ( rand() % (mConf.getWidth() - 100)));
				mEnemy[i].setY(0);
				mEnemy[i].setCrashX(21);
				mEnemy[i].setCrashY(29);
				break;
			}
		}
	}

}

void Mechanic::TangoDown(Enemy mEnemy[], Bullet mBullet[], int maxE, int maxB, Player &mPlayer, Wave &mWave, Sound &mSound){
	for(int j =0; j < maxE; j++){
		if(mEnemy[j].getLive()){
			for(int i = 0; i < maxB; i++){
				if(mBullet[i].getLive()){
					if(mBullet[i].getX() > (mEnemy[j].getX() - mEnemy[j].getCrashX()) &&
						mBullet[i].getX() < (mEnemy[j].getX() + mEnemy[j].getCrashX()) &&
						mBullet[i].getY() > (mEnemy[j].getY() - mEnemy[j].getCrashY()) &&
						mBullet[i].getY() < (mEnemy[j].getY() + mEnemy[j].getCrashY()))
					{
						mEnemy[j].setHP(mEnemy[j].getHP() - mPlayer.getDmg());

						mBullet[i].setLive(false);
						if(mEnemy[j].getHP() > 0){
							cout << "Trafiony! Pozosta³e ¿ycie:" << mEnemy[j].getHP() << endl;
						}
					}
				}
			}
			if(mEnemy[j].getHP() <= 0){
				mEnemy[j].setLive(false);
				int score = mPlayer.getScore() + mEnemy[j].getMaxHP();
				mPlayer.setScore(score);
				cout << "Zabity! Wynik:" << score << endl;
				mPlayer.incNrKilled();
				switch(mPlayer.getStage()){
				case 0:
					mSound.zergDie();
					break;
				case 1:
					mSound.zergDie();
					break;
				case 2:
					mSound.terranDie();
					break;
				case 3:
					mSound.protossDie();
					break;
				}
				if(mEnemy[j].getType() == 6){
					mWave.setBossAlive(false);
				}
				if(mEnemy[j].getType() == 16){
					mWave.setBossAlive(false);
				}
				if(mEnemy[j].getType() == 26){
					mWave.setBossAlive(false);
				}
			}
		}
	}
}
void Mechanic::TangoDown(Enemy mEnemy[], Bullet mBullet[], int maxE, int maxB, Player &mPlayer, Sound &mSound){
	for(int i = 0; i < maxB; i++){
		if(mBullet[i].getLive()){
			for(int j =0; j < maxE; j++){
				if(mEnemy[j].getLive()){
					if(mBullet[i].getX() > (mEnemy[j].getX() - mEnemy[j].getCrashX()) &&
						mBullet[i].getX() < (mEnemy[j].getX() + mEnemy[j].getCrashX()) &&
						mBullet[i].getY() > (mEnemy[j].getY() - mEnemy[j].getCrashY()) &&
						mBullet[i].getY() < (mEnemy[j].getY() + mEnemy[j].getCrashY()))
					{
						mBullet[i].setLive(false);
						mEnemy[j].setLive(false);
						int score = mPlayer.getScore() + 10;
						mPlayer.setScore(score);
						cout << "Trafiony! Wynik:" << score << endl;
						mSound.zergDie();
						mPlayer.incNrKilled();
					}
				}
			}
		}
	}
}

void Mechanic::PlayerColl(Enemy mEnemy[], int max, Player &mPlayer, Sound &mSound){
	for(int i = 0; i < max; i++)
	{
		if(mEnemy[i].getLive())
		{
			if(mEnemy[i].getX() - mEnemy[i].getCrashX() < mPlayer.getX() + mPlayer.getCrashX() &&
				mEnemy[i].getX() + mEnemy[i].getCrashX() > mPlayer.getX() - mPlayer.getCrashX() &&
				mEnemy[i].getY() - mEnemy[i].getCrashY() < mPlayer.getY() + mPlayer.getCrashY() &&
				mEnemy[i].getY() + mEnemy[i].getCrashY() > mPlayer.getY() - mPlayer.getCrashY())
			{
				int lives = mPlayer.getLives();
				lives--;

				mPlayer.setLives(lives);
				Config mConf;
				mPlayer.setX(mConf.getWidth() /2);
				mPlayer.setY(mConf.getHeight() - 50);
				cout << "Tracisz ¿ycie! Pozosta³y " <<  mPlayer.getLives() << endl;
				mSound.playerDie();
				if(mEnemy[i].getHP() != 1)
					mEnemy[i].setHP(mEnemy[i].getHP() - 50);
				else
					mEnemy[i].setLive(false);
				mPlayer.setRestTime(180);
				mPlayer.setDmg(10);


				WriteOutputReportEdit(1);
			}
		}
	}
}

void Mechanic::Restart(Player &mPlayer, Enemy mEnemy[], Bullet mBullet[], Config &mConf){
	cout << "Restart gry";
	mPlayer.setDmg(10);
	mPlayer.setLives(3);
	mPlayer.setX(mConf.getWidth() / 2);
	mPlayer.setY(mConf.getHeight() / 2);
	mPlayer.setScore(0);
	mPlayer.setTimer(0);
	mPlayer.setStage(1);
	mPlayer.setSubStage(1);
	mPlayer.zeroStats();
	mPlayer.setRepeat(0);
	mPlayer.setDmg(10);
	mPlayer.setRestTime(0);
	for(int i = 0; i < mConf.getMaxBullet(); i++){
		mBullet[i].setLive(false);
	}

	for(int i = 0; i < mConf.getMaxEnemy(); i++){
		mEnemy[i].setLive(false);
	}
	mConf.gameOver = false;
}
void Mechanic::Restart(Player &mPlayer, Enemy mEnemy[], Bullet mBullet[], Config &mConf, int maxEnemy){
	cout << "Restart gry" << endl;
	mPlayer.setDmg(10);
	mPlayer.setLives(3);
	mPlayer.setX(mConf.getWidth() / 2);
	mPlayer.setY(mConf.getHeight() / 2);
	mPlayer.setScore(0);
	mPlayer.setTimer(0);
	mPlayer.setStage(1);
	mPlayer.setSubStage(1);
	mPlayer.zeroStats();
	mPlayer.setRepeat(0);
	mPlayer.setDmg(10);
	mPlayer.setRestTime(0);
	for(int i = 0; i < mConf.getMaxBullet(); i++){
		mBullet[i].setLive(false);
	}

	for(int i = 0; i < maxEnemy; i++){
		mEnemy[i].setLive(false);
	}
	mConf.gameOver = false;
}
int Mechanic::getLevel(ALLEGRO_EVENT_QUEUE *eventQueue, Bitmap &mBitmap, Sound &mSound){
	bool end = false;
	ALLEGRO_FONT *font36 = al_load_font("Starcraft.ttf", 36, 0);
	ALLEGRO_FONT *font24 = al_load_font("Starcraft.ttf", 24, 0);
	Config mConf;
	int wybor = 1;
	int max = 4;
	Text mText;




	while(!end){
		mSound.game();
		mText.drawUI(mBitmap);
		al_draw_textf(font36, al_map_rgb(220,220,220), mConf.getWidth() / 2, 40, ALLEGRO_ALIGN_CENTER , "Poziom trudnosci");

		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);


		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode)	{
			case ALLEGRO_KEY_UP:
				mSound.point();
				wybor--;
				break;
			case ALLEGRO_KEY_DOWN:
				mSound.point();
				wybor++;
				break;
			case ALLEGRO_KEY_ENTER:
				mSound.click();
				al_rest(0.35);
				end = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				mSound.click();
				al_rest(0.35);
				wybor = 0;
				end = true;

				break;

			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			wybor = 0;
			end = true;
		}

		if(wybor <=0 && !end){
			wybor = max;
		}
		if(wybor > max){
			wybor = 1;
		}

		if(wybor == 1){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 200, ALLEGRO_ALIGN_CENTER , "Latwy");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 200, ALLEGRO_ALIGN_CENTER , "Latwy");
		}
		if(wybor == 2){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 250, ALLEGRO_ALIGN_CENTER , "Sredni");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 250, ALLEGRO_ALIGN_CENTER , "Sredni");
		}
		if(wybor == 3){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 300, ALLEGRO_ALIGN_CENTER , "Trudny");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 300, ALLEGRO_ALIGN_CENTER , "Trudny");
		}
		if(wybor == 4){
			al_draw_textf(font24, al_map_rgb(255,0,0), mConf.getWidth() / 2, 350, ALLEGRO_ALIGN_CENTER , "Brutalny");
		} else {
			al_draw_textf(font24, al_map_rgb(220,220,220), mConf.getWidth() / 2, 350, ALLEGRO_ALIGN_CENTER , "Brutalny");
		}

		mText.viewInfo();
		mText.viewVersion();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
	cout << "Poziom trudnosci: " << wybor << endl;
	return wybor;

}

void Mechanic::PlayerUpgrade(Upgrade &mUpgrade, Player &mPlayer, Sound &mSound){
	if(mUpgrade.getLive()){


		if(mUpgrade.getX()+5 > (mPlayer.getX() - mPlayer.getCrashX()) &&
			mUpgrade.getX()-5 < (mPlayer.getX() + mPlayer.getCrashX()) &&				
			mUpgrade.getY()+5 > (mPlayer.getY() - mPlayer.getCrashY()) &&
			mUpgrade.getY()-5 < (mPlayer.getY() + mPlayer.getCrashY()))
		{
			mUpgrade.setLive(false);
			switch(mUpgrade.getType()){
			case 1:
				if(mPlayer.getDmg() <= 20){
					mPlayer.setDmg(mPlayer.getDmg() + 10);
					mPlayer.setScore(mPlayer.getScore() + 500);	
					//////////STM
					if(mPlayer.getDmg() == 20)
						WriteOutputReportEdit(2);
					else if(mPlayer.getDmg() == 30)
						WriteOutputReportEdit(3);
					//////////STM
				}
				cout << "Zwiêkszasz dmg do:" << mPlayer.getDmg() << endl;
				break;
			case 2:
				mPlayer.setLives(mPlayer.getLives() + 1);
				mPlayer.setScore(mPlayer.getScore() + 500);
				cout << "Zwiêkszasz ¿ycie do:" << mPlayer.getLives() << endl;
				//////////STM
				WriteOutputReportEdit(4);
				//////////STM
			}
			mSound.upgrade(mUpgrade.getType());
			
		}
	}
}