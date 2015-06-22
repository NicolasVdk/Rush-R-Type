#include "../includes/Enemy.class.hpp"
#include "../includes/Bullets.class.hpp"

Enemy::Enemy( void ) : Entity()
{

}

Enemy::Enemy( Env *e, std::string d[], int l ) : Entity(e, "Enemy", BORDER + rand() % (e->getMaxX() - BORDER), 1, d, l, 2.5)
{
	if (this->_env->getScore() >= 200 && boss == 0)
	{
		this->_name = "Boss";
		boss = 1;
		this->_x = this->_env->getMaxX() / 2;
		this->_y = 1;
		this->_speed = 2.8;
		this->_type = 4;
		this->_life = 200;
	}
	else if (this->_env->getScore() >= 100 && rand() % 100 < 10)
	{
		this->_speed = 3.5;
		this->_type = 3;
		this->_life = 20;
	}
	else if (rand() % 100 < 30)
		this->_type = 2;
	else
		this->_type = 1;
	if (this->_x < e->getMaxX()/2)
		this->_side = 0;
	else
		this->_side = 1;
	pushEnemy();
}

Enemy::Enemy( Enemy const & src ) : Entity(src)
{

}

void	Enemy::pushEnemy(void)
{
	this->_env->collision.pushEnemy(this);
}

void	Enemy::move( void )
{
	if (this->_type != 4)
	{
		if (this->_side == 0)
		{
			moveRight();
			moveRight();
			moveDown();
			if (this->_x > this->_env->getMaxX())
				this->_side = 1;
		}
		else if (this->_side == 1)
		{
			moveLeft();
			moveLeft();
			moveDown();
			if (this->_x < 0)
				this->_side = 0;
		}
		if (this->_type == 3)
		{
			if (rand() % (100 * this->_env->getRate()) < 30)
				this->_side = this->_side == 0 ? 1 : 0;
			if (rand() % (100 * this->_env->getRate()) < 80)
				Fire();
		}
		else if (rand() % (100 * this->_env->getRate()) < 50)
			Fire();
	}
	else
	{
		if (this->_y < 30)
			moveDown();
		else
			this->_speed += 0.0001;
		if (this->_side == 0)
		{
			moveRight();
			if (this->_x > this->_env->getMaxX())
				this->_side = 1;
		}
		else if (this->_side == 1)
		{
			moveLeft();
			if (this->_x < 0)
				this->_side = 0;
		}
		if (rand() % (100 * this->_env->getRate()) < 20)
			this->_side = this->_side == 0 ? 1 : 0;
		if (this->_life < 100)
		{
			if (rand() % (100 * this->_env->getRate()) < 2000)
				Fire();
		}
		else
		{
			if (rand() % (100 * this->_env->getRate()) < 1000)
				Fire();
		}
	}

}

void	Enemy::Fire()
{
	if (this->_type == 4)
	{
		std::string		s1[] = { "/" };
		std::string		s2[] = { "|" };
		std::string		s3[] = { "\\" };
			new Bullets(this->_env, this->_x, this->_y + 1, s1, 0, 17.0, 1);
			new Bullets(this->_env, this->_x, this->_y + 1, s2, 0, 18.0, 0);
			new Bullets(this->_env, this->_x, this->_y + 1, s2, 0, 17.0, 2);
	}
	else if (this->_type == 3)
	{
		std::string		s1[] = { "/" };
		std::string		s2[] = { "|" };
		std::string		s3[] = { "\\" };
		new Bullets(this->_env, this->_x, this->_y + 1, s1, 0, 17.0, 1);
		new Bullets(this->_env, this->_x, this->_y + 1, s2, 0, 18.0, 0);
		new Bullets(this->_env, this->_x, this->_y + 1, s2, 0, 17.0, 2);
	}
	else if (this->_type == 2)
	{
		std::string		s1[] = { "/" };
		std::string		s2[] = { "\\" };
		new Bullets(this->_env, this->_x, this->_y + 1, s1, 0, 18.0, 1);
		new Bullets(this->_env, this->_x, this->_y + 1, s2, 0, 18.0, 2);
	}
	else
	{
		std::string		s[] = { "|" };
		new Bullets(this->_env, this->_x, this->_y + 1, s, 0, 18.0, 0);
	}
}

Enemy & Enemy::operator=( Enemy const & rhs )
{
	return (*this);
}

Enemy::~Enemy( void )
{

}
