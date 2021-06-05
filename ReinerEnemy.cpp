#include <string>
#include <random>
#include "Point.hpp"
#include "PlayScene.hpp"
#include "ReinerEnemy.hpp"
#include "Turret.hpp"
#include "Collider.hpp"

ReinerEnemy::ReinerEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 20, 120, 1, 50) {
}
void ReinerEnemy::Update(float deltaTime) {
	float remainSpeed = speed * deltaTime;
	Position.x -= Velocity.x * deltaTime;
	Position.y += Velocity.y * deltaTime;
	PlayScene* scene = getPlayScene();

	reload -= deltaTime;
	if (reload <= 0) {
		// shoot.
		reload = coolDown;
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<int> distr(-100, 100);
		Velocity.y = distr(eng);
		CreateBullet();
	}



	// reach the base
	if (Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2) {
		Hit(1011);   // disappear
		getPlayScene()->Hit();   // home gets hit
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}