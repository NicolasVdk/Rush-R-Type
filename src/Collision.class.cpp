/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collision.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 18:00:43 by bdurst            #+#    #+#             */
/*   Updated: 2015/06/24 21:32:01 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Enemy.class.hpp"
#include "../includes/Bullets.class.hpp"
#include "../includes/Player.class.hpp"
#include "../includes/Collision.class.hpp"
#include "../includes/Env.class.hpp"

Collision::Collision(Env *e) : _env(e), _beginEnemy(NULL),  _beginPlayer(NULL), _beginBullet(NULL)
{
	return ;
}

Collision::~Collision(void)
{
	return ;
}

Collision::Collision(Collision const & src)
{
	*this = src;
}

Collision &	Collision::operator=(Collision const & rhs)
{
	(void)rhs;
	return (*this);
}

void				Collision::pushEnemy(Enemy *new_enemy)
{
	listEnemy	*tmp;
	listEnemy	*new_node;

	if (new_enemy)
	{
		if (this->_beginEnemy)
		{
			tmp = this->_beginEnemy;
			new_node = new listEnemy;
			while (tmp->next)
				tmp = tmp->next;
			new_node->prev = tmp;
			new_node->enemy = new_enemy;
			new_node->next = NULL;
			tmp->next = new_node;
		}
		else
		{
			new_node = new listEnemy;
			new_node->prev = NULL;
			new_node->next = NULL;
			new_node->enemy = new_enemy;
			this->_beginEnemy = new_node;
		}
	}
}

void				Collision::pushBullet(Bullets *new_bullet)
{
	listBullet	*tmp;
	listBullet	*new_node;

	if (new_bullet)
	{
		if (this->_beginBullet)
		{
			tmp = this->_beginBullet;
			new_node = new listBullet;
			while (tmp->next)
				tmp = tmp->next;
			new_node->prev = tmp;
			new_node->bullet = new_bullet;
			new_node->next = NULL;
			tmp->next = new_node;
		}
		else
		{
			new_node = new listBullet;
			new_node->prev = NULL;
			new_node->next = NULL;
			new_node->bullet = new_bullet;
			this->_beginBullet = new_node;
		}
	}
}

void				Collision::pushPlayer(Player *new_player)
{
	listPlayer	*tmp;
	listPlayer	*new_node;

	if (new_player)
	{
		if (this->_beginPlayer)
		{
			tmp = this->_beginPlayer;
			new_node = new listPlayer;
			while (tmp->next)
				tmp = tmp->next;
			new_node->prev = tmp;
			new_node->player = new_player;
			new_node->next = NULL;
			tmp->next = new_node;
		}
		else
		{
			new_node = new listPlayer;
			new_node->prev = NULL;
			new_node->next = NULL;
			new_node->player = new_player;
			this->_beginPlayer = new_node;
		}
	}
}

void				Collision::dieEnemy(void)
{
	listEnemy	*tmp;
	listEnemy	*tmp2;

	if (this->_beginEnemy)
	{
		tmp = this->_beginEnemy;
		while (tmp)
		{
			if (tmp->enemy->getLife() <= 0 || tmp->enemy->getY() < 0 || tmp->enemy->getY() > this->_env->getMaxY())
			{
				this->_env->setEnemys(this->_env->getEnemys() - 1);
				if (tmp->enemy->getLife() <= 0)
					_env->addScore(tmp->enemy->getScore());
				if (tmp == this->_beginEnemy)
					this->_beginEnemy = tmp->next;
				tmp2 = tmp->next;
				/*if (tmp->next)
					tmp2 = tmp->next;
				else
					tmp2 = NULL;*/
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp->enemy)
					delete tmp->enemy;
				if (tmp)
					delete tmp;
				tmp = tmp2;
			}
			else
				tmp = tmp->next;
		}
	}
}

void				Collision::dieBullet(void)
{
	listBullet	*tmp;
	listBullet	*tmp2;

	if (this->_beginBullet)
	{
		tmp = this->_beginBullet;
		while (tmp)
		{
			if (tmp->bullet->getLife() <= 0 || tmp->bullet->getY() < 0 || tmp->bullet->getY() > this->_env->getMaxY())
			{
				if (tmp == this->_beginBullet)
					this->_beginBullet = tmp->next;	
				tmp2 = tmp->next;
				/*if (tmp->next)
					tmp2 = tmp->next;
				else
					tmp2 = NULL;*/
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp->bullet && tmp)
					delete tmp->bullet;
				if (tmp)
					delete tmp;
				tmp = tmp2;
			}
			else
				tmp = tmp->next;
		}
	}
}

void				Collision::diePlayer(void)
{
	listPlayer	*tmp;
	listPlayer	*tmp2;

	if (this->_beginPlayer)
	{
		tmp = this->_beginPlayer;
		while (tmp->next)
		{
			if (tmp->player->getLife() <= 0)
			{
				this->_env->setPlayers(this->_env->getPlayers() - 1);
				if (tmp == this->_beginPlayer)
					this->_beginPlayer = tmp->next;	
				tmp2 = tmp->next;
				/*if (tmp->next)
					tmp2 = tmp->next;
				else
					tmp2 = NULL;*/
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp)
					delete tmp;
				tmp = tmp2;
			}
			else
				tmp = tmp->next;
		}
	}
}

void				Collision::dieEnemyPrint(void)
{
	listEnemy	*tmp;
	listEnemy	*tmp2;

	if (this->_beginEnemy)
	{
		tmp = this->_beginEnemy;
		while (tmp)
		{
			if (tmp->enemy->getLife() <= 0)
			{
				this->_env->setEnemys(this->_env->getEnemys() - 1);
				if (tmp->enemy->getLife() <= 0)
					_env->addScore(tmp->enemy->getScore());
				if (tmp == this->_beginEnemy)
					this->_beginEnemy = tmp->next;
				tmp2 = tmp->next;
				/*if (tmp->next)
					tmp2 = tmp->next;
				else
					tmp2 = NULL;*/
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp->enemy && tmp)
					delete tmp->enemy;
				if (tmp)
					delete tmp;
				tmp = tmp2;
			}
			else
			{
				tmp->enemy->printEntity();
				tmp = tmp->next;
			}
		}
	}
}

void				Collision::dieBulletPrint(void)
{
	listBullet	*tmp;
	listBullet	*tmp2;

	if (this->_beginBullet)
	{
		tmp = this->_beginBullet;
		while (tmp)
		{
			if (tmp->bullet->getLife() <= 0 || tmp->bullet->getY() < 0 || tmp->bullet->getY() > this->_env->getMaxY())
			{
				if (tmp == this->_beginBullet)
					this->_beginBullet = tmp->next;
				tmp2 = tmp->next;
				/*if (tmp->next)
					tmp2 = tmp->next;
				else
					tmp2 = NULL;*/
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp->bullet && tmp)
					delete tmp->bullet;
				if (tmp)
					delete tmp;
				tmp = tmp2;
			}
			else
			{
				if (tmp->bullet)
					tmp->bullet->printBullet();
				tmp = tmp->next;
			}
		}
	}
}

void				Collision::diePlayerPrint(void)
{
	listPlayer	*tmp;
	listPlayer	*tmp2;

	if (this->_beginPlayer)
	{
		tmp = this->_beginPlayer;
		while (tmp)
		{
			if (tmp->player->getLife() <= 0)
			{
				this->_env->setPlayers(this->_env->getPlayers() - 1);
				if (tmp == this->_beginPlayer)
					this->_beginPlayer = tmp->next;
				tmp2 = tmp->next;
				/*if (tmp->next)
					tmp2 = tmp->next;
				else
					tmp2 = NULL;*/
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				if (tmp)
					delete tmp;
				tmp = tmp2;
			}
			else
			{
				tmp->player->printEntity();
				tmp = tmp->next;
			}
		}
	}
}

void			Collision::colEnemyPlayer(void)
{
	listEnemy	*tmpE;
	listPlayer	*tmpP;
	
	if (this->_beginEnemy && this->_beginPlayer)
	{
		tmpE = this->_beginEnemy;
		while (tmpE)
		{
			tmpP = this->_beginPlayer;
			while (tmpP)
			{
				if (tmpE->enemy->getX() == tmpP->player->getX() && tmpE->enemy->getY() == tmpP->player->getY())
				{
					tmpE->enemy->modifLife(-1);
					tmpP->player->modifLife(-1);
				}
				tmpP = tmpP->next;
			}
			tmpE = tmpE->next;
		}
	}
}

void			Collision::colEnemyBullet(void)
{
	listEnemy	*tmpE;
	listBullet	*tmpB;
	
	if (this->_beginEnemy && this->_beginBullet)
	{
		tmpE = this->_beginEnemy;
		while (tmpE)
		{
			tmpB = this->_beginBullet;
			while (tmpB)
			{
				if (tmpE->enemy->getX() == tmpB->bullet->getX() && tmpE->enemy->getY() == tmpB->bullet->getY() && tmpB->bullet->getDir() == 1)
				{
					tmpE->enemy->modifLife(-1);
					tmpB->bullet->modifLife(-1);
				}
				tmpB = tmpB->next;
			}
			tmpE = tmpE->next;
		}
	}
}


void			Collision::colBulletPlayer(void)
{
	listBullet	*tmpB;
	listPlayer	*tmpP;
	
	if (this->_beginBullet && this->_beginPlayer)
	{
		tmpB = this->_beginBullet;
		while (tmpB)
		{
			tmpP = this->_beginPlayer;
			while (tmpP)
			{
				if (tmpB->bullet->getX() == tmpP->player->getX() && tmpB->bullet->getY() == tmpP->player->getY() && tmpB->bullet->getDir() == 0)
				{
					tmpB->bullet->modifLife(-1);
					tmpP->player->modifLife(-1);
				}
				tmpP = tmpP->next;
			}
			tmpB = tmpB->next;
		}
	}
}

void			Collision::moveEnemy(void)
{
	listEnemy	*tmpE;
	listBullet	*tmpB;
	listPlayer	*tmpP;

	if (this->_beginEnemy && this->_beginPlayer)
	{
		tmpE = this->_beginEnemy;
		tmpP = this->_beginPlayer;
		tmpB = this->_beginBullet;
		while (tmpE)
		{
			if (tmpE->enemy)
				tmpE->enemy->move();
			tmpE = tmpE->next;
		}
		this->colEnemyPlayer();
		this->colEnemyBullet();
	}
	this->dieEnemy();
	this->diePlayer();
	this->dieBullet();
}

void			Collision::moveBullet(void)
{
	listEnemy	*tmpE;
	listBullet	*tmpB;
	listPlayer	*tmpP;

	if (this->_beginBullet && this->_beginPlayer)
	{
		tmpE = this->_beginEnemy;
		tmpP = this->_beginPlayer;
		tmpB = this->_beginBullet;
		while (tmpB)
		{
			if (tmpB->bullet)
				tmpB->bullet->move();
			tmpB = tmpB->next;
		}
		this->colBulletPlayer();
		this->colEnemyBullet();
	}
	this->dieEnemyPrint();
	this->diePlayerPrint();
	this->dieBulletPrint();
}
