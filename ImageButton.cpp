#include <functional>
#include <memory>

#include "Collider.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Point.hpp"
#include "Resources.hpp"

namespace Engine {
	/*  @param img 滑鼠碰到的圖
		@param imgIn 平常的圖  
		其他和普通物件一樣 */
	ImageButton::ImageButton(std::string img, std::string imgIn, float x, float y, float w, float h, float anchorX, float anchorY) :
		Image(img, x, y, w, h, anchorX, anchorY), imgOut(Resources::GetInstance().GetBitmap(img)), imgIn(Resources::GetInstance().GetBitmap(imgIn)) {
		Point mouse = GameEngine::GetInstance().GetMousePosition();
		mouseIn = Collider::IsPointInBitmap(Point((mouse.x - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (mouse.y - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
		if (!mouseIn || !Enabled) bmp = imgOut;
		else bmp = this->imgIn;
	}
	// 按下後的回應
	void ImageButton::SetOnClickCallback(std::function<void(void)> onClickCallback) {
		OnClickCallback = onClickCallback;
	}
	void ImageButton::OnMouseDown(int button, int mx, int my) {
		if ((button & 1) && mouseIn && Enabled) {
			if (OnClickCallback)
				OnClickCallback();
		}
	}
	// 判斷要顯示進還出
	void ImageButton::OnMouseMove(int mx, int my) {
		mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
		if (!mouseIn || !Enabled) bmp = imgOut;
		else bmp = imgIn;
	}
}
