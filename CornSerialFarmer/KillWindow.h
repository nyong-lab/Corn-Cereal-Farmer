#pragma once

#include <GameObject.h>
class ImageRenderer;
class Animator;
class UI;

class KillWindow : public GameObject
{
public:
	KillWindow(int date, int npc1 = 999, int npc2 = 999, int npc3 = 999, int npc4 = 999);
	~KillWindow();

public:
	int m_Npc1 = 0;
	int m_Npc2 = 0;
	int m_Npc3 = 0;
	int m_Npc4 = 0;

	GameObject* m_NpcSelect[4];
	Animator* m_NpcSelectAnimator[4];

	GameObject* m_NpcSelectIcon[4];
	ImageRenderer* m_NpcSelectImage[4];
};

