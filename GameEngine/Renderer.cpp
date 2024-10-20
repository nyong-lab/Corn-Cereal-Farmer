#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
	: Component(typeid(this).name())
{

}

Renderer::Renderer(string name)
	: Component(name)
{

}

Renderer::~Renderer()
{

}

void Renderer::Start()
{

}

void Renderer::Update(float deltaTime)
{

}

void Renderer::FixedUpdate(float deltaTime)
{

}

void Renderer::Render()
{

}

void Renderer::Finalize()
{

}