#include "pch.h"
#include "Resource.h"
#include "PathManager.h"
#include "Image.h"
#include "GraphicsEngine.h"
using namespace Path;

Image::Image()
	: Resource()
	, m_Image()
{

}

Image::~Image()
{

}

bool Image::Load(wstring filePath, wstring fileName, FLOAT size)
{
	SetFilePath(MakeFilePath(filePath));
	
	GraphicsEngine::GetInstance()->LoadBitmapFromFile(
		&m_Image, 
		GetFilePath().c_str()
	);

	return true;
}

void Image::UnLoad()
{
	if (m_Image != nullptr)
	{
		m_Image->Release();
		m_Image = nullptr;
	}
}
