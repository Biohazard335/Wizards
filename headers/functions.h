#ifndef FUNCTIONS_H
#define FUNCITONS_H

class Mage;

void resetScreen(int linesBefore);

RELATION elementRelation(Element element1, Element element2);

void printHP(Mage player, Mage cpu);

void battle(Mage& player, Mage cpu);
#endif
