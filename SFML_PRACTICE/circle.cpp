#include <SFML/Graphics.hpp>
#include <iostream>


int circle()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Circle", sf::State::Windowed ,settings);

	// create
	sf::CircleShape circle(100.f, 60);

	// color & outline
	circle.setFillColor(sf::Color::Yellow);
	circle.setOutlineThickness(25.f);
	circle.setOutlineColor(sf::Color::Green);

	// origin
	circle.setOrigin({ 100.f, 100.f });

	// transformation
	circle.setPosition({ 400.f, 300.f });

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
		window.draw(circle);

		// display
		window.display();
	}

	return 0;
};