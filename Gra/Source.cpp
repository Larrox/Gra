#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include<allegro5\bitmap.h>
#include<allegro5\bitmap_draw.h>
#include<allegro5\allegro_image.h>


int main(void)
{
	int FPS = 20;
	int width = 640;
	int height = 480;
	bool redraw = true;
	int licznik = 0;
	bool done = false;
	int pos_x = 300;
	int pos_y = 400;
	int bpos_x = 322;
	int bpos_y = 420;
	al_init_image_addon();

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *Statek = NULL;

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
	al_convert_mask_to_alpha(Statek, al_map_rgb(255, 255, 255));



	while (!done)
	{
		al_draw_filled_circle(bpos_x, bpos_y, 5, al_map_rgb(255, 255, 255));
		al_draw_scaled_bitmap(Statek, 1, 1, 174, 178, pos_x, pos_y, 50, 60, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			bpos_y -= 10;
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
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_UP){
			pos_y = pos_y - 10;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
			pos_y = pos_y + 10;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_LEFT){
			pos_x = pos_x - 10;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_RIGHT){
			pos_x = pos_x + 10;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
			done = true;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
			bpos_y = pos_y + 20;
			bpos_x = pos_x + 22;
			al_flip_display();
			al_start_timer(timer);
		}
	}

	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_bitmap(Statek);
	return 0;
}