#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "ChickenBullet.hpp"
#include "Group.hpp"
#include "ErythrocyteTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

const int ErythrocyteTurret::Price = 50;
ErythrocyteTurret::ErythrocyteTurret(float x, float y) :
	Turret("play/turret-3.png", x, y, 15, 100, Price, 2) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void ErythrocyteTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new ChickenBullet(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}