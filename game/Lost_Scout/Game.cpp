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
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, UP2, DOWN2, LEFT2, RIGHT2, SPACE2, R };

void game(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue,  ALLEGRO_TIMER *timer, Bitmap & mBitmap){
	//Config mConf;
	Wave mWave;

	Bullet *mBullet = new Bullet [mConf.getMaxBullet()];
	Bullet *mBullet2 = new Bullet [mConf.getMaxBullet()];
	Enemy *mEnemy = new Enemy [mConf.getMaxEnemy()];
	Upgrade mUpgrade;
	cout << "Start gry" << endl;
	bool end = false;
	bool rysuj = false;
	bool score = false;
	bool save = false;
	bool pause = false;
	Player mPlayer1(false);
	Player mPlayer2(true);
	Text mText;
	Mechanic mMech;
	Sound mSound(mConf);
	Background mBG;

	bool cziter = FALSE;

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	bool keys[11] = {false, false, false, false, false, false, false, false, false, false, false};
	bool czity[2] = {false, false};

	al_start_timer(timer);	

	////////////////STM
	bool conn = FindTheHID();	
	bool conn2 = FALSE;
	if(conn)
		conn2 = FindTheHID2();
	char buffer_out[64];
	char buffer_in[64];
	for (int i=0;i<64;i++) {
		buffer_out[i]=0;	
		buffer_in[i]=0;
	}
	char buffer_out2[64];
	char buffer_in2[64];
	for (int i=0;i<64;i++) {
		buffer_out2[i]=0;	
		buffer_in2[i]=0;
	}
	int blokstrzal = 0;
	int blokstrzal2 = 0;
	////////////////STM

	int graczy = mMech.getPlayers(exit, eventQueue, mBitmap, mSound);
	while(!end && exit == 0){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);
		if(conn){
			ReadInputReport(buffer_in);	//////////STM
		}else{
			//cout <<"'";
		}
		if(conn2 && graczy == 2){
			ReadInputReport2(buffer_in2);	//////////STM
		}else if (graczy == 2){
			//cout <<"*";
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode)	{
				//PLAYER 1
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_F1:
				czity[0] = true;
				cout << "F1" << endl;
				break;
			case ALLEGRO_KEY_F2:
				czity[1] = true;
				cout << "F2" << endl;
				break;
			case ALLEGRO_KEY_F3:
				cout << "F3" << endl;
				if(czity[0] && czity[1]){
					cout << "Czit wprowadzony" << endl;
					if(!cziter){
						cziter = true;
						cout << "Lol, cziterrr" << endl;
					}
					else
					{
						cziter = false;
						cout << "Wracasz na dobre tory..." << endl;
					}
				}
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
				if(!pause && !mConf.gameOver && mPlayer1.getRestTime() == 0 && mPlayer2.getRestTime() == 0){
					mSound.shoot();
					mMech.Fire(mBullet, mConf.getMaxBullet(), mPlayer1);
				}
				keys[SPACE] = true;
				break;
			if(graczy == 2){
				//PLAYER 2
				case ALLEGRO_KEY_W:
					keys[UP2] = true;
					break;
				case ALLEGRO_KEY_S:
					keys[DOWN2] = true;
					break;
				case ALLEGRO_KEY_D:
					keys[RIGHT2] = true;
					break;
				case ALLEGRO_KEY_A:
					keys[LEFT2] = true;
					break;
				case ALLEGRO_KEY_G:
					if(!pause && !mConf.gameOver && mPlayer1.getRestTime() == 0 && mPlayer2.getRestTime() == 0){
						mSound.shoot();
						mMech.Fire(mBullet2, mConf.getMaxBullet(), mPlayer2);
					}
					keys[SPACE2] = true;
					break;
				}

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
					mMech.Restart(mPlayer1, mEnemy, mBullet, mConf);
					if(graczy == 2){
					mMech.Restart(mPlayer2, mEnemy, mBullet2, mConf);
					}
					save = false;
					mConf.gameOver = false;
				}
				break;
			case ALLEGRO_KEY_M:
				mSound.muteSound(mConf);
				break;
			case ALLEGRO_KEY_ENTER:
				if(mConf.gameOver && save == false && graczy == 1){
					mSound.click();
					mPlayer1.saveScore(exit, eventQueue, mBitmap, mSound);
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
			case ALLEGRO_KEY_F1:
				czity[0] = false;
				break;
			case ALLEGRO_KEY_F2:
				czity[1] = false;
				break;
			if(graczy == 2){
				//PLAYER 2
				case ALLEGRO_KEY_W:
					keys[UP2] = false;
					break;
				case ALLEGRO_KEY_S:
					keys[DOWN2] = false;
					break;
				case ALLEGRO_KEY_D:
					keys[RIGHT2] = false;
					break;
				case ALLEGRO_KEY_A:
					keys[LEFT2] = false;
					break;
				case ALLEGRO_KEY_G:
					keys[SPACE2] = false;
					break;
			}
			}
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			mSound.click();
			al_rest(0.35);
			end = true;
			exit = 1;
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER){		

			mSound.game();
			rysuj = true;
			if(!pause){
				if(keys[UP])
					mPlayer1.up();
				if(keys[DOWN])
					mPlayer1.down();
				if(keys[LEFT])
					mPlayer1.left();
				if(keys[RIGHT])
					mPlayer1.right();
				if(graczy == 2){
				if(keys[UP2])
					mPlayer2.up();
				if(keys[DOWN2])
					mPlayer2.down();
				if(keys[LEFT2])
					mPlayer2.left();
				if(keys[RIGHT2])
					mPlayer2.right();
				}
				///////////KOD DO STMa
				if(conn){
					mPlayer1.move(buffer_in);	
				}else{
					//cout <<"'";
				}
				if(conn2  && graczy == 2){
					mPlayer2.move(buffer_in2);	
				}else{
					//cout <<"'";
				}
				///////////KOD DO STMa
			}
			if(!mConf.gameOver){
				if(!pause){
					mWave.wyzwalacz(mEnemy, mConf.getMaxEnemy(), mPlayer1, mPlayer2, mBitmap, mUpgrade);		//!!!

					for(int i=0 ; i < mConf.getMaxBullet(); i++){
						if(mBullet[i].getLive())
							mBullet[i].update();
					}
					for(int i=0 ; i < mConf.getMaxBullet(); i++){
						if(mBullet2[i].getLive())
							mBullet2[i].update();
					}
					if(mUpgrade.getLive())
						mUpgrade.update(mPlayer1);
					//!!!
					if(mPlayer1.getRestTime() == 0 && mPlayer2.getRestTime() == 0){		//
						mBG.update();
						for(int i=0 ; i < mConf.getMaxEnemy(); i++){
							if(mEnemy[i].getReady() && mEnemy[i].getReleseTime() == mPlayer1.getTimer()){		//!!!
								mEnemy[i].setLive(true);
								mEnemy[i].setReady(false);
							}
							if(mEnemy[i].getLive())
								mEnemy[i].updateWave(mPlayer1);		//!!!
						}
						if(mUpgrade.getReady() && mUpgrade.getReleseTime() == mPlayer1.getTimer()){		//!!!
							mUpgrade.setLive(true);
							mUpgrade.setReady(false); 
							mSound.newUpgrade();
						}
						
						mMech.TangoDown( mEnemy, mBullet, mConf.getMaxEnemy(), mConf.getMaxBullet(), mPlayer1, mWave, mSound);
						if(graczy == 2)
							mMech.TangoDown( mEnemy, mBullet2, mConf.getMaxEnemy(), mConf.getMaxBullet(), mPlayer2, mWave, mSound);
						///##########################
						if(!cziter){
						
							mMech.PlayerColl(mEnemy, mConf.getMaxEnemy(), mPlayer1, mSound);
							if(graczy == 2)
								mMech.PlayerColl(mEnemy, mConf.getMaxEnemy(), mPlayer2, mSound);
						} else {
							mText.cziter();
						}
						mMech.PlayerUpgrade(mUpgrade, mPlayer1, mSound);
						if(graczy == 2)
							mMech.PlayerUpgrade(mUpgrade, mPlayer2, mSound);
					}
					if(mPlayer1.getLives() <= 0 || mPlayer2.getLives() <= 0 ){
						mConf.gameOver = true;
						cout << "Koniec gry, wynik: " << mPlayer1.getScore() << endl;
					}
				}
			}
		}

		if(rysuj && al_is_event_queue_empty(eventQueue))
		{
			//STM
					if(buffer_in[3] == 1 && blokstrzal == 0){
						if(mPlayer1.getRestTime() == 0){
							cout << "a";
							mSound.shoot();
							mMech.Fire(mBullet, mConf.getMaxBullet(), mPlayer1);
							blokstrzal = 20;
						}
					} else if(buffer_in[3] == 0){
						blokstrzal = 0;
					}
					if(blokstrzal > 0)
						blokstrzal--;

					if(buffer_in2[3] == 1 && blokstrzal2 == 0){
						if(mPlayer2.getRestTime() == 0){
							cout << "a";
							mSound.shoot();
							mMech.Fire(mBullet2, mConf.getMaxBullet(), mPlayer2);
							blokstrzal2 = 20;
						}
					} else if(buffer_in2[3] == 0){
						blokstrzal2 = 0;
					}
					if(blokstrzal2 > 0)
						blokstrzal2--;
			//STM
			rysuj = false;
			if(!mConf.gameOver){
				mBG.show();
				if(mPlayer1.getRestTime() == 0 && mPlayer2.getRestTime() == 0 && !pause){
					mPlayer1.incTimer();
					mPlayer2.incTimer();
				}
				if(mPlayer1.getRestTime() > 0){
					if(mPlayer1.getRestTime() % 3 == 0){
						mPlayer1.show();
						if(graczy == 2)
						mPlayer2.show();
					}
				} else if(mPlayer2.getRestTime() > 0){
					if(mPlayer2.getRestTime() % 3 == 0){
						mPlayer1.show();
						if(graczy == 2)
						mPlayer2.show();
					}
				} else {
					mPlayer1.show();
					if(graczy == 2)
					mPlayer2.show();
				}

				for(int i=0 ; i < mConf.getMaxBullet(); i++){
					if(mBullet[i].getLive())
						mBullet[i].show(mPlayer1); ////////////////////////////////////
					if(mBullet2[i].getLive())
						mBullet2[i].show(mPlayer2);
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
				if(mPlayer1.getRestTime() > 0){
					if(mPlayer1.getRestTime() > 180){
						mText.nextPhase(mPlayer1);
					}
					mText.countDown(mPlayer1);
					mPlayer1.setRestTime(mPlayer1.getRestTime() - 1);
				}
				if(mPlayer2.getRestTime() > 0){
					mText.countDown(mPlayer2);
					mPlayer2.setRestTime(mPlayer2.getRestTime() - 1);
				}

				mText.drawUI(mBitmap);
				if(graczy != 2)
					mText.viewScore(mPlayer1.getScore(), mPlayer1.getLives(), mPlayer1.getNrKilled(), mPlayer1.getNrLeft(), mPlayer1.getNrShoots());
				else
					mText.viewScoreMulti(mPlayer1, mPlayer2);
				mText.timer(mPlayer1);
			} else {
				// KONIEC GRY //////////////////////////
				mText.drawUI(mBitmap);
				if(graczy != 2){
					mText.viewBigScore(mPlayer1.getScore());
					if(save){
						mText.saved();
					}
				} else {
					mText.viewBigScore(mPlayer1.getScore(), mPlayer2.getScore());
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
	delete [] mBullet2;
	delete [] mEnemy;
}
