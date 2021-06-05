#include <allegro5/base.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BoomTurret.hpp"
#include "BoomBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int BoomTurret::Price = 80;
BoomTurret::BoomTurret(float x, float y) :
	Turret("play/turret-4.png", x, y, 25, 1, Price, 999) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void BoomTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(0, 0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new BoomBullet(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}

void BoomTurret::Hit(float damage) {
	hp -= damage;
	if (hp <= 0) {
		CreateBullet();
		OnExplode();
		getPlayScene()->TowerGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}

void BoomTurret::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
}

void BoomTurret::Draw() const {
	if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	Sprite::Draw();
	al_draw_circle(Position.x, Position.y, 300, al_map_rgb(0, 0, 255), 2);
}