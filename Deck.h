#pragma once
#include "PlayingCards.h"
class Deck
{
private:
	PlayingCards* deck[52];
	int size;
public:
	Deck();
	int getSize();
	bool IsEmpty();
	PlayingCards Remove(int i);
	~Deck();
	void diaplayall();

};

