#ifndef ENEMY_CLASS_HPP
# define ENEMY_CLASS_HPP

# define BORDER 10
# include "Entity.class.hpp"

class Enemy : public Entity
{
	public:
		Enemy( Env *e, std::string d[], int l );
		Enemy( Enemy const & src);
		void	move( void );
		void	Fire( void );
		Enemy & operator=( Enemy const & rhs);
		~Enemy( void );

		void		pushEnemy(void);

	private:
		Enemy( void );
		int		_side;
	
};

static	int		boss = 0;

#endif
