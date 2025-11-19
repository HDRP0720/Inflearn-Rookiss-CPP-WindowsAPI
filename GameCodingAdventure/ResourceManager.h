#pragma once

class ResourceBase;
class LineMesh;

class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager);

	~ResourceManager();

public:
	void Init();
	void Clear();

	const LineMesh* GetLineMesh(wstring key);

private:
	unordered_map<wstring, LineMesh*> _lineMeshes;
};

