#pragma once

#include "Component.h"
#include "Vector2.h"

class Scene;
class Transform;
class GameOjbect;


/// <summary>
/// ���� �ۼ��� : 2023.08.09 
/// �ۼ��� : �赿��
/// 
/// ������Ʈ ī�޶�
/// </summary>
class Camera : public Component
{
public:
	Camera();
	~Camera();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void DebugRender() override;
	
public:
	void SetScene(Scene* scene) { m_Scene = scene; }
	 //WorldToCameraMatrix

private:
	/// ������ ������Ʈ�� ���� ���⼭ UI�� ���� ���� ����?
	Scene* m_Scene = nullptr;

	/// ȭ�鿡�� ��� �������ΰ�. �»� 0,0
	Vector2 m_ViewPosition;

	/// ȭ�鿡�� �׷��� ī�޶��� ũ�� 1 : �� ȭ��ũ��, 0 : �Ⱥ���
	Vector2 m_ViewSize;


	float m_Zoom;
};


