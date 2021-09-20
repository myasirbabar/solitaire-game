#pragma once
#include "Deck.h"
#include "PileofCards.h"
class Solitaire
{
private:
	Deck deckofCards;
	PileofCards *stock;
	PileofCards *waste;
	PileofCards *home[4];
	PileofCards *playingPile[7];
	ConsoleFunctions cf;
public:
	Solitaire();
	void Shuffle();
	void dealToPlayingPiles();
	void DisplayGame();
	point getClickedPoint();
	PileofCards* getClickedPile(point p, int& a, int& c);
	void moveFromStock();
	void moveFromWasteToHome(int a);
	void moveFromWasteToPlayingPile(int a, int c);
	void moveFromPlayingPileToHome(int a, int b, int c);
	void moveFromPlayingPileToPlayingPile(int a, int b, int c1, int c2);
	void moveFromHomeToPlayingPile(int a, int b, int c);
	void Play();
	~Solitaire();
	point movement(PlayingCards& card);
	bool win();
	void chkpts();
};

