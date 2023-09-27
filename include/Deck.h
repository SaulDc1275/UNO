#pragma once
#include "Cards.h"
class Deck : public Cards
{
private:
	Cards principalDeck[108];
	Cards player1Deck[30];
	Cards player2Deck[30];
	int remainingCards;
	sf::Texture cardTextures[108];
	sf::Texture* textura1;
public:
	Deck();

	void shuffleDeck();
	void fillDeck();


};
