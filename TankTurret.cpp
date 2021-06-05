#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <iostream>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "TankTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

const int TankTurret::Price = 30;

TankTurret::TankTurret(float x, float y) :
	Turret("play/turret-6.png", x, y, 15, 500, Price, 999) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
// CreateBullet 是 pure virtual 一定要寫不然不能 new 物件
void TankTurret::CreateBullet() {
	std::cout << "no bullet for tank\n";
}