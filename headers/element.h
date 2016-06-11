#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
using namespace std;

enum TIER{
	BASE,
	TIER_1,
	TIER_2,
	TIER_3,
	TIER_4,
	ULT
};


enum ELEM{
	FIRE,
	WATER,
	AIR,
	EARTH,
	LIFE,
	NONE
};


enum RELATION{
	WEAK = -1,
	EQUAL,
	POWERFUL,
	NoNE
};


struct Element{
	string name;
	ELEM elem;
	ELEM win[1],
		lose[1];
};

const Element 
	fire={"Fire",FIRE,
			{LIFE},
			{WATER}
		},
	life={"Life",LIFE,
			{EARTH},
			{FIRE}
		},
	earth={"Earth",EARTH,
			{AIR},
			{LIFE}
		},
	air={"Air",AIR,
			{WATER},
			{EARTH}
		},
	water={"Water",WATER,
			{FIRE},
			{AIR}
		},
	none={"",NONE,
			{},
			{}
		};
		
struct Stat{
	Element element;
	int level;
};

		
RELATION elementRelation(Element element1, Element element2);
		
#endif
