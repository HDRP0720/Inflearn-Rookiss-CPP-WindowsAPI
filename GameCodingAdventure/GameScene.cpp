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
	// Player 추가
	{
		Player* player = GET_SINGLETON(ObjectManager)->CreateObject<Player>();
		player->SetPos(Pos{ 400, 400 });
		GET_SINGLETON(ObjectManager)->Add(player);
	}

	// Monster 추가
	//for(int32 i = 0; i < 5; i++)
	{
		Monster* monster = GET_SINGLETON(ObjectManager)->CreateObject<Monster>();
		//monster->SetPos(Pos{ static_cast<float>((i + 1) * 100), 100 });
		monster->SetPos(Pos{ 100, 100 });
		GET_SINGLETON(ObjectManager)->Add(monster);
	}

}

void GameScene::Update()
{
	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
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
