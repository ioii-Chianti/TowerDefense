#include "IControl.hpp"

// 處理有所有 event (滑鼠、鍵盤)
// 動作之後會做啥讓 derive 去實作
namespace Engine {
	void IControl::OnKeyDown(int keyCode) {}
	void IControl::OnKeyUp(int keyCode) {}
	void IControl::OnMouseDown(int button, int mx, int my) {}
	void IControl::OnMouseUp(int button, int mx, int my) {}
	void IControl::OnMouseMove(int mx, int my) {}
	void IControl::OnMouseScroll(int mx, int my, int delta) {}
}