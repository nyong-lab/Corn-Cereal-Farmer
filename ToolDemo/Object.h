#pragma once
#include "../D2Dimgui/D2DEngine1.h"
#include "../Math/Vector2.h"
#include "../D2Dimgui/imgui.h"
#include <string>

/// <summary>
/// 임시로 만든 object의 부모클래스
/// 
/// 2023.07.31
/// 
/// 일단 상속구조로 만들어둘 예정 (근데 게임엔진을 가져오면 이 친구의 구조는 우찌 생겨먹어야 될까요)
/// </summary>
class Object
{

public:
	Object(int id, std::string name, Vector2 position, Vector2 size);
	~Object();

	virtual void Move(Vector2 vec) = 0;
	virtual void Render(D2DEngine1* d2dEngine) = 0;
	virtual void Update() = 0;

protected:
	std::string m_Name; //이름
	int m_ID; // 식별 번호
	Vector2 m_Position; //위치값
	Vector2 m_Size; //크기
	bool m_CollisionCheck; // 충돌체크 (마우스 이동을 위해서)
	ID3D11ShaderResourceView* m_Texture; // 이미지 렌더를 위한 코드
	std::string m_WindowID;


//getter setter
public:
	Vector2 GetPosition() { return m_Position; }
	void SetPosition(Vector2 position) { m_Position = position; }
	Vector2 GetSize() { return m_Size; }
	void SetSize(Vector2 size) { m_Size = size; }
	bool GetCollision() { return m_CollisionCheck;  }
	void SetCollision(bool collision) { m_CollisionCheck = collision; }
	int GetID() { return m_ID; }
	void SetID(int id) { m_ID = id; }
	std::string GetWindowID() { return m_WindowID; }
	void SetWindowID(std::string windowID) { m_WindowID = windowID; }
	ID3D11ShaderResourceView* GetImage() { return m_Texture; }
};

