#include <iostream>
#include <ctime>
#include <windows.h>

#include "mage.h"
#include "functions.h"
using namespace std;

int main(){
	srand(time(NULL));
	Mage  player("player",fire);
	
	Mage cpu("cpu",water);
	
	player.createMage();
	
	cpu.createRandomMage(15);
	
	cout<<"\n";
	system("pause");
	
	
	battle(player, cpu);
	
	return 0;
}

