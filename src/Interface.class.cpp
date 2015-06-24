/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interface.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 19:16:59 by kperreau          #+#    #+#             */
/*   Updated: 2015/06/24 21:07:57 by kperreau         ###   ########.fr       */
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

void			Interface::displayLife(Player *player, Player *player2)
{
	attron(COLOR_PAIR(7));
	mvprintw(0, 12, "P1 : Life: %d", player->getLife());
	mvprintw(1, 12, "P2 : Life: %d", player2->getLife());
	return ;
}

void			Interface::displayLife(Player *player)
{
	attron(COLOR_PAIR(7));
	mvprintw(0, 12, "Life: %d", player->getLife());
	return ;
}

void			Interface::displayScore(void)
{
	attron(COLOR_PAIR(7));
	mvprintw(0, 26, "Score: %d", this->_env->getScore());
	return ;
}

void			Interface::displayNenemy(void)
{
	attron(COLOR_PAIR(7));
	mvprintw(1, 0, "Enemy: %d", this->_env->getEnemys());
	return ;
}

void			Interface::genEnemys(void)
{
	int		n = this->_env->getEnemys();

	if (n < (20 + (this->_env->getScore() / 100)) * this->_env->getPlayers())
	{
		std::string     s[] = { "0" };
		for (int i = n - (this->_env->getScore() / 100); i < (20 + (this->_env->getScore() / 100)) * this->_env->getPlayers(); ++i)
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
			if (rand() % 100 < 1)
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
		speed = 30.0;
	else if (this->_env->getScore() >= 100)
		speed = 23.0;
	else
		speed = 15.0;
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

void			Interface::start(char *av)
{
	int				key = 0;
	std::string     s[] = { "0" };
	std::string     s2[] = { "^" };
	int				stop = 0;
	srand(time(0));

	(void)s;
	(void)av;
	std::string *bg = new std::string[this->_env->getMaxY() + 1];
	Player	*player1 = new Player(this->_env, "Player", s2, 5);
	Player	*player2 = new Player(this->_env, "Player", s2, 5);
	this->genBackground(bg);

	while (key != ESCAPE)
	{
		if (inc_life * 100 <= this->_env->getScore())
		{
			inc_life++;
			if (player1->getLife() > 0 && player1->getLife() < 5) player1->modifLife(1);
			if (player2->getLife() > 0 && player2->getLife() < 5) player2->modifLife(1);
		}
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
			this->displayLife(player1, player2);
			this->displayNenemy();
			this->displayFps();
			wrefresh(stdscr);
		}
		else
			mvprintw(this->_env->getMaxY() / 2 + 1, this->_env->getMaxX() / 2 - 3, "PAUSE");
		switch ((key = getch()))
		{
			case TOP: if (player1->getLife() > 0) player1->moveUp(); break ;
			case BOTTOM: if (player1->getLife() > 0) player1->moveDown(); break ;
			case LEFT: if (player1->getLife() > 0) player1->moveLeft(); break ;
			case RIGHT: if (player1->getLife() > 0) player1->moveRight(); break ;
			case ENTER: if (player1->getLife() > 0) player1->Fire(); break ;
			case W_K: if (player2->getLife() > 0) player2->moveUp(); break ;
			case S_K: if (player2->getLife() > 0) player2->moveDown(); break ;
			case A_K: if (player2->getLife() > 0) player2->moveLeft(); break ;
			case D_K: if (player2->getLife() > 0) player2->moveRight(); break ;
			case SPACE: if (player2->getLife() > 0) player2->Fire(); break ;
			case STOP: stop = !stop; break ;
		}
	}
	delete player1;
	delete player2;
	this->Over();
	return ;
}

void			Interface::start(void)
{
	char			buffsize[1024];
	int				key = 0;
	std::string     s[] = { "0" };
	std::string     s2[] = { "^" };
	int				stop = 0;
	srand(time(0));

	(void)s;
	(void)buffsize;
	std::string *bg = new std::string[this->_env->getMaxY() + 1];
	Player	*player1 = new Player(this->_env, "Player", s2, 5);
	this->genBackground(bg);

	while (key != ESCAPE)
	{
		if (inc_life * 100 <= this->_env->getScore())
		{
			inc_life++;
			if (player1->getLife() > 0 && player1->getLife() < 5) player1->modifLife(1);
		}
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
			this->displayLife(player1);
			this->displayNenemy();
			this->displayFps();
			wrefresh(stdscr);
		}
		else
			mvprintw(this->_env->getMaxY() / 2 + 1, this->_env->getMaxX() / 2 - 3, "PAUSE");
		switch ((key = getch()))
		{
			case TOP: if (player1->getLife() > 0) player1->moveUp(); break ;
			case BOTTOM: if (player1->getLife() > 0) player1->moveDown(); break ;
			case LEFT: if (player1->getLife() > 0) player1->moveLeft(); break ;
			case RIGHT: if (player1->getLife() > 0) player1->moveRight(); break ;
			case SPACE: if (player1->getLife() > 0) player1->Fire(); break ;
			case STOP: stop = !stop; break ;
		}
	}
	delete player1;
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
