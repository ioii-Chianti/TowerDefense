#ifndef REINERENEMY_HPP
#define REINERENEMY_HPP
#include "Enemy.hpp"

class ReinerEnemy : public Enemy {
public:
	ReinerEnemy(int x, int y);
	void Update(float deltaTime) override;
};
#endif // REINERENEMY_HPP