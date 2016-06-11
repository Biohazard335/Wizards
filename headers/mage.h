#ifndef MAGE_H
#define MAGE_H

#include "spell.h"
#include "clothing.h"

class Mage{
	private:
		Element mage_element;
		int level=1;
		int baseHP=100;
		Stat baseAtk[5]={{fire,10},{water,10},{air,10},{earth,10},{life,10}};
		Stat baseDef[5]={{fire,10},{water,10},{air,10},{earth,10},{life,10}};
		Stat baseMana[5]={{fire,50},{water,50},{air,50},{earth,50},{life,50}};
		Spell spells[6] = {fire_missile,water_missile, air_missile, rock_missile, leaf_missile, null_spell};
		Clothing robe=basic_robe, hood=basic_hood, pendant=basic_pendant, boots=basic_boots;
		Clothing rings[8]={empty_ring,empty_ring,empty_ring,empty_ring,empty_ring,empty_ring,empty_ring,empty_ring};
		int exp=0;
		
	public:
		Stat atk[5]={{fire,10},{water,10},{air,10},{earth,10},{life,10}};
		Stat def[5]={{fire,10},{water,10},{air,10},{earth,10},{life,10}};
		Stat mana[5]={{fire,50},{water,50},{air,50},{earth,50},{life,50}};
		string name;
		int hp=100;
		int cast_time=0, cool_time=0;
		
		Spell getSpell(int index){return spells[index];}
		Element getElement(){return mage_element;}
		int getLevel(){return level;}
		
		void printAtks();
		void printDefs();
		void createRandomMage(int l);
		void prebattle();
		void createMage();
		void levelUp();
		void cpuLevelUp();
		int chooseAttack();
			
		Mage(string n, Element e, Stat a[5], Stat d[5]);
		Mage(string n, Element e, Stat a[5], Stat d[5], Spell s[6]);
		Mage(string n, Element e);
};
#endif
