#include <SFML/Graphics.hpp>
#include <iostream>

struct MouseState
{
	bool isLeftPressed = false;
	bool isRightPressed = false;
	bool isMiddlePressed = false;
	bool isScrollUp = false;
	bool isScrollDown = false;
};


void drawMouse(sf::RenderWindow& window, const MouseState& mouseState)
{
	sf::Vector2f clickSize({ 150, 150 });
	sf::Color idleColor(sf::Color::White);
	sf::Color activeColor(sf::Color::Blue);
	sf::Color outlineColor(sf::Color::Black);
	float outlineThickness = 3.f;

	sf::RectangleShape leftClick(clickSize);
	leftClick.setFillColor(mouseState.isLeftPressed ? activeColor : idleColor);
	leftClick.setOutlineColor(outlineColor);
	leftClick.setOutlineThickness(outlineThickness);
	leftClick.setPosition({ 250, 200 });

	sf::RectangleShape rightClick(clickSize);
	rightClick.setFillColor(mouseState.isRightPressed ? activeColor : idleColor);
	rightClick.setOutlineColor(outlineColor);
	rightClick.setOutlineThickness(outlineThickness);
	rightClick.setPosition({ 410, 200 });

	sf::Vector2f scrollSize({ 10.f, 30.f });
	sf::RectangleShape mouseScrollUp(scrollSize);
	mouseScrollUp.setPosition({ 400.f, 200.f });
	mouseScrollUp.setFillColor(mouseState.isScrollUp ? activeColor : idleColor);
	mouseScrollUp.setOutlineColor(outlineColor);
	mouseScrollUp.setOutlineThickness(outlineThickness);


	sf::RectangleShape mouseScrollDown(scrollSize);
	mouseScrollDown.setPosition({ 400.f, 320.f });
	mouseScrollDown.setFillColor(mouseState.isScrollDown ? activeColor : idleColor);
	mouseScrollDown.setOutlineColor(outlineColor);
	mouseScrollDown.setOutlineThickness(outlineThickness);


	sf::Vector2f middleSize({ 10.f, 90.f });
	sf::RectangleShape middleMouse(middleSize);
	middleMouse.setPosition({ 400.f, 230.f });
	middleMouse.setOutlineColor(outlineColor);
	middleMouse.setOutlineThickness(outlineThickness);
	middleMouse.setFillColor(mouseState.isMiddlePressed ? activeColor : idleColor);

	sf::RectangleShape body({ 310.f, 200.f });
	body.setPosition({ 250.f, 350.f });
	body.setFillColor(sf::Color::White);
	body.setOutlineThickness(4.f);
	body.setOutlineColor(sf::Color::Black);


	window.draw(leftClick);
	window.draw(rightClick);
	window.draw(mouseScrollUp);
	window.draw(mouseScrollDown);
	window.draw(middleMouse);
	window.draw(body);
}



int mouseInput()
{
	sf::Clock scrollClock;
	float scrollFlashTime = 0.15f;

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Mouse Input");
	sf::Font font;

	MouseState mouseState;


	if (!font.openFromFile("./monda.ttf"))
	{
		std::cout << "Error loading font!";
	}

	sf::Text mousePosText(font);
	mousePosText.setPosition({ 10.f, 570.f });
	mousePosText.setCharacterSize(16);

	sf::CircleShape mouseTracker(30.f, 100);

	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == sf::Mouse::Button::Left)
				{
					mouseState.isLeftPressed = true;
				}
				else if (mousePressed->button == sf::Mouse::Button::Right)
				{
					mouseState.isRightPressed = true;
				}
				else if (mousePressed->button == sf::Mouse::Button::Middle)
				{
					mouseState.isMiddlePressed = true;
				}
			}
			else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (mouseReleased->button == sf::Mouse::Button::Left)
					mouseState.isLeftPressed = false;

				else if (mouseReleased->button == sf::Mouse::Button::Right)
					mouseState.isRightPressed = false;

				else if (mouseReleased->button == sf::Mouse::Button::Middle)
					mouseState.isMiddlePressed = false;
			}
			else if (const auto* mouseScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				if (mouseScrolled->delta > 0)
				{
					mouseState.isScrollUp = true;
					mouseState.isScrollDown = false;
				}
				else if (mouseScrolled->delta < 0)
				{
					mouseState.isScrollDown = true;
					mouseState.isScrollUp = false;
				}
				scrollClock.restart();
			}

			if (scrollClock.getElapsedTime().asSeconds() > scrollFlashTime)
			{
				mouseState.isScrollDown = false;
				mouseState.isScrollUp = false;
			}

			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			mousePosText.setString("x: " + std::to_string(mousePos.x) + " y: " + std::to_string(mousePos.y));

			mouseTracker.setPosition(sf::Vector2f(mousePos));
			mouseTracker.setFillColor(sf::Color::Magenta);
			mouseTracker.setOrigin({ 15.f, 15.f });
		}

		window.clear(sf::Color::Black);

		drawMouse(window, mouseState);
		window.draw(mousePosText);
		window.draw(mouseTracker);

		window.display();
	}


	return 0;
}