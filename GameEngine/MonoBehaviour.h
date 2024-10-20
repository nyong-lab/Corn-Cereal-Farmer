 #pragma once

#include "Component.h"
#include <functional>
#include "CallInfo.h"
#include "Manifold.h"

/// <summary>
/// ���� �ۼ��� : 2023.07.31
/// �ۼ��� : �赿�� 
/// 
/// UserScript�� �θ�Ŭ����
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
	// �浹 ���� �Լ�
	virtual void OnCollisionEnter(const Manifold& collision) override {};
	virtual void OnCollisionStay(const Manifold& collision) override {};
	virtual void OnCollisionExit(const Manifold& collision) override {};

public:
	/// �̺�Ʈ ���� �Լ�
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