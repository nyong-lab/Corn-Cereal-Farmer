#pragma once


#include "Scene.h"
#include "ZicoMath.h"

class GameManagerScript;

class MainScene: public Scene
{//
private:
	using Scene::Scene;
	virtual void Enter() override;

private:
	// 임시 변수
	// 우리의 카메라 컴포넌트 코드는 카메라 위치를 화면의 중심으로 보기 때문에 화면의 원점을 카메라의 중앙으로 옮겨줬다.
	// 우리가 보는 화면은 위 작업을 진행한 결과물이기 때문에 화면의 중심좌표는 960,540 이다.
	// 즉 배치할 오브젝트들은 화면의 중심좌표인 960,540 을 원점으로 봐야하기 때문에 아래 startPoint를 활용해야함
	Vector2 m_StartPoint{ 960.f, 540.f };
};