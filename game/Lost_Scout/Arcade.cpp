#include "Game.h"
#include "config.h"
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "background.h"
#include "text.h"
#include "bitmap.h"
#include "mechanic.h"
#include "_STM.h"

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, UP2, DOWN2, LEFT2, RIGHT2, SPACE2, R };

void arcade(Config &mConf, int &exit, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue,  ALLEGRO_TIMER *timer, Bitmap & mBitmap){
	//Config mConf;
	Bullet *mBullet = new Bullet [mConf.getMaxBullet()];
	Bullet *mBullet2 = new Bullet [mConf.getMaxBullet()];
	cout << "Start gry" << endl;
	bool end = false;
	bool rysuj = false;
	bool score = false;
	bool pause = false;
	int maxenemy;

	Player mPlayer(false);
	Player mPlayer2(true);
	Text mText;
	Mechanic mMech;
	Sound mSound(mConf);
	Background mBG;

	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue,al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

		bool keys[11] = {false, false, false, false, false, false, false, false, false, false, false};
	
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

	int level = mMech.getLevel(exit, eventQueue, mBitmap, mSound);
	switch (level){
	case 1: 
		maxenemy = mConf.getArcadeEnemyEasy();
		break;
	case 2: 
		maxenemy = mConf.getArcadeEnemyMedium();
		break;
	case 3: 
		maxenemy = mConf.getArcadeEnemyHard();
		break;
	case 4: 
		maxenemy = mConf.getArcadeEnemyBrutal();
		break;
	case 0:
		maxenemy = 0;
		end = true;
		break;
	}
	Enemy *mEnemy = new Enemy [maxenemy];
	int graczy = 0;
	if(exit == 0)
	graczy = mMech.getPlayers(exit, eventQueue, mBitmap, mSound);
	if(exit == 0)
	while(!end){
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
					if(!pause){
						if(!pause && !mConf.gameOver && mPlayer.getRestTime() == 0 && mPlayer2.getRestTime() == 0){
						mSound.shoot();
						mMech.Fire(mBullet, mConf.getMaxBullet(), mPlayer);
						}
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
						if(!pause && !mConf.gameOver && mPlayer.getRestTime() == 0 && mPlayer2.getRestTime() == 0){
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
						mMech.Restart(mPlayer, mEnemy, mBullet, mConf, maxenemy);
						if(graczy == 2){
						mMech.Restart(mPlayer2, mEnemy, mBullet2, mConf);
					}
					break;
				case ALLEGRO_KEY_M:
					mSound.muteSound(mConf);
					break;
				case ALLEGRO_KEY_P:
					if(!mConf.gameOver){
						if(pause){
							pause = false;
						} else {
							pause = true;
						}
					}
				}
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
			end = true;
			exit = 1;
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
					mPlayer.move(buffer_in);	
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
					
					for(int i=0 ; i < mConf.getMaxBullet(); i++){
						if(mBullet[i].getLive())
							mBullet[i].update();
					}
					for(int i=0 ; i < mConf.getMaxBullet(); i++){
						if(mBullet2[i].getLive())
							mBullet2[i].update();
					}
					if(mPlayer.getRestTime() == 0 && mPlayer2.getRestTime() == 0){
						mBG.update();
						mPlayer.incTimer();
						if(mPlayer.getTimer() > 120)
						mMech.NewEnemy(mEnemy, maxenemy, mPlayer, level);
						for(int i=0 ; i < maxenemy; i++){
							if(mEnemy[i].getLive())
								mEnemy[i].update(mPlayer);
						}
			
						mMech.TangoDown( mEnemy, mBullet, maxenemy, mConf.getMaxBullet(), mPlayer, mSound);
						mMech.PlayerColl(mEnemy, maxenemy, mPlayer, mSound);
						if(graczy == 2){
							mMech.TangoDown( mEnemy, mBullet2, maxenemy, mConf.getMaxBullet(), mPlayer2, mSound);
							mMech.PlayerColl(mEnemy, maxenemy, mPlayer2, mSound);
						}
					}
					if(mPlayer.getLives() <= 0 || mPlayer2.getLives() <= 0){
						mConf.gameOver = true;
						cout << "Koniec gry, wynik: " << mPlayer.getScore() << endl;
					}
				}
			}
		}

		if(rysuj && al_is_event_queue_empty(eventQueue))
		{
			///////////////////STM
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
			///////////////////STM

			
			rysuj = false;
			if(!mConf.gameOver){
				mBG.show();
				if(mPlayer.getRestTime() > 0){
					if(mPlayer.getRestTime() % 3 == 0){
						
					mPlayer.show();
					if(graczy == 2)
					mPlayer2.show();
					}
				} else if(mPlayer2.getRestTime() > 0){
					if(mPlayer2.getRestTime() % 3 == 0){	
					mPlayer.show();
					mPlayer2.show();
					}
				} else {
					mPlayer.show();
					if(graczy == 2)
					mPlayer2.show();
				}
				for(int i=0 ; i < mConf.getMaxBullet(); i++){
					if(mBullet[i].getLive())
					mBullet[i].show(mPlayer);
					if(mBullet2[i].getLive())
					mBullet2[i].show(mPlayer);
				}
				for(int i=0 ; i < maxenemy; i++){
					if(mEnemy[i].getLive())
						mEnemy[i].show();
				}
				if(mPlayer.getRestTime() > 0){
					mText.countDown(mPlayer);
					mPlayer.setRestTime(mPlayer.getRestTime() - 1);
				}	
				if(mPlayer2.getRestTime() > 0){
					mText.countDown(mPlayer2);
					mPlayer2.setRestTime(mPlayer2.getRestTime() - 1);
				}
				mText.drawUI(mBitmap);
				if(graczy != 2)
					mText.viewScore(mPlayer.getScore(), mPlayer.getLives(), mPlayer.getNrKilled(), mPlayer.getNrLeft(), mPlayer.getNrShoots());
				else
					mText.viewScoreMulti(mPlayer, mPlayer2);
			} else {
				mText.drawUI(mBitmap);
				if(graczy != 2){
					mText.viewScore(mPlayer.getScore(), mPlayer.getLives(), mPlayer.getNrKilled(), mPlayer.getNrLeft(), mPlayer.getNrShoots());
					mText.viewBigScoreArc(mPlayer.getScore());
				} else {
					mText.viewScoreMulti(mPlayer, mPlayer2);
					mText.viewBigScoreArc(mPlayer.getScore(), mPlayer2.getScore());
				}
			}
			if(pause){
				mText.pause();
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
