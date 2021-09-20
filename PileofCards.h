#pragma once
#include "PlayingCards.h"
class PileofCards
{
private:
	PlayingCards* pile;
	int top;
	int size;
	point startPt;
	point endPt;

public:
	//PileofCards();
	PileofCards(int size = 0);
	~PileofCards();
	PlayingCards Peek();
	PlayingCards Remove();
	void Add(PlayingCards &card);
	bool IsEmpty();
	bool IsFull();
	int getTop(); 
	int getsize();
	void setStartPt(int x, int y); 
	point getStartPt();
	void setEndPt(int x, int y);
	point getEndPt(); 
	PileofCards& operator=(const PileofCards& poc); 
	PlayingCards viewCard(int i); 
	void SimpleDisplay(int num); 
	void CascadingDisplay(); 

};

