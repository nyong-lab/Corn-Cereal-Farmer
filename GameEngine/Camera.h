#pragma once

#include "Component.h"
#include "Vector2.h"

class Scene;
class Transform;
class GameOjbect;


/// <summary>
/// 최초 작성일 : 2023.08.09 
/// 작성자 : 김동일
/// 
/// 컴포넌트 카메라
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
	/// 렌더할 오브젝트의 모임 여기서 UI는 렌더 하지 말까?
	Scene* m_Scene = nullptr;

	/// 화면에서 어디 찍을것인가. 좌상 0,0
	Vector2 m_ViewPosition;

	/// 화면에서 그려질 카메라의 크기 1 : 딱 화면크기, 0 : 안보임
	Vector2 m_ViewSize;


	float m_Zoom;
};


