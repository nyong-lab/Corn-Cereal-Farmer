#pragma once

class GameObject;
class Collider;


/// ========= ������Ʈ =========

/// <summary>
/// ������Ʈ�� Ÿ���� ��ȣ�� �������� ��� �̺�Ʈ���� �켱������ ������.
/// �ٸ��ǹ̷� ū ��ȣ�� ���� ���� ��ܿ� �������Ѵ�.
/// </summary>
enum class OBJECT_TYPE
{
	DEFAULT,	// �Ŵ��� ������Ʈ
	BACKGROUND, // ���

	FARM,		// ��
	ADDITINAL,  // ���, ����, ����, ���� ���� ����� �̹���,�ִϸ��̼�



	ANIMAL,		// ����	
	NPC,		// NPC
	BUILDING,	// �ǹ�
	WILDBOAR,   // �����
	TREE,		// ����
	PLAYER,		// �÷��̾�
	PLAYER_AIM, // �÷��̾� ����


	TEXTBUBBLE,	// ��ǳ��
	INTERACTION_ARROW, // ��ȣ�ۿ� ȭ��ǥ
	POLICEVIEW,	// Police �þ�
	NPCVIEW,	// NPC �þ�


	EFFECT,		// ����Ʈ
	// �Ʒ��� ������Ʈ Ÿ�Ժ��ʹ� ���콺 �̺�Ʈ�� �߻���
	UI = 30,

	CAMERA = 31,
	END = 32,
};

/// ========= �浹 ���� =========
struct Collision
{
	Collider* myCollider;

	GameObject* otherObject;
	Collider* otherCollider;
};


/// ========== FSM ���� =========
enum class STATE_TYPE
{
	IDLE,
	WALK,
	DEAD,
};