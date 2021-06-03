#ifndef IOBJECT_HPP
#define IOBJECT_HPP
#include <list>
#include <utility>

#include "Point.hpp"

namespace Engine {
	/// <summary>
	/// The base interface class for objects that needs to be drawn or rendered.
	/// 給所有會被畫出的物件的介面
	/// </summary>
	class IObject {
		friend class Group;
	protected:
		// The iterator of objects linked-list when added to scene.
		// Can make removing objects faster.
		// Reference: Iterator, which is also a Design Pattern when implementing.
		// 開一個這 list<std::pair<bool, IObject*>> 這個型態的迭代器 / 指標
		std::list<std::pair<bool, IObject*>>::iterator objectIterator{};
		/// <summary>
		/// The interface cannot be instantiated directly, must be inherited.
		/// </summary>
		explicit IObject() = default;
		/// <summary>
		/// <summary>
		/// Construct an IObject.
		/// 參數用於初始化 Position, Size, Anchor
		/// </summary>
		/// <param name="x">X-coordinate.</param>
		/// <param name="y">Y-coordinate.</param>
		/// <param name="w">Width of the image, 0 indicates original size.</param>
		/// <param name="h">Height of the image, 0 indicates original size.</param>
		/// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
		/// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
		explicit IObject(float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
	public:
		// Determines whether this object should be drawn and updated.
		// 會不會顯示
		bool Visible = true;
		// The object's position, center depends on Anchor.
		Point Position;
		// The object's size.
		Point Size;
		// The center of the object. (0, 0) means top-left, (1, 1) means bottom-right.
		Point Anchor;
		/// <summary>
		/// The default virtual destructor to support polymorphism destruction.
		/// </summary>
		virtual ~IObject() = default;
		/// <summary>
		/// Copy constructor does not add a new instance to scene, they are still the same object.
		/// </summary>
		IObject(const IObject& other) = default;
		/// <summary>
		/// Copy assignment operator does not add a new instance to scene, they are still the same object.
		/// </summary>
		IObject& operator=(IObject const&) = default;
		/// <summary>
		/// Retrieve the object iterator for later insertion.
		/// </summary>
		/// <returns>The object iterator.</returns>
		std::list<std::pair<bool, IObject*>>::iterator GetObjectIterator() const;
		/// <summary>
		/// Draw to window display.
		/// This is called when the game should redraw the window.
		/// 被畫出的初始化
		/// </summary>
		virtual void Draw() const;
		/// <summary>
		/// Run game logic such as updating the world, checking for collision, and so on.
		/// This is called when the game should update its logic, usually 'fps' times per second.
		/// 更新新的影格
		/// </summary>
		/// <param name="deltaTime">Time elapsed since last update, can be used to calculate value changes.</param>
		virtual void Update(float deltaTime);
	};
}
#endif // IOBJECT_HPP
