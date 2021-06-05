#include <allegro5/base.h>
#include <random>

#include "Collider.hpp"
#include "DirtyEffect.hpp"
#include "EnemyBullet.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"
#include "Turret.hpp"

PlayScene* EnemyBullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void EnemyBullet::OnExplode(Turret* turret) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), turret->Position.x, turret->Position.y));
}
EnemyBullet::EnemyBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
	Sprite("play/bullet-11.png", position.x, position.y), speed(500), damage(10), parent(parent) {
	Velocity = forwardDirection * speed;
	Rotation = rotation;
	CollisionRadius = 4;
}
void EnemyBullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
	for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
		if (!turret->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->GetRadius())) {
			OnExplode(turret);
			turret->Hit(damage);
			getPlayScene()->EnemyBulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
		getPlayScene()->EnemyBulletGroup->RemoveObject(objectIterator);
}
