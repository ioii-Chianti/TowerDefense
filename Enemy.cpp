#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "EnemyBullet.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"

PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
void Enemy::CreateBullet() {
	// direction of shooting
	Engine::Point diff = Engine::Point(-1, 0);
	float rotation = ALLEGRO_PI / 2;
	// param this is shoot from whom
	getPlayScene()->EnemyBulletGroup->AddNewObject(new EnemyBullet(Position, diff, rotation, this));
	AudioHelper::PlayAudio("missile.wav");
}

Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money) :
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money), coolDown(2) {
	CollisionRadius = radius;
	reachEndTime = 0;
	// x, y ���t��, Velocity.x = speed
	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	if (damage == 2 && Velocity.x > 0)
		Velocity.x = Velocity.x > 10 ? Velocity.x - 10 : 0;
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		if (damage != 1011) getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
void Enemy::Update(float deltaTime) {
	float remainSpeed = speed * deltaTime;
	Position.x -= Velocity.x * deltaTime;
	Position.y += Velocity.y * deltaTime;
	PlayScene* scene = getPlayScene();

	// close to turret, should stop
	for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
		if (!turret->Visible)
			continue;
		
		Engine::Point checkPosition(Position.x - 100, Position.y);
		if (Engine::Collider::IsCircleOverlap(checkPosition, CollisionRadius * 2, turret->Position, turret->GetRadius())) {
			Velocity.x = 0;
			// shoot to turret
			reload -= deltaTime;
				if (reload <= 0) {
					// shoot.
					reload = coolDown;
					CreateBullet();
				}
		}
	}

	// reach the base
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(1011);   // disappear
		getPlayScene()->Hit();   // home gets hit
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}
void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
