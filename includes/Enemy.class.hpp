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
		int		getScore( void );
		Enemy & operator=( Enemy const & rhs);
		~Enemy( void );

		void		pushEnemy(void);
		void		dLife(void);

	private:
		Enemy( void );
		int		_side;
		int		_score;
		int		_wall;
		int		_aff_boss;
};

static	int		boss = 1;
static	int		numberofboss = 0;
static	int		look = 0;
#endif
