/// [2023/7/31] �ڿ���
/// --------------------------
/// �̹���, ���� �� ���ӿ��� �ʿ��� ���ҽ���
/// ��� �������ִ� ���ҽ� �Ŵ����� ����� ����
/// 
/// ������ ��� �����. 
/// �ϴ� ���ø��� ����, �ϳ��� �ʿ� ���ҽ��� �����ϵ�
/// ���̳��� ĳ��Ʈ�� �̿��� ���ҽ��� Get�� �� �ְ� �غ��߰ڴ�
#pragma once

#include <assert.h>
#include <windows.h>
#include <string>
using std::wstring;
#include <map>
using std::map;
using std::pair;
using std::make_pair;
// ���漱��
class Resource;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

public:
	void Initialize();
	void Finalize();

	static ResourceManager* GetInstance() {
		if (!g_Instance) {
			g_Instance = new ResourceManager;
			atexit(ReleaseInstance);
		}
		return g_Instance;
	}

	static void ReleaseInstance() {
		if (g_Instance) {
			delete g_Instance;
			g_Instance = nullptr;
		}
	}

	/// <summary>
	/// ���ҽ��� ������ ����, ������ ���� �ҷ��ͼ� ���ҽ� �����̳ʿ� �ִ´�
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="key"> �����ϰ� �ҷ��ö� ����ϴ� Ű�� </param>
	/// <param name="filePath"> ���ҽ� �ҷ��� �� �ʿ��� ���� ��� </param>
	/// <param name="fileName"> ��Ʈ �̸� </param>
	/// <param name="size"> ��Ʈ ������ </param>
	/// <returns></returns>
	template<typename T>
	T* LoadResource(
		LPCWSTR key,
		LPCWSTR filePath = L"",
		wstring fileName = L"",
		FLOAT size = 0.f
	);


private:
	static ResourceManager* g_Instance;
	map<wstring, Resource*> m_Resources;
};



#include "ResourceManager.hpp"
