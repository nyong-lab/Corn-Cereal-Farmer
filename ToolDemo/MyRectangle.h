#pragma once

#include "Object.h"
#include "../D2Dimgui/D2DEngine1.h"
#include "../Math/Vector2.h"

/// <summary>
/// 사각형
/// 
/// object의 시작은 사각형 그리기임
/// 
/// 2023.07.31
/// </summary>

class MyRectangle :
    public Object
{
public:
	MyRectangle(int id, std::string name, Vector2 position, Vector2 size);
    ~MyRectangle();

	virtual void Move(Vector2 vec) override;
	virtual void Render(D2DEngine1* d2dEngine) override;
	virtual void Update() override;
};

