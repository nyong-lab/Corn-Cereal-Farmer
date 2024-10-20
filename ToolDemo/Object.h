#pragma once
#include "../D2Dimgui/D2DEngine1.h"
#include "../Math/Vector2.h"
#include "../D2Dimgui/imgui.h"
#include <string>

/// <summary>
/// �ӽ÷� ���� object�� �θ�Ŭ����
/// 
/// 2023.07.31
/// 
/// �ϴ� ��ӱ����� ������ ���� (�ٵ� ���ӿ����� �������� �� ģ���� ������ ���� ���ܸԾ�� �ɱ��)
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
	std::string m_Name; //�̸�
	int m_ID; // �ĺ� ��ȣ
	Vector2 m_Position; //��ġ��
	Vector2 m_Size; //ũ��
	bool m_CollisionCheck; // �浹üũ (���콺 �̵��� ���ؼ�)
	ID3D11ShaderResourceView* m_Texture; // �̹��� ������ ���� �ڵ�
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

