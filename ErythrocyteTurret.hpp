#ifndef ERYTHROCYTETURRET_HPP
#define ERYTHROCYTETURRET_HPP
#include "Turret.hpp"

class ErythrocyteTurret : public Turret {
public:
	static const int Price;
	ErythrocyteTurret(float x, float y);
	void CreateBullet() override;
};
#endif // ERYTHROCYTETURRET_HPP
