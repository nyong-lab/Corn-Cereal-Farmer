/// [2023/8/9] �ڿ���
/// --------------------------
/// Component�� ��ӹ��� UI
/// ��� UI�� �θ� Ŭ�����̴�

#pragma once

#include "../Math/Vector2.h"
#include "Component.h"

class UI : public Component
{
public:
	UI();
	virtual ~UI();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

public:
	// Getter & Setter
	bool GetMouseOn() { return m_MouseOn; }
	void SetLeftButtonDown(bool isBtnDown) { m_LeftButtonDown = isBtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLeftButtonDown();
	virtual void MouseLeftButtonUp();
	virtual void MouseLeftButtonClick();

	void MouseOnCheck();

protected:
	UI* m_parentUI;

	Vector2 m_FinalPosition;	// UI�� ���� ��ǥ ��ġ

	bool m_MouseOn;				// UI ���� ���콺�� �ִ���
	bool m_LeftButtonDown;		// UI�� ���� ��ư�� ���� �� �ִ���

	friend class UIManager;
};