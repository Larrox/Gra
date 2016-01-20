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
	bool pojawienie;
	int poczatkowey;
};
struct Pocisk{
	int x;
	int y;
	bool live;
	int predkosc;
	int dmg;
	bool dobry;
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
struct Dzialo{
	bool live;
	int x;
	int y;
	ALLEGRO_BITMAP *bitmap1;
	ALLEGRO_BITMAP *bitmap2;
	int hp;
	int hx;
	int hy;
};
struct Boss{
	int x;
	int y;
	bool live;
	int hp;
	Dzialo lewe;
	Dzialo prawe;
	Dzialo srodkowe;
	ALLEGRO_BITMAP *bitmap;
	int hx;
	int hy;
	int poczatkowey;
	bool pojawienie;
	int predkosc;
};