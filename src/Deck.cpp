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

   
}








