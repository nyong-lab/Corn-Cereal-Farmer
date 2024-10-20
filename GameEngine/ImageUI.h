/// [2023/8/11] 박연하
/// --------------------------
/// 부모 UI 사이즈에 맞춰 이미지를 그려주는 컴포넌트

#pragma once

#include "UI.h"

enum class IMAGE_EVENT
{
	DEFALUT,
	HOVER,
	LBTDOWN,
	LBTUP,
	LBTCLICK,
};

class ImageUI : public UI
{
public:
	ImageUI(
		Vector2 size,
		ID2D1Bitmap* image,
		bool imageChangeMode = false,
		Vector2 imageOffset = {0.f, 0.f},
		Vector2 slicePos = {0.f, 0.f}
	);
	virtual ~ImageUI();

public:
	virtual void Render() override;
	virtual void FixedUpdate(float deltatime) override;

	virtual void MouseOn();
	virtual void MouseLeftButtonDown();
	virtual void MouseLeftButtonUp();
	virtual void MouseLeftButtonClick();

protected:
	ID2D1Bitmap* m_Image;

	Vector2 m_SlicePos;
	Vector2 m_ImageOffset;

	bool m_ImageChangeMode;
	IMAGE_EVENT m_ImageChange;
	IMAGE_EVENT m_beforeImageState;
};

