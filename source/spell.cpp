#include <iostream>

#include "mage.h"
#include "spell.h"

using namespace std;
	
void Spell::printAttack(){
	cout<<name;
	for(int i=name.size();i<=15;i++){
		cout<<" ";
	}
	cout<<"(C:"<<cast_time<<"s";
	if(cool_time!=0){
		cout<<", R:"<<cool_time<<"s";
	}
	cout<<")\t{";
		for(int index=0; index<5;index++){
			if(mana[index].level!=0){
				cout<<stats[index].element.name[0]<<":"<<mana[index].level<<" ";
			}
		}
	cout<<"}";
}

Stat Spell::checkStat(Element check){
	for(int i=0;i<5;i++){
		if(check.elem == stats[i].element.elem){
			return stats[i];
		}
	}
}

Stat Spell::getMana(Element check){
	for(int i=0;i<5;i++){
		if(check.elem == stats[i].element.elem){
			return mana[i];
		}
	}
}
	
Spell::Spell(int cat, int cot, string n,  Stat s[5], Stat m[5], int p, TIER ti){
	cast_time=cat;
	cool_time=cot;
	name=n;
	for(int i=0; i<5;i++){
		stats[i].level=s[i].level;
		mana[i].level=m[i].level;
	}
	power=p;
	tier =ti;
}

void Spell::performAttack(Mage& attacker, Mage& defender){
	int damage = 0;
	int elemdamage=0;
	int r=0;
	double multiplier=1.0;
	for(int index = 0; index<5;index++){
		elemdamage = static_cast<int>(power * (stats[index].level/100.00) * (attacker.atk[index].level*1.0) / (defender.def[index].level*1.0));
		r=rand()%((elemdamage/10)+1);	
		if(elemdamage!=0){
			cout<<endl<<stats[index].element.name[0]<<":"<<power<<"b *"<<(stats[index].level/100.00)<<"% *"<<(attacker.atk[index].level*1.0)
			<<"a /"<<(defender.def[index].level*1.0)<<"d";					
		switch(elementRelation(stats[index].element, defender.getElement())){
			case WEAK: multiplier= multiplier *.84;
			cout<<" weak";
			break;
			case POWERFUL: multiplier= multiplier *1.2;
			cout<<" powerful";
			break;
		}
		switch(elementRelation(stats[index].element, attacker.getElement())){
			case EQUAL: multiplier= multiplier *1.5;
			cout<<" stab";
			break;
		}
		cout<<" +"<<r<<"r = "<<elemdamage+r;
		}				
		damage += elemdamage+r;					
	}
	cout<<"\n"<<damage<<" * "<<multiplier;
	defender.hp-=static_cast<int>(damage*multiplier);
	cout<<"\n"<<attacker.name<<" used "<<name<<" for "<<static_cast<int>(damage*multiplier)<<" damage!\n\n";
 }

const Spell 
	fire_missile 	(5,0,"fire missile", 	new Stat[5]	{{fire,100},	{water,0},		{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,5},		{water,0},		{air,0},		{earth,0},		{life,0}},
											12,BASE),
	fire_jab	 	(1,1,"fire jab", 		new Stat[5]	{{fire,100},	{water,0},		{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,5  },	{water,0},		{air,0},		{earth,0},		{life,0}},
											5,TIER_1),
	fire_beam 		(2,0,"fire beam", 		new Stat[5]	{{fire,60},		{water,0},		{air,40},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,4},		{water,0},		{air,3},		{earth,0},		{life,0}},
											15,TIER_1),
	flare		 	(1,5,"flare", 			new Stat[5]	{{fire,100},	{water,0},		{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,15},		{water,0},		{air,0},		{earth,0},		{life,0}},
											25,TIER_2),
	fire_wave 		(7,0,"fire wave", 		new Stat[5]	{{fire,70},		{water,0},		{air,30},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,7},		{water,0},		{air,3},		{earth,0},		{life,0}},
											20,TIER_2),
	fire_blast 		(3,0,"fire blast", 		new Stat[5]	{{fire,100},	{water,0},		{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,50},		{water,0},		{air,0},		{earth,0},		{life,0}},
											100,ULT),
	water_missile	(5,0,"water missile", 	new Stat[5]	{{fire,0},		{water,100},	{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,5},		{air,0},		{earth,0},		{life,0}},
											10,BASE),
	water_jab		(1,1,"water jab", 		new Stat[5]	{{fire,0},		{water,100},	{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,5},		{air,0},		{earth,0},		{life,0}},
											5,TIER_1),
	steam_missile 	(5,0,"steam missile", 	new Stat[5]	{{fire,50},		{water,50},		{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,3},		{water,3},		{air,0},		{earth,0},		{life,0}},
											10,TIER_1),
	ice_missile 	(5,0,"ice missile", 	new Stat[5]	{{fire,0},		{water,50},		{air,50},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,3},		{air,3},		{earth,0},		{life,0}},
											10,TIER_1),
	thunderstorm	(6,0,"thunderstorm",  	new Stat[5]	{{fire,20},		{water,40},		{air,40},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,5},		{water,10},		{air,10},		{earth,0},		{life,0}},
											50,TIER_4),
	avalanche	 	(3,0,"avalanche", 		new Stat[5]	{{fire,0},		{water,40},		{air,30},		{earth,30},		{life,0}},
											new Stat[5]	{{fire,0},		{water,15},		{air,6},		{earth,6},		{life,0}},
											70,ULT),
	air_missile 	(4,0,"air missile",  	new Stat[5]	{{fire,0},		{water,0},		{air,100},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,5},		{earth,0},		{life,0}},
											10,BASE),
	air_jab		 	(1,1,"wind jab", 	 	new Stat[5]	{{fire,0},		{water,0},		{air,100},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,5},		{earth,0},		{life,0}},
											5,TIER_1),
	storm_strike 	(8,0,"storm strike",  	new Stat[5]	{{fire,0},		{water,50},		{air,50},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,6},		{air,6},		{earth,0},		{life,0}},
											30,TIER_3),
	tornado		 	(7,0,"tornado",  		new Stat[5]	{{fire,0},		{water,0},		{air,100},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,20},		{earth,0},		{life,0}},
											50,TIER_4),
	hurricane 		(8,0,"hurricane",  		new Stat[5]	{{fire,0},		{water,50},		{air,50},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,15},		{air,15},		{earth,0},		{life,0}},
											70,ULT),
	rock_missile	(5,0,"rock missile",  	new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,100},	{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,5},		{life,0}},
											10,BASE),
	rock_jab		(1,1,"rock jab",  		new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,100},	{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,5},		{life,0}},
											5,TIER_1),
	mud_missile 	(5,0,"mud missile", 	new Stat[5]	{{fire,0},		{water,50},		{air,0},		{earth,50},		{life,0}},
											new Stat[5]	{{fire,0},		{water,3},		{air,0},		{earth,3},		{life,0}},
											10,TIER_1),
	sand_swirl	 	(5,0,"sand swirl",	 	new Stat[5]	{{fire,0},		{water,0},		{air,50},		{earth,50},		{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,3},		{earth,3},		{life,0}},
											10,TIER_1),
	magma_missile	(7,0,"magma missile",	new Stat[5]	{{fire,50},		{water,0},		{air,0},		{earth,50},		{life,0}},
											new Stat[5]	{{fire,3},		{water,0},		{air,0},		{earth,3},		{life,0}},
											25,TIER_2),
	leaf_missile	(5,0,"leaf missile", 	new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,100}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,5}},
											10,BASE),
	leaf_jab		(1,1,"leaf jab", 		new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,100}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,5}},
											5,TIER_1),
	root_shank		(5,0,"root shank",	 	new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,30},		{life,70}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,3},		{life,3}},
											10,TIER_1),
	vine_strike		(7,0,"vine strike", 	new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,100}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,10}},
											20,TIER_2),
	null_spell		(0,0,"\0", 				new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,0}},
											new Stat[5]	{{fire,0},		{water,0},		{air,0},		{earth,0},		{life,0}},
											0,ULT);
					
const Spell all_attacks[]={fire_jab,flare,fire_wave,fire_beam,water_jab,steam_missile,ice_missile,avalanche,thunderstorm,air_jab,tornado,storm_strike,
	hurricane,rock_jab,mud_missile,sand_swirl,magma_missile,leaf_jab,vine_strike,root_shank,fire_blast};
const int num_of_spells=21;
