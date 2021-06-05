#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed;
	float hp;
	int money;
	float coolDown;
	float reload = 0;
	//std::list<Enemy*>::iterator lockedEnemyIterator;
	PlayScene* getPlayScene();
	virtual void OnExplode();
	virtual void CreateBullet();
public:
	float reachEndTime;
	//Turret *Target = nullptr;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money);
 	virtual void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // ENEMY_HPP
