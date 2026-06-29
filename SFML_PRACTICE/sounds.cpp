#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int sounds()
{
	sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "Sounds");
	window.setKeyRepeatEnabled(false);

	sf::SoundBuffer buffer_button;
	sf::SoundBuffer buffer_coin;
	sf::SoundBuffer buffer_gun;

	if (!buffer_button.loadFromFile("./sounds/button.mp3"))
	{
		std::cerr << "failed to load ./sounds/button.mp3\n";
	}
	if (!buffer_coin.loadFromFile("./sounds/coin.mp3"))
	{
		std::cerr << "failed to load ./sounds/coin.mp3\n";
	}
	if (!buffer_gun.loadFromFile("./sounds/gun.mp3"))
	{
		std::cerr << "failed to load ./sounds/gun.mp3\n";
	}

	sf::Sound sound_button(buffer_button);
	sf::Sound sound_coin(buffer_coin);
	sf::Sound sound_gun(buffer_gun);

	sound_gun.setLooping(true);
	sound_coin.setPitch(0.5f);
	sound_button.setVolume(140.f);

	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (auto keyPress = event->getIf<sf::Event::KeyPressed>())
			{
				switch (keyPress->scancode)
				{
				case sf::Keyboard::Scancode::S:
					sound_button.play();
					break;
				case sf::Keyboard::Scancode::A:
					sound_coin.play();
					break;
				case sf::Keyboard::Scancode::D:
					sound_gun.play();
					break;
				}
			}
			else if (auto keyRelease = event->getIf<sf::Event::KeyReleased>())
			{
				switch (keyRelease->scancode)
				{
				case sf::Keyboard::Scancode::D:
					sound_gun.stop();
					break;
				}
			}
		}

		window.clear(sf::Color::Yellow);
		
		window.display();
	}

	return 0;
}