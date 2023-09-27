#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Deck.h"
#include <algorithm> 
#include <random> 


using namespace std;

int main()
{
    bool usada = false;  // Para marcar si la carta se ha "eliminado" de la mano del jugador
    bool repartida = false;  // Para marcar si la carta se ha repartido
    bool reachedMiddle = false;
    bool closed = false;
    sf::RenderWindow renderWindow(sf::VideoMode(1920, 1080), "UNO");
    renderWindow.setFramerateLimit(30);
    sf::Event event;

    sf::Texture texture;
    texture.loadFromFile("../assets/Images/Menu.png");
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
    DeckButton.loadFromFile("/assets/Images/UNO cards HD/uno.png");
    sf::Sprite DeckButton1(DeckButton);
    DeckButton1.setScale(90.0f / DeckButton1.getLocalBounds().width, 125.0f / DeckButton1.getLocalBounds().height);
    DeckButton1.setPosition(851, 240);

    for (int i = 1; i <= 40; i++) { 
        string filename = "C:\\Users\\ema_9\\Documents\\Visual Studio 2022\\Proyectos\\Test project\\images\\Images\\UNOCARDS\\card" + std::to_string(i) + ".png";

        if (!cardTextures[i - 1].loadFromFile(filename)) {
            std::cerr << "Error al cargar la textura de la carta " << i << std::endl;
            
        }
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

    Cards PileOfCards[104];
    Cards mazoJugador1[20];
    Cards mazoJugador2[20];
    int cartasDisponibles = 80;
    // Copiar las 7 primeras cartas mezcladas al mazo del jugador 1
    for (int i = 0; i < 7; i++) {
        mazoJugador1[i] = cartas[i];
        cartas[i].repartida = true; // Marca la carta como repartida
        cartasDisponibles--;
    }



    // Copiar las siguientes 7 cartas mezcladas al mazo del jugador 2
    for (int i = 0; i < 7; i++) {
        mazoJugador2[i] = cartas[i];
        cartas[i].repartida = true; // Marca la carta como repartida
        cartasDisponibles--;
    }



    int x = 0;         //Posición inicial del mazo del jugador 1
    int y = 540;

    int SIZE = 0;
    int SIZE1 = 7;
    int SIZE2 = 7;


    sf::RectangleShape cardButtons[20]; // Arreglo de botones invisibles para las cartas

    
    for (int i = 0; i < SIZE1; i++) {
        cardButtons[i] = sf::RectangleShape(sf::Vector2f(90, 125)); // Tamaño del botón igual al de las cartas
        cardButtons[i].setPosition(x, y);
        cardButtons[i].setTexture(mazoJugador1[i].getTexture()); // Asignar la textura de la carta al botón
        x += 90;

        if (x >= 821) {
            reachedMiddle = true; // Se alcanzó la mitad de la pantalla
            x = 0;
            if (reachedMiddle == true) {
                y += 125;
            }
        }
    }


    if (closed == true) {
        while (Game.isOpen()) {
            while (Game.pollEvent(event1)) {
                if (event1.type == sf::Event::Closed) {
                    Game.close();
                }

                if (event1.type == sf::Event::MouseButtonPressed) {
                    if (event1.mouseButton.button == sf::Mouse::Left) {
                        if (SIZE1 < 20 && cartasDisponibles > 0) {
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(Game);
                            sf::FloatRect buttonBounds = DeckButton1.getGlobalBounds();

                            if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {                               
                                mazoJugador1[SIZE1] = cartas[cartasDisponibles - 1];
                                cartas[cartasDisponibles - 1].repartida = true; // Marca la carta como repartida
                                cartasDisponibles--; // Reduce el número de cartas disponibles en el mazo principal
                                SIZE1++; // Incrementa el tamaño del mazo del jugador 1
                                sf::RectangleShape cardButton(sf::Vector2f(90, 125));
                                cardButton.setPosition(x, y);
                                cardButton.setTexture(mazoJugador1[SIZE1 - 1].getTexture()); // Asigna la textura de la carta al botón
                                cardButtons[SIZE1 - 1] = cardButton;
                            }
                        }
                    }
                    if (event1.mouseButton.button == sf::Mouse::Right) {
                        if (SIZE2 < 20 && cartasDisponibles > 0) {   // Verifica que el tamaño del mazo del jugador 2 sea menor que 20
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(Game);
                            sf::FloatRect buttonBounds = DeckButton1.getGlobalBounds();

                            if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
                                // Agrega una carta del mazo principal a mazoJugador2
                                mazoJugador2[SIZE2] = cartas[cartasDisponibles - 1];
                                cartas[cartasDisponibles - 1].repartida = true;
                                cartasDisponibles--;
                                SIZE2++;
                            }
                        }
                    }
                }

                if (event1.type == sf::Event::MouseButtonPressed) {
                    if (event1.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(Game);

                        // Verificar si se hizo clic en alguno de los botones invisibles
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
                                break; // Sal del bucle una vez que se juegue una carta
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

            x = 0;         //Posición inicial del mazo del jugador 1
            y = 540;
            int x1 = 911;      // Posición en la mitad de la pantalla para el mazo total
            int x2 = 1822;     // Posición inicial del mazo del jugador 2
            int y1 = 240;      // Posición vertical del mazo total
            int y2 = 540;
            int x3 = 961;
            int y3 = 240;

            // ...
            for (int i = 0; i < SIZE1; i++) {
                sf::RectangleShape cardButton(sf::Vector2f(90, 125)); // Crea un botón para la carta
                cardButton.setPosition(x, y);
                cardButton.setTexture(mazoJugador1[i].getTexture()); // Asigna la textura de la carta al botón
                Game.draw(cardButton); // Dibuja el botón en su posición
                x += 90;

                if (x >= 821) {
                    reachedMiddle = true; // Se alcanzó la mitad de la pantalla
                    x = 0;
                    if (reachedMiddle == true) {
                        y += 125;
                    }
                }
            }
           



            // Dibuja todas las cartas en el mazo del jugador 2
            for (int i = 0; i < SIZE2; i++) {
                sf::Sprite sprite2(*(mazoJugador2[i].getTexture()));
                sprite2.setPosition(x2, y2);
                sprite2.setScale(tamanoX / sprite2.getLocalBounds().width, tamanoY / sprite2.getLocalBounds().height);
                Game.draw(sprite2);
                x2 -= 90;

                if (x2 <= 1001) {
                    reachedMiddle = true; // Se alcanzó la mitad de la pantalla
                    x2 = 1822;
                    if (reachedMiddle == true) {
                        y2 += 125;
                    }
                }
            }

            for (int i = 0; i < SIZE; i++) {
                sf::Sprite sprite2;
                sprite2.setTexture(*PileOfCards[i].getTexture()); // Configura la textura del sprite
                sprite2.setPosition(x3, y3);
                sprite2.setScale(tamanoX / sprite2.getLocalBounds().width, tamanoY / sprite2.getLocalBounds().height);
                Game.draw(sprite2);
                std::cout << "PileOfCards[" << i << "]: Color = " << PileOfCards[i].getColor() << ", Number = " << PileOfCards[i].getNumber() << std::endl;
            }
            Game.display();
        }
    }
    return 0;
}
