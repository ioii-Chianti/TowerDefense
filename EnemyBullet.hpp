#ifndef ENEMYBULLET_HPP
#define ENEMYBULLET_HPP
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class EnemyBullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	Enemy* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Turret* turret);
public:
	Turret* Target = nullptr;
	explicit EnemyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void Update(float deltaTime) override;
};
#endif // ENEMYBULLET_HPP