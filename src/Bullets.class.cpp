#include "../includes/Bullets.class.hpp"

Bullets::Bullets( void ) : Entity()
{
	this->_dir = 0;
}

Bullets::Bullets( Env *e, double x, double y, std::string d[], int dir, double speed, int t) : Entity(e, "Bullets", x, y, d, 1, speed)
{
	this->_type = t;
	this->_dir = dir;
	pushBullet();
}

Bullets::Bullets( Bullets const & src ) : Entity(src)
{
	this->_dir = 0;
}

void	Bullets::move( void )
{
	if (this->_dir)
		moveUp();
	else
		moveDown();
	if (this->_type == 1)
		moveLeft();
	if (this->_type == 2)
		moveRight();
}

int		Bullets::getDir( void ) const
{
	return (this->_dir);
}

void	Bullets::printBullet(void) const
{
	if (this->_dir > 0)
		attron(COLOR_PAIR(14));
	else
		attron(COLOR_PAIR(11));
	mvprintw(this->_y, this->_x, "%s", this->_display[0].c_str());
}

void	Bullets::pushBullet(void)
{
	this->_env->collision.pushBullet(this);
}

Bullets & Bullets::operator=( Bullets const & rhs )
{
	return (*this);
}

Bullets::~Bullets( void )
{
}
