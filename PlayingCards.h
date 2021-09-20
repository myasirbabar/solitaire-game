#pragma once
#include"ConsoleFunctions.h"
class PlayingCards
{
private:
	int rank; //integer 1 – 13
	int suit; //integer 0 – 3
	char color; // red or black - ‘b’ for black , ‘r’ for red
	bool faceUp;
	bool top;

public:
	static int const diamond, heart, spade, club;
	PlayingCards(int rank = 1, int suit = 0);
	void display(int x, int y);
	bool isFaceUp(); //retunrs value of faceUp
	void setFaceUp(bool value); //sets value of faceUp
	bool isTop(); //retunrs value of top
	void setTop(bool value); //sets value of top
	int getSuit(); //getter for suit value
	int getRank(); //getter for rank value
	char getColor(); //getter for color value

};

