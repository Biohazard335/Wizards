#ifndef TYPES_H
#define TYPES_H
class Item{
	public:
		int stack;
};

struct Stack{
	Item item;
	int amount=0;
};
#endif
