#include<SFML/Graphics.hpp>
#include <iostream>
#include <functional>

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
	std::function<void()> m_onClick;

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

	bool contains(sf::Vector2f point) const
	{
		sf::Transform inverse = getTransform().getInverse();
		sf::Vector2f localPoint = inverse.transformPoint(point);

		return m_shape.getGlobalBounds().contains(localPoint);
	}

	void setOnClick(std::function<void()> callback)
	{
		m_onClick = callback;
	}

	void handleClick(sf::Vector2f mousePosition)
	{
		if (contains(mousePosition) && m_onClick)
		{
			m_onClick();
		}
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

	// create button objects
	Button incrementButton(font, "+");
	incrementButton.setPosition({ 100, 250 });

	Button decrementButton(font, "-");
	decrementButton.setPosition({ 220, 250 });

	Button resetButton(font, "reset", { 220.f, 50.f });
	resetButton.setPosition({ 100, 350 });

	// create counter text
	int count = 0;
	sf::Text counterText(font);
	counterText.setString(std::to_string(count));
	auto counterTextBounds = counterText.getLocalBounds();
	counterText.setOrigin({counterTextBounds.size.x / 2.f , counterTextBounds.size.y / 2.f});
	counterText.setPosition({200.f, 150.f});

	incrementButton.setOnClick([&]() {
		count++;
		counterText.setString(std::to_string(count));
		});

	decrementButton.setOnClick([&]() {
		count--;
		counterText.setString(std::to_string(count));
		});

	resetButton.setOnClick([&]() {
		count = 0;
		counterText.setString(std::to_string(count));
		});

	// create window
	sf::RenderWindow window(sf::VideoMode({ 400, 500 }), "Counter");

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
		mouse.Update();
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF{
		    static_cast<float>(mousePos.x),
		    static_cast<float>(mousePos.y)
		};

		if (mouse.onPress)
		{
			incrementButton.handleClick(mousePosF);
			decrementButton.handleClick(mousePosF);
			resetButton.handleClick(mousePosF);
		}

		window.clear(sf::Color::Black);

		window.draw(counterText);
		window.draw(incrementButton);
		window.draw(decrementButton);
		window.draw(resetButton);

		window.display();
	}
	return 0;
}