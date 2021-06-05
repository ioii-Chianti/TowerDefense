#ifndef HUNGRYENEMY_HPP
#define HUNGRYENEMY_HPP
#include "Enemy.hpp"

class HungryEnemy : public Enemy {
public:
	HungryEnemy(int x, int y);
	void Hit(float damage) override;
};
#endif // HUNGRYENEMY_HPP