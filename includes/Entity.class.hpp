// *************************************** //
// *       Canonical class Entity        * //
// * generated by Mde-pach Python script * //
// *************************************** //

#ifndef ENTITY_CLASS_HPP
# define ENTITY_CLASS_HPP

# include <iostream>
# include <curses.h>
#include "Env.class.hpp"

class Entity
{
	public:

		Entity(void);
		Entity(Env *env, const std::string Name, double x, double y, std::string display[], int life, double speed);
		Entity(Entity const & src);
		~Entity(void);
		Entity &		operator=(Entity const & rhs);

		std::string		getName(void) const;
		int				getX(void) const;
		int				getY(void) const;
		double			getSpeed(void) const;
		int				getLife(void) const;

		void			moveUp(void);
		void			moveDown(void);
		void			moveLeft(void);
		void			moveRight(void);

		void			printEntity(void);
		void			modifLife(int i);

	protected:

		std::string		_name;
		double			_x;
		double			_y;
		double			_speed;
		int				_life;
		int				_type;
		std::string		_display[1];
		Env				*_env;
};

#endif
