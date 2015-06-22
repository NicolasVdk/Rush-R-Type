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
	if (this->_env->getScore() >= 500)
	{
		std::string		s1[] = { "/" };
		std::string		s2[] = { "|" };
		std::string		s3[] = { "\\" };
		new Bullets(this->_env, this->_x + 1, this->_y, s1, 1, 50.0, 0);
		new Bullets(this->_env, this->_x - 1, this->_y, s1, 1, 50.0, 0);
		new Bullets(this->_env, this->_x, this->_y, s1, 1, 50.0, 0);
		new Bullets(this->_env, this->_x, this->_y + 1, s1, 1, 17.0, 1);
		new Bullets(this->_env, this->_x, this->_y + 1, s2, 1, 17.0, 2);
	}
	else if (this->_env->getScore() >= 100)
	{
		std::string		s[] = { "|" };
		new Bullets(this->_env, this->_x + 1, this->_y, s, 1, 50.0, 0);
		new Bullets(this->_env, this->_x - 1, this->_y, s, 1, 50.0, 0);
		new Bullets(this->_env, this->_x, this->_y, s, 1, 50.0, 0);
	}
	else
	{
		std::string		s[] = { "|" };
		new Bullets(this->_env, this->_x, this->_y, s, 1, 50.0, 0);
	}
}

Player::~Player( void )
{

}
