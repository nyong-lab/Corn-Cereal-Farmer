/// [2023/8/12] 박연하
/// --------------------------
/// 이미지를 출력하는 렌더러

#pragma once
#include "Renderer.h"
#include "../Math/Vector2.h"

class Image;

class ImageRenderer : public Renderer
{
public:
	ImageRenderer(
		ID2D1Bitmap* image,
		Vector2 positionOffset = { 0.f, 0.f },
		Vector2 sliceStartPos = { 999.f, 999.f },
		Vector2 sliceSize = { 999.f, 999.f }
	);
	virtual ~ImageRenderer();

public:
	// Getter & Setter
	void SetImage(ID2D1Bitmap* image) { m_Image = image; }

	void SetPositionOffset(Vector2 positionOffset) { m_PositionOffset = positionOffset; }
	void SetSliceStartPos(Vector2 sliceStartPos) { m_SliceStartPos = sliceStartPos; }
	void SetSliceSize(Vector2 sliceSize) { m_SliceSize = sliceSize; }
	void SetAdditionalOffset(D2D1_RECT_F additionalOffset) { m_AdditionalOffset = additionalOffset; }

	Vector2 GetSize() { return m_Size; }
	ID2D1Bitmap* GetImage() { return m_Image; }

	void SetOpacity(float opacity) { m_Opacity = opacity; }
	bool GetPadeInComplete() { return m_ActiveFadeIn; }
	bool GetPadeOutComplete() { return m_ActiveFadeOut; }

	bool GetIsActivate() const { return m_IsActivate; }
	void SetIsActivate(bool val) { m_IsActivate = val; }

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

public:
	void FadeIn(float outputTime);
	void FadeOut(float outputTime);
	void ApplyFadeInOut(float deltaTime);

private:
	/// 원본
	ID2D1Bitmap* m_Image;

	Vector2 m_Size;
	Vector2 m_PositionOffset;
	Vector2 m_SliceStartPos;
	Vector2 m_SliceSize;
	D2D1_RECT_F m_AdditionalOffset;

	bool m_ActiveFadeOut;
	bool m_ActiveFadeIn;
	float m_TimePassed;
	float m_FadeValue;
	float m_Opacity;

	bool m_IsActivate;
};

