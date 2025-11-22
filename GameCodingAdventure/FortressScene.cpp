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

	_playerTurn = 1;
	ChangePlayerTurn();
}

void FortressScene::Update()
{
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
		obj->Update();

	_sumTime += deltaTime;
	if (_sumTime >= 1.0f)
	{
		_sumTime = 0.0f;

		int32 time = GET_SINGLETON(UIManager)->GetRemainTime();
		time = max(0, time - 1);
		GET_SINGLETON(UIManager)->SetRemainTime(time);

		if (time == 0)
			ChangePlayerTurn();
	}
}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLETON(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
		obj->Render(hdc);
}

void FortressScene::ChangePlayerTurn()
{
	_playerTurn = (_playerTurn + 1) % 2;

	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
	{
		if (obj->GetObjectType() != ObjectType::Player) continue;

		Player* player = static_cast<Player*>(obj);
		if (player->GetPlayerId() == _playerTurn)
			player->SetPlayerTurn(true);
		else
			player->SetPlayerTurn(false);
	}

	// TODO: 할일 - 임시적인 데이터 초기화
	GET_SINGLETON(UIManager)->SetRemainTime(10);
	GET_SINGLETON(UIManager)->SetStaminaPercent(100.0f);
	GET_SINGLETON(UIManager)->SetPowerPercent(0.0f);
	GET_SINGLETON(UIManager)->SetWindPercent(static_cast<float>(-100 + rand() % 200));
}
