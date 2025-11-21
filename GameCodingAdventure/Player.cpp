#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"

Player::Player() : Object(ObjectType::Player)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// TODO: 할일 - 스탯 임시 처리 (Data sheet 필요)
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	//_pos.x = 400;
	//_pos.y = 500;
	_pos = { 400, 500 };
}

void Player::Update()
{
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	if (_isPlayerTurn == false) return;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= _stat.speed * deltaTime;
		_dir = Dir::Left;
	}

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += _stat.speed * deltaTime;
		_dir = Dir::Right;
	}

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::W))
		//_pos.y -= _stat.speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::S))
		//_pos.y += _stat.speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::Q))
	{
		// TODO: 할일 - 포신 각도 조절
	}


	if (GET_SINGLETON(InputManager)->GetButton(KeyType::E))
	{
		// TODO: 할일 - 포신 각도 조절
	}


	if (GET_SINGLETON(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO: 할일 - 미사일 생성 및 발사
	}
}

void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left)
	{
		const LineMesh* mesh = GET_SINGLETON(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
	}
	else
	{
		const LineMesh* mesh = GET_SINGLETON(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
			mesh->Render(hdc, _pos, -0.5f, 0.5f);
	}


	// Change Color
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank)
		return L"MissileTank";

	return L"CannonTank";
}
