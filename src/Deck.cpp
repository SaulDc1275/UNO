#include "../include/Deck.h"


Deck::Deck() {
    remainingCards = 108; // Cambiar a 108 para reflejar todas las cartas de UNO

    // Cargar las texturas de las cartas
    for (int i = 0; i < 108; i++) {
        string filename = "D:\\Proyecto Progra 1\\Images\\UNOCARDS\\card" + std::to_string(i) + ".png";
        if (!cardTextures[i].loadFromFile(filename)) {
            std::cerr << "Error al cargar la textura de la carta " << i << std::endl;
            // Manejar el error adecuadamente si la carga de textura falla
        }
    }

    fillDeck(); // Llena el mazo de cartas con valores y texturas
    shuffleDeck(); // Mezcla el mazo de cartas
}




void Deck::shuffleDeck()
{
    Cards temp;
    for (int i = 0; i < 108; ++i) {
        int random = rand() % 108;
        temp = principalDeck[i];
        principalDeck[i] = principalDeck[random];
        principalDeck[random] = temp;
    }
}

void Deck::fillDeck() {
    int index = 0;
    for (int number = 0; number <= 9; ++number) {
        for (int color = 0; color < 4; ++color) {
            principalDeck[index].setNumber(number);
            principalDeck[index].setColor(color);
            principalDeck[index].setTexture(&cardTextures[index]); // Asigna la textura a la carta
            index++;
        }
    }
}
