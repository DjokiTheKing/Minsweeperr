#include "Game.h"

//constructor - here we initialise variables
Game::Game()
	:
	//making the minefield
	minefield(width, std::vector<Tile>(height)),
	//initialising random device
	rd(),
	//initialising random number generator
	rng(rd()),
	//initialising the distributions
	disx(0,width-1),
	disy(0,height-1)
{
	//loading textures
	o.loadFromFile("sprites/one.png");
	t.loadFromFile("sprites/two.png");
	th.loadFromFile("sprites/three.png");
	fr.loadFromFile("sprites/four.png");
	fi.loadFromFile("sprites/five.png");
	sx.loadFromFile("sprites/six.png");
	se.loadFromFile("sprites/seven.png");
	ei.loadFromFile("sprites/eight.png");
	bm.loadFromFile("sprites/openbn.png");
	bmc.loadFromFile("sprites/openbf.png");
	nbo.loadFromFile("sprites/opennob.png");
	fl.loadFromFile("sprites/flag.png");
	cl.loadFromFile("sprites/closed.png");
	op.loadFromFile("sprites/opene.png");
	//setting the textures to their respective sprites
	one.setTexture(o);
	two.setTexture(t);
	three.setTexture(th);
	four.setTexture(fr);
	five.setTexture(fi);
	six.setTexture(sx);
	seven.setTexture(se);
	eight.setTexture(ei);
	openbn.setTexture(bm);
	openbf.setTexture(bmc);
	opennob.setTexture(nbo);
	flagg.setTexture(fl);
	closedd.setTexture(cl);
	opene.setTexture(op);
	//calculating number of bombs
	int nbombs = int(float(width * height) * 0.16);
	//saving number of bombs that needs to be flagged
	bombsleft = nbombs;
	//setting the bombs on random coordinates, while there are bombs to be set
	while (nbombs) {
		//getting the random coordinates
		int rx = disx(rng);
		int ry = disy(rng);
		//checking whether the tile on those coordinates is empty
		if (minefield[rx][ry].value == 0) {
			//setting a bomb to it
			minefield[rx][ry].value = -1;
			//decreasing a number of bombs that needs to be set
			--nbombs;
		}
	}
	//we go thru all tiles and calculate number of bombs around that tile
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			//first we check that this tile is not a bomb
			if (minefield[i][j].value == 0) {
				//then we go thru all the tiles around it
				for (int ij = i - 1; ij < (i + 2); ++ij) {
					for (int jj = j - 1; jj < (j + 2); ++jj) {
						//then we check whether that tile is whitin the mine field
						if (ij >= 0 && ij < width) {
							if (jj >= 0 && jj < height) {
								//and we check whether that tile has a bomb on it
								if (minefield[ij][jj].value == -1) {
									//if it does, we increment the value of the current tile by one
									++minefield[i][j].value;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Game::logic(sf::RenderWindow& wnd)
{
	//check if user won
	if (bombsleft == 0) {
		bool done = true;
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				if (minefield[i][j].st == closed && minefield[i][j].value > -1) {
					done = false;
				}
			}
		}
		if(!done)
			//he won game is over
			GameOver = true;
	}
	//logic
	if (!GameOver) {
		//taking mouse position
		sf::Vector2i mp = sf::Mouse::getPosition(wnd);
		//scaling it down based on if window size and tile size
		int posx = int(((double(mp.x)-3.0*ratiow)/ratiow) / 16.0), posy = int(((double(mp.y)-3.0*ratioh)/ratioh) / 16.0);
		//checking if it's within the window
		if (posx >= 0 && posx < width && posy >= 0 && posy < height) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (minefield[posx][posy].st != open && !clicked) {
					if (minefield[posx][posy].st == flag) {
						minefield[posx][posy].st = closed;
						++bombsleft;
					}
					else {
						minefield[posx][posy].st = flag;
						--bombsleft;
					}
					clicked = true;
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (!clicked) {
					openp(posx, posy);
					clicked = true;
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
				if (!clicked) {
					std::vector<sf::Vector2i> tbo;
					int nf = 0;
					for (int i = posx - 1; i < (posx + 2); ++i) {
						for (int j = posy - 1; j < (posy + 2); ++j) {
							if (i >= 0 && i < width) {
								if (j >= 0 && j < height) {
									if (minefield[i][j].st == flag) {
										++nf;
									}
									else {
										tbo.push_back(sf::Vector2i(i, j));
									}
								}
							}
						}
					}
					if (nf == minefield[posx][posy].value) {
						for (auto i : tbo) {
							openp(i.x, i.y);
						}
					}
					clicked = true;
				}
			}
			else{
				clicked = false;
			}
		}
	}
}

void Game::draw(sf::RenderWindow& wnd)
{
	//going thru all tiles and drawing them based on their coordinates and their value
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (minefield[i][j].st == closed) {
				closedd.setPosition(sf::Vector2f(i * 16+3, j * 16+3));
				wnd.draw(closedd);
			}
			else if (minefield[i][j].st == open) {
				switch (minefield[i][j].value) {
				case -3:
					opennob.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(opennob);
					break;
				case -2:
					openbf.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(openbf);
					break;
				case -1:
					openbn.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(openbn);
					break;
				case 0:
					opene.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(opene);
					break;
				case 1:
					one.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(one);
					break;
				case 2:
					two.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(two);
					break;
				case 3:
					three.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(three);
					break;
				case 4:
					four.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(four);
					break;
				case 5:
					five.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(five);
					break;
				case 6:
					six.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(six);
					break;
				case 7:
					seven.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(seven);
					break;
				case 8:
					eight.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
					wnd.draw(eight);
					break;
				}
			}
			else {
				flagg.setPosition(sf::Vector2f(i * 16 + 3, j * 16 + 3));
				wnd.draw(flagg);
			}
		}
	}
}

void Game::openp(int x, int y)
{
	if (minefield[x][y].st == closed) {
		if (minefield[x][y].value == -1) {
			for (int i = 0; i < width; ++i) {
				for (int j = 0; j < height; ++j) {
					if (minefield[i][j].value == -1) {
						minefield[i][j].st = open;
					}
					if (minefield[i][j].st == flag && minefield[i][j].value > -1) {
						minefield[i][j].st = open;
						minefield[i][j].value = -3;
					}
				}
			}
			minefield[x][y].value = -2;
			GameOver = true;
		}
		else if (minefield[x][y].value > 0) {
			minefield[x][y].st = open;
		}
		else {
			std::vector<sf::Vector2i> fo;
			fo.push_back(sf::Vector2i(x, y));
			while (fo.size()) {
				minefield[fo[0].x][fo[0].y].st = open;
				for (int i = fo[0].x - 1; i < (fo[0].x + 2); ++i) {
					for (int j = fo[0].y - 1; j < (fo[0].y + 2); ++j) {
						if (i >= 0 && i < width) {
							if (j >= 0 && j < height) {
								if (minefield[i][j].value > 0) {
									minefield[i][j].st = open;
								}
								else {
									if (minefield[i][j].st == closed) {
										fo.push_back(sf::Vector2i(i, j));
									}
								}
							}
						}
					}
				}
				fo.erase(fo.begin());
			}
		}
	}
}
