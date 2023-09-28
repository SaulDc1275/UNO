#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "../include/Deck.h"
#include <algorithm> 
#include <random> 


using namespace std;

int main()
{
    // Para marcar si la carta se ha repartido
    bool reachedMiddle = false;
    bool closed = false;
    sf::RenderWindow renderWindow(sf::VideoMode(1920, 1080), "UNO");
    renderWindow.setFramerateLimit(30);
    sf::Event event;

    sf::Texture texture;
    texture.loadFromFile("assets/Images/Menu.png");
    sf::Sprite sprite(texture);

    sf::RectangleShape button(sf::Vector2f(400, 100)); // Tamaño del botón
    button.setPosition(744, 600); // Posición del botón
    sf::Color color(203, 67, 53);
    button.setFillColor(color);

    sf::Font font;
    font.loadFromFile("assets/Font/ARCO for OSX.otf"); // tarea
    
    sf::Text buttonText;
    buttonText.setFont(font); // Establecer la fuente
    buttonText.setString("Jugar"); // Texto que se mostrará en el botón
    buttonText.setCharacterSize(60); // Tamaño del texto
    buttonText.setFillColor(sf::Color::White); // Color del texto
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = renderWindow.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (button.getGlobalBounds().contains(mousePos)) {
                        renderWindow.close();
                        closed = true;
                    }
                }
            }
        }
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.draw(button);
        renderWindow.draw(buttonText);
        renderWindow.display();
    }

    sf::RenderWindow Game(sf::VideoMode(1920, 1080), "UNO");
    sf::Event event1;
    renderWindow.setFramerateLimit(30);

    sf::Texture texture1;
    texture1.loadFromFile("assets/Images/Fondo1.png");
    sf::Sprite sprite1(texture1);

    sf::Texture cardTextures[40];

    sf::Texture DeckButton;
    DeckButton.loadFromFile("assets/Images/WILDCARDS/uno.png");
    sf::Sprite DeckButton1(DeckButton);
    DeckButton1.setScale(90.0f / DeckButton1.getLocalBounds().width, 125.0f / DeckButton1.getLocalBounds().height);
    DeckButton1.setPosition(851, 240);

    for (int i = 1; i <= 40; i++) { 
         
        cardTextures[i - 1].loadFromFile("assets/Images/UNOCARDS/card" + std::to_string(i) + ".png");   
    }
    Cards cartas[80]; // Duplicamos el tamaño a 80

    // Duplicar las cartas en el mazo "cartas"
    for (int i = 0; i < 80; i++) {
        cartas[i].setTexture(&(cardTextures[i % 40]));
        cartas[i].assignColorAndNumber(i % 40);

    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(std::begin(cartas), std::end(cartas), g);//Mezclar el mazo

    sf::Music music;


    music.openFromFile("assets/Music/Aombra_-_Motizan.mp3");



    music.play();






    int cartasDisponibles = 80;

    /*sf::Texture wildDraw4Texture;
    wildDraw4Texture.loadFromFile("assets/Images/WILDCARDS/draw4.png");
    for (int i = 0; i < 2; i++) {
        Cards wildDraw4Card;
        wildDraw4Card.setTexture(&wildDraw4Texture);
        // Asigna cualquier número o color que desees, o simplemente deja ambos en blanco si no son relevantes para esta carta comodín
        wildDraw4Card.assignColorAndNumber(-1); // -1 para indicar que no tiene número ni color
        cartas[cartasDisponibles] = wildDraw4Card;
        cartasDisponibles++;
    }

    sf::Texture wildCardsTexture[12];
    for (int i = 1; i <= 12; i++) {
        wildCardsTexture[i - 1].loadFromFile("assets/Images/WILDCARDS/wildcard (" + std::to_string(i) + ").png");
    }

    for (int i = 0; i < 12; i++) {
        Cards wildCard;
        wildCard.setTexture(&wildCardsTexture[i]);
        // Asigna cualquier número o color que desees, o simplemente deja ambos en blanco si no son relevantes para esta carta comodín
        wildCard.assignColorAndNumber(-1); // -1 para indicar que no tiene número ni color
        cartas[cartasDisponibles] = wildCard;
        cartasDisponibles++;
    }*/     //Daba fallos y no supe como arreglarlo




    Cards PileOfCards[108];
    Cards mazoJugador1[20];
    Cards mazoJugador2[20];
    
    // Copiar las 7 primeras cartas mezcladas al mazo del jugador 1
    for (int i = 0; i < 7; i++) {
        mazoJugador1[i] = cartas[i];
        cartas[i].repartida = true; // Marca la carta como repartida
        cartasDisponibles--;
    }


    std::shuffle(std::begin(cartas), std::end(cartas), g);
    // Copiar las siguientes 7 cartas mezcladas al mazo del jugador 2
    for (int i = 0; i < 7; i++) {
        mazoJugador2[i] = cartas[i];
        cartas[i].repartida = true; // Marca la carta como repartida
        cartasDisponibles--;
    }



    int x1 = 0;         
    int y1 = 540;
    int x2 = 1822;
    int y2 = 540;
    int SIZE = 0;
    int SIZE1 = 7;
    int SIZE2 = 7;


    sf::RectangleShape cardButtons[20]; // Arreglo de botones invisibles para las cartas
    sf::RectangleShape cardButtons2[20];
    
    for (int i = 0; i < SIZE1; i++) {
        cardButtons[i] = sf::RectangleShape(sf::Vector2f(90, 125)); // Tamaño del botón igual al de las cartas
        cardButtons[i].setPosition(x1, y1);
        cardButtons[i].setTexture(mazoJugador1[i].getTexture()); // Asignar la textura de la carta al botón
        x1 += 90;

        if (x1 >= 821) {
            reachedMiddle = true; // Se alcanzó la mitad de la pantalla
            x1 = 0;
            if (reachedMiddle == true) {
                y1 += 125;
            }
        }
    }
    for (int i = 0; i < SIZE2; i++) {
        cardButtons2[i] = sf::RectangleShape(sf::Vector2f(90, 125)); // Tamaño del botón igual al de las cartas
        cardButtons2[i].setPosition(x2, y2);
        cardButtons2[i].setTexture(mazoJugador1[i].getTexture()); // Asignar la textura de la carta al botón
        x2 -= 90;

        if (x2 <= 1001) {
            reachedMiddle = true; // Se alcanzó la mitad de la pantalla
            x2 = 1822;
            if (reachedMiddle == true) {
                y2 += 125;
            }
        }
    }

    int Turno = 1;

    if (closed == true) {
        while (Game.isOpen()) {
            while (Game.pollEvent(event1)) {
                if (event1.type == sf::Event::Closed) {
                    Game.close();
                }

                if (event1.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(Game);

                    if (Turno == 1 && SIZE1 < 20 && cartasDisponibles > 0) {
                        if (event1.mouseButton.button == sf::Mouse::Left) {
                            sf::FloatRect buttonBounds = DeckButton1.getGlobalBounds();

                            if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                                // Agrega una carta del mazo principal a mazoJugador1
                                mazoJugador1[SIZE1] = cartas[cartasDisponibles - 1];
                                cartas[cartasDisponibles - 1].repartida = true;
                                cartasDisponibles--;
                                SIZE1++;

                                // Ajusta la posición del botón de la carta en la mano del jugador 1
                                sf::RectangleShape cardButton(sf::Vector2f(90, 125));
                                cardButton.setPosition(x1, y1);
                                cardButton.setTexture(mazoJugador1[SIZE1 - 1].getTexture());
                                cardButtons[SIZE1 - 1] = cardButton;
                            }
                        }
                    }

                    if (Turno == 2 && SIZE2 < 20 && cartasDisponibles > 0) {
                        if (event1.mouseButton.button == sf::Mouse::Left) {
                            sf::FloatRect buttonBounds = DeckButton1.getGlobalBounds();

                            if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                                // Agrega una carta del mazo principal a mazoJugador2
                                mazoJugador2[SIZE2] = cartas[cartasDisponibles - 1];
                                cartas[cartasDisponibles - 1].repartida = true;
                                cartasDisponibles--;
                                SIZE2++;

                                // Ajusta la posición del botón de la carta en la mano del jugador 2
                                sf::RectangleShape cardButton(sf::Vector2f(90, 125));
                                cardButton.setPosition(x2, y2);
                                cardButton.setTexture(mazoJugador2[SIZE2 - 1].getTexture());
                                cardButtons2[SIZE2 - 1] = cardButton;
                            }
                        }
                    }
                }


                if (event1.type == sf::Event::MouseButtonPressed) {
                    if (event1.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(Game);

                        if (Turno == 1) {
                            for (int i = 0; i < SIZE1; i++) { // Revisa las cartas en la mano del jugador 1
                                if (cardButtons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                                    // Agrega la carta al montón de cartas jugadas (PileOfCards)
                                    PileOfCards[SIZE] = mazoJugador1[i];
                                    SIZE++; // Aumenta el tamaño del montón de cartas jugadas
                                    // Elimina la carta de la mano del jugador 1 (ajusta las posiciones de las otras cartas si es necesario)
                                    for (int j = i; j < SIZE1 - 1; j++) {
                                        mazoJugador1[j] = mazoJugador1[j + 1];
                                    }
                                    SIZE1--; // Disminuye el tamaño de la mano del jugador 1
                                    Turno = 2;
                                    break; // Sal del bucle una vez que se juegue una carta
                                }
                            }
                        }
                        else if (Turno == 2) {
                            for (int i = 0; i < SIZE2; i++) { // Revisa las cartas en la mano del jugador 2
                                if (cardButtons2[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                                    // Agrega la carta al montón de cartas jugadas (PileOfCards)
                                    PileOfCards[SIZE] = mazoJugador2[i];
                                    SIZE++; // Aumenta el tamaño del montón de cartas jugadas
                                    // Elimina la carta de la mano del jugador 2 (ajusta las posiciones de las otras cartas si es necesario)
                                    for (int j = i; j < SIZE2 - 1; j++) {
                                        mazoJugador2[j] = mazoJugador2[j + 1];
                                    }
                                    SIZE2--; // Disminuye el tamaño de la mano del jugador 2
                                    Turno = 1;
                                    break; // Sal del bucle una vez que se juegue una carta
                                }
                            }
                        }
                    }
                }


            }
            Game.clear();
            Game.draw(sprite1);
            Game.draw(DeckButton1);

            float tamanoX = 90.0f;
            float tamanoY = 125.0f;

            int x = 911;      // Posición en la mitad de la pantalla para el mazo total
            int y = 240;      // Posición vertical del mazo total
            int x3 = 961;
            int y3 = 240;

            
            x1 = 0;         //Posición inicial del mazo del jugador 1
            y1 = 540;
            for (int i = 0; i < SIZE1; i++) {
                sf::RectangleShape cardButton(sf::Vector2f(90, 125));
                cardButton.setPosition(x1, y1);
                cardButton.setTexture(mazoJugador1[i].getTexture());
                Game.draw(cardButton);
                x1 += 90;

                if (x1 >= 821) {
                    x1 = 0;
                    y1 += 125;
                }
            }
           



            // Dibuja todas las cartas en el mazo del jugador 2
            x2 = 1822;     // Posición inicial del mazo del jugador 2
            y2 = 540;
            for (int i = 0; i < SIZE2; i++) {
                sf::RectangleShape cardButton2(sf::Vector2f(90, 125));
                cardButton2.setPosition(x2, y2);
                cardButton2.setTexture(mazoJugador2[i].getTexture());
                Game.draw(cardButton2);
                x2 -= 90;

                if (x2 <= 1001) {
                    x2 = 1822;
                    y2 += 125;
                }
            }

            for (int i = 0; i < SIZE; i++) {
                sf::Sprite sprite2;
                sprite2.setTexture(*PileOfCards[i].getTexture()); // Configura la textura del sprite
                sprite2.setPosition(x3, y3);
                sprite2.setScale(tamanoX / sprite2.getLocalBounds().width, tamanoY / sprite2.getLocalBounds().height);
                Game.draw(sprite2);
                
            }
            Game.display();
        }
    }
    return 0;
}
