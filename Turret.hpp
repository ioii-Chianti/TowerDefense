#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Sprite.hpp"

class Enemy;
class EnemyBullet;
class PlayScene;

class Turret: public Engine::Sprite {
protected:
	int hp;
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
	float CollisionRadius;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void OnExplode();
    virtual void CreateBullet() = 0;
public:
    bool Enabled = true;  // 可不可以買
    bool Preview = false;   // 可以買按下去那個影子
    Enemy* Target = nullptr;
    //std::list<Enemy*> lockedEnemies;
    //std::list<EnemyBullet*> lockedEnemyBullets;
    Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y, float radius, int hp, int price, float coolDown);
    // new
    virtual void Hit(float damage);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetHp() const;
	int GetPrice() const;
	float GetRadius() const;
};
#endif // TURRET_HPP
