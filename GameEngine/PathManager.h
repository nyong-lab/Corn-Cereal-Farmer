/// [2023/7/31] �ڿ���
/// --------------------------
/// ���� ��θ� �޾ƿ��� �����Լ�

#pragma once

#include <string>
using std::wstring;


namespace Path
{
	wstring GetBasePath();
	wstring MakeFilePath(wstring filePath);
	//bool FileExists(wstring filePath);
};

