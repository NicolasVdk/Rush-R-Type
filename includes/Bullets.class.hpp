#ifndef BULLETS_CLASS_HPP
# define BULLETS_CLASS_HPP
# include "Entity.class.hpp"


class Bullets : public Entity
{
	public:
		Bullets( Env *e, double x, double y, std::string d[], int dir, double speed, int t);
		Bullets( Bullets const & src );
		int		getDir( void ) const;
		void	move( void );
		Bullets & operator=(Bullets const & rhs );
		~Bullets( void );

		void		pushBullet(void);
		void		printBullet(void) const;

	private:
		Bullets( void );
		int		_dir;
};

#endif
