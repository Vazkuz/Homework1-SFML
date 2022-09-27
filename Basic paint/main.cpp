#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>

void ChangeColor(sf::Color& brushColor)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        brushColor = sf::Color::Green;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        brushColor = sf::Color::Red;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        brushColor = sf::Color::Blue;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        brushColor = sf::Color::Yellow;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        brushColor = sf::Color::Magenta;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
        brushColor = sf::Color::Black;
}

void ChangeShape(int& brushPointCount) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        brushPointCount = 100; // Circle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        brushPointCount = 3; // Triangle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        brushPointCount = 4; // Square
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        brushPointCount = 5; // Pentagon
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        brushPointCount = 8; // Octagon
}

int main()
{
    //::getFullscreenModes()[0]
    sf::RenderWindow window(sf::VideoMode(1280,720), "Basic painter!");
    //window.clear(sf::Color::White);
    window.display();

    float brushSize = 20.f;
    float lastBrushSize = brushSize;
    int brushPointCount = 100;
    sf::Color brushColor = sf::Color::Green;
    std::string filename = "Homework 1 Screenshot.png";
    bool isBrushOn = true;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                brushSize += 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                brushSize -= 1.f;
                if (brushSize < 0)
                    brushSize = 0;
            }

            ChangeColor(brushColor);
            ChangeShape(brushPointCount);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                sf::Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                texture.copyToImage().saveToFile(filename);
                std::cout << "Screenshot saved to " << filename << std::endl;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (isBrushOn) {
                    lastBrushSize = brushSize;
                    brushSize = 0.f;
                }
                else {
                    brushSize = lastBrushSize;
                }
                isBrushOn = !isBrushOn;
            }
        }

        sf::CircleShape shape(brushSize, brushPointCount);
        shape.setFillColor(brushColor);
        
        shape.setPosition(sf::Mouse::getPosition(window).x - brushSize /2., sf::Mouse::getPosition(window).y - brushSize / 2.);
        window.draw(shape);
        window.display();
    }

    return 0;
}
