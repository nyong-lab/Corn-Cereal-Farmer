#include "pch.h"
#include "Manifold.h"
#include "CollisionDefine.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"

void Manifold::Solve()
{
	CollisionFunc::CheckGJK(this, collider1, collider2);
}




void Manifold::SolveContact()
{


	Rigidbody* bodyA = collider1->GetGameObject()->GetComponent<Rigidbody>();
	Rigidbody* bodyB = collider2->GetGameObject()->GetComponent<Rigidbody>();
	// 
	//     float massA = (bodyA != nullptr) ? bodyA->GetMass() : 0.0f;
	//     float massB = (bodyB != nullptr) ? bodyB->GetMass() : 0.0f;
	// 
	//     // devided by zero ���� ���ش�..
	//     if (massA == 0.0f && massB == 0.0f) {
	//         return;
	//     }
	// 
	// 
	//     float totalInverseMass = 1.0f / (massA + massB);
	// 
	//     // ���޽� ũ�� ����
	//     float impulseMagnitude = depth / totalInverseMass;
	// 
	//     
	//     // ���� ������ ���޽��� ����Ѵ�.
	//     Vector2 impulse = normal * impulseMagnitude;
	Vector2 impulse = normal * (depth - 0.01f);
	// 
	// 
	//     // ��� �ٵ� ���޽��� ���Ѵ�.
	//     if (bodyA != nullptr) {
	//         bodyA->ApplyForce(impulse);
	//     }
	//     if (bodyB != nullptr) {
	//         bodyB->ApplyForce(-impulse);
	//     }


	if (bodyA != nullptr && !collider2->IsTrigger()) {
		Vector2 pos = bodyA->GetTransform()->GetLocalPosition();
		pos += impulse;
		bodyA->GetTransform()->SetLocalPosition(pos);
	}
	if (bodyB != nullptr && !collider1->IsTrigger()) {
		Vector2 pos = bodyB->GetTransform()->GetLocalPosition();
		pos -= impulse;
		bodyB->GetTransform()->SetLocalPosition(pos);
	}
}