/// [2023/7/31] 박연하
/// --------------------------
/// 리소스들은 이 클래스를 상속받게 할 예정

#pragma once

#include <string>
using std::wstring;

class Resource
{
public:
	Resource();
	virtual ~Resource();

public:
	virtual bool Load(wstring filePath, wstring fileName, FLOAT size) abstract;
	virtual void UnLoad() abstract;
	
public:
	void SetFilePath(wstring filePath) { m_filePath = filePath; }
	wstring GetFilePath() { return m_filePath; }

private:
	wstring m_filePath;
};