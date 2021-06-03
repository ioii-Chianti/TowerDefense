#include "Point.hpp"
#include "IObject.hpp"

namespace Engine {
	IObject::IObject(float x, float y, float w, float h, float anchorX, float anchorY) :
		Position(Point(x, y)), Size(Point(w, h)), Anchor(Point(anchorX, anchorY)) {}
	std::list<std::pair<bool, IObject*>>::iterator IObject::GetObjectIterator() const {
		return objectIterator;
	}   // 回傳這個物件內的 iterator
	void IObject::Draw() const {}
	void IObject::Update(float deltaTime) {}
}
