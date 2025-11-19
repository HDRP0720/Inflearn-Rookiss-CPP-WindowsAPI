#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	// Player Ãß°¡
	{
		Player* player = GET_SINGLETON(ObjectManager)->CreateObject<Player>();
		player->SetPos({ 400, 400 });
		GET_SINGLETON(ObjectManager)->Add(player);
	}

}

void GameScene::Update()
{
	const vector<Object*>& objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
	{
		obj->Update();
	}
}

void GameScene::Render(HDC hdc)
{
	const vector<Object*>& objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
	{
		obj->Render(hdc);
	}
}
