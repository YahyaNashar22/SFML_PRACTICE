#include <SFML/Graphics.hpp>
#include <iostream>

int keyboardInput()
{
	sf::RenderWindow window(sf::VideoMode({ 1024, 768 }), "Keyboard Input");

	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (auto* key = event->getIf<sf::Event::KeyPressed>())
			{
				switch (key->code)
				{
				case sf::Keyboard::Key::W:
					std::cout << "FORWARRRDD !!";
					break;
				default:
					std::cout << sf::Keyboard::getDescription(key->scancode).toAnsiString();
					std::cout << " is pressed\n";
					break;
				}
			}
		}

		window.clear(sf::Color::Blue);

		window.display();
	}

	return 0;
}