#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "HungryEnemy.hpp"

HungryEnemy::HungryEnemy(int x, int y) : Enemy("play/enemy-4.png", x, y, 20, 20, 50, 20) {}
void HungryEnemy::Hit(float damage) {
	if (damage == 3)
		Velocity.x = Velocity.x >= 120 ? 120 : Velocity.x + 10;
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it : lockedTurrets)
			it->Target = nullptr;
		for (auto& it : lockedBullets)
			it->Target = nullptr;
		Enemy::getPlayScene()->EarnMoney(money);
		Enemy::getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}