#include<SFML/Graphics.hpp>
#include <iostream>

class Mouse
{
public:
	// states
	bool isPressed = false;
	bool onPress = false;
	bool onRelease = false;

	// function - update states
	void Update()
	{
		// reset onPress & onRelease
		onPress = false;
		onRelease = false;

		// when mouse is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			// when mouse isn't pressed yet
			if (!isPressed)
			{
				onPress = true;
			}
			isPressed = true;
		}
		else
		{
			// when mouse is still pressed
			if (isPressed)
			{
				onRelease = true;
			}
			isPressed = false;
		}
	}
};

class Button : public sf::Drawable, public sf::Transformable
{
	sf::RectangleShape m_shape;
	sf::Text m_text;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();

		target.draw(m_shape, states);
		target.draw(m_text, states);
	}

public:
	Button(const sf::Font& font, const std::string& text, sf::Vector2f size = { 100.f, 50.f }, sf::Color color = sf::Color::White, unsigned int characterSize = 24) : m_shape(size), m_text(font)
	{
		m_shape.setSize(size);
		m_shape.setFillColor(color);

		m_text.setString(text);
		m_text.setFillColor(sf::Color::Black);
		m_text.setCharacterSize(characterSize);
		auto bounds = m_text.getLocalBounds();
		m_text.setOrigin({
			bounds.position.x + bounds.size.x / 2.f,
			bounds.position.y + bounds.size.y / 2.f
			});
		m_text.setPosition({ size.x / 2.f, size.y / 2.f
			});

	};

	sf::Vector2f getSize()
	{
		return this->m_shape.getSize();
	}
};

int counter()
{
	sf::Font font;
	if (!font.openFromFile("./monda.ttf"))
	{
		std::cerr << "Error: Failed to load font from ./monda.ttf\n";
		return -1;
	}
	// create mouse object
	Mouse mouse;
	Button button(font, "Hello");
	button.setOrigin(button.getSize() / 2.f);
	button.setPosition({ 200, 250 });


	// create window
	sf::RenderWindow window(sf::VideoMode({ 400, 500 }), "Counter");

	while (window.isOpen())
	{
		// handle events
		if (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		mouse.Update();

		if (mouse.onPress)
		{
			std::cout << "mouse pressed\n";
		}
		if (mouse.onRelease)
		{
			std::cout << "mouse released\n";
		}

		window.clear(sf::Color::Black);

		window.draw(button);

		window.display();
	}
	return 0;
}