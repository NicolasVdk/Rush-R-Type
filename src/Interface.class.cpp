/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interface.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 19:16:59 by kperreau          #+#    #+#             */
/*   Updated: 2015/06/21 23:07:52 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Interface.class.hpp"

Interface::Interface(Env *env) : _env(env)
{
	return ;
}

Interface::~Interface(void)
{
	return ;
}

void			Interface::displayFps(void)
{
	attron(COLOR_PAIR(7));
	mvprintw(0, 0, "Fps: %d", this->_env->getRate());
	return ;	
}

void			Interface::displayLife(Player *player)
{
	attron(COLOR_PAIR(7));
	mvprintw(0, 13, "Life: %d", player->getLife());
	return ;	
}

void			Interface::displayScore(void)
{
	attron(COLOR_PAIR(7));
	mvprintw(0, 22, "Score: %d", this->_env->getScore());
	return ;	
}

void			Interface::genEnemys(void)
{
	int		n = this->_env->getEnemys();

	if (n < 20)
	{
		std::string     s[] = { "0" };
		for (int i = n; i < 20; ++i)
		{
			if (rand() % (100 * this->_env->getRate()) < 7)
			{
				new Enemy(this->_env, s, 1);
				this->_env->setEnemys(this->_env->getEnemys() + 1);
			}
		}
	}
	return ;
}

void			Interface::resize(void)
{
	if (getmaxx(stdscr) != this->_env->getMaxX() ||
		getmaxy(stdscr) != this->_env->getMaxY())
	{
		endwin();
		std::cout << "Window resized !!" << std::endl;
		exit(0);
	}
	return ;
}

void			Interface::genBackground(std::string *bg)
{
	int			x = this->_env->getMaxX();
	int			y = this->_env->getMaxY();

	for (int x2 = 0; x2 < x; ++x2)
	{
		for (int y2 = 0; y2 < y; ++y2)
		{
			if (rand() % 100 < 3)
				bg[y2].append(".");
			else
				bg[y2].append(" ");
		}
	}
}

void			Interface::background(std::string *bg)
{
	static double p = 0;
	double speed = 0.0;

	if ((int)p > this->_env->getMaxY())
		p = 0;
	if (this->_env->getScore() >= 200)
		attron(COLOR_PAIR(9));
	else if (this->_env->getScore() >= 100)
		attron(COLOR_PAIR(8));
	else
		attron(COLOR_PAIR(13));
	for (int y = 0; y < this->_env->getMaxY(); ++y)
		mvprintw(((int)p + y) % this->_env->getMaxY(), 0, "%s", bg[y].c_str());
	if (this->_env->getScore() >= 200)
		speed = 25.0;
	else if (this->_env->getScore() >= 100)
		speed = 20.0;
	else
		speed = 10.0;
	p += speed / (float)this->_env->getRate();
	attron(COLOR_PAIR(7));
}

void			Interface::Over(void)
{
	endwin();
	std::cout << "Game Over." << std::endl << "Your score is : " <<
		this->_env->getScore() << std::endl;
	return ;
}

void			Interface::start(void)
{
	int				key = 0;
	std::string     s[] = { "0" };
	std::string     s2[] = { "^" };
	int				stop = 0;
	srand(time(0));

	std::string *bg = new std::string[this->_env->getMaxY() + 1];
	Player   *player = new Player(this->_env, "Player", s2, 5);
	this->genBackground(bg);

	while (key != ESCAPE)
	{
		this->resize();
		this->_env->setRate();
		if (!stop)
		{
			erase();
			this->background(bg);
			attron(COLOR_PAIR(7));
			this->genEnemys();
			this->_env->collision.moveEnemy();
			if (this->_env->getPlayers() < 1)
				break ;
			this->_env->collision.moveBullet();
			if (this->_env->getPlayers() < 1)
				break ;
			this->displayScore();
			this->displayLife(player);
			this->displayFps();
			wrefresh(stdscr);
		}
		else
			mvprintw(this->_env->getMaxY() / 2 + 1, this->_env->getMaxX() / 2 - 3, "PAUSE");
		switch ((key = getch()))
		{
			case TOP: player->moveUp(); break ;
			case BOTTOM: player->moveDown(); break ;
			case LEFT: player->moveLeft(); break ;
			case RIGHT: player->moveRight(); break ;
			case SPACE: player->Fire(); break ;
			case STOP: stop = !stop; break ;
			//default: if (key > 0)mvprintw(4, 5, "test: %d", key);
		}
	}
	this->Over();
	return ;
}

Interface &		Interface::operator=(const Interface & rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}
