#include "PlayingCards.h"
#include <iostream>
#include<io.h>
#include<fcntl.h>
using namespace std;

PlayingCards::PlayingCards(int rank, int suit) {
	ConsoleFunctions cf;
	while (rank < 1 || rank > 13) {
		cf.RestoreMode();
		cout << "Invalid Rank Number, Enter in 1 - 13 : ";
		cin >> rank;
	}
	while (suit < 0 || suit > 3) {
		cf.RestoreMode();
		cout << "Invalid Suit Number, Enter in 0 - 3 : ";
		cin >> suit;
	}
	this->rank = rank;
	this->suit = suit;

	if (this->suit == 0 || this->suit == 1)
		color = 'r';
	else if (this->suit == 2 || this->suit == 3)
		color = 'b';

	faceUp = true;
	top = true;
}

void PlayingCards::display(int x, int y) {
	wstring symbol;
	if (suit == 0)
		symbol = L"\u2666";
	else if (suit == 1)
		symbol = L"\u2665";
	else if (suit == 2)
		symbol = L"\u2660";
	else if (suit == 3)
		symbol = L"\u2663";

	ConsoleFunctions cf;
	cf.SetCursorAt(x, y);

	if (isFaceUp() && isTop()) {
		if (color == 'r')
			cf.SetColor(red, white);
		else if (color == 'b')
			cf.SetColor(black, white);

		if (rank != 1 && rank < 11)
			cout << rank;
		else if (rank == 1)
			cout << "A";
		else if (rank == 11)
			cout << "J";
		else if (rank == 12)
			cout << "Q";
		else if (rank == 13)
			cout << "K";

		_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << symbol;
		_setmode(_fileno(stdout), _O_TEXT);
		int index = 1;
		if (rank == 10)
			index = 2;
		for (int j = 0; j < 8; j++) {
			for (int i = index; i < 6; i++) {
				cout << " ";
				if (j == 7 && i == 5) {
					_setmode(_fileno(stdout), _O_U8TEXT);
					wcout << symbol;
					_setmode(_fileno(stdout), _O_TEXT);
					if (rank != 1 && rank < 11)
						cout << rank;
					else if (rank == 1)
						cout << "A";
					else if (rank == 11)
						cout << "J";
					else if (rank == 12)
						cout << "Q";
					else if (rank == 13)
						cout << "K";
				}
			}
			if (j > 0 && j < 7) {
				if (rank == 10)
					cout << "   ";
				else
					cout << "  ";
			}
			cout << endl;
			cf.SetCursorAt(x, ++y);
		}
	}

	else if (!(isFaceUp()) && isTop()) {
		cf.SetColor(red, red);
		for (int j = 0; j < 8; j++) {
			for (int i = -1; i < 6; i++)
				cout << " ";

			cout << endl;
			cf.SetCursorAt(x, ++y);
		}

	}

	else if (!(isFaceUp()) && !(isTop())) {
		cf.SetColor(red, red);
		for (int j = 0; j < 2; j++) {
			for (int i = -1; i < 6; i++) {
				if (j == 0)
					cout << " ";
				else {
					cf.SetColor(gray, red);
					cout << "_";
				}

			}
			cout << endl;
			cf.SetCursorAt(x, ++y);
		}

	}

	else if (isFaceUp() && !(isTop())) {
		if (color == 'r')
			cf.SetColor(red, white);
		else if (color == 'b')
			cf.SetColor(black, white);

		if (rank != 1 && rank < 11)
			cout << rank;
		else if (rank == 1)
			cout << "A";
		else if (rank == 11)
			cout << "J";
		else if (rank == 12)
			cout << "Q";
		else if (rank == 13)
			cout << "K";

		_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << symbol;
		_setmode(_fileno(stdout), _O_TEXT);

		int index = 1;
		if (rank == 10)
			index = 2;

		for (int j = 0; j < 2; j++) {
			for (int i = index; i < 6; i++) {
				if (j == 0) {
					cout << " ";
				}
				else {
					cf.SetColor(gray, white);
					cout << "_";

				}
			}
			if (j == 1) {
				if (rank == 10)
					cout << "___";
				else
					cout << "__";
			}
			cout << endl;
			cf.SetCursorAt(x, ++y);
		}

	}

	cf.~ConsoleFunctions();
}

bool PlayingCards::isFaceUp() {
	return faceUp;
}

void PlayingCards::setFaceUp(bool value) {
	faceUp = value;
}

bool PlayingCards::isTop() {
	return top;
}

void PlayingCards::setTop(bool value) {
	top = value;
}

int PlayingCards::getSuit() {
	return suit;
}

int PlayingCards::getRank() {
	return rank;
}

char PlayingCards::getColor() {
	return color;
}