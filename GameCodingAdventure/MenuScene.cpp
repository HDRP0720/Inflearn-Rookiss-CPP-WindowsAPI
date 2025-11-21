#include "pch.h"
#include "MenuScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init()
{
}

void MenuScene::Update()
{
	if (GET_SINGLETON(InputManager)->GetButtonDown(KeyType::E))
		GET_SINGLETON(SceneManager)->ChangeScene(SceneType::FortressScene);
}

void MenuScene::Render(HDC hdc)
{
	const LineMesh* mesh = GET_SINGLETON(ResourceManager)->GetLineMesh(L"Menu");
	if (mesh)
		mesh->Render(hdc, Pos{ 0, 0 });
}
