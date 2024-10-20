#pragma once

template<class T>
void SafeRelease(T** ppT)
{
	if (*ppT != nullptr)
	{
		(*ppT)->Release();
		(*ppT) = nullptr;
	}
}