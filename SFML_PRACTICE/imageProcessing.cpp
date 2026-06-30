#include <SFML/Graphics.hpp>

int imageProcessing()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Image Processing");

	sf::Image image("./images/mouse.png");
	unsigned int image_w = image.getSize().x;
	unsigned int image_h = image.getSize().y;

	// image processing
	for (unsigned int i = 0; i < image_w; i++)
	{
		for (unsigned int j = 0; j < image_h; j++)
		{
			// get color of pixel
			sf::Color color = image.getPixel({ i, j });

			uint8_t value = (color.r + color.g + color.b) / 3;
			if (value < 128) value = 0;
			else		 value = 255;

			color.r = value;
			color.g = value;
			color.b = value;

			// set color of pixel
			image.setPixel({ i, j }, color);
		}
	}


	sf::Texture texture(image);
	texture.setSmooth(true);

	sf::Sprite sprite(texture);
	float scale = static_cast<float>(window.getSize().x) / image_w;
	sprite.setScale({ scale, scale });


	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (auto keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::S)
				{
					bool success = image.saveToFile("./images/edited.png");
				}
			}
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);

		window.display();
	}

	return 0;
}