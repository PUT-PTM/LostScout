#include "Game.h"
#include "config.h"
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "text.h"
#include "wave.h"
#include "upgrade.h"
#include "background.h"
#include "sound.h"
#include "mechanic.h"
#include "bitmap.h"

#include "_STM.h"
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, R };

void game(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue,  ALLEGRO_TIMER *timer, Bitmap & mBitmap){
	Config mConf;
	Wave mWave;

	Bullet *mBullet = new Bullet [mConf.getMaxBullet()];
	Enemy *mEnemy = new Enemy [mConf.getMaxEnemy()];
	Upgrade mUpgrade;
	cout << "Start gry" << endl;
	bool end = false;
	bool rysuj = false;
	bool score = false;
	bool save = false;
	bool pause = false;
	int blokstrzal = 0;
	Player mPlayer;
	Text mText;
	Mechanic mMech;
	Sound mSound;
	Background mBG;

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	bool keys[6] = {false, false, false, false, false, false};


	al_start_timer(timer);	

	////////////////STM
	bool conn = FindTheHID();	
	char buffer_out[64];
	char buffer_in[64];
	for (int i=0;i<64;i++) {
		buffer_out[i]=0;	
		buffer_in[i]=0;
	}

	////////////////STM
	while(!end){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);
		if(conn){
			ReadInputReport(buffer_in);	//////////STM
		}else{
			cout <<"'";
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode)	{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				if(!pause && !mConf.gameOver && mPlayer.getRestTime() == 0){
					mSound.shoot();
					mMech.Fire(mBullet, mConf.getMaxBullet(), mPlayer);
				}
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				mSound.click();
				al_rest(0.35);
				//end = true;
				if(mConf.gameOver == false)
					mConf.gameOver = true;
				else
					end = true;
				break;
			case ALLEGRO_KEY_R:
				if(mConf.gameOver){
					mSound.click();
					mMech.Restart(mPlayer, mEnemy, mBullet, mConf);
					save = false;
					mConf.gameOver = false;
				}
				break;
			case ALLEGRO_KEY_ENTER:
				if(mConf.gameOver && save == false){
					mSound.click();
					mPlayer.saveScore(eventQueue, mBitmap, mSound);
					save = true;
				}
				break;
			case ALLEGRO_KEY_P:
				if(!mConf.gameOver){
					if(pause){
						pause = false;
						mSound.click();
					} else {
						pause = true;
						mSound.click();
					}
				}
				break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode)	{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				//end = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			mSound.click();
			al_rest(0.35);
			end = true;
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER){		

			mSound.game();
			rysuj = true;
			if(!pause){
				if(keys[UP])
					mPlayer.up();
				if(keys[DOWN])
					mPlayer.down();
				if(keys[LEFT])
					mPlayer.left();
				if(keys[RIGHT])
					mPlayer.right();

				///////////KOD DO STMa
				if(conn){
					mPlayer.move(buffer_in);	
				}else{
					//cout <<"'";
				}
				///////////KOD DO STMa
			}
			if(!mConf.gameOver){
				if(!pause){
					mWave.wyzwalacz(mEnemy, mConf.getMaxEnemy(), mPlayer, mBitmap, mUpgrade);

					for(int i=0 ; i < mConf.getMaxBullet(); i++){
						if(mBullet[i].getLive())
							mBullet[i].update();
					}
					if(mUpgrade.getLive())
						mUpgrade.update(mPlayer);
					if(mPlayer.getRestTime() == 0){
						mBG.update();
						for(int i=0 ; i < mConf.getMaxEnemy(); i++){
							if(mEnemy[i].getReady() && mEnemy[i].getReleseTime() == mPlayer.getTimer()){
								mEnemy[i].setLive(true);
								mEnemy[i].setReady(false);
							}
							if(mEnemy[i].getLive())
								mEnemy[i].updateWave(mPlayer);
						}
						if(mUpgrade.getReady() && mUpgrade.getReleseTime() == mPlayer.getTimer()){
							mUpgrade.setLive(true);
							mUpgrade.setReady(false); 
							mSound.newUpgrade();
						}
						
						mMech.TangoDown( mEnemy, mBullet, mConf.getMaxEnemy(), mConf.getMaxBullet(), mPlayer, mWave, mSound);
						//mMech.PlayerColl(mEnemy, mConf.getMaxEnemy(), mPlayer, mSound);
						mMech.PlayerUpgrade(mUpgrade, mPlayer, mSound);
					}
					if(mPlayer.getLives() <= 0){
						mConf.gameOver = true;
						cout << "Koniec gry, wynik: " << mPlayer.getScore() << endl;
					}
				}
			}
		}

		if(rysuj && al_is_event_queue_empty(eventQueue))
		{

					if(buffer_in[3] == 1 && blokstrzal == 0){
						if(mPlayer.getRestTime() == 0){
							cout << "a";
							mSound.shoot();
							mMech.Fire(mBullet, mConf.getMaxBullet(), mPlayer);
							blokstrzal = 20;
						}
					} else if(buffer_in[3] == 0){
						blokstrzal = 0;
					}
					if(blokstrzal > 0)
						blokstrzal--;

			rysuj = false;
			if(!mConf.gameOver){
				mBG.show();
				if(mPlayer.getRestTime() == 0 && !pause){
					mPlayer.incTimer();
				}
				if(mPlayer.getRestTime() > 0){
					if(mPlayer.getRestTime() % 3 == 0){
						mPlayer.show();
					}
				} else {
					mPlayer.show();
				}

				for(int i=0 ; i < mConf.getMaxBullet(); i++){
					if(mBullet[i].getLive())
						mBullet[i].show(mPlayer);
				}
				for(int i=0 ; i < mConf.getMaxEnemy(); i++){
					if(mEnemy[i].getLive())
						mEnemy[i].show(mBitmap, mText);
				}
				if(mUpgrade.getLive())
					mUpgrade.show(mBitmap, mText);

				if(pause){
					mText.pause();
				}
				if(mPlayer.getRestTime() > 0){
					if(mPlayer.getRestTime() > 180){
						mText.nextPhase(mPlayer);
					}
					mText.countDown(mPlayer);
					mPlayer.setRestTime(mPlayer.getRestTime() - 1);
				}
				mText.drawUI(mBitmap);
				mText.viewScore(mPlayer.getScore(), mPlayer.getLives(), mPlayer.getNrKilled(), mPlayer.getNrLeft(), mPlayer.getNrShoots());
				mText.timer(mPlayer);
			} else {
				mText.drawUI(mBitmap);
				mText.viewBigScore(mPlayer.getScore());
				if(save){
					mText.saved();
				}


			}
			mText.viewVersion();
			mText.viewInfo();
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	cout << "Wyjœcie z pêtli" << endl;
	al_destroy_event_queue(eventQueue);
	delete [] mBullet;
	delete [] mEnemy;
}
