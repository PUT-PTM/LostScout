#include "main.h"
#include "config.h"

#include "sound.h"

Sound::Sound(Config &mConf){

	nrTrack = rand() % 6;
	menuMusicS = NULL;
	menuMusicI = NULL;
	menuMusicS = al_load_sample("music/menu.wav");
	menuMusicI = al_create_sample_instance(menuMusicS);
	al_set_sample_instance_playmode(menuMusicI, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(menuMusicI, al_get_default_mixer());

	gotS = NULL;
	gotI = NULL;
	gotS = al_load_sample("music/1-got.wav");
	gotI = al_create_sample_instance(gotS);
	al_set_sample_instance_gain(gotI, 0.7);
	al_attach_sample_instance_to_mixer(gotI, al_get_default_mixer());

	t1S = NULL;
	t1I = NULL;
	t1S = al_load_sample("music/Terran - 1.wav");
	t1I = al_create_sample_instance(t1S);
	al_set_sample_instance_gain(t1I, 0.7);
	al_attach_sample_instance_to_mixer(t1I, al_get_default_mixer());

	t2S = NULL;
	t2I = NULL;
	t2S = al_load_sample("music/Terran - 2.wav");
	t2I = al_create_sample_instance(t2S);
	al_set_sample_instance_gain(t2I, 0.7);
	al_attach_sample_instance_to_mixer(t2I, al_get_default_mixer());

	t3S = NULL;
	t3I = NULL;
	t3S = al_load_sample("music/Terran - 3.wav");
	t3I = al_create_sample_instance(t3S);
	al_set_sample_instance_gain(t3I, 0.7);
	al_attach_sample_instance_to_mixer(t3I, al_get_default_mixer());

	t4S = NULL;
	t4I = NULL;
	t4S = al_load_sample("music/Terran - 4.wav");
	t4I = al_create_sample_instance(t4S);
	al_set_sample_instance_gain(t4I, 0.7);
	al_attach_sample_instance_to_mixer(t4I, al_get_default_mixer());

	pointS = NULL;
	pointI = NULL;
	pointS = al_load_sample("music/fx/MouseOver.wav");
	pointI = al_create_sample_instance(pointS);
	al_attach_sample_instance_to_mixer(pointI, al_get_default_mixer());

	clickS = NULL;
	clickI = NULL;
	clickS = al_load_sample("music/fx/MouseDown.wav");
	clickI = al_create_sample_instance(clickS);
	al_attach_sample_instance_to_mixer(clickI, al_get_default_mixer());

	shootS = NULL;
	shootS = al_load_sample("music/fx/phohit00.wav");

	zergDieS = NULL;
	zergDieS = al_load_sample("music/fx/zavdth00.wav");
	terranDieS = NULL;
	terranDieS = al_load_sample("music/fx/explo1.wav");
	protossDieS = NULL;
	protossDieS = al_load_sample("music/fx/pscdth00.wav");
	playerDieS = NULL;
	playerDieS = al_load_sample("music/fx/pscdth00.wav");
	lifeS = NULL;
	lifeS = al_load_sample("music/fx/life.wav");
	dmgS = NULL;
	dmgS = al_load_sample("music/fx/dmg.wav");
	newUpS = NULL;
	newUpS = al_load_sample("music/fx/newUp.wav");


	mute = mConf.mute;
}

Sound::~Sound(){
	al_destroy_sample(menuMusicS);
	al_destroy_sample_instance(menuMusicI);
	al_destroy_sample(gotS);
	al_destroy_sample_instance(gotI);
	al_destroy_sample(t1S);
	al_destroy_sample_instance(t1I);
	al_destroy_sample(t2S);
	al_destroy_sample_instance(t2I);
	al_destroy_sample(t3S);
	al_destroy_sample_instance(t3I);
	al_destroy_sample(t4S);
	al_destroy_sample_instance(t4I);
	al_destroy_sample(pointS);
	al_destroy_sample_instance(pointI);
	al_destroy_sample(clickS);
	al_destroy_sample_instance(clickI);
	al_destroy_sample(shootS);
	al_destroy_sample(zergDieS);
	al_destroy_sample(terranDieS);
	al_destroy_sample(protossDieS);
	al_destroy_sample(lifeS);
	al_destroy_sample(dmgS);
	al_destroy_sample(newUpS);
}

void Sound::menu(){
	if(!mute){
	cout << "Muzyka start - menu" << endl;
	al_play_sample_instance(menuMusicI);
	}
}

void Sound::game(){
	if(!mute){
	switch(nrTrack){
	case 0:
		//al_play_sample_instance(gotI);                                //Czy ja chcê to dawaæ? :/
		nrTrack++;
		break;
	case 1:
		if(!al_get_sample_instance_playing(gotI)){
			al_play_sample_instance(t1I);
			nrTrack++;
		}
		break;
	case 2:
		if(!al_get_sample_instance_playing(t1I)){
			al_play_sample_instance(t2I);
			nrTrack++;
		}
		break;
	case 3:
		if(!al_get_sample_instance_playing(t2I)){
			al_play_sample_instance(t3I);
			nrTrack++;
		}
		break;
	case 4:
		if(!al_get_sample_instance_playing(t3I)){
			al_play_sample_instance(t4I);
			nrTrack++;
		}
		break;
	case 5:
		if(!al_get_sample_instance_playing(t4I)){
			// al_play_sample_instance(gotI);							 //Same here
			nrTrack = 1;
		}
		break;
	}
	}
}

void Sound::point(){
	if(!mute)
	al_play_sample_instance(pointI);
}
void Sound::click(){
	if(!mute)
	al_play_sample_instance(clickI);
}
void Sound::shoot(){
	if(!mute)
	al_play_sample(shootS, 0.5, 0, 1.2, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void Sound::zergDie(){
	if(!mute)
	al_play_sample(zergDieS, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void Sound::terranDie(){
	if(!mute)
	al_play_sample(terranDieS, 0.8, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void Sound::protossDie(){
	if(!mute)
	al_play_sample(protossDieS, 0.8, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void Sound::playerDie(){
	if(!mute)
	al_play_sample(playerDieS, 1.5, 0, 0.8, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void Sound::upgrade(int type){
	if(!mute){
	switch(type){
	case 1:
	al_play_sample(dmgS, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	break;
	case 2:
	al_play_sample(lifeS, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	break;
	}
	}
}
void Sound::newUpgrade(){
	if(!mute)
	al_play_sample(newUpS, 1.0, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	
}

void Sound::muteSound(Config &mConf){
	if(!mConf.mute){
		mConf.mute = true;
		mute = true;
		cout << "Dzwiek wyciszony" << endl;
		al_stop_sample_instance(menuMusicI);
		al_stop_sample_instance(gotI);
		al_stop_sample_instance(t1I);
		al_stop_sample_instance(t2I);
		al_stop_sample_instance(t3I);
		al_stop_sample_instance(t4I);


	} else {
		mConf.mute = false;
		mute = false;
		cout << "Dzwiek przywrocony" << endl;
	}
}