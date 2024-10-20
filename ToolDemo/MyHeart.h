#pragma once
#include "Object.h"
#include "../D2Dimgui/D2DEngine1.h"
#include "../Math/Vector2.h"

/// <summary>
/// ��Ʈ ����� ����ϴ� object
/// �� ������ ���� ���� �ڵ��ϱ� �Ⱦ ���� ���� Ŭ����
/// 
/// 2023.08.01
/// �ۼ��� : ������
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

