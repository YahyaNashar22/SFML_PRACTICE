#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML PRACTICE");


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
		}
	}

	return 0;
};