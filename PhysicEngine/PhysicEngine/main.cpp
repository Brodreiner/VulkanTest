#include <chrono>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	std::vector<sf::CircleShape> circleVector;

	sf::Texture blockRedTexture;
	if (!blockRedTexture.loadFromFile("png/block.png"))
		throw std::runtime_error("Unable to load Texture!");

	sf::Sprite blockRedSprite;
	blockRedSprite.setTexture(blockRedTexture);


	sf::Font font;
	if (!font.loadFromFile("DooM.ttf"))
		throw std::runtime_error("Unable to load DooM.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("Hello World!");
	text.setColor(sf::Color::Red);


	for (auto i = 0; i < 10000; ++i)
	{
		sf::CircleShape circle(10);
		circle.setPosition(10 + 10*(i%100), 100+10*(i/100));
		circleVector.emplace_back(std::move(circle));
	}


	auto lastTimePoint = std::chrono::high_resolution_clock::now();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		auto currentTimePoint = std::chrono::high_resolution_clock::now();
		auto timeDelta = currentTimePoint - lastTimePoint;
		lastTimePoint = currentTimePoint;


		auto xyz = std::chrono::duration_cast<std::chrono::microseconds>(timeDelta).count();
		auto fps = (int)(1000000.0 / xyz);
		auto fpsString = std::to_string(fps);
		text.setString(fpsString);

		window.clear();
		for(auto& circle : circleVector)
		{
			window.draw(circle);
		}
		window.draw(text);
		window.display();
	}

	return 0;
}