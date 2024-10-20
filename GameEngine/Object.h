#pragma once

/// <summary>
/// 최초 작성일 : 2023.07.26 
/// 작성자 : 김동일
/// 유니티를 참고하여 게임 엔진 구조를 짜는 중...
/// 
/// 유니티에서는 Component 클래스가 Object 를 상속받던데 그 이유는 무엇인가.. 필요성을 모르겠다. 
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
	int GetInstanceID() const { return m_InstanceID; }  // 1. ID 와 타입의 차이가 무엇인가 2. ID가 필요한 이유는? 프리팹과 관련있는건가?

	string GetName() const { return m_Name; }

	static void Destory(Object* obj);
	static void DestoryAll(); 
	static void DontDestroyOnLoad(Object* obj); // 우리가 만들 게임에 필요한 함수일까? 

	// static void DestroyImmediate(Objects* obj); // 호출되는 순간 이벤트로 넘어가는걸 기다리지 않고 그 즉시 파괴시키는 함수
	// static ?? FindObjectOfType();  // Type 을 enum으로 관리하고 추가적으로 Type을 가지는 멤버변수도 만들어줘야 할까?
	// static ?? FindObjectsOfType();
	// static Instantiate();	// 유니티 프리팹 시스템인가? 

	bool operator==(const Object& other) const { return m_InstanceID == other.m_InstanceID;}
	bool operator!=(const Object& other) const { return m_InstanceID != other.m_InstanceID;}

private:
	string m_Name = "";
	bool m_Persistent = false;
	int m_InstanceID = 0;
	// int hideFlags = 0;  // 은신 관련 변수인듯 하다. 

};

