

template<typename T>
T* ResourceManager::LoadResource(LPCWSTR key, LPCWSTR filePath, wstring fileName, FLOAT size)
{
	auto iter = m_Resources.find(key);
	if (iter == m_Resources.end())
	{
		assert(filePath != L"" && "���ҽ� ó�� �ҷ��ö� ���ϰ�� �ʼ�!");

		T* resource = new T();
		if (resource->Load(filePath, fileName, size))
		{
			// �ε� �����ϸ� ���ҽ� �ֱ�
			m_Resources.insert(make_pair(key, resource));
			return resource;
		}
		else
		{
			assert(nullptr && "���ҽ� Ÿ���� �ȸ���!");
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
