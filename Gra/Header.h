struct Statek{
	int x;
	int y;
	int predkosc;
	bool live;
	int hp;
	ALLEGRO_BITMAP *bitmap;
	//hitbox
	int hx;
	int hy;
};
struct Pocisk{
	int x;
	int y;
	bool live;
	int predkosc;
	int dmg;
};
