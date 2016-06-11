#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
using namespace std;


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

