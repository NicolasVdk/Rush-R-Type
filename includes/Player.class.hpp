#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP
# include "Entity.class.hpp"

class Player : public Entity
{
	public:
		Player( Env *e, std::string name, std::string d[], int l);
		Player( Player const & src );
		void	Fire( void );
		Player & operator=( Player const & rhs );
		~Player();

		void		pushPlayer(void);

	private:
		Player( void );
};

#endif
