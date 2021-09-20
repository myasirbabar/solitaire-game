#include "PileofCards.h"
#include "ConsoleFunctions.h"

PileofCards::PileofCards(int size){
	this->size = size;
	pile = new PlayingCards[this->size];
	top = -1;
	startPt.x = 0, startPt.y = 0, endPt.x = 0, endPt.y = 0;
}

PileofCards::~PileofCards(){
	if (pile != NULL) 
		delete pile;
}

PlayingCards PileofCards:: Peek(){
	return pile[top];
}

PlayingCards PileofCards::Remove(){
	if (top != -1) {
		PlayingCards temp = pile[top];
		top--;
		if (top != -1) {
			pile[top].setTop(true);
			if (pile[top].isFaceUp() == false)
				pile[top].setFaceUp(true);
		}
		return temp;
	}
}

void PileofCards::Add(PlayingCards &card){
	if (!(IsFull())) {
		if(top != -1)
			pile[top].setTop(false);

		top++;
		pile[top] = card;
		pile[top].setTop(true);
		//pile[top].setFaceUp(false);
		return;
	}
	cout << "No space For New Card " << endl;
	return;
}

bool PileofCards::IsEmpty(){

	if (top == -1)
		return true;
	else
		return false;
}

bool PileofCards::IsFull(){

	if(top == size-1)
		return true;

	return false;
}

int PileofCards::getTop() {
	return top;
}

void PileofCards::setStartPt(int x, int y) {
	startPt.x = x;
	startPt.y = y;
	return;
}

point PileofCards::getStartPt() {
	return startPt;
}

void PileofCards::setEndPt(int x, int y) { 
	endPt.x = x;
	endPt.y = y;
	return;
}

point PileofCards::getEndPt() {
	return endPt;
}

PileofCards& PileofCards::operator=(const PileofCards& poc) {
	if (&poc == this) {
		return *this;
	}
	*this = poc;

	return *this;
}

PlayingCards PileofCards::viewCard(int i) {
	return pile[i];
}

void PileofCards::SimpleDisplay(int num) {
	if (top == -1) {
		int x = startPt.x, y = startPt.y;
		ConsoleFunctions cf;
		cf.SetCursorAt(y, x);
		cf.SetColor(dark_green, dark_green);
			for (int j = 0; j < 8; j++) {
				for (int i = -1; i < 6; i++)
					cout << " ";
				cout << endl;
				cf.SetCursorAt(y, ++x);
			}
	}

	else {
		if(num == 1)
			pile[top].setFaceUp(false);
		pile[top].display(startPt.y, startPt.x);
	}

	return;
}

void PileofCards::CascadingDisplay() {
	if (top == -1) {
		int x = startPt.x, y = startPt.y;
		ConsoleFunctions cf;
		cf.SetCursorAt(y, x);
		cf.SetColor(dark_green, dark_green);
		for (int j = 0; j < 8; j++) {
			for (int i = -1; i < 6; i++)
				cout << " ";
			cout << endl;
			cf.SetCursorAt(y, ++x);
		}
	}
	
	else {
		int y = startPt.y, x = startPt.x;
		for (int i = 0; i < top + 1; i++) {
			pile[i].display(y, x);
			x += 2;
		}

	}

	return;
}

int PileofCards::getsize() {
	return size;
}