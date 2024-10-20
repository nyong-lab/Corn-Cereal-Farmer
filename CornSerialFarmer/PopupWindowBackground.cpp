#include "PopupWindowBackground.h"
#include "Define.h"

#include "ResourceManager.h"
#include "ImageRenderer.h"
#include "UI.h"
#include "Image.h"
#include "Panel.h"

#include "Transform.h"

PopupWindowBackground::PopupWindowBackground()
	: GameObject("PopupWindowBG", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 540.f));
	GetTransform()->SetSize(Vector2(1920.f, 1080.f));

	UI* emptyPanel = new Panel;
	AddComponent(emptyPanel);

	ImageRenderer* popupWindowBGImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"PopupWindow_BG", L"/Image/UI/popup_window_background.png")->GetImage());
	AddComponent(popupWindowBGImage);
}

PopupWindowBackground::~PopupWindowBackground()
{

}
