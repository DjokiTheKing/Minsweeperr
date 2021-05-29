//preporcessor stuff
//if GAME_H is not defined everything between ifndef and endif happens
//this is so that only one copy of this class is in a single file when we are including multiple files this is important
#ifndef GAME_H
#define GAME_H
//neccesary SFML files
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//includibng vector and random from standard C++ library
#include <vector>
#include <random>

//we need to get the extern window width window height and ratios when resizing
extern int windoww, windowh;extern double ratiow, ratioh;

//this is the Game class
class Game {
public:
	//constructor
	Game();
	//logic function
	void logic(sf::RenderWindow& wnd);
	//drawing function
	void draw(sf::RenderWindow& wnd);
	//function that just returns is it GameOver or not
	bool isgameover() { return GameOver; };
private:
	//function that opens a Tile
	void openp(int x, int y);
	//it's an enum that defines closed,flag and open
	enum state :char { closed = 0, flag = 1, open = 2 } ;
	//this is the definition of a Tile
	struct Tile {
		//value contains values which range from -3 to 8
		//-3 > if the flag is where there is no bomb
		//-2 > is the bomb that you clicked on
		//-1 > is a bomb
		// 0 > empty
		// 1,2,3,4,5,6,7,8 > number of bombs around that tile
		int value = 0;
		//state whether tile is closed,open or has a flag on it
		state st = closed;
	};
	//how many bombs are left to flag
	int bombsleft;
	//i get how many tiles there are back from window width and window height
	short width = (windoww-6) / 16, height = (windowh-6) / 16;
	//textures
	sf::Texture o, t, th, fr, fi, sx, se, ei, bm, bmc, nbo, fl, cl, op;
	//sprites
	sf::Sprite one, two, three, four, five, six, seven, eight, openbn, openbf, opennob, flagg, closedd, opene;
	//this is our minefield matrix
	std::vector<std::vector<Tile>> minefield;
	//this is a random device(true rng) that we use to seed the pseudo random number generator 
	std::random_device rd;
	//this is a pseudo random number generator
	std::mt19937 rng;
	//this gets the value from random number generator and squishies it between two values
	std::uniform_int_distribution<int> disx,disy;
	//GameOver - self explanatory, clicked saves wheter we clicked somewhere
	bool GameOver = false,clicked = false;
};

#endif // !GAME_H