

template<typename T>
T* ResourceManager::LoadResource(LPCWSTR key, LPCWSTR filePath, wstring fileName, FLOAT size)
{
	auto iter = m_Resources.find(key);
	if (iter == m_Resources.end())
	{
		assert(filePath != L"" && "리소스 처음 불러올땐 파일경로 필수!");

		T* resource = new T();
		if (resource->Load(filePath, fileName, size))
		{
			// 로드 성공하면 리소스 넣기
			m_Resources.insert(make_pair(key, resource));
			return resource;
		}
		else
		{
			assert(nullptr && "리소스 타입이 안맞음!");
			return nullptr;
		}
	}
	else
	{
		T* resource = dynamic_cast<T*>(iter->second);
		assert(resource);
		return resource;
	}

}
