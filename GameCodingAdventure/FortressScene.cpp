#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"
#include "Player.h"
#include "LineMesh.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h";
#include "TimeManager.h";

FortressScene::FortressScene()
{
}

FortressScene::~FortressScene()
{
}

void FortressScene::Init()
{
	GET_SINGLETON(UIManager)->Init();

	// Player
	{
		Player* player = GET_SINGLETON(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::MissileTank);

		player->SetPlayerId(0);
		player->SetPlayerTurn(true);

		player->SetPos(Vector{ 100, 400 });
		GET_SINGLETON(ObjectManager)->Add(player);
	}

	// Player
	{
		Player* player = GET_SINGLETON(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::CannonTank);

		player->SetPlayerId(1);
		player->SetPlayerTurn(false);

		player->SetPos(Vector{ 700, 400 });
		GET_SINGLETON(ObjectManager)->Add(player);
	}


}

void FortressScene::Update()
{
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
		obj->Update();
}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLETON(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
		obj->Render(hdc);
}
