#include "pch.h"
#include "Object.h"


/// <summary>
/// 생성자
/// </summary>
Object::Object()
{
}

/// <summary>
/// 소멸자
/// </summary>
Object::~Object()
{
}

/// <summary>
/// 오브젝트 업데이트
/// </summary>
void Object::Update(float deltaTime)
{

}


/// <summary>
/// 오브젝트 렌더
/// </summary>
void Object::Render()
{

}

/// <summary>
/// 명시적 해제
/// </summary>
void Object::Finalize()
{

}

/// <summary>
/// 오브젝트 파괴
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
/// 모든 오브젝트 파괴
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
/// 씬 전환시에 파괴되지 않도록 설정
/// </summary>
void Object::DontDestroyOnLoad(Object* obj)
{
	/*if (obj)
	{
		obj->m_Persistent = true;
	}*/
}