#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

int linechart()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Line Chart");

	int data[5] = { 1, 3, 1, 2, 5 };
	int dataLength = sizeof(data) / sizeof(data[0]);
	int data_max = *std::max_element(data, data + dataLength);

	// shapes
	sf::RectangleShape line;
	line.setFillColor(sf::Color::Blue);

	sf::CircleShape dot;
	dot.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{

		float w = static_cast<float>(window.getSize().x);
		float h = static_cast<float>(window.getSize().y);
		float window_min = static_cast<float>(std::min(w, h));


		float space = w / dataLength;
		float scale = 0.9f * h / data_max;
		float radius = 0.02f * window_min;
		float width = radius / 2;

		dot.setRadius(radius);
		dot.setOrigin({ radius, radius });

		line.setSize({ 100.f, width });
		line.setOrigin({ 0.f, width / 2 });

		float x_old = 0.f;
		float y_old = 0.f;


		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Yellow);

		for (int i = 0; i < dataLength; i++)
		{
			float x = (i + 0.5f) * space;
			float y = h - (data[i] * scale);

			dot.setPosition({ x, y });
			window.draw(dot);

			if (i > 0)
			{


				float  dx = x_old - x;
				float dy = y_old - y;
				float angle = std::atan2(dy, dx);
				float length = std::sqrt(dx * dx + dy * dy);

				line.setRotation(sf::radians(angle));
				line.setPosition({ x, y });
				line.setSize({ length, width });

				window.draw(line);
			}

			x_old = x;
			y_old = y;
		}


		window.display();
	}

	return 0;
}