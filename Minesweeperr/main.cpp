//I am using library called SFML(Simple Fast Multimedia Library) because i do not know how to do directx or opengl programming
//Here i include the necceasry files for it to work
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//this is the Game header that contains the Game class that i made
//inside of it is the whole game
#include "Game.h"

int main() {
	{
	//inputing the width-height
		//textbox-rectangle for input text message
		sf::RectangleShape ir;
		ir.setFillColor(sf::Color::Transparent);
		ir.setOutlineColor(sf::Color::Black);
		ir.setOutlineThickness(2);
		ir.setSize(sf::Vector2f(160, 50));
		ir.setPosition(sf::Vector2f(70, 74));
		//input string
		sf::String pi;
		//font
		sf::Font font; font.loadFromFile("fonts/times.ttf");
		//input text
		sf::Text it("", font, 30);
		it.setPosition(sf::Vector2f(110, 78));
		it.setFillColor(sf::Color::Black);
		//input text message
		sf::Text pt("Input width and height then press enter,\n       in format WIDTHxHEIGHT:\n         (max is 65x65,min is 8x8)",font,18);
		pt.setFillColor(sf::Color::Black);
		pt.setPosition(sf::Vector2f(6, 0));
		//input window
		sf::RenderWindow inint;
		inint.create(sf::VideoMode(300, 160), "Input Size");
		inint.setFramerateLimit(30);
		//loop for window events
		while (inint.isOpen()) {
			//event handling 
			sf::Event event;
			while (inint.pollEvent(event)) {
				//close event is sent when x is pressed so we close our window then
				if (event.type == sf::Event::Closed) {
					inint.close();
					return 0;
				}
				//checking whether the key is pressed(if a key is pressed that is not text)
				if (event.type == sf::Event::KeyPressed) {
					//check if it's enter
					if (event.key.code == sf::Keyboard::Enter && pi.getSize()>2) {
						//checking if the first character is a number
						if (pi[0] >= '0' && pi[0] <= '9') {
							//making a check if the input string is of the format number-char-number 
							bool a = false, c = false;
							for (auto i : pi) {
								//we already checked wether first character is a number so now we chack if there is a normal character
								//we use a as a switch to go from checking for a character to checking for a number again
								if (i < '0' || i > '9') {
									a = true;
								}//here we check if there is a number again 
								else if (a && i >= '0' && i <= '9') {
									c = true;
								}
							}
							//if the input string has valid values then we calculate width and height from it
							if (c) {
								//variables for input width and height
								int w, h;
								//here we take the value of the first character which will always be a number
								//and convert it from characters to intagers by subtracking character 0 from it
								//because in ascii '0' is equal to int 48, '1' is equal to 49 and so on
								w = pi[0] - '0';
								//we delete the first character and move on
								pi.erase(0, 1);
								//we check if the next character is a number
								if (pi[0] >= '0' && pi[0] <= '9')
								{
									//if it is we multiply our width with 10 because we now know that first number was value in the tens place
									w *= 10;
									//then we add that number the same way we did the first
									w += pi[0] - '0';
									pi.erase(0, 1);
								}
								//here we check if more than two numbers were inputed for the width and if there were we remove that and the separating character
								if (pi[0] >= '0' && pi[0] <= '9') {
									pi.erase(0, 2);
								}
								else {
									pi.erase(0, 1);
								}
								//here we repeat the same thing we did for the width just for the height
								h = pi[0] - '0';
								pi.erase(0, 1);
								if (pi.getSize())
								{
									h *= 10;
									h += pi[0] - '0';
									pi.clear();
								}
								//here we check if the inputed width and height are valid
								//and if they are we multiply our window width and window height by them
								//because we set them earlier to 16 which is tile width and height
								//and we close the input window
								if(w > 7 && w < 66 && h > 7 && h < 66)
								{ 
									windoww *= w;
									windowh *= h;
									inint.close();
								}
							}
						}
					}
				}
				//checking whether text is entered(single character)
				if (event.type == sf::Event::TextEntered) {
					//checking if it is any of the standard ascii
					if (event.text.unicode < 128) {
						//checking if it is a number or character in ascii, numbers start at 48(0) and above is everything else,below that are special characters 
						if (event.text.unicode > 47 && pi.getSize() < 5) {
							//if it is a character/number add it to the end of the string
							pi += event.text.unicode;
						}
						else if (event.text.unicode == 8 && pi.getSize() > 0) //checking if it is special character 8(backspace) and if input string has anything in it
						{
							//deleting the last character entered
							pi.erase(pi.getSize() - 1, 1);
						}
						//setting the input text to the input string
						it.setString(pi);
					}
				}
			}
			//clearing the window
			inint.clear(sf::Color::White);
			//drawing the input text message, input text and input textbox-rectangle
			inint.draw(ir);
			inint.draw(it);
			inint.draw(pt);
			//displaying changes
			inint.display();
		}
	}
	//adding 6 pixels for the border
	windowh += 6;
	windoww += 6;
	//making game object
	Game *g = new Game;
	//making the main window
	sf::RenderWindow window;
	window.create(sf::VideoMode(windoww, windowh),"Minesweeper");
	window.setVerticalSyncEnabled(true);
	//making the border
	sf::RectangleShape br;
	br.setFillColor(sf::Color::Transparent);
	br.setOutlineColor(sf::Color::Color(100, 100, 140));
	br.setOutlineThickness(3);
	br.setSize(sf::Vector2f(float(windoww-6), float(windowh-6)));
	br.setPosition(sf::Vector2f(3.0, 3.0));
	//main window loop
	while (window.isOpen()) {
		//handeling events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close event
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)//resize event, so that if we resize the window we get the new window width/height
			{
				ratiow = double(event.size.width) / double(windoww);
				ratioh = double(event.size.height) / double(windowh);
			}
		}
		//checking if it's game over
		if (g->isgameover()) {
			//if it is u can create a new game by pressing letter R
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				delete g;
				g = new Game;
			}
		}
		//clearing the window
		window.clear();
		//drawing the border
		window.draw(br);
		//doing game logic
		g->logic(window);
		//drawing the game
		g->draw(window);
		//displaying changes
		window.display();
	}
	return 0;
}