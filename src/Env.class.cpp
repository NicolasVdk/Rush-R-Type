/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 18:54:44 by kperreau          #+#    #+#             */
/*   Updated: 2015/06/24 21:09:08 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Env.class.hpp"

Env::Env( void ) : collision(this)
{
	this->_players = 0;
	this->_score = 0;
	this->_enemys = 0;
	this->init_shell();
	this->_maxX = getmaxx(stdscr);
	this->_maxY = getmaxy(stdscr);
	if (this->getMaxX() < 20 || this->getMaxY() < 20)
	{
		endwin();
		std::cout << "Resize Window pleaze !" << std::endl;
		exit(0);
	}
	this->_rate = 0;
	return ;
}

Env::Env(Collision *e) : collision(this)
{
	(void)e;
	this->_score = 0;
	this->init_shell();
	this->_maxX = getmaxx(stdscr);
	this->_maxY = getmaxy(stdscr);
	this->_rate = 0;
	return ;
}

Env::Env(const Env & env) : collision(this)
{
	*this = env;
	return ;
}

Env::~Env(void)
{
	return ;
}

void			Env::init_shell(void) const
{
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_RED);
	init_pair(5, COLOR_GREEN, COLOR_GREEN);
	init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLUE, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_BLACK);
	init_pair(10, COLOR_YELLOW, COLOR_BLACK);
	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_color(12, 300, 300, 300);
	init_pair(13, 12, COLOR_BLACK);
	init_pair(14, COLOR_CYAN, COLOR_BLACK);
	curs_set(0);
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
}

int			Env::getMaxX(void) const
{
	return (this->_maxX);
}

int			Env::getMaxY(void) const
{
	return (this->_maxY);
}

long		Env::getRate(void) const
{
	return (this->_rate);
}

int			Env::getEnemys(void) const
{
	return (this->_enemys);
}

int			Env::getScore(void) const
{
	return (this->_score);
}

int			Env::getPlayers(void) const
{
	return (this->_players);
}

void		Env::setPlayers(int val)
{
	this->_players = val;
	return ;
}

void		Env::setRate(void)
{
	static clock_t	oldtime = 0;
	static clock_t	time = 0;

	oldtime = time;
	time = clock();
	if ((time - oldtime) > 0)
		this->_rate = CLOCKS_PER_SEC / (time - oldtime);
	return ;
}

void		Env::setEnemys(int val)
{
	this->_enemys = val;
	return ;
}

void		Env::addScore(int val)
{
	this->_score += val;
	return ;
}

Env &		Env::operator=(const Env & rhs)
{
	if (this != &rhs)
	{
		this->_maxX = rhs.getMaxX();
		this->_maxY = rhs.getMaxY();
		this->_rate = rhs.getRate();
	}
	return (*this);
}
