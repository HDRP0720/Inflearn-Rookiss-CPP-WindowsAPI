#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init()
{
	// Player
	{
		//LineMesh* mesh = new LineMesh();
		//mesh->Load(L"Player.txt");
		//_lineMeshes[L"Player"] = mesh;
	}

	// UI
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"UI.txt");
		_lineMeshes[L"UI"] = mesh;
	}

	// Menu
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"Menu.txt");
		_lineMeshes[L"Menu"] = mesh;
	}

	// MissileTank
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"MissileTank.txt");
		_lineMeshes[L"MissileTank"] = mesh;
	}

	// CannonTank
	{
		LineMesh* mesh = new LineMesh();
		mesh->Load(L"CannonTank.txt");
		_lineMeshes[L"CannonTank"] = mesh;
	}

}

void ResourceManager::Clear()
{
	for (auto mesh : _lineMeshes)
		SAFE_DELETE(mesh.second);

	_lineMeshes.clear();
}

const LineMesh* ResourceManager::GetLineMesh(wstring key)
{
	auto findIt = _lineMeshes.find(key);
	if (findIt == _lineMeshes.end()) return nullptr;

	return findIt->second;
}
