#include <iostream>
#include <windows.h>
#include <iostream>

#include "mage.h"
using namespace std;

void saveMage(Mage &player){
	ofstream output(player.name+".txt");
	output<<player.level<<" "<<player.baseHP;
	for(int i=0; i<5; i++){
		output<<" "<<player.baseAtk[i].level;
		output<<" "<<player.baseDef[i].level;
		output<<" "<<player.baseMana[i].level;
	}
	for(int i=0;i<6;i++){
		output<<player.spells[i].name;
	}
}

void readMage(Mage &player){
	ifstream input(player.name+".txt");
	input>>player.level>>player.baseHP;
	for(int i=0; i<5;i++){
		input>>player.baseAtk[i].level;
		input>>player.baseDef[i].level;
		input>>player.baseMana[i].level;
	}
	
	string spells[6];
	for(int i=0;i<6; i++){
		input>>spells[i];
	}
}


void resetScreen(int linesBefore){
	for(int i=0; i<(25-linesBefore);i++){
		cout<<"\n";
	}
}

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
			choice = player.chooseAttack();
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
