#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Cleaner.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"

const int Cleaner::Price = 0;
Cleaner::Cleaner(float x, float y) :
	Turret("play/bomb.png", x, y, 15, 0, Price, 0) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Cleaner::CreateBullet() {}