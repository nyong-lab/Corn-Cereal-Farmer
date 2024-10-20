
/// <summary>
/// ���� �ۼ��� : 2023.08.21
/// �ۼ��� : ��â��
/// 
/// 
/// ������ �ݶ��̴� 
/// </summary>

#pragma once
#include "Collider.h"
class PolygonCollider :
    public Collider
{
public:
	PolygonCollider();
	~PolygonCollider();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void DebugRender() override;

	virtual void Finalize() override;

public:
	// get- set
	void AddVertice(Vector2 vertice);
	Vector2* GetVertices() { return (Vector2*)vertices; }
	const int GetVerticeCount() { return verticeCount; }

public:
	// �浹 ���� �Լ�
	virtual void OnCollisionEnter(const Manifold& collision) override;
	virtual void OnCollisionStay(const Manifold& collision) override;
	virtual void OnCollisionExit(const Manifold& collision) override;


public:
	virtual bool Collides(CircleCollider* circle) override;
	virtual bool Collides(BoxCollider* box) override;
	virtual Vector2 FindFurthestVertice(Vector2 direction) override;
	virtual int FindFurthestVerticeIndex(Vector2 direction) override;

private:
	int verticeCount;
	D2D1_POINT_2F* vertices;


};