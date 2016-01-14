#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include<allegro5\bitmap.h>
#include<allegro5\bitmap_draw.h>
#include<allegro5\allegro_image.h>
#include"Header.h"
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_font.h>
#include<stdio.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>

void DefiniujStatek(Statek &gracz, ALLEGRO_BITMAP *mapa){
	gracz.x = 300;
	gracz.y = 750;
	gracz.predkosc = 5;
	gracz.hp = 5;
	gracz.bitmap = mapa;
	gracz.live = true;
	gracz.hx = 40;
	gracz.hy = 40;
	gracz.upgradetype = 0;
	gracz.punkty = 0;
}
void RysujStatek(Statek &gracz){
	if (gracz.live){
		al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x, gracz.y, 50, 60, 0);
	}

}
void RysujArmia(Statek &gracz){
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x + 100, gracz.y + 80, 50, 60, 0);
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x + 200, gracz.y, 50, 60, 0);
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x + 70, gracz.y, 50, 60, 0);
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x + 130, gracz.y, 50, 60, 0);
}
void Ruch1(Statek &gracz){
	if (gracz.x <= 400 && gracz.y == 0){
		gracz.x += gracz.predkosc;
	}
	if (gracz.x == 400 && gracz.y <= 100){
		gracz.y += gracz.predkosc;
	}
	if (gracz.x >= 0 && gracz.y == 100){
		gracz.x -= gracz.predkosc;
	}
	if (gracz.x == 0 && gracz.y >= 0){
		gracz.y -= gracz.predkosc;
	}
}
void DefiniujWrog(Statek &gracz, ALLEGRO_BITMAP *mapa){
	gracz.x = 200;
	gracz.y = 100;
	gracz.predkosc = 2;
	gracz.bitmap = mapa;
	gracz.hp = 2;
	gracz.pojawienie = false;
	gracz.live = true;
	gracz.hx = 40;
	gracz.hy = 40;
	gracz.upgradetype = 0;
}
void DefiniujBoss(Boss &boss, ALLEGRO_BITMAP *bmboss, ALLEGRO_BITMAP *dzialo1, ALLEGRO_BITMAP *dzialo2){
	boss.x = 0;
	boss.y = 0;
	boss.bitmap = bmboss;
	boss.hp = 20;
	boss.hx = 40;
	boss.hy = 40;
	boss.live = false;

	boss.lewe.bitmap1 = dzialo1;
	boss.lewe.bitmap2 = dzialo2;
	boss.lewe.hp = 5;
	boss.lewe.hx = 40;
	boss.lewe.hy = 40;
	boss.lewe.live = false;
	boss.lewe.x = 110;
	boss.lewe.y = 110;

	boss.prawe.bitmap1 = dzialo1;
	boss.prawe.bitmap2 = dzialo2;
	boss.prawe.hp = 5;
	boss.prawe.hx = 40;
	boss.prawe.hy = 40;
	boss.prawe.live = false;
	boss.prawe.x = 430;
	boss.prawe.y = 105;

	boss.srodkowe.bitmap1 = dzialo1;
	boss.srodkowe.bitmap2 = dzialo2;
	boss.srodkowe.hp = 5;
	boss.srodkowe.hx = 40;
	boss.srodkowe.hy = 40;
	boss.srodkowe.live = false;
	boss.srodkowe.x = 260;
	boss.srodkowe.y = 221;
}
void RysujBoss(Boss &boss){
	if (boss.live){
		al_draw_bitmap(boss.bitmap, boss.x, boss.y, 0);
		if (boss.lewe.live){
			al_draw_bitmap(boss.lewe.bitmap1, boss.lewe.x, boss.lewe.y, 0);
		}
		if (!boss.lewe.live){
			al_draw_bitmap(boss.lewe.bitmap2, boss.lewe.x, boss.lewe.y, 0);
		}
		if (boss.prawe.live){
			al_draw_bitmap(boss.prawe.bitmap1, boss.prawe.x, boss.prawe.y, 0);
		}
		if (!boss.prawe.live){
			al_draw_bitmap(boss.prawe.bitmap2, boss.prawe.x, boss.prawe.y, 0);
		}
		if (boss.srodkowe.live){
			al_draw_bitmap(boss.srodkowe.bitmap1, boss.srodkowe.x, boss.srodkowe.y, 0);
		}
		if (!boss.srodkowe.live){
			al_draw_bitmap(boss.srodkowe.bitmap2, boss.srodkowe.x, boss.srodkowe.y, 0);
		}
	}

}
void DefiniujPocisk(Pocisk zwykly[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		zwykly[i].predkosc = 10;
		zwykly[i].dmg = 1;
		zwykly[i].live = false;
		zwykly[i].dobry = true;
	}
}
void DefiniujPociskUp(Pocisk ulepszony[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		ulepszony[i].predkosc = 10;
		ulepszony[i].dmg = 2;
		ulepszony[i].live = false;
		ulepszony[i].dobry = true;
	}
}
void DefiniujPociskWroga(Pocisk zwykly[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		zwykly[i].predkosc = 10;
		zwykly[i].dmg = 1;
		zwykly[i].live = false;
		zwykly[i].dobry = false;
	}
}
void RysujPocisk(Pocisk zwykly[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live){
			al_draw_filled_circle(zwykly[i].x, zwykly[i].y, 5, al_map_rgb(255, 255, 255));
		}
	}
}
void RysujPociskUp(Pocisk ulepszony[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		if (ulepszony[i].live){
			al_draw_filled_circle(ulepszony[i].x, ulepszony[i].y, 7, al_map_rgb(255, 255, 0));
		}
	}
}
void RysujPociskWroga(Pocisk zwykly[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live){
			al_draw_filled_circle(zwykly[i].x, zwykly[i].y, 5, al_map_rgb(255, 0, 100));
		}
	}
}
void StrzelajPocisk(Pocisk zwykly[], int ilosc, Statek &gracz){
	for (int i = 0; i < ilosc; i++){
		if (!zwykly[i].live && gracz.live){
			zwykly[i].x = gracz.x + 22;
			zwykly[i].y = gracz.y + 20;
			zwykly[i].live = true;
			break;
		}
	}
}
void StrzelajPociskBossa(Pocisk zwykly[], int ilosc, Dzialo &lewe){
	for (int i = 0; i < ilosc; i++){
		if (!zwykly[i].live && lewe.live){
			zwykly[i].x = lewe.x + 22;
			zwykly[i].y = lewe.y + 20;
			zwykly[i].live = true;
			break;
		}
	}
}
void RuszajPocisk(Pocisk zwykly[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live){
			zwykly[i].y -= zwykly[i].predkosc;
			if (zwykly[i].y < 0){
				zwykly[i].live = false;
			}
		}
	}
}
void RuszajPociskWroga(Pocisk zwykly[], int ilosc, int height){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live){
			zwykly[i].y += zwykly[i].predkosc;
			if (zwykly[i].y > height){
				zwykly[i].live = false;
			}
		}
	}
}
void Trafienie(Pocisk zwykly[], int ilosc, Statek &wrog, Upgrade &up, int czas, Wybuch &wybuch, Statek &gracz, ALLEGRO_SAMPLE *boom, ALLEGRO_SAMPLE *collision){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live && wrog.live){
			if (
				zwykly[i].dobry == true &&
				zwykly[i].x >(wrog.x + 22 - wrog.hx) &&
				zwykly[i].x <(wrog.x + 22 + wrog.hx) &&
				zwykly[i].y >(wrog.y + 20 - wrog.hy) &&
				zwykly[i].y <(wrog.y + 20 + wrog.hy)){
				al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				wrog.hp -= zwykly[i].dmg;
				zwykly[i].live = false;
				gracz.punkty += 10;
				if (wrog.hp <= 0){
					wrog.live = false;
					up.live = true;
					up.x = wrog.x + 10;
					up.y = wrog.y + 10;
					up.type = (czas % 3) + 1;
					wybuch.live = true;
					al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					wybuch.x = wrog.x + 10;
					wybuch.y = wrog.y + 10;
					gracz.punkty += 100;
				}

			}
		}
	}
}
void Trafieniegracza(Pocisk zwykly[], int ilosc, Statek &wrog, Wybuch &wybuch, ALLEGRO_SAMPLE *boom, ALLEGRO_SAMPLE *collision){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live && wrog.live){
			if (
				zwykly[i].dobry == false &&
				zwykly[i].x >(wrog.x + 22 - wrog.hx) &&
				zwykly[i].x <(wrog.x + 22 + wrog.hx) &&
				zwykly[i].y >(wrog.y + 20 - wrog.hy) &&
				zwykly[i].y <(wrog.y + 20 + wrog.hy)){
				al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				wrog.hp -= zwykly[i].dmg;
				zwykly[i].live = false;
				if (wrog.hp <= 0){
					wrog.live = false;
					wybuch.live = true;
					al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					wybuch.x = wrog.x + 10;
					wybuch.y = wrog.y + 10;
				}

			}
		}
	}
}
void TrafienieDziala(Pocisk zwykly[], int ilosc, Dzialo &lewe, Upgrade &up, int czas, Wybuch &wybuch, Statek &gracz, ALLEGRO_SAMPLE *boom, ALLEGRO_SAMPLE *collision){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live && lewe.live){
			if (
				zwykly[i].dobry == true &&
				zwykly[i].x >(lewe.x + 22 - lewe.hx) &&
				zwykly[i].x <(lewe.x + 22 + lewe.hx) &&
				zwykly[i].y >(lewe.y + 20 - lewe.hy) &&
				zwykly[i].y <(lewe.y + 20 + lewe.hy)){
				al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				lewe.hp -= zwykly[i].dmg;
				zwykly[i].live = false;
				gracz.punkty += 10;
				if (lewe.hp <= 0){
					lewe.live = false;
					up.live = true;
					up.x = lewe.x + 10;
					up.y = lewe.y + 10;
					up.type = (czas % 3) + 1;
					wybuch.live = true;
					al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					wybuch.x = lewe.x + 10;
					wybuch.y = lewe.y + 10;
					gracz.punkty += 100;
				}

			}
		}
	}
}
void TrafienieBossa(Pocisk zwykly[], int ilosc, Boss &boss, Upgrade &up, int czas, Wybuch &wybuch, Statek &gracz, ALLEGRO_SAMPLE *boom, ALLEGRO_SAMPLE *collision){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live && boss.live && !boss.lewe.live && !boss.prawe.live && !boss.srodkowe.live){
			if (
				zwykly[i].dobry == true &&
				zwykly[i].x >(290 - boss.hx) &&
				zwykly[i].x <(290 + boss.hx) &&
				zwykly[i].y >(180 - boss.hy) &&
				zwykly[i].y <(180 + boss.hy)){
				al_play_sample(collision, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				boss.hp -= zwykly[i].dmg;
				zwykly[i].live = false;
				gracz.punkty += 10;
				if (boss.hp <= 0){
					boss.live = false;
					up.live = true;
					up.x = 270;
					up.y = 210;
					up.type = (czas % 3) + 1;
					wybuch.live = true;
					al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					wybuch.x = 270;
					wybuch.y = 210;
					gracz.punkty += 100000;
				}

			}
		}
	}
}
void DefiniujUpgrade(Upgrade &up){
	up.live = false;
	up.predkosc = 3;
}
void RysujUpgrade(Upgrade up){
	if (up.live){
		switch (up.type){
		case 1:
			al_draw_filled_ellipse(up.x, up.y, 20, 30, al_map_rgb(255, 255, 0));
			break;
		case 2:
			al_draw_filled_ellipse(up.x, up.y, 20, 30, al_map_rgb(255, 0, 0));
			break;
		case 3:
			al_draw_filled_ellipse(up.x, up.y, 20, 30, al_map_rgb(0, 255, 0));
			break;
		}
	}
}
void RuszajUpgrade(Upgrade &up, int height){
	if (up.live){
		up.y += up.predkosc;
		if (up.y >= height){
			up.live = false;
		}
	}
}
void Zbieranie(Statek &gracz, Upgrade &up, int &czas, ALLEGRO_SAMPLE *take){
	if (gracz.live && up.live){
		if (
			up.x >(gracz.x + 22 - gracz.hx) &&
			up.x <(gracz.x + 22 + gracz.hx) &&
			up.y >(gracz.y + 20 - gracz.hy) &&
			up.y <(gracz.y + 20 + gracz.hy)){
			gracz.upgradetype = up.type;
			up.live = false;
			al_play_sample(take, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			gracz.punkty += 100;
			czas = 0;
		}
	}
}
void Pojawienie(Statek &wrog, int y){
	if (wrog.pojawienie){
		al_draw_scaled_bitmap(wrog.bitmap, 1, 1, 174, 178, wrog.x, y, 50, 60, 0);
		if (y < wrog.y){
			y += wrog.predkosc;
		}
		if (y >= wrog.y){
			wrog.pojawienie = false;
			wrog.live = true;
			al_draw_filled_ellipse(300, 400, 20, 30, al_map_rgb(0, 255, 0));
		}
	}
}
int main(void)
{
	int FPS = 60;
	int width = 640;
	int height = 880;
	bool redraw = true;
	bool done = false;
	bool moveup = false;
	bool movedown = false;
	bool moveleft = false;
	bool moveright = false;
	bool space = false;
	int pos_x2 = 200;
	int pos_y2 = 0;
	int spowalniacz = 0;
	const int num_pociski = 20, num_pociski2 = 30;
	int czas = 0;
	const int maxFrame = 5;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 20;
	bool menu = true, game = false, menu2 = false, gameover = false, endgame = false;
	int menuy = 390;
	int y = 0;
	int strzelanie = 0;


	Statek gracz;
	Statek wrog;
	Pocisk zwykly[20];
	Pocisk ulepszony[20];
	Pocisk wrogi[20];
	Upgrade upgrade;
	Wybuch wybuch1;
	Boss boss;
	wybuch1.live = false;

	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *BM_Statek = NULL;
	ALLEGRO_BITMAP *BM_Wrog = NULL;
	ALLEGRO_BITMAP *BM_Tlo = NULL;
	ALLEGRO_BITMAP *BM_Exp[maxFrame];
	ALLEGRO_BITMAP *BM_Boss = NULL;
	ALLEGRO_BITMAP *BM_Dzialo1 = NULL;
	ALLEGRO_BITMAP *BM_Dzialo2 = NULL;
	ALLEGRO_BITMAP *BM_Dopalacz = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *title = NULL;
	ALLEGRO_SAMPLE *Shoot = NULL;
	ALLEGRO_SAMPLE *Explode = NULL;
	ALLEGRO_SAMPLE *Final = NULL;
	ALLEGRO_SAMPLE *Take = NULL;
	ALLEGRO_SAMPLE *Accept = NULL;
	ALLEGRO_SAMPLE *Over = NULL;
	ALLEGRO_SAMPLE *Bye = NULL;
	ALLEGRO_SAMPLE *Esc = NULL;
	ALLEGRO_SAMPLE *Collision = NULL;
	al_reserve_samples(3);

	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize allegro!", NULL, NULL);
		return -1;
	}

	display = al_create_display(width, height);

	if (!display)
	{
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize display!", NULL, NULL);
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		//fprintf("failed to create timer!\n");
		return -1;
	}

	al_init_primitives_addon();
	al_install_keyboard();


	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_flip_display();
	BM_Statek = al_load_bitmap("statek.png");
	BM_Wrog = al_load_bitmap("statek2.png");
	BM_Exp[0] = al_load_bitmap("exp1.png");
	BM_Exp[1] = al_load_bitmap("exp2.png");
	BM_Exp[2] = al_load_bitmap("exp3.png");
	BM_Exp[3] = al_load_bitmap("exp4.png");
	BM_Exp[4] = al_load_bitmap("exp5.png");
	BM_Tlo = al_load_bitmap("tlo.png");
	BM_Boss = al_load_bitmap("gzibon.png");
	BM_Dzialo1 = al_load_bitmap("dzialo1.png");
	BM_Dzialo2 = al_load_bitmap("dzialo2.png");
	BM_Dopalacz = al_load_bitmap("dopalacz.png");
	Shoot = al_load_sample("shoot.wav");
	Explode = al_load_sample("wybuch.wav");
	Final = al_load_sample("final.wav");
	Take = al_load_sample("upgrade.wav");
	Accept = al_load_sample("accept.wav");
	Over = al_load_sample("gameover.wav");
	Bye = al_load_sample("bye.wav");
	Esc = al_load_sample("esc.wav");
	Collision = al_load_sample("collision.wav");

	for (int i = 0; i < maxFrame; i++){
		al_convert_mask_to_alpha(BM_Exp[i], al_map_rgb(255, 255, 255));
	}
	al_convert_mask_to_alpha(BM_Statek, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BM_Wrog, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BM_Boss, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BM_Dzialo1, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BM_Dzialo2, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BM_Dopalacz, al_map_rgb(255, 255, 255));
	DefiniujStatek(gracz, BM_Statek);
	DefiniujWrog(wrog, BM_Wrog);
	DefiniujPocisk(zwykly, num_pociski);
	DefiniujPociskUp(ulepszony, num_pociski);
	DefiniujPociskWroga(wrogi, num_pociski2);
	DefiniujUpgrade(upgrade);
	DefiniujBoss(boss, BM_Boss, BM_Dzialo1, BM_Dzialo2);
	printf("Lewe:%i\t%i\n", boss.lewe.x, boss.lewe.y);
	font = al_load_font("ALGER.ttf", 36, NULL);
	title = al_load_font("ALGER.ttf", 56, NULL);
	al_start_timer(timer);


	while (!done)
	{
		if (menu){
			al_flip_display();
			al_draw_bitmap(BM_Tlo, 0, 0, 0);
			al_draw_textf(title, al_map_rgb(255, 255, 255), width / 2, 50, ALLEGRO_ALIGN_CENTRE, "The Adventures of PapJack");
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 400, ALLEGRO_ALIGN_CENTRE, "New game");
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 500, ALLEGRO_ALIGN_CENTRE, "Exit game");
			al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, width / 2 + 110, menuy, 50, 60, 0);
			al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, width / 2 - 140, menuy, 50, 60, 0);
			al_stop_timer(timer);
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
				if (menuy == 390){
					menuy = 490;
				}
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_UP){
				if (menuy == 490){
					menuy = 390;
				}
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
				if (menuy == 390){
					al_play_sample(Accept, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					game = true;
					menu = false;
				}
				if (menuy == 490){
					al_play_sample(Bye, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					al_rest(1);
					done = true;
				}
			}
		}
		if (gameover){
			al_stop_timer(timer);
			al_play_sample(Over, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			al_draw_bitmap(BM_Tlo, 0, 0, 0);
			al_draw_textf(title, al_map_rgb(255, 255, 255), width / 2, 400, ALLEGRO_ALIGN_CENTRE, "Game Over");
			al_flip_display();
			al_rest(4);
			done = true;
		}
		if (game){
			al_draw_bitmap(BM_Tlo, 0, 0, 0);
			RysujStatek(gracz);
			RysujStatek(wrog);
			RysujBoss(boss);
			//RysujArmia(wrog);
			RysujPocisk(zwykly, num_pociski);
			RysujPociskUp(ulepszony, num_pociski);
			RysujPociskWroga(wrogi, num_pociski2);
			RysujUpgrade(upgrade);
			if (wybuch1.live){
				al_draw_scaled_bitmap(BM_Exp[curFrame], 50, 50, 500, 500, wybuch1.x, wybuch1.y, 200, 200, 0);
			}
			al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 0, 0, "Punkty: %i", gracz.punkty);
			//al_flip_display();
			//al_clear_to_color(al_map_rgb(0, 0, 0));
			al_start_timer(timer);
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			spowalniacz++;
			spowalniacz = spowalniacz % 10000;
			czas++;
			czas = czas % 10000;
			strzelanie++;
			strzelanie = strzelanie % 10000;
			frameCount++;
			frameCount = frameCount % 10000;
			//Pojawienie(wrog, y);
			Ruch1(wrog);
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;
				//al_clear_to_color(al_map_rgb(0, 0, 0));
				al_flip_display();
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
				switch (ev.keyboard.keycode)
				{

				case ALLEGRO_KEY_RIGHT: moveright = true; break;

				case ALLEGRO_KEY_LEFT: moveleft = true; break;

				case ALLEGRO_KEY_UP:  moveup = true; break;

				case ALLEGRO_KEY_DOWN: movedown = true; break;

				case ALLEGRO_KEY_SPACE: space = true; break;

				}
			}
			if (ev.type == ALLEGRO_EVENT_KEY_UP){
				switch (ev.keyboard.keycode)
				{

				case ALLEGRO_KEY_RIGHT: moveright = false; break;

				case ALLEGRO_KEY_LEFT: moveleft = false; break;

				case ALLEGRO_KEY_UP:  moveup = false; break;

				case ALLEGRO_KEY_DOWN: movedown = false; break;

				case ALLEGRO_KEY_SPACE: space = false; break;

				}
			}
			if (moveup == true && gracz.y>500){
				gracz.y -= gracz.predkosc;
				al_draw_bitmap(BM_Dopalacz, gracz.x + 5, gracz.y + 50, 0);
			}
			if (movedown == true && gracz.y<800){
				gracz.y += gracz.predkosc;
			}
			if (moveright == true && gracz.x<570){
				gracz.x += gracz.predkosc;
			}
			if (moveleft == true && gracz.x>30){
				gracz.x -= gracz.predkosc;
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				al_play_sample(Esc, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				menu2 = true;
				game = false;
			}
			if (space == true && spowalniacz % 30 == 1){
				if (gracz.upgradetype == 1){
					StrzelajPocisk(ulepszony, num_pociski, gracz);
					al_play_sample(Shoot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
				else{
					StrzelajPocisk(zwykly, num_pociski, gracz);
					al_play_sample(Shoot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
			if (gracz.upgradetype == 2){
				gracz.predkosc = 30;
			}
			else{
				gracz.predkosc = 5;
			}
			if (gracz.upgradetype == 3){
				gracz.hp = 5;
				gracz.upgradetype = 0;
			}
			if (czas >= 1000){
				gracz.upgradetype = 0;

			}
			if (frameCount >= frameDelay){
				if (++curFrame >= maxFrame){
					curFrame = 0;
				}
				frameCount = 0;
				if (curFrame == 4){
					wybuch1.live = false;
				}
			}
			Zbieranie(gracz, upgrade, czas, Take);
			RuszajPocisk(zwykly, num_pociski);
			Trafienie(zwykly, num_pociski, wrog, upgrade, czas, wybuch1, gracz, Explode, Collision);
			RuszajPocisk(ulepszony, num_pociski);
			Trafienie(ulepszony, num_pociski, wrog, upgrade, czas, wybuch1, gracz, Explode, Collision);
			RuszajUpgrade(upgrade, height);
			TrafienieDziala(zwykly, num_pociski, boss.lewe, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieDziala(ulepszony, num_pociski, boss.lewe, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieDziala(zwykly, num_pociski, boss.prawe, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieDziala(ulepszony, num_pociski, boss.prawe, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieDziala(zwykly, num_pociski, boss.srodkowe, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieDziala(ulepszony, num_pociski, boss.srodkowe, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieBossa(zwykly, num_pociski, boss, upgrade, czas, wybuch1, gracz, Explode, Collision);
			TrafienieBossa(ulepszony, num_pociski, boss, upgrade, czas, wybuch1, gracz, Explode, Collision);
			if (strzelanie % 80 == 1){
				StrzelajPocisk(wrogi, num_pociski2, wrog);
				StrzelajPociskBossa(wrogi, num_pociski2, boss.lewe);
				StrzelajPociskBossa(wrogi, num_pociski2, boss.prawe);
				StrzelajPociskBossa(wrogi, num_pociski2, boss.srodkowe);
			}
			RuszajPociskWroga(wrogi, num_pociski2, height);
			Trafieniegracza(wrogi, num_pociski2, gracz, wybuch1, Explode, Collision);
			if (gracz.hp <= 0 && !wybuch1.live){
				game = false;
				gameover = true;
			}
			if (gracz.punkty == 220){
				boss.live = true;
				boss.srodkowe.live = true;
				boss.lewe.live = true;
				boss.prawe.live = true;
			}
			if (gracz.punkty >= 10000 && !upgrade.live){
				game = false;
				endgame = true;
			}
			al_flip_display();
		}
		if (menu2){
			al_stop_timer(timer);
			al_draw_bitmap(BM_Tlo, 0, 0, 0);
			al_draw_textf(title, al_map_rgb(255, 255, 255), width / 2, 50, ALLEGRO_ALIGN_CENTRE, "The Adventures of PapJack");
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 400, ALLEGRO_ALIGN_CENTRE, "Resume game");
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 500, ALLEGRO_ALIGN_CENTRE, "Exit game");
			al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, width / 2 + 110, menuy, 50, 60, 0);
			al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, width / 2 - 140, menuy, 50, 60, 0);
			al_flip_display();
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
				if (menuy == 390){
					menuy = 490;
				}
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_UP){
				if (menuy == 490){
					menuy = 390;
				}
			}
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
				if (menuy == 390){
					al_play_sample(Accept, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					game = true;
					menu2 = false;
				}
				if (menuy == 490){
					al_play_sample(Bye, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					al_rest(1);
					done = true;
				}
			}
		}
		if (endgame){
			al_play_sample(Final, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			al_draw_bitmap(BM_Tlo, 0, 0, 0);
			al_draw_textf(title, al_map_rgb(255, 255, 255), width / 2, 100, ALLEGRO_ALIGN_CENTRE, "You have slain Mr Gzibon!!!");
			al_flip_display();
			al_rest(3);
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 250, ALLEGRO_ALIGN_CENTRE, "Galactic is save now ;))");
			al_flip_display();
			al_rest(2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 350, ALLEGRO_ALIGN_CENTRE, "Thanks for playing");
			al_flip_display();
			al_rest(2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 450, ALLEGRO_ALIGN_CENTRE, "Please support");
			al_flip_display();
			al_rest(2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), width / 2, 550, ALLEGRO_ALIGN_CENTRE, "Bye");
			al_flip_display();
			al_play_sample(Bye, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			al_rest(1);
			done = true;
		}
	}
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(BM_Statek);
	al_destroy_bitmap(BM_Wrog);
	al_destroy_bitmap(BM_Boss);
	al_destroy_bitmap(BM_Dzialo1);
	al_destroy_bitmap(BM_Dzialo2);
	al_destroy_bitmap(BM_Dopalacz);
	al_destroy_sample(Shoot);
	al_destroy_sample(Explode);
	al_destroy_sample(Final);
	al_destroy_sample(Take);
	al_destroy_sample(Accept);
	al_destroy_sample(Over);
	al_destroy_sample(Bye);
	al_destroy_sample(Esc);
	al_destroy_sample(Collision);
	for (int i = 0; i < maxFrame; i++){
		al_destroy_bitmap(BM_Exp[i]);
	}
	al_destroy_font(font);
	al_destroy_font(title);
	return 0;
}