#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include<allegro5\bitmap.h>
#include<allegro5\bitmap_draw.h>
#include<allegro5\allegro_image.h>
#include"Header.h"

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
}
void RysujStatek(Statek &gracz){
	if (gracz.live){
		al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x, gracz.y, 50, 60, 0);
	}

}
void RysujArmia(Statek &gracz){
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x+100, gracz.y+80, 50, 60, 0);
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x+200, gracz.y, 50, 60, 0);
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x+70, gracz.y, 50, 60, 0);
	al_draw_scaled_bitmap(gracz.bitmap, 1, 1, 174, 178, gracz.x+130, gracz.y, 50, 60, 0);
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
	gracz.y = 0;
	gracz.predkosc = 2;
	gracz.bitmap = mapa;
	gracz.hp = 2;
	gracz.live = true;
	gracz.hx = 40;
	gracz.hy = 40;
	gracz.upgradetype = 0;
}
void DefiniujPocisk(Pocisk zwykly[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		zwykly[i].predkosc = 10;
		zwykly[i].dmg = 1;
		zwykly[i].live = false;
	}
}
void DefiniujPociskUp(Pocisk ulepszony[], int ilosc){
	for (int i = 0; i < ilosc; i++){
		ulepszony[i].predkosc = 10;
		ulepszony[i].dmg = 2;
		ulepszony[i].live = false;
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
void Trafienie(Pocisk zwykly[], int ilosc, Statek &wrog, Upgrade &up, int czas, Wybuch &wybuch){
	for (int i = 0; i < ilosc; i++){
		if (zwykly[i].live && wrog.live){
			if (
				zwykly[i].x >(wrog.x +22 - wrog.hx) &&
				zwykly[i].x <(wrog.x +22 + wrog.hx) &&
				zwykly[i].y >(wrog.y +20 - wrog.hy) &&
				zwykly[i].y <(wrog.y +20 + wrog.hy)){
					wrog.hp -= zwykly[i].dmg;
					zwykly[i].live = false;
					if (wrog.hp <= 0){
						wrog.live = false;
						up.live = true;
						up.x = wrog.x + 10;
						up.y = wrog.y + 10;
						up.type = (czas % 3) + 1;
						wybuch.live = true;
						wybuch.x = wrog.x + 10;
						wybuch.y = wrog.y + 10;
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
void Zbieranie(Statek &gracz, Upgrade &up, int czas){
	if (gracz.live && up.live){
		if (
			up.x >(gracz.x + 22 - gracz.hx) &&
			up.x <(gracz.x + 22 + gracz.hx) &&
			up.y >(gracz.y + 20 - gracz.hy) &&
			up.y <(gracz.y + 20 + gracz.hy)){
				gracz.upgradetype = up.type;
				up.live = false;
				czas = 0;
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
	const int num_pociski = 20;
	int czas = 0;
	const int maxFrame = 5;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 20;
	
	Statek gracz;
	Statek wrog;
	Pocisk zwykly[20];
	Pocisk ulepszony[20];
	Upgrade upgrade;
	Wybuch wybuch1;
	wybuch1.live = false;

	al_init_image_addon();

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *BM_Statek = NULL;
	ALLEGRO_BITMAP *BM_Wrog = NULL;
	ALLEGRO_BITMAP *BM_Tlo = NULL;
	ALLEGRO_BITMAP *BM_Exp[maxFrame];

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
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	BM_Statek = al_load_bitmap("statek.png");
	BM_Wrog = al_load_bitmap("statek2.png");
	BM_Exp[0] = al_load_bitmap("exp1.png");
	BM_Exp[1] = al_load_bitmap("exp2.png");
	BM_Exp[2] = al_load_bitmap("exp3.png");
	BM_Exp[3] = al_load_bitmap("exp4.png");
	BM_Exp[4] = al_load_bitmap("exp5.png");
	BM_Tlo = al_load_bitmap("tlo.png");
	for (int i = 0; i < maxFrame; i++){
		al_convert_mask_to_alpha(BM_Exp[i], al_map_rgb(255, 255, 255));
	}
	al_convert_mask_to_alpha(BM_Statek, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(BM_Wrog, al_map_rgb(255, 255, 255));
	DefiniujStatek(gracz, BM_Statek);
	DefiniujWrog(wrog, BM_Wrog);
	DefiniujPocisk(zwykly, num_pociski);
	DefiniujPociskUp(ulepszony, num_pociski);
	DefiniujUpgrade(upgrade);


	while (!done)
	{
		al_draw_bitmap(BM_Tlo, 0, 0, 0);
		RysujStatek(gracz);
		RysujStatek(wrog);
		//RysujArmia(wrog);
		RysujPocisk(zwykly, num_pociski);
		RysujPociskUp(ulepszony, num_pociski);
		RysujUpgrade(upgrade);
		if (wybuch1.live){
			al_draw_scaled_bitmap(BM_Exp[curFrame], 50, 50, 500, 500 , wybuch1.x, wybuch1.y, 200, 200 , 0);
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_start_timer(timer);
		spowalniacz++;
		spowalniacz = spowalniacz % 10000;
		czas++;
		czas = czas % 10000;
		Ruch1(wrog);
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
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
			done = true;
		}
		if (space == true && spowalniacz%30==1){
			if (gracz.upgradetype == 1){
				StrzelajPocisk(ulepszony, num_pociski, gracz);
			}
			else{
				StrzelajPocisk(zwykly, num_pociski, gracz);
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
		if (++frameCount >= frameDelay){
			if (++curFrame >= maxFrame){
				curFrame = 0;
			}
			frameCount = 0;
			if (curFrame == 4){
				wybuch1.live = false;
			}
		}
		Zbieranie(gracz, upgrade, czas);
		RuszajPocisk(zwykly, num_pociski);
		Trafienie(zwykly, num_pociski, wrog, upgrade, czas, wybuch1);
		RuszajPocisk(ulepszony, num_pociski);
		Trafienie(ulepszony, num_pociski, wrog, upgrade, czas, wybuch1);
		RuszajUpgrade(upgrade, height);
	}
	
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(BM_Statek);	
	al_destroy_bitmap(BM_Wrog);
	for (int i = 0; i < maxFrame; i++){
		al_destroy_bitmap(BM_Exp[i]);
	}
	return 0;
}