/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 18:52:24 by kperreau          #+#    #+#             */
/*   Updated: 2015/06/21 20:25:39 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_CLASS_HPP
# define ENV_CLASS_HPP

# include <iostream>
# include <string>
# include <curses.h>
# include <ctime>
# include "Collision.class.hpp"

class Env
{
	public:

		Collision collision;
		Env( void );
		Env(Collision *e);
		Env(const Env & env);
		~Env(void);

		int		getMaxX(void) const;
		int		getMaxY(void) const;
		long	getRate(void) const;
		int		getScore(void) const;
		int		getEnemys(void) const;
		int		getPlayers(void) const;

		void	setPlayers(int val);
		void	setEnemys(int n);
		void	setRate(void);
		void	addScore(int val);
		

		Env &operator=(const Env & env);

	private:

		int		_maxX;
		int		_maxY;
		long	_rate;
		int		_score;
		int		_enemys;
		int		_players;

		void	init_shell(void) const;
};

#endif
