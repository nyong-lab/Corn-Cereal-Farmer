#include "pch.h"
#include "PathManager.h"
#include <windows.h>

#include <algorithm>
wstring Path::GetBasePath()
{
	WCHAR basePath[256];
	// 현재 디렉토리 경로를 가져온다
	GetCurrentDirectory(255, basePath);
	size_t length = wcslen(basePath);

	// 상위 폴더로 이동
	for (int i = length - 1; i >= 0; i--)
	{
		if (basePath[i] == '\\')
		{
			// NULL
			basePath[i] = '\0';
			break;
		}
	}

	wstring tempString = basePath;
	std::replace(tempString.begin(), tempString.end(), '\\', '/');

	tempString += L"/Resources";
// 	length = tempString.length();
// 	wcscpy_s(basePath, length + 1, tempString.c_str());
// 	wcscat_s(basePath, 255, L"/Resources");
	
	return tempString;
}

wstring Path::MakeFilePath(wstring filePath)
{
	wstring path;
	path += GetBasePath();
	path += filePath;
// 	WCHAR path[256] = {0};
// 	wcscat_s(path, 255, GetBasePath());
// 	wcscat_s(path, 255, filePath);
	return path;
}
