#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>


int piano()
{
	sf::RenderWindow window(sf::VideoMode({ 1000, 300 }), "Piano");

	window.setKeyRepeatEnabled(false);

	sf::SoundBuffer c_note;
	sf::SoundBuffer d_note;
	sf::SoundBuffer meow;


	if (!c_note.loadFromFile("./sounds/c_note.mp3") || !d_note.loadFromFile("./sounds/d_note.mp3") || !meow.loadFromFile("./sounds/meow.mp3"))
	{
		std::cerr << "Error: Failed to load sound effect\n";
	}

	sf::SoundBuffer buffers[] = { c_note, d_note, meow };


	int activeBuffer = 0;

	sf::Sound sound_D1(buffers[activeBuffer]); sound_D1.setPitch(std::pow(2, -10 / 12.f));
	sf::Sound sound_E1(buffers[activeBuffer]); sound_E1.setPitch(std::pow(2, -8 / 12.f));
	sf::Sound sound_F1(buffers[activeBuffer]); sound_F1.setPitch(std::pow(2, -7 / 12.f));
	sf::Sound sound_G1(buffers[activeBuffer]); sound_G1.setPitch(std::pow(2, -5 / 12.f));
	sf::Sound sound_A1(buffers[activeBuffer]); sound_A1.setPitch(std::pow(2, -3 / 12.f));
	sf::Sound sound_B1(buffers[activeBuffer]); sound_B1.setPitch(std::pow(2, -1 / 12.f));
	sf::Sound sound_C2(buffers[activeBuffer]);
	sf::Sound sound_D2(buffers[activeBuffer]); sound_D2.setPitch(std::pow(2, 2 / 12.f));
	sf::Sound sound_E2(buffers[activeBuffer]); sound_E2.setPitch(std::pow(2, 4 / 12.f));
	sf::Sound sound_F2(buffers[activeBuffer]); sound_F2.setPitch(std::pow(2, 5 / 12.f));
	sf::Sound sound_G2(buffers[activeBuffer]); sound_G2.setPitch(std::pow(2, 7 / 12.f));
	sf::Sound sound_A2(buffers[activeBuffer]); sound_A2.setPitch(std::pow(2, 9 / 12.f));
	sf::Sound sound_B2(buffers[activeBuffer]); sound_B2.setPitch(std::pow(2, 11 / 12.f));
	sf::Sound sound_C3(buffers[activeBuffer]); sound_C3.setPitch(2.f);

	// keyboard
	sf::Keyboard::Scan keys[] =
	{
		sf::Keyboard::Scan::Tab,
		sf::Keyboard::Scan::Q,
		sf::Keyboard::Scan::W,
		sf::Keyboard::Scan::E,
		sf::Keyboard::Scan::R,
		sf::Keyboard::Scan::T,
		sf::Keyboard::Scan::Y,
		sf::Keyboard::Scan::U,
		sf::Keyboard::Scan::I,
		sf::Keyboard::Scan::O,
		sf::Keyboard::Scan::P,
		sf::Keyboard::Scan::LBracket,
		sf::Keyboard::Scan::RBracket,
		sf::Keyboard::Scan::Backslash,
		sf::Keyboard::Scan::C
	};

	// piano white keys
	sf::RectangleShape whiteKey;
	whiteKey.setFillColor(sf::Color::White);
	whiteKey.setOutlineColor(sf::Color::Black);
	whiteKey.setOutlineThickness(-1.f);


	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (event->is<sf::Event::Resized>())
			{
				window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(window.getSize()))));
			}
			else if (auto key = event->getIf<sf::Event::KeyPressed>())
			{
				if (key->scancode == keys[0]) sound_D1.play();
				if (key->scancode == keys[1]) sound_E1.play();
				if (key->scancode == keys[2]) sound_F1.play();
				if (key->scancode == keys[3]) sound_G1.play();
				if (key->scancode == keys[4]) sound_A1.play();
				if (key->scancode == keys[5]) sound_B1.play();
				if (key->scancode == keys[6]) sound_C2.play();
				if (key->scancode == keys[7]) sound_D2.play();
				if (key->scancode == keys[8]) sound_E2.play();
				if (key->scancode == keys[9]) sound_F2.play();
				if (key->scancode == keys[10]) sound_G2.play();
				if (key->scancode == keys[11]) sound_A2.play();
				if (key->scancode == keys[12]) sound_B2.play();
				if (key->scancode == keys[13]) sound_C3.play();
				if (key->scancode == keys[14])
				{
					activeBuffer = (activeBuffer + 1) % std::size(buffers);
					sound_D1.setBuffer(buffers[activeBuffer]);
					sound_E1.setBuffer(buffers[activeBuffer]);
					sound_F1.setBuffer(buffers[activeBuffer]);
					sound_G1.setBuffer(buffers[activeBuffer]);
					sound_A1.setBuffer(buffers[activeBuffer]);
					sound_B1.setBuffer(buffers[activeBuffer]);
					sound_C2.setBuffer(buffers[activeBuffer]);
					sound_D2.setBuffer(buffers[activeBuffer]);
					sound_E2.setBuffer(buffers[activeBuffer]);
					sound_F2.setBuffer(buffers[activeBuffer]);
					sound_G2.setBuffer(buffers[activeBuffer]);
					sound_A2.setBuffer(buffers[activeBuffer]);
					sound_B2.setBuffer(buffers[activeBuffer]);
					sound_C3.setBuffer(buffers[activeBuffer]);
				}
			}
		}

		float window_w = window.getView().getSize().x;
		float window_h = window.getView().getSize().y;

		window.clear(sf::Color::Black);

		// draw piano
		int key_n = 14;
		float key_w = window_w / key_n;
		for (int i = 0; i < key_n; i++)
		{
			// major
			whiteKey.setSize({ key_w, window_h });
			whiteKey.setPosition({ i * key_w, 0.f });
			if (sf::Keyboard::isKeyPressed(keys[i]))
			{
				whiteKey.setFillColor(sf::Color(0, 170, 255));
			}
			else
			{
				whiteKey.setFillColor(sf::Color::White);
			}

			window.draw(whiteKey);

			// minor
			if (i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 7 || i == 8 || i == 10 || i == 11 || i == 12)
			{
				whiteKey.setSize({ key_w / 2, window_h * 0.6f });
				whiteKey.setPosition({ (i - 0.25f) * key_w, 0.f });
				whiteKey.setFillColor(sf::Color::Black);
				window.draw(whiteKey);
			}

		}

		window.display();
	}
	return 0;
}