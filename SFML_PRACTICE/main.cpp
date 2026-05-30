#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML PRACTICE");

	// create
	sf::RectangleShape rectangle({ 400.f, 200.f });

	// color & outline
	rectangle.setFillColor(sf::Color::Magenta);
	rectangle.setOutlineThickness(25.f);
	rectangle.setOutlineColor(sf::Color::Yellow);

	// origin
	rectangle.setOrigin({ 200.f, 100.f });

	// transformation
	rectangle.setPosition({ 400.f, 300.f });
	rectangle.setRotation(sf::degrees(15.f));
	rectangle.setScale({ 1.1f, 1.f });


	// runtime loop 
	while (window.isOpen())
	{
		// handle events
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (event->is<sf::Event::Resized>())
			{
				std::cout << "Window: " << window.getSize().x << ", " << window.getSize().y << "\n";
				std::cout << "View: " << window.getView().getSize().x << ", " << window.getView().getSize().y << "\n";

				// set the view equal to window
				// at the center and same size
				sf::View view({ 400.f, 300.f }, sf::Vector2f(window.getSize()));
				window.setView(view);
			}
		}

		// fill window with color
		window.clear(sf::Color(0, 0, 0));

		// draw
		window.draw(rectangle);

		// display
		window.display();
	}

	return 0;
};