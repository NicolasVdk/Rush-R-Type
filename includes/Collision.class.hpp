/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collision.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 18:30:10 by bdurst            #+#    #+#             */
/*   Updated: 2015/06/21 18:59:07 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_CLASS_HPP
# define COLLISION_CLASS_HPP

class Enemy;
class Bullets;
class Player;
class Env;

class Collision
{
	public:

				 	~Collision(void);
					Collision(Env *e);
					Collision(Collision const & src);

		void		pushEnemy(Enemy *new_enemy);
		void		pushBullet(Bullets *new_bullet);
		void		pushPlayer(Player *new_player);

		void		dieEnemy(void);
		void		dieBullet(void);
		void		diePlayer(void);
		void		dieEnemyPrint(void);
		void		dieBulletPrint(void);
		void		diePlayerPrint(void);

		void		colEnemyPlayer(void);
		void		colEnemyBullet(void);

		void		colBulletPlayer(void);
		void		colBulletEnemy(void);

		void		moveEnemy(void);
		void		moveBullet(void);
	
		Collision &	operator=(Collision const & rhs);

	private:

				 	Collision(void);

		Env 			*_env;
		struct			listEnemy
		{
			Enemy		*enemy;
			listEnemy	*prev;
			listEnemy	*next;
		};
		struct			listBullet
		{
			Bullets		*bullet;
			listBullet	*prev;
			listBullet	*next;
		};
		struct			listPlayer
		{
			Player		*player;
			listPlayer	*prev;
			listPlayer	*next;
		};
		listEnemy		*_beginEnemy;
		listPlayer		*_beginPlayer;
		listBullet		*_beginBullet;
};

#endif
