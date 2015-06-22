#include "../includes/Player.class.hpp"
#include "../includes/Bullets.class.hpp"

Player::Player( void ) : Entity()
{

}

Player::Player( Env *e, std::string s, std::string d[], int l) : Entity(e, s, (double)e->getMaxX()/2, (double)e->getMaxY() - 1, d, l, 1.0)
{
	this->_type = 0;
	this->_env->setPlayers(this->_env->getPlayers() + 1);
	pushPlayer();
}

Player::Player( Player const & src ) : Entity(src)
{

}

Player & Player::operator=( Player const & rhs )
{
	return (*this);
}

void	Player::pushPlayer(void)
{
	this->_env->collision.pushPlayer(this);
}

void	Player::Fire()
{
	std::string		s[] = { "|" };
	new Bullets(this->_env, this->_x, this->_y, s, 1, 50.0, 0);
}

Player::~Player( void )
{

}
