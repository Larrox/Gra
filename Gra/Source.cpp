#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include<allegro5\bitmap.h>
#include<allegro5\bitmap_draw.h>
#include<allegro5\allegro_image.h>


int main(void)
{
	int FPS = 60;
	int width = 640;
	int height = 480;
	bool redraw = true;
	bool done = false;
	bool moveup = false;
	bool movedown = false;
	bool moveleft = false;
	bool moveright = false;
	bool space = false;
	int pos_x = 300;
	int pos_y = 400;
	int pos_x2 = 200;
	int pos_y2 = 0;
	int bpos_x = 322;
	int bpos_y = 420;
	int bx[1000], by[1000];
	int licznik = 0;
	int spowalniacz = 0;
	for (int i = 0; i < 1000; i++){
		bx[i] = pos_x + 22;
		by[i] = pos_y + 20;

	}
	al_init_image_addon();

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *Statek = NULL;
	ALLEGRO_BITMAP *Statek2 = NULL;

	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL,
			"failed to initialize allegro!", NULL, NULL);
		return -1;
	}

	display = al_create_display(640, 480);

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
	Statek = al_load_bitmap("statek.png");
	Statek2 = al_load_bitmap("statek2.png");
	al_convert_mask_to_alpha(Statek, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(Statek2, al_map_rgb(255, 255, 255));



	while (!done)
	{
		al_draw_scaled_bitmap(Statek, 1, 1, 174, 178, pos_x, pos_y, 50, 60, 0);
		al_draw_scaled_bitmap(Statek2, 1, 1, 174, 178, pos_x2, pos_y2, 50, 60, 0);
		al_draw_scaled_bitmap(Statek2, 1, 1, 174, 178, pos_x2+100, pos_y2+80, 50, 60, 0);
		al_draw_scaled_bitmap(Statek2, 1, 1, 174, 178, pos_x2+200, pos_y2, 50, 60, 0);
		al_draw_scaled_bitmap(Statek2, 1, 1, 174, 178, pos_x2+70, pos_y2, 50, 60, 0);
		al_draw_scaled_bitmap(Statek2, 1, 1, 174, 178, pos_x2 + 130, pos_y2, 50, 60, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_start_timer(timer);
		spowalniacz++;
		if (pos_x2 <= 400 && pos_y2 == 0){
			pos_x2+=2;
		}
		if (pos_x2 == 400 && pos_y2 <=100){
			pos_y2+=2;
		}
		if (pos_x2 >= 0 && pos_y2 == 100){
			pos_x2-=2;
		}
		if (pos_x2 == 0 && pos_y2 >= 0){
			pos_y2-=2;
		}
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
		if (moveup == true && pos_y>200){
			pos_y -= 5;
		}
		if (movedown == true && pos_y<400){
			pos_y += 5;
		}
		if (moveright == true && pos_x<570){
			pos_x += 5;
		}
		if (moveleft == true && pos_x>40){
			pos_x -= 5;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
			done = true;
		}
		if (space == true && spowalniacz % 30 == 1){
			licznik++;
		}
		for (int i = 0; i < licznik; i++){
			by[i] -= 3;
			al_draw_filled_circle(bx[i], by[i], 5, al_map_rgb(255, 255, 255));
		}
	}
	
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(Statek);
	return 0;
}