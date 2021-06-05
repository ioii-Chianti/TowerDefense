#ifndef CLEARNER_HPP
#define CLEARNER_HPP
#include "Turret.hpp"

class Cleaner: public Turret {
public:
	static const int Price;
    Cleaner(float x, float y);
	void CreateBullet() override;
};
#endif // CLEARNER_HPP
