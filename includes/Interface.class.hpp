/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interface.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 18:05:12 by kperreau          #+#    #+#             */
/*   Updated: 2015/06/21 22:27:54 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_CLASS_HPP
# define INTERFACE_CLASS_HPP
# define ESCAPE 27
# define TOP 259
# define BOTTOM 258
# define LEFT 260
# define RIGHT 261
# define SPACE 32
# define W_K 119
# define A_K 97
# define S_K 115
# define D_K 100
# define ENTER 10
# define STOP 360

# include <iostream>
# include <ctime>
# include <curses.h>
# include "Env.class.hpp"
# include "Player.class.hpp"
# include "Enemy.class.hpp"

class Interface
{
	public:

		Interface(Env *env);
		Interface(const Interface & interface);
		~Interface(void);
	
		void		start(char *av);
		void		start(void);
	
		Interface &operator=(const Interface & interface);

	private:
	
		Env *	_env;
	
		void		displayFps(void);
		void		displayLife(Player *player, Player *player2);
		void		displayLife(Player *player);
		void		displayScore(void);
		void		genEnemys(void);
		void		resize(void);
		void		genBackground(std::string *bg);
		void		background(std::string *bg);
		void		Over(void);
};

static	int	inc_life = 1;

#endif
