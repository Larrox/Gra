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
	int upgradetype;
	int punkty;
};
struct Pocisk{
	int x;
	int y;
	bool live;
	int predkosc;
	int dmg;
};
struct Upgrade{
	int type;
	int x;
	int y;
	int predkosc;
	bool live;
};
struct Wybuch{
	bool live;
	int x;
	int y;
};