#include <SFML/Graphics.hpp>

int generateRandomColor(int random)
{
	int color = 150 + (255 - 100) * random;
	return color;
}
 int barchart()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Bar Chart");

	unsigned int w = window.getSize().x;
	unsigned int h = window.getSize().y;

	int data[5] = { 1, 4, 3, 6, 1 };
	int dataLength = sizeof(data) / sizeof(data[0]);

	sf::RectangleShape bar;


	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);

		for (int i = 0; i < dataLength; i++)
		{
			bar.setSize({ 100.f, data[i] * 100.f });
			bar.setPosition({ (i +0.f ) * static_cast<float>(w) / dataLength,static_cast<float>(h)});
			bar.setOrigin({ bar.getSize().x / 2, bar.getSize().y});
			bar.setFillColor(sf::Color(generateRandomColor(4*i), generateRandomColor(10*i), generateRandomColor(3*i)));
			window.draw(bar);
		}

		window.display();
	}

	return 0;
}