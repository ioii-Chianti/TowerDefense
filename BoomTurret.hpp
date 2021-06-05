#pragma once
#ifndef BOOMTURRET_HPP
#define BOOMTURRET_HPP
#include "Turret.hpp"

class BoomTurret : public Turret {
public:
	static const int Price;
	BoomTurret(float x, float y);
	void CreateBullet() override;
	void Hit(float damage) override;
	void Update(float deltaTime) override;
	void Draw() const;
};
#endif // BOOMTURRET_HPP