#ifndef SPELL_H
#define SPELL_H

#include "element.h"

class Mage;

class Spell{
	public:
		int cast_time, cool_time;
		string name;
		Stat stats[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		Stat mana[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		int power;
		TIER tier;	
		
		void printAttack();
		Stat checkStat(Element check);	
		Stat getMana(Element check);	
		Spell(int cat, int cot, string n,  Stat s[5], Stat m[5], int p, TIER ti);	
		Spell(){}	
		void performAttack(Mage& attacker, Mage& defender);
};

extern const Spell
	fire_missile, water_missile, air_missile, rock_missile, leaf_missile, null_spell,
	fire_jab,flare,fire_wave,fire_beam,water_jab,steam_missile,ice_missile,avalanche,thunderstorm,air_jab,tornado,storm_strike,hurricane,
	rock_jab,mud_missile,sand_swirl,magma_missile,leaf_jab,vine_strike,root_shank,fire_blast;
					
extern const Spell all_attacks[];

extern const int num_of_spells;
		
	

	
#endif
