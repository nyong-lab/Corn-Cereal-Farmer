#include "pch.h"
#include "Input.h"
#include <assert.h>
Input* Input::g_Instance = nullptr;

Input::Input()
{
	
}

Input::~Input()
{

}

const int Input::arrayVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	'1',
	'2',
	'3',
	'4',
	'5',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LBUTTON,
	VK_RBUTTON,

	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
};




void Input::Initialize()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		m_KeyVector.push_back(KeyInfo{ KEY_STATE::NONE, false });
	}
}

void Input::Update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	// HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	HWND hWnd = GetFocus();

	// �����찡 ��Ŀ������ �� 
	if (hWnd != nullptr) {
		// Mouse ��ġ ��� 

		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(hWnd, &ptPos);

		m_CurMousePos = Vector2((float)ptPos.x, (float)ptPos.y);

		for (int i = 0; i < (int)KEY::LAST; ++i) {
			// Ű�� �����ֵ�. 
			if (GetAsyncKeyState(arrayVK[i]) & 0x8000)
			{
				if (m_KeyVector[i].bPrevPushed) {
					// ���� �����ӿ� ���� �־���. 
					m_KeyVector[i].keyState = KEY_STATE::HOLD;
				}
				else {
					// ���� �����ӿ� �������� �ʾѵ�. 
					m_KeyVector[i].keyState = KEY_STATE::TAP;
				}
				m_KeyVector[i].bPrevPushed = true;
			}
			// Ű�� �ȴ����ִ�. 
			else {
				if (m_KeyVector[i].bPrevPushed) {
					// ���� �����ӿ��� �����־���. 
					m_KeyVector[i].keyState = KEY_STATE::AWAY;
				}
				else {
					// ���� �����ӿ� �������� �ʾҵ�. 
					m_KeyVector[i].keyState = KEY_STATE::NONE;
				}
				m_KeyVector[i].bPrevPushed = false;
			}

		}
	}
	// ��Ŀ���� �ƴҶ� 
	else {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			m_KeyVector[i].bPrevPushed = false;

			if (KEY_STATE::TAP == m_KeyVector[i].keyState || KEY_STATE::HOLD == m_KeyVector[i].keyState)
			{
				m_KeyVector[i].keyState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_KeyVector[i].keyState) {
				m_KeyVector[i].keyState = KEY_STATE::NONE;
			}
		}
	}

}

bool Input::GetKeyDown(KEY key)
{
	assert(g_Instance);
	return g_Instance->m_KeyVector[(int)key].keyState == KEY_STATE::TAP;
}

bool Input::GetKeyUp(KEY key)
{
	assert(g_Instance);
	return g_Instance->m_KeyVector[(int)key].keyState == KEY_STATE::AWAY;
}

bool Input::GetKey(KEY key)
{
	assert(g_Instance);
	return g_Instance->m_KeyVector[(int)key].keyState == KEY_STATE::HOLD;
}

Vector2 Input::GetMousePos()
{
	assert(g_Instance);
	return g_Instance->m_CurMousePos;
}

