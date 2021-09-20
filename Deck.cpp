#include "Deck.h"

Deck::Deck() {
	size = 52;
	int j = 0;
	for (int i = 1; i <= 13; i++) {
		deck[j] = new PlayingCards(i, PlayingCards::diamond);
		j++;
	}
	for (int i = 1; i <= 13; i++) {
		deck[j] = new PlayingCards(i, PlayingCards::heart);
		j++;
	}
	for (int i = 1; i <= 13; i++) {
		deck[j] = new PlayingCards(i, PlayingCards::spade);
		j++;
	}
	for (int i = 1; i <= 13; i++) {
		deck[j] = new PlayingCards(i, PlayingCards::club);
		j++;
	}
}

Deck::~Deck() {
	for (int i = 0; i < size; i++) {
		if (deck[i] != NULL){
			delete deck[i];
		}
	}
}

void Deck::diaplayall() {
	int x = 0, y = 0;
	for (int i = 0; i < size; i++) {
		deck[i]->display(x, y);
		Sleep(400);
		system("cls");
	}
}

int Deck::getSize() {
	return size;
}

bool Deck::IsEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}

PlayingCards Deck::Remove(int i) {
	if (deck[i] != NULL) {
		PlayingCards* temp = deck[i];
		deck[i] = NULL;
		for (int index = i + 1; index < size; index++) {
			deck[index - 1] = deck[index];
		}
		size--;
		return *temp;
	}
}


