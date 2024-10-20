 #pragma once

#include "Component.h"
#include <functional>
#include "CallInfo.h"
#include "Manifold.h"

/// <summary>
/// 최초 작성일 : 2023.07.31
/// 작성자 : 김동일 
/// 
/// UserScript의 부모클래스
/// </summary>
/// 
/// 






class MonoBehaviour : public Component
{
public:
	MonoBehaviour(string name);
	virtual ~MonoBehaviour();

public:
	virtual void Start() override {};
	virtual void Update(float deltaTime) override {};
	virtual void FixedUpdate(float deltaTime) override {};
	virtual void Render() override final {};
	virtual void Finalize() override {};

public:
	// 충돌 관련 함수
	virtual void OnCollisionEnter(const Manifold& collision) override {};
	virtual void OnCollisionStay(const Manifold& collision) override {};
	virtual void OnCollisionExit(const Manifold& collision) override {};

public:
	/// 이벤트 헬퍼 함수
	template <typename T>
	CallInfo MakeCallInfo(void (T::* func)(std::any))
	{
		static_assert(std::is_base_of_v<MonoBehaviour, T>, "T must be derived from MonoBehaviour");
		return CallInfo{ this, 
			[this, func](std::any handler) 
			{ 
				(static_cast<T*>(this)->*func)(handler); 
			} 
		};
	}
};