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

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, R };

void arcade(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *eventQueue,  ALLEGRO_TIMER *timer, Bitmap & mBitmap){
	Config mConf;
	Bullet *mBullet = new Bullet [mConf.getMaxBullet()];
	
	cout << "Start gry" << endl;
	bool end = false;
	bool rysuj = false;
	bool score = false;
	bool pause = false;
	int maxenemy;

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
	
	int level = mMech.getLevel(eventQueue, mBitmap, mSound);
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


	while(!end){
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventQueue, &ev);

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
						if(mPlayer.getRestTime() == 0){
						mSound.shoot();
						mMech.Fire(mBullet, mConf.getMaxBullet(), mPlayer);
						}
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
						mMech.Restart(mPlayer, mEnemy, mBullet, mConf, maxenemy);
					}
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
			}
			if(!mConf.gameOver){
				if(!pause){
					
					for(int i=0 ; i < mConf.getMaxBullet(); i++){
						if(mBullet[i].getLive())
							mBullet[i].update();
					}
					if(mPlayer.getRestTime() == 0){
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

			
			rysuj = false;
			if(!mConf.gameOver){
				mBG.show();
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
				for(int i=0 ; i < maxenemy; i++){
					if(mEnemy[i].getLive())
						mEnemy[i].show();
				}
				if(mPlayer.getRestTime() > 0){
					mText.countDown(mPlayer);
					mPlayer.setRestTime(mPlayer.getRestTime() - 1);
				}		
				mText.drawUI(mBitmap);
				mText.viewScore(mPlayer.getScore(), mPlayer.getLives(), mPlayer.getNrKilled(), mPlayer.getNrLeft(), mPlayer.getNrShoots());
			} else {
				mText.drawUI(mBitmap);
				mText.viewScore(mPlayer.getScore(), mPlayer.getLives(), mPlayer.getNrKilled(), mPlayer.getNrLeft(), mPlayer.getNrShoots());
				mText.viewBigScoreArc(mPlayer.getScore());		
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
