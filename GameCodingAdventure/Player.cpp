#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"
#include "UIManager.h"
#include "Bullet.h"

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

	UpdateFireAngle();

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
	{
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.0f, 75.0f);
	}
	if (GET_SINGLETON(InputManager)->GetButton(KeyType::S))
	{
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.0f, 75.0f);
	}

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::Q))
	{
		// TODO: 할일 - 포신 각도 조절
	}


	if (GET_SINGLETON(InputManager)->GetButton(KeyType::E))
	{
		// TODO: 할일 - 포신 각도 조절
	}

	// TODO: 할일 - 파워 게이지 처리, 미사일 생성 및 발사
	if (GET_SINGLETON(InputManager)->GetButton(KeyType::SpaceBar))
	{
		
		float percent = GET_SINGLETON(UIManager)->GetPowerPercent();
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLETON(UIManager)->SetPowerPercent(percent);
	}
	if (GET_SINGLETON(InputManager)->GetButtonUp(KeyType::SpaceBar))
	{
		_isPlayerTurn = false;

		float percent = GET_SINGLETON(UIManager)->GetPowerPercent();
		float speed = 100 * percent;
		float angle = GET_SINGLETON(UIManager)->GetBarrelAngle();

		Bullet* bullet = GET_SINGLETON(ObjectManager)->CreateObject<Bullet>();
		bullet->SetOwner(this);
		bullet->SetPos(_pos);
		bullet->SetVelocity(Vector{ speed * ::cos(angle * PI / 180.0f), -1 * speed * ::sin(angle * PI / 180.0f) });
		GET_SINGLETON(ObjectManager)->Add(bullet);
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

	if (_isPlayerTurn)
	{
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		// Change Color
		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}



}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank)
		return L"MissileTank";

	return L"CannonTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left)
	{
		GET_SINGLETON(UIManager)->SetPlayerAngle(180.0f);
		GET_SINGLETON(UIManager)->SetBarrelAngle(180.0f - _fireAngle);
	}
	else
	{
		GET_SINGLETON(UIManager)->SetPlayerAngle(0.0f);
		GET_SINGLETON(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
