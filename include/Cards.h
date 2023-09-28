#include <iostream>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class Cards 
{
private:
	sf::Texture* textura;
	int number;
	int color;
	sf::Sprite sprite;
	
public:

	int getColor();
	int getNumber();
	
	void setNumber(int _number);
	void setColor(int _color);
	void setTexture(sf::Texture* _textura) {
		textura = _textura;
	}
	
	sf::Texture* getTexture() const
	{
		return textura;
	}

	// Método para establecer el sprite de la carta
	void setSprite(const sf::Sprite& newSprite) {
		sprite = newSprite;
	}

	sf::Sprite& getSprite() {
		return sprite;
	}

	void assignColorAndNumber(int cardIndex) {
		// Calcula el color y el número basado en el índice de la carta
		int newColor = (cardIndex / 10) + 1; // Divide el índice entre 10 y suma 1
		int newNumber = cardIndex % 10; // Obtiene el número tomando el módulo 10

		// Establece los valores en la instancia actual de Cards
		setColor(newColor);
		setNumber(newNumber);
	}
	bool usada = false;  // Para marcar si la carta se ha "eliminado" de la mano del jugador
	bool repartida = false;  // Para marcar si la carta se ha repartido
	void assignColor(int cardIndex) {
		int newColor = (cardIndex / 10) + 1;
		setColor(newColor);
	}

};
