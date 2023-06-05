#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>


//in the standard namespace
using namespace std;

//variables
const int width{ 400 };
const int height{ 200 };

class Button
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;
	int state;

	Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, string text)
	{
		this->position = position;
		this->size = size;
		button.setPosition(position);
		button.setSize(size);
		button.setFillColor(color);
		font.loadFromFile("resources/RobotoMono-Light.ttf");
		this->text.setFont(font);
		this->text.setString(text);
		this->text.setCharacterSize(size.y / 3);
		this->text.setFillColor(sf::Color::Black);
		this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 2);

		this->button.setOrigin(this->button.getLocalBounds().width / 2, this->button.getLocalBounds().height / 2);
		this->text.setPosition(position);

		this->state = 0;
	}


	void run_python_script(string pythonScript)
	{
		// build command to run the Python script
		string command = "python " + pythonScript;

		// run the command using system()
		int result = system(command.c_str());

	}


	void update(sf::Vector2i mousePos, sf::Text text)
	{
		if (mousePos.x > position.x - size.x / 2 && mousePos.x < position.x + size.x / 2 && mousePos.y > position.y - size.y / 2 && mousePos.y < position.y + size.y / 2)
		{
			button.setFillColor(sf::Color(200, 200, 200));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				state = 1;

				cout << "BEPINEX" << endl;
				//run 'resources/bepinex.py'
				run_python_script("resources/bepinex.py");

				//set the text to INSTALLED
				this->text.setString("FINISHED");
				this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 2);


			}
			else
			{
				state = 2;
			}
		}
		else
		{
			button.setFillColor(sf::Color(255, 255, 255));
			state = 0;
		}
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}
};



int main()
{
	//set up window
	sf::RenderWindow window(sf::VideoMode(width, height), "daltonyx", sf::Style::None);
	sf::Event event;
	sf::Image icon;
	icon.loadFromFile("resources/Icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::RectangleShape titlebar(sf::Vector2f(width, 50));
	titlebar.setFillColor(sf::Color(30, 30, 30));

	sf::Text title;
	sf::Font font;
	font.loadFromFile("resources/RobotoMono-Light.ttf");
	title.setFont(font);
	title.setString("REGIONS OF RUIN LOADER");
	title.setCharacterSize(20);
	title.setFillColor(sf::Color::White);
	title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
	title.setPosition(width / 2, 20);

	sf::Text title2;
	title2.setFont(font);
	title2.setString("");
	title2.setCharacterSize(15);
	title2.setFillColor(sf::Color::White);
	title2.setOrigin(title2.getLocalBounds().width / 2, title2.getLocalBounds().height / 2);
	title2.setPosition(width / 2, 40);

	sf::Text info1;
	info1.setFont(font);
	info1.setString("INSTALLS BEPINEX TO STEAM'S REGIONS OF RUIN C DRIVE LOCATION");
	info1.setCharacterSize(10);
	info1.setFillColor(sf::Color::White);
	info1.setOrigin(info1.getLocalBounds().width / 2, info1.getLocalBounds().height / 2);
	info1.setPosition(width / 2, 70);

	//button
	Button button1(sf::Vector2f(width / 2, 120), sf::Vector2f(200, 50), sf::Color(255, 255, 255), "INSTALL");

	sf::RectangleShape exitbutton(sf::Vector2f(50, 50));
	exitbutton.setFillColor(sf::Color(30, 30, 30));
	exitbutton.setPosition(width - 50, 0);
	sf::Text x_text;
	x_text.setFont(font);
	x_text.setString("X");
	x_text.setCharacterSize(20);
	x_text.setFillColor(sf::Color::White);
	x_text.setOrigin(x_text.getLocalBounds().width / 2, x_text.getLocalBounds().height / 2);
	x_text.setPosition(width - 25, 20);

	sf::Text credit;
	credit.setFont(font);
	credit.setString("<3 Daltonyx");
	credit.setCharacterSize(10);
	credit.setFillColor(sf::Color::White);
	credit.setOrigin(credit.getLocalBounds().width / 2, credit.getLocalBounds().height / 2);
	credit.setPosition(width / 2, height - 20);




	//look for events while the window is open
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
				}
			}

			//if mouse is clicked on the exit button
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (sf::Mouse::getPosition(window).x > width - 50 && sf::Mouse::getPosition(window).x < width && sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < 50)
					{
						window.close();
					}
				}
			}
		}
		//clear the window
		window.clear(sf::Color(50, 50, 50));
		window.draw(titlebar);
		window.draw(title);
		window.draw(title2);
		window.draw(info1);
		button1.update(sf::Mouse::getPosition(window), button1.text);
		button1.draw(window);

		window.draw(exitbutton);
		window.draw(x_text);

		window.draw(credit);


		//draw the window
		window.display();
	}
	//return okay if the program exits properly
	return 0;
}