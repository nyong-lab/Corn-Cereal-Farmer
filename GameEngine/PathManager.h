/// [2023/7/31] 박연하
/// --------------------------
/// 파일 경로를 받아오는 전역함수

#pragma once

#include <string>
using std::wstring;


namespace Path
{
	wstring GetBasePath();
	wstring MakeFilePath(wstring filePath);
	//bool FileExists(wstring filePath);
};

