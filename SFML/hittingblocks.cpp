#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 500), "SFML");

	//Bottom grey box
    sf::RectangleShape bottom(sf::Vector2f(2000, 100));
    sf::Color farba(100, 100, 100);
	bottom.setFillColor(farba);
	bottom.setPosition(0, 400);
    bottom.setOutlineColor(sf::Color::Cyan);
    bottom.setOutlineThickness(5);
    
    //collision line
	sf::RectangleShape line(sf::Vector2f(5, 300));
	line.setPosition(95, 100);
	line.setFillColor(sf::Color::Cyan);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

		window.draw(bottom);
        window.draw(line);

        window.display();
    }

	return 0;
}