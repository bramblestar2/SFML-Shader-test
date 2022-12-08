#pragma once
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	//Free memory
	virtual ~Window();

	void run();
	void render();
	void update();
	void updateDt();
	void updateSFMLEvents();
private:
	void initWindow();
	
	sf::Clock dtClock, timeClock;
	double dt;

	sf::RenderWindow* window;
	sf::Event event;

	sf::Shader shader;

	sf::VertexArray arr;
};

