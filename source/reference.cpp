#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
using namespace std;

void resetScreen(int linesBefore){
	for(int i=0; i<(25-linesBefore);i++){
		cout<<"\n";
	}
}


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

enum TIER{
	BASE,
	TIER_1,
	TIER_2,
	TIER_3,
	TIER_4,
	ULT
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

RELATION elementRelation(Element element1, Element element2){
	for(int i =0;i<1;i++){
		if(element2.elem==element1.win[i]){
			return POWERFUL;
		}else if(element2.elem==element1.lose[i]){
			return WEAK;
		}
	}
	if(element1.elem==element2.elem){
		return EQUAL;
	}else{
		return NoNE;
	}
}

struct Stat{
	Element element;
	int level;
};

enum CLOTHING{
	ROBE,
	HOOD,
	PENDANT,
	BOOTS,
	RING
};


class Item{
	public:
		int stack;
};

struct Stack{
	Item item;
	int amount=0;
};

class Clothing: public Item{
	public:
		string name;
		TIER tier=BASE;
		CLOTHING type;
		Stat atk[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		Stat def[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		Stat mana[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
		int hp=0;
		
	create(Clothing base){
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
			cout<<"Clothing type mismatch!";
		}
	}
		
	Clothing(string n, CLOTHING ty, Stat a[5], Stat d[5], Stat m[5], int h,TIER t){
		name=n;
		tier =t;
		type=ty;
		for(int i=0;i<5;i++){
			atk[i].level=a[i].level;
			def[i].level=d[i].level;
			mana[i].level=m[i].level;
		}
		hp=h;
		stack=1;
	}
	Clothing(){
	}
};

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
												5,BASE);

class Mage;

class Spell{
	public:
	int cast_time, cool_time;
	string name;
	Stat stats[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
	Stat mana[5]={{fire,0},{water,0},{air,0},{earth,0},{life,0}};
	int power;
	TIER tier;	
	
	void printAttack(){
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

	Stat checkStat(Element check){
		for(int i=0;i<5;i++){
			if(check.elem == stats[i].element.elem){
				return stats[i];
			}
		}
	}
	
	Stat getMana(Element check){
		for(int i=0;i<5;i++){
			if(check.elem == stats[i].element.elem){
				return mana[i];
			}
		}
	}
		
	Spell(int cat, int cot, string n,  Stat s[5], Stat m[5], int p, TIER ti){
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
	Spell(){
	}
	void performAttack(Mage& attacker, Mage& defender);
};

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
					
const Spell all_attacks[]={fire_jab,flare,fire_wave,fire_beam,water_jab,steam_missile,ice_missile,avalanche,thunderstorm,air_jab,tornado,storm_strike,hurricane,
	rock_jab,mud_missile,sand_swirl,magma_missile,leaf_jab,vine_strike,root_shank,fire_blast};
	
	
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
	Clothing rings[8]={};
	int exp=0;
	
	public:
	Stat atk[5]={{fire,10},{water,10},{air,10},{earth,10},{life,10}};
	Stat def[5]={{fire,10},{water,10},{air,10},{earth,10},{life,10}};
	Stat mana[5]={{fire,50},{water,50},{air,50},{earth,50},{life,50}};
	string name;
	int hp=100;
	int cast_time=0, cool_time=0;
	
	
	Spell getSpell(int index){
		return spells[index];
	}
	
	void printAtks(){
		for(int index=0; index<5;index++){
			cout<<atk[index].element.name[0]<<":"<<atk[index].level<<" ";
		}
	}
	void printDefs(){
		for(int index=0; index<5;index++){
			cout<<def[index].element.name[0]<<":"<<def[index].level<<" ";
		}
	}
	Element getElement(){
		return mage_element;
	}
	int getLevel(){
		return level;
	}
	void createRandomMage(int l);
	
	void prebattle(){
		hp=baseHP+robe.hp+hood.hp+pendant.hp+boots.hp;
		for(int i=0;i<5;i++){
			atk[i].level= baseAtk[i].level+robe.atk[i].level+hood.atk[i].level+pendant.atk[i].level+boots.atk[i].level;
			def[i].level= baseDef[i].level+robe.def[i].level+hood.def[i].level+pendant.def[i].level+boots.def[i].level;
			for(int j=0;j<8;j++){
				atk[i].level+=rings[j].atk[i].level;
				def[i].level+=rings[j].def[i].level;
				hp+= rings[j].hp;
			}
		}
		cast_time=-1;
		cool_time=0;
	}
	
	void createMage(){
		int input =-1;
		cout<<"Enter name: ";
		cin>>name;
		while(true){
			cout<<"\n\nChoose your Mage Element:\n0) Fire\n1) Water\n2) Air\n3) Earth\n4) Life\n5) None\n";
			cin>> input;
			if(input<0 || input>5){
				cout<<"Error: invalid input\n";
			}else{
				break;
			}
		}
		switch(static_cast<ELEM>(input)){
			case FIRE: mage_element=fire; spells[5]=fire_jab;baseAtk[0].level=12;break;
			case WATER: mage_element=water; spells[5]=water_jab;baseAtk[1].level=12;break;
			case AIR: mage_element=air; spells[5]=air_jab;baseAtk[2].level=12; break;
			case EARTH: mage_element=earth; spells[5]=rock_jab;baseAtk[3].level=12;break;
			case LIFE: mage_element=life; spells[5]=leaf_jab;baseAtk[4].level=12; break;
			case NONE: mage_element=none; break;
			default: cout<<"ERROR";
		}
		robe.create(basic_robe);
		hood.create(basic_hood);
		pendant.create(basic_pendant);
		boots.create(basic_boots);
	}

	void levelUp(){
		for(int i=0; i<5;i++){
			if(baseAtk[i].element.elem==mage_element.elem){
				baseAtk[i].level+=7;
				baseDef[i].level+=5;
				baseMana[i].level+=7;
			}else{
				baseAtk[i].level+=5;
				baseDef[i].level+=5;
				baseMana[i].level+=5;
			}
		}
		baseHP+=5;
		cout<<"\nLevel Up!\nAttack  {";
		printAtks();
		cout<<"}\nDefense {";
		printDefs();
		cout<<"}\nMana    {";
		for(int index=0; index<5;index++){
			cout<<mana[index].element.name[0]<<":"<<mana[index].level<<" ";
		}
		cout<<"}";
	}
	
	void cpuLevelUp(){
		int random=0;
		random = rand()%8;
		if(random>5){
			for(int i=0;i<5;i++){
				if(baseAtk[i].element.elem==mage_element.elem){
					baseAtk[i].level+=5;
				}
			}
		}else{
			baseAtk[random].level+=5;
		}
		random = rand()%5;
		baseDef[random].level+=1;
		for(int i=0;i<5;i++){
			if(baseAtk[i].element.elem==mage_element.elem){
				baseAtk[i].level+=7;
				baseDef[i].level+=5;
				baseMana[i].level+=7;
			}else{
				baseAtk[i].level+=5;
				baseDef[i].level+=5;
				baseMana[i].level+=5;
			}
		}
		baseHP+=5;
	}
		
	Mage(string n, Element e, Stat a[5], Stat d[5]){
		name=n;
		mage_element =e;
		for(int i=0;i<5;i++){
			baseAtk[i]=a[i];
			baseDef[i]=d[i];
		}
		robe.create(basic_robe);
		hood.create(basic_hood);
		pendant.create(basic_pendant);
		boots.create(basic_boots);
	}
	Mage(string n, Element e, Stat a[5], Stat d[5], Spell s[6]){
		name=n;
		mage_element =e;
		for(int i=0;i<5;i++){
			baseAtk[i]=a[i];
			baseDef[i]=d[i];
			spells[i]=s[i];
		}
		spells[6]=s[6];
		robe.create(basic_robe);
		hood.create(basic_hood);
		pendant.create(basic_pendant);
		boots.create(basic_boots);
	}
	Mage(string n, Element e){
		name=n;
		mage_element =e;
		robe.create(basic_robe);
		hood.create(basic_hood);
		pendant.create(basic_pendant);
		boots.create(basic_boots);
	}
		
};

	
void printHP(Mage player, Mage cpu){
	cout<<"\t  "<<player.getElement().name<<" Mage "<<player.name;
	for(int i=player.name.size();i<=15;i++){
		cout<<" ";
	}
	cout<<"\t\t  "<<cpu.getElement().name<<" Mage "<<cpu.name;
	cout<<"\nLevel: "<<player.getLevel()<<"\t\tHP: "<<player.hp<<"\t\tLevel: "<<cpu.getLevel()<<"\t\tHP: "<<cpu.hp;
	cout<<"\nAttack  {";
	player.printAtks();
	cout<<"}\tAttack  {";
	cpu.printAtks();
	cout<<"}\nDefense {";
	player.printDefs();
	cout<<"}\tDefense {";
	cpu.printDefs();
	cout<<"}\nMana    {";
	for(int index=0; index<5;index++){
		cout<<player.mana[index].element.name[0]<<":"<<player.mana[index].level<<" ";
	}
	cout<<"}";
}


int chooseAttack(Mage& player){
	int choice=0;
	bool able=false;
	cout<<"\n\nChoose your attack!";
	for(int index = 0; index<6; index++){
		cout<<"\n"<<(index)<<") ";
		player.getSpell(index).printAttack();
	}
	resetScreen(13);
	while(!able){
		able=true;
		
		cin>> choice;
		
		if(player.getSpell(choice).name=="\0"){
			cout<<"Invalid selection\n";
			able=false;
		}
		
		if(choice>=0 && choice<6){
			for( int i=0; i< 5; i++){
				if(player.mana[i].level<player.getSpell(choice).mana[i].level){
					able=false;
					cout<<"Not enough Mana!\n";
					break;
				}
			}
		}else{
			cout<<"Invalid selection\n";
			able=false;
		}
	}
	player.cast_time=player.getSpell(choice).cast_time;
			
	for(int i=0; i<5 ;i++){
		player.mana[i].level-=player.getSpell(choice).mana[i].level;
	}
	return choice;
}

void battle(Mage& player, Mage cpu){
	player.prebattle();
	cpu.prebattle();
	int choice=0, damage=0, cpuchoice;
	
	do{
		
		if(player.cast_time==0){
			player.getSpell(choice).performAttack(player,cpu);
			printHP(player,cpu);
			resetScreen(7);
			player.cast_time=-1;
			system("pause");
		}
		if(player.hp<0 || cpu.hp<0){
			break;
		}
		if(player.cast_time==-1 && player.cool_time==0){
			printHP(player,cpu);
			choice = chooseAttack(player);
			player.cast_time=player.getSpell(choice).cast_time;
			player.cool_time=player.getSpell(choice).cool_time;
		}
		if(player.cast_time==-1 && player.cool_time>0){
			player.cool_time-=1;
		}
		if(player.cast_time>0){
			player.cast_time-=1;
		}
		
		if(cpu.cast_time==0){
			cpu.getSpell(cpuchoice).performAttack(cpu,player);
			printHP(player,cpu);
			resetScreen(7);
			cpu.cast_time=-1;
			system("pause");
		}
		if(player.hp<0 || cpu.hp<0){
			break;
		}
		if(cpu.cast_time==-1 && cpu.cool_time==0){
			cpuchoice = rand() % 6;
			cpu.cast_time=cpu.getSpell(cpuchoice).cast_time;
			cpu.cool_time=cpu.getSpell(cpuchoice).cool_time;
		}
		if(cpu.cast_time==-1 && cpu.cool_time>0){
			cpu.cool_time-=1;
		}
		if(cpu.cast_time>0){
			cpu.cast_time-=1;
		}
		
		cout<<".\n";
		Sleep(1000);
		
	}while(player.hp>0 && cpu.hp>0);
}


int main(){
	srand(time(NULL));
	Mage player("player",fire);
	
	Mage cpu("cpu",water);
	
//	player.createMage();

	player.createRandomMage(15);
	
	cpu.createRandomMage(15);
	
	cout<<"\n";
	system("pause");
	
	
	battle(player, cpu);
	
	return 0;
}

void Mage::createRandomMage(int l){
	Spell chosen;
	int random=0, attack_index=1;
	level=l;
	random = rand()%6;
	switch(static_cast<ELEM>(random)){
		case FIRE:
			mage_element=fire;
			spells[0]=fire_missile;break;
		case WATER:
			mage_element=water;
			spells[0]=water_missile;break;
		case AIR:
			mage_element=air;
			spells[0]=air_missile;break;
		case EARTH:
			mage_element=earth;
			spells[0]=rock_missile;break;
		case LIFE:
			mage_element=life;
			spells[0]=leaf_missile;break;
		case NONE:
			break;
	}
	
	
	do{
		bool redo=false;
		bool element_match=false;
		random = rand()% 21;
		chosen = all_attacks[random];
		for(int i=0;i<6;i++){
			if(chosen.name==spells[i].name){
				redo=true;
			}
		}
		if(redo){
			continue;
		}
		for(int i=0;i<5;i++){
			if(chosen.mana[i].level!=0 && chosen.mana[i].element.elem==mage_element.elem){
				element_match=true;
			}
		}
		
		random = rand()% 101;
		if(element_match){
			if((random>=(90-level*2) && chosen.tier==ULT)
			||(random>=(80-level*2) && chosen.tier==TIER_4)
			||(random>=(60-level*2) && chosen.tier==TIER_3)
			||(random>=(40-level*2) && chosen.tier==TIER_2)
			||(random>=(20-level*2) && chosen.tier==TIER_1)){
				spells[attack_index]=chosen;
				attack_index+=1;
			}
		}else{
			if((random>=(95-level*2) && chosen.tier==ULT)
			||(random>=(90-level*2) && chosen.tier==TIER_4)
			||(random>=(85-level*2) && chosen.tier==TIER_3)
			||(random>=(80-level*2) && chosen.tier==TIER_2)
			||(random>=(75-level*2) && chosen.tier==TIER_1)){
				spells[attack_index]=chosen;
				attack_index+=1;
			}
		}
	}while(attack_index<6);
	
	
	for(int i=0;i<5;i++){
		if(baseAtk[i].element.elem==mage_element.elem){
			baseAtk[i].level=12;
			baseDef[i].level=10;
		}else{
			baseAtk[i].level=10;
			baseDef[i].level=10;
		}
	}
	for(int i=1;i<level;i++){
		cpuLevelUp();
	}
	
	
	robe.create(basic_robe);
	hood.create(basic_hood);
	pendant.create(basic_pendant);
	boots.create(basic_boots);
/*	cout<<"\t  "<<mage_element.name<<" Mage "<<name;
	cout<<"\nLevel: "<<getLevel()<<"\t\tHP: "<<baseHP;
	cout<<"\nAttack  {";
	for(int index=0; index<5;index++){
		cout<<baseAtk[index].element.name[0]<<":"<<baseAtk[index].level<<" ";
	}
	cout<<"}\nDefense {";
	for(int index=0; index<5;index++){
		cout<<baseDef[index].element.name[0]<<":"<<baseDef[index].level<<" ";
	}
	cout<<"}\n\nSpells:";
	for(int index = 0; index<6; index++){
		cout<<"\n"<<(index)<<") ";
		getSpell(index).printAttack();
	}*/
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
