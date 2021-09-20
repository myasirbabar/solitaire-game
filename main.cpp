#include <iostream>
#include"Solitaire.h"
#include<Windows.h>

using namespace std;

const int PlayingCards::diamond = 0;
const int PlayingCards::heart = 1;
const int PlayingCards::spade = 2;
const int PlayingCards::club = 3;

int main(){

	ConsoleFunctions cf; cf.setConsoleWindowAndBufferSize(152, 61);
	Solitaire S;
	S.Shuffle();
	S.dealToPlayingPiles();
	S.DisplayGame();
	S.Play();

	 cf.SetCursorAt(0, 30); Beep(2200, 900);
	cout << " YOU WON " << endl;
	cout << "------------" << endl;
	cout << " GAME ENDED " << endl;
	cout << "------------" << endl;
	cout << "Developed By Muhammad Yasir " << endl;
	
}