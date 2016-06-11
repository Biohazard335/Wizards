#include <iostream>
#include <ctime>

#include "element.h"
#include "spell.h"
#include "mage.h"
#include "functions.h"
using namespace std;

void Mage::printAtks(){
	for(int index=0; index<5;index++){
		cout<<atk[index].element.name[0]<<":"<<atk[index].level<<" ";
	}
}
void Mage::printDefs(){
	for(int index=0; index<5;index++){
		cout<<def[index].element.name[0]<<":"<<def[index].level<<" ";
	}
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

void Mage::prebattle(){
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

void Mage::createMage(){
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

void Mage::levelUp(){
	for(int i=0; i <5;i++){
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

void Mage::cpuLevelUp(){
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



int Mage::chooseAttack(){
	return 0;
	int choice=0;
	bool able=false;
	cout<<"\n\nChoose your attack!";
	for(int index = 0; index<6; index++){
		cout<<"\n"<<(index)<<") ";
		getSpell(index).printAttack();
	}
	resetScreen(13);
	while(!able){
		able=true;
		
		cin>> choice;
		
		if(getSpell(choice).name=="\0"){
			cout<<"Invalid selection\n";
			able=false;
		}
		
		if(choice>=0 && choice<6){
			for( int i=0; i< 5; i++){
				if(mana[i].level<getSpell(choice).mana[i].level){
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
	cast_time=getSpell(choice).cast_time;
			
	for(int i=0; i<5 ;i++){
		mana[i].level-=getSpell(choice).mana[i].level;
	}
	return choice;
}


	
Mage::Mage(string n, Element e, Stat a[5], Stat d[5]){
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

Mage::Mage(string n, Element e, Stat a[5], Stat d[5], Spell s[6]){
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

Mage::Mage(string n, Element e){
	name=n;
	mage_element =e;
	robe.create(basic_robe);
	hood.create(basic_hood);
	pendant.create(basic_pendant);
	boots.create(basic_boots);
}
