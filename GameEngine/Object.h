#pragma once

/// <summary>
/// ���� �ۼ��� : 2023.07.26 
/// �ۼ��� : �赿��
/// ����Ƽ�� �����Ͽ� ���� ���� ������ ¥�� ��...
/// 
/// ����Ƽ������ Component Ŭ������ Object �� ��ӹ޴��� �� ������ �����ΰ�.. �ʿ伺�� �𸣰ڴ�. 
/// <summary>

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Finalize();

public:
	int GetInstanceID() const { return m_InstanceID; }  // 1. ID �� Ÿ���� ���̰� �����ΰ� 2. ID�� �ʿ��� ������? �����հ� �����ִ°ǰ�?

	string GetName() const { return m_Name; }

	static void Destory(Object* obj);
	static void DestoryAll(); 
	static void DontDestroyOnLoad(Object* obj); // �츮�� ���� ���ӿ� �ʿ��� �Լ��ϱ�? 

	// static void DestroyImmediate(Objects* obj); // ȣ��Ǵ� ���� �̺�Ʈ�� �Ѿ�°� ��ٸ��� �ʰ� �� ��� �ı���Ű�� �Լ�
	// static ?? FindObjectOfType();  // Type �� enum���� �����ϰ� �߰������� Type�� ������ ��������� �������� �ұ�?
	// static ?? FindObjectsOfType();
	// static Instantiate();	// ����Ƽ ������ �ý����ΰ�? 

	bool operator==(const Object& other) const { return m_InstanceID == other.m_InstanceID;}
	bool operator!=(const Object& other) const { return m_InstanceID != other.m_InstanceID;}

private:
	string m_Name = "";
	bool m_Persistent = false;
	int m_InstanceID = 0;
	// int hideFlags = 0;  // ���� ���� �����ε� �ϴ�. 

};

