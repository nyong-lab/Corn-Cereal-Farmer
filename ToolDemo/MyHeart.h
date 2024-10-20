#pragma once
#include "Object.h"
#include "../D2Dimgui/D2DEngine1.h"
#include "../Math/Vector2.h"

/// <summary>
/// 하트 모양을 출력하는 object
/// 밥 먹으러 가기 전에 코딩하기 싫어서 대충 만든 클래스
/// 
/// 2023.08.01
/// 작성자 : 고윤서
/// </summary>

class MyHeart :
    public Object
{
public:
    MyHeart(int id, std::string name, Vector2 position, Vector2 size);
    ~MyHeart();

	virtual void Move(Vector2 vec) override;
	virtual void Render(D2DEngine1* d2dEngine) override;
	virtual void Update() override;
};

