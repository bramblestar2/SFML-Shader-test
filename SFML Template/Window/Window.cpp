#include "Window.h"
#include <time.h>

Window::Window() : arr(sf::LinesStrip, 100)
{
	initWindow();
	srand(time(NULL));

	for (int i = 0; i < arr.getVertexCount(); i++)
		arr[i] = sf::Vertex(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));

	shader.loadFromFile("shader.frag", sf::Shader::Fragment);
	shader.setUniform("blur_radius", sf::Vector2f(0.01, 0.01));
}

Window::~Window()
{
	delete window;
}

void Window::run()
{
	while (window->isOpen())
	{
		update();
		updateDt();
		updateSFMLEvents();
		render();
	}
}

void Window::render()
{
	window->clear();

	sf::RenderTexture t;
	t.create(window->getSize().x, window->getSize().y);

	shader.setUniform("blur_radius", sf::Vector2f(sin(timeClock.getElapsedTime().asSeconds())/2, sin(timeClock.getElapsedTime().asSeconds())/2));

	t.draw(arr);
	sf::Texture a;
	a.loadFromFile("R.png");
	t.draw(sf::Sprite(a));
	t.setSmooth(true);
	
	window->draw(sf::Sprite(t.getTexture()), &shader);
	//window->draw(sf::Sprite(t.getTexture()));

	window->display();
}

void Window::update()
{
}

void Window::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Window::updateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
				window->close();
				break;
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
						window->close();
						break;
				}
				break;
		}
	}
}

void Window::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(400, 400), "TITLE", sf::Style::Default);
	window->setFramerateLimit(60);
}
