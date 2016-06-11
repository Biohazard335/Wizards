#ifndef CLOTHING_H
#define CLOTHING_H
#include <string>

enum CLOTHING{
	ROBE,
	HOOD,
	PENDANT,
	BOOTS,
	RING
};


class Clothing/*: public Item*/{
	public:
		string name;
		TIER tier=BASE;
		CLOTHING type;
		Stat atk[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		Stat def[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		Stat mana[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		int hp=0;
		
	void create(Clothing base);
		
	Clothing(string n, CLOTHING ty, Stat a[5], Stat d[5], Stat m[5], int h,TIER t);
};

extern const Clothing
		basic_robe,
		basic_hood,
		basic_pendant,
		basic_boots,
		empty_ring ;
		
#endif
