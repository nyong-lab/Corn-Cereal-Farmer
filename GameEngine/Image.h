/// [2023/8/1] 박연하
/// --------------------------
/// 리소스를 상속받은 이미지 클래스

#pragma once
#include "Resource.h"

struct ID2D1Bitmap;

class Image : public Resource
{
public:
	Image();
	virtual ~Image();

public:
	virtual bool Load(wstring filePath, wstring fileName, FLOAT size) override;
	virtual void UnLoad() override;

public:
	void SetImage(ID2D1Bitmap* image) { m_Image = image; }
	ID2D1Bitmap* GetImage() { return m_Image; }

private:
	ID2D1Bitmap* m_Image;
};

