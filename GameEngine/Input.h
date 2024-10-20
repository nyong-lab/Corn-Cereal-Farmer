#pragma once

#include "Input.h"

#include <vector>
using std::vector;



#include "../Math/Vector2.h"

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,

	F1,
	F2,
	F3,
	F4,

	LAST,// 키 마지막
};


struct KeyInfo
{
	KEY_STATE keyState;
	bool bPrevPushed;
};

class Input
{
private:
	static const int arrayVK[(int)KEY::LAST];

	Input();
	~Input();

public:
	void Initialize() ;
	void Update();

	static Input* GetInstance() {
		if (!g_Instance) {
			g_Instance = new Input;
			atexit(ReleaseInstance);
		}
		return g_Instance;
	}

	static void ReleaseInstance() {
		if (g_Instance) {
			delete g_Instance;
			g_Instance = nullptr;
		}
	}

public:
	static bool GetKeyDown(KEY key);
	static bool GetKeyUp(KEY key);
	static bool GetKey(KEY key);
	static Vector2 GetMousePos();


private:
	static Input* g_Instance;

	vector<KeyInfo> m_KeyVector;
	Vector2			m_CurMousePos;

};

