#include "pch.h"
#include "Object.h"


/// <summary>
/// ������
/// </summary>
Object::Object()
{
}

/// <summary>
/// �Ҹ���
/// </summary>
Object::~Object()
{
}

/// <summary>
/// ������Ʈ ������Ʈ
/// </summary>
void Object::Update(float deltaTime)
{

}


/// <summary>
/// ������Ʈ ����
/// </summary>
void Object::Render()
{

}

/// <summary>
/// ����� ����
/// </summary>
void Object::Finalize()
{

}

/// <summary>
/// ������Ʈ �ı�
/// </summary>
void Object::Destory(Object* obj)
{
// 	if (obj)
// 	{
// 		auto iter = find(m_Objects.begin(), m_Objects.end(), obj);
// 
// 		if (iter != m_Objects.end())
// 		{
// 			m_Objects.erase(iter);
// 			delete obj;
// 		}
// 	}
}

/// <summary>
/// ��� ������Ʈ �ı�
/// </summary>
void Object::DestoryAll()
{
// 	vector<Object*> tempObjects;
// 
// 	for (auto iter : m_Objects) 
// 	{
// 		if (!iter->m_Persistent)
// 		{
// 			delete iter;
// 		}
// 
// 		else
// 		{
// 			tempObjects.push_back(iter);
// 		}
// 	}
// 
// 	m_Objects.clear();
// 	m_Objects = tempObjects;
}

/// <summary>
/// �� ��ȯ�ÿ� �ı����� �ʵ��� ����
/// </summary>
void Object::DontDestroyOnLoad(Object* obj)
{
	/*if (obj)
	{
		obj->m_Persistent = true;
	}*/
}