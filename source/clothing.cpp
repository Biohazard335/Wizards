#include <iostream>

#include "element.h"
#include "clothing.h"

void Clothing::create(Clothing base){
	if(type==base.type){
		tier=base.tier;
		name=base.name;
//			cout<<"\n"<<name<<":\t";
		for(int i=0;i<5;i++){
			atk[i].level=base.atk[i].level+rand()%((base.atk[i].level/10)+6)-2;
			def[i].level=base.def[i].level+rand()%((base.def[i].level/10)+6)-2;
			mana[i].level=base.mana[i].level+rand()%((base.mana[i].level/10)+6)-2;
//				cout<<atk[i].element.name[0]<<atk[i].level<<"/"<<def[i].level<<"\t";
		}
		hp=base.hp+ rand()%((base.hp/10)+5)-2;
	}else{
		std::cout<<"Clothing type mismatch!";
	}
}
	
Clothing::Clothing(string n, CLOTHING ty, Stat a[5], Stat d[5], Stat m[5], int h,TIER t){
	name=n;
	tier =t;
	type=ty;
	for(int i=0;i<5;i++){
		atk[i].level=a[i].level;
		def[i].level=d[i].level;
		mana[i].level=m[i].level;
	}
	hp=h;
//	stack=1;
}


const Clothing
	basic_robe ("basic robe",ROBE,				new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//atk
												new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//def
												new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//mana
												5,BASE),
	basic_hood ("basic hood",HOOD,				new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//atk
												new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//def
												new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//mana
												5,BASE),
	basic_pendant ("basic pendant",PENDANT,		new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//atk
												new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//def
												new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//mana
												5,BASE),
	basic_boots ("basic boots",BOOTS,			new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//atk
												new Stat[5] {{fire,1},{water,1},{air,1},{earth,1},{life,1}},//def
												new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//mana
												5,BASE),
	empty_ring ("empty_ring",RING,				new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//atk
												new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//def
												new Stat[5] {{fire,0},{water,0},{air,0},{earth,0},{life,0}},//mana
												5,BASE);
