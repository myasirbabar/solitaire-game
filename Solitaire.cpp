#include "Solitaire.h"
#include<stdlib.h>
#include <ctime>
#include<Windows.h>

Solitaire::Solitaire() {
	stock = new PileofCards(52);
	stock->setStartPt(2, 2);
	stock->setEndPt(9, 8);
	waste = new PileofCards(52);
	waste->setStartPt(2, 10);
	waste->setEndPt(9, 16);
	int x = 26, y = 32;
	for (int i = 0; i < 4; i++) {
		home[i] = new PileofCards(13);
		home[i]->setStartPt(2, x);
		home[i]->setEndPt(9,y);
		x += 8;
		y += 8;
	}
	int index = 14, s = 2;
	for (int i = 0; i < 7; i++) {
		playingPile[i] = new PileofCards(index);
		index++;
		playingPile[i]->setStartPt(15, s);
		s += 8;
	}
}

void Solitaire::Shuffle(){
	int i;
	//srand(time(0));
	while (!deckofCards.IsEmpty())
	{
		i = rand() % deckofCards.getSize();
		PlayingCards c = deckofCards.Remove(i);
		c.setFaceUp(false);
		stock->Add(c);
	}
}

void Solitaire::dealToPlayingPiles(){
	int r = 20, c = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < i+1; j++) {
			PlayingCards temp = stock->Remove();
			temp.setFaceUp(false);
			temp.setTop(false);
			if (j + 1 == i + 1) {
				temp.setFaceUp(true);
				temp.setTop(true);
				r += 2; c += 8;
				playingPile[i]->setEndPt(r, c);
			}
			playingPile[i]->Add(temp);
		}
	}
}

void Solitaire::DisplayGame() {
	stock->SimpleDisplay(1);
	waste->SimpleDisplay(0);
	for (int i = 0; i < 4; i++)
		home[i]->SimpleDisplay(0);
	for (int i = 0; i < 7; i++)
		playingPile[i]->CascadingDisplay();
}

Solitaire::~Solitaire() {
	if (stock != NULL)
		delete stock;

	if (waste != NULL)
		delete waste;

	for (int i = 0; i < 4; i++)
		if (home[i] != NULL)
			delete home[i];

	for (int i = 0; i < 7; i++)
		if (playingPile[i] != NULL)
			delete playingPile[i];
}

point Solitaire::getClickedPoint(){
		point p;
		ConsoleFunctions temp;
		bool flag = false;
		while (flag == false){
			temp.DetectEvent();
			if (temp.IsMouseLeftClickEvent(p)){
				flag = true;
			}
		}
		return p;
}

PileofCards* Solitaire::getClickedPile(point p, int& a, int& c) { // p.y == rows,,, startpt.x === rows
	
	if (p.x >= stock->getStartPt().y &&  p.x <= stock->getEndPt().y && p.y >= stock->getStartPt().x && p.y <= stock->getEndPt().x) {
		
		return stock;
	}

	else if (p.x >= waste->getStartPt().y && p.x <= waste->getEndPt().y && p.y >= waste->getStartPt().x && p.y <= waste->getEndPt().x) {
		
		return waste;
	}

	for (int i = 0; i < 4; i++) {
		if (p.x >= home[i]->getStartPt().y && p.x <= home[i]->getEndPt().y && p.y >= home[i]->getStartPt().x && p.y <= home[i]->getEndPt().x) {
			//cout << "home : " << i + 1 << endl;
			a = i;
			return  home[i];
		}
	}
	
	int loc;
	for (int i = 0; i < 7; i++) {
		if (p.x >= playingPile[i]->getStartPt().y && p.x <= playingPile[i]->getEndPt().y && p.y >= playingPile[i]->getStartPt().x && p.y <= playingPile[i]->getEndPt().x) {
			loc = 0;
			for (int index = playingPile[i]->getStartPt().x; index <= playingPile[i]->getEndPt().x; index+=2) {

				if (playingPile[i]->getTop() == 0){
					c = playingPile[i]->getTop();
					//cout << c << endl;
					break;
			    }

				else if (playingPile[i]->getTop() == loc-1) {
					//cout << "in single check ";
					c = playingPile[i]->getTop();
					//cout << c << endl;
					break;
				}

				else if (index == p.y || index + 1 == p.y){
					//cout << "in 2 checks ";
					c = (index - playingPile[i]->getStartPt().x - loc);
					//cout << c << endl;
					break;
				}
				
				loc++;
			}			
			a = i;
			return playingPile[i];
		}
	}

}

void Solitaire::moveFromStock() {
	if (stock->getTop() == -1)
		return;

	PlayingCards temp = stock->Remove();
	temp.setFaceUp(true);
	waste->Add(temp);
}

void Solitaire::moveFromWasteToHome(int a) {
	if (waste->getTop() == -1)
		return;
	PlayingCards temp = waste->Remove();
	temp.setFaceUp(true);
	home[a]->Add(temp);
}

void Solitaire::moveFromWasteToPlayingPile(int a, int c) {
	if (waste->getTop() == -1)
		return;
	

	PlayingCards temp = waste->Remove();
	temp.setFaceUp(true);
	playingPile[a]->Add(temp);

	if(playingPile[a]->getTop() != 0)
		playingPile[a]->setEndPt(playingPile[a]->getEndPt().x + 2, playingPile[a]->getEndPt().y);

}

void Solitaire::moveFromPlayingPileToHome(int a, int b, int c) {
	if (playingPile[b]->getTop() == -1)
		return;

	PlayingCards temp = playingPile[b]->Remove();
	if(playingPile[b]->getTop() != -1)
		playingPile[b]->setEndPt(playingPile[b]->getEndPt().x - 2, playingPile[b]->getEndPt().y);
	temp.setFaceUp(true);
	home[a]->Add(temp);
}

void Solitaire::moveFromPlayingPileToPlayingPile(int a, int b, int c1, int c2) {
	if (playingPile[b]->getTop() == -1)
		return;

	for (int i = c2; i <= playingPile[b]->getTop(); i++) {
		PlayingCards temp = playingPile[b]->viewCard(i);

		if (playingPile[b]->getTop() != -1)
			playingPile[b]->setEndPt(playingPile[b]->getEndPt().x - 2, playingPile[b]->getEndPt().y);

		temp.setFaceUp(true);
		playingPile[a]->Add(temp);

		if (playingPile[a]->getTop() != 0)
			playingPile[a]->setEndPt(playingPile[a]->getEndPt().x + 2, playingPile[a]->getEndPt().y);
	}
	for (int i = playingPile[b]->getTop(); i >= c2; i--) {
		
		PlayingCards temp2 = playingPile[b]->Remove();
	}
	if (playingPile[b]->getTop() == -1)
		playingPile[b]->setEndPt(22, playingPile[b]->getEndPt().y);
}

void Solitaire::moveFromHomeToPlayingPile(int a, int b, int c) {
	if (home[b]->getTop() == -1)
		return;

	PlayingCards temp = home[b]->Remove();
	temp.setFaceUp(true);
	playingPile[a]->Add(temp);
	if (playingPile[a]->getTop() != 0)
		playingPile[a]->setEndPt(playingPile[a]->getEndPt().x + 2, playingPile[a]->getEndPt().y);
}

void Solitaire::Play() {
	cf.setConsoleTitle("TASH");
	int a = -1, c = -1, b = -1, d = -1, check = 0;
	point click;
	PileofCards* clickedpile;
	click = getClickedPoint();  PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
	clickedpile = getClickedPile(click, a, c);

START:
	if (clickedpile != stock && clickedpile != waste && clickedpile != playingPile[a] && clickedpile != home[a]) {
		system("cls");
		DisplayGame();
		cf.SetCursorAt(0, 0);
		cout << '\a';
		cout << "Select a pile " << endl;
		goto AGAIN;
	}

	if (clickedpile->getTop() == -1 && clickedpile != stock) {
		system("cls");
		DisplayGame();
		cf.SetCursorAt(0, 0);
		cout << '\a'; cout << "Empty Pile " << endl;
		goto AGAIN;
	}

	//STOCK ---- WASTE 
	if (clickedpile == stock) {
		if (stock->getTop() != -1) {
			moveFromStock();
			
		}
		
		else if (stock->getTop() == -1) {
			for (int i = waste->getTop(); i > -1; i--) {
				PlayingCards temp = waste->Remove();
				temp.setFaceUp(false);
				stock->Add(temp);
			}
		}
		system("cls");
		DisplayGame();
	}

	//WASTE --- HOME / PlayingPile
	else if (clickedpile == waste) {
		system("cls");
		DisplayGame();
		cf.SetCursorAt(0, 0);
		cout << "Waste Pile Selected " << endl;

		//PlayingCards temp = waste->Remove();
		/*PlayingCards temp = waste->Peek();
		click = movement(temp);*/

		click = getClickedPoint(); 
		PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
		clickedpile = getClickedPile(click, a, c);

		while (clickedpile != home[a] && clickedpile != playingPile[a]) {
			//waste->Add(temp); //DONE FOR MOVEMENT FUNCTION
			system("cls");
			DisplayGame();
			cf.SetCursorAt(0, 0);
			cout << '\a'; cout << "Invalid Click, Select home or Playing Pile " << endl;
			click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
			clickedpile = getClickedPile(click, a, c);
		}

		if (clickedpile == home[a]) {
			if (home[a]->getTop() == -1) {

				if (waste->Peek().getRank() != 1) {
					system("cls");
					DisplayGame();
					cf.SetCursorAt(0, 0);
					cout << '\a'; cout << " Home Pile must start with Ace, Click another " << endl;
					check = 1;
					goto AGAIN;
				}

				else {
					moveFromWasteToHome(a);
				}
			}
			
			else {
				if ((waste->Peek().getSuit() != home[a]->Peek().getSuit() || waste->Peek().getRank() - 1 != home[a]->Peek().getRank())) {

					system("cls");
					DisplayGame();
					cf.SetCursorAt(0, 0);
					cout << '\a'; cout << " Invalid Sequence, Sequence : Ace - King, Click another " << endl;
					check = 1;
					goto AGAIN;

				}
				
				else {
					moveFromWasteToHome(a);
				}
			}
			
			if (win()) {
				system("cls");
				DisplayGame();
				return;
			}
		}

		else if (clickedpile == playingPile[a]) {
			if ((waste->Peek().getColor() == playingPile[a]->Peek().getColor() ||
				waste->Peek().getRank() + 1 != playingPile[a]->Peek().getRank()) && (playingPile[a]->getTop() != -1)) {

				system("cls");
				DisplayGame();
				cf.SetCursorAt(0, 0);
				cout << '\a'; cout << " Invalid Squence, Cards must be in opposite color and in rank order, Click another " << endl;
				check = 1;
				goto AGAIN;
			}
			
			while (playingPile[a]->getTop() != c) {
				system("cls");
				DisplayGame();
				cf.SetCursorAt(0, 0);
				cout << '\a'; cout << "Invalid Move, Select Top card of Pile" << endl;
				click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
				clickedpile = getClickedPile(click, a, c);
			}
			moveFromWasteToPlayingPile(a,c);	
		}
		
		system("cls");
		DisplayGame();
	}

	//PlayingPile ---- HOME / PLAYING PILE
	else if (clickedpile == playingPile[a]){

		if (clickedpile->viewCard(c).isFaceUp() == false || playingPile[a]->getTop() == -1) {
			system("cls");
			DisplayGame();
			cf.SetCursorAt(0, 0);
			cout << '\a'; cout << "Invalid Click, Try Again " << endl;
			check = 1;
			goto AGAIN;
		}
	
		system("cls");
		DisplayGame();
		cf.SetCursorAt(0, 0);
		cout << "Card Number " << c + 1 << " Selected of Playing Pile " << a + 1 << endl;

		int b1 = a;
		d = c;
		click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
		clickedpile = getClickedPile(click, a, c);
		b = a;

		while (clickedpile != home[a] && clickedpile != playingPile[a]) {
			system("cls");
			DisplayGame();
			cf.SetCursorAt(0, 0);
			cout << '\a'; cout << "Invalid Click, Select home or Playing Pile " << endl;
			click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
			clickedpile = getClickedPile(click, a, c);
		}

		if (clickedpile == home[a]) {
			if (home[a]->getTop() == -1) {

				if (playingPile[b1]->Peek().getRank() != 1) {
					system("cls");
					DisplayGame();
					cf.SetCursorAt(0, 0);
					cout << '\a'; cout << " Home Pile must start with Ace, Click another " << endl;
					check = 1;
					goto AGAIN;
				}

				else {
					moveFromPlayingPileToHome(a,b1,c);
				}
			}

			else {
				if ((playingPile[b1]->Peek().getSuit() != home[a]->Peek().getSuit() ||
					playingPile[b1]->Peek().getRank() - 1 != home[a]->Peek().getRank())) {

					system("cls");
					DisplayGame();
					cf.SetCursorAt(0, 0);
					cout << '\a'; cout << " Invalid Sequence, Sequence : Ace - King, Click another " << endl;
					check = 1;
					goto AGAIN;

				}

				else {
					moveFromPlayingPileToHome(a, b1, c);
				}
			}

			if (win()) {
				system("cls");
				DisplayGame();
				return;
			}
		}

		else if(clickedpile == playingPile[a]){

			if ((playingPile[b1]->viewCard(d).getColor() == playingPile[a]->Peek().getColor() ||
				playingPile[b1]->viewCard(d).getRank() + 1 != playingPile[a]->viewCard(c).getRank()) &&
				(playingPile[a]->getTop() != -1)) {

				system("cls");
				DisplayGame();
				cf.SetCursorAt(0, 0);
				cout << '\a'; cout << " Invalid Squence, Cards must be in opposite color and in rank order" << endl;
				check = 1;
				goto AGAIN;
			}

			if (playingPile[a]->getsize() == playingPile[a]->getTop() + 1) {
				cf.SetCursorAt(0, 0);
				cout << '\a'; cout << "Pile is full " << endl;
				check = 1;
				goto AGAIN;
			}

			while (playingPile[a]->getTop() != c) {
				system("cls");
				DisplayGame();
				cf.SetCursorAt(0, 0);
				cout << '\a'; cout << "Invalid Move, Select Top card of Pile" << endl;
				click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
				clickedpile = getClickedPile(click, a, c);
			}
			moveFromPlayingPileToPlayingPile(a, b1, c, d);
		}
		
		system("cls");
		DisplayGame();
	}

	//HOME ---- PLAYINGPILE
	else if (clickedpile == home[a]) {

		system("cls");
		DisplayGame();
		cf.SetCursorAt(0, 0);
		cout << "Home Pile : " << a + 1 << " Selected" << endl;

		b = a;
		click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
		clickedpile = getClickedPile(click, a, c);
		
		while (clickedpile != playingPile[a]) {
			click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
			clickedpile = getClickedPile(click, a, c);
		}

		if ((home[b]->Peek().getColor() == playingPile[a]->Peek().getColor() ||
			home[b]->Peek().getRank() + 1 != playingPile[a]->Peek().getRank()) && (playingPile[a]->getTop() != -1)) {

			system("cls");
			DisplayGame();
			cf.SetCursorAt(0, 0);
			cout << '\a'; cout << " Invalid Squence, Cards must be in opposite color and in rank order, Click another " << endl;
			check = 1;
			goto AGAIN;
		}
		
		while (playingPile[a]->getTop() != c) {
			//cout << "in here" << endl;
			click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
			clickedpile = getClickedPile(click, a, c);
		}

		moveFromHomeToPlayingPile(a, b, c);
		system("cls");
		DisplayGame();

		click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
		clickedpile = getClickedPile(click, a, c);
	}

	AGAIN:
		click = getClickedPoint(); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME); PlaySound(TEXT("click.wav"), NULL, SND_ASYNC | SND_FILENAME);
		clickedpile = getClickedPile(click, a, c);

	goto START;
}

bool Solitaire::win() {
	int win = 0;
	for (int i = 0; i < 4; i++) {
		if (home[i]->getTop() == home[i]->getsize() - 1)
			win++;

		if (win == 4)
			return true;
	}
	return false;
}

void Solitaire::chkpts() {
	point temp = stock->getStartPt();
	int x = temp.x, y = temp.y;
	cf.SetCursorAt(y, x);
	cout << "s";

	temp = stock->getEndPt();
	x = temp.x, y = temp.y;
	cf.SetCursorAt(y, x);
	cout << "e";

	temp = waste->getEndPt();
	x = temp.x, y = temp.y;
	cf.SetCursorAt(y, x);
	cout << "e";

	temp = waste->getStartPt();
	x = temp.x, y = temp.y;
	cf.SetCursorAt(y, x);
	cout << "s";

	for (int i = 0; i < 4; i++) {
		temp = home[i]->getStartPt();
		x = temp.x, y = temp.y;
		cf.SetCursorAt(y, x);
		cout << "s";

		temp = home[i]->getEndPt();
		x = temp.x, y = temp.y;
		cf.SetCursorAt(y, x);
		cout << "e";

	}

	for (int i = 0; i < 7; i++) {
		temp = playingPile[i]->getStartPt();
		x = temp.x, y = temp.y;
		cf.SetCursorAt(y, x);
		cout << "s";

		temp = playingPile[i]->getEndPt();
		x = temp.x, y = temp.y;
		cf.SetCursorAt(y, x);
		cout << "e";

	}

}

point Solitaire::movement(PlayingCards& obj) {
	point p;
	int i = 0;
	cf.DetectEvent();
	while (cf.IsMouseLeftClickEvent(p) == false)
	{
		//cf.DetectEvent();
		if (cf.getMousePosition(p))
		{
			cf.SetCursorAt(p.x, p.y);
			obj.display(p.x, p.y);
			//cf.SetColor((i++)%15 +1 , (++i) % 15 +1);
			//cout << 'A';
		}
		Sleep(150);
		system("cls");
		DisplayGame();
		cf.DetectEvent();
	}
	return p;
}