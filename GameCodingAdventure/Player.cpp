#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Missile.h"
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

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::A))
		_pos.x -= _stat.speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::D))
		_pos.x += _stat.speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::W))
		_pos.y -= _stat.speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::S))
		_pos.y += _stat.speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::Q))
		_barrelAngle += 10 * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::E))
		_barrelAngle -= 10 * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// TODO: 할일 - 미사일 추가 및 발사
		Missile* missile = GET_SINGLETON(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());
		missile->SetAngle(_barrelAngle);
		GET_SINGLETON(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	const LineMesh* mesh = GET_SINGLETON(ResourceManager)->GetLineMesh(L"Player");
	if (mesh)
		mesh->Render(hdc, _pos);

	// Change Color
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	// Draw barrel line
	Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

Pos Player::GetFirePos()
{
	Pos firePos = _pos;
	firePos.x += _barrelLength * ::cos(_barrelAngle);
	firePos.y -= _barrelLength * ::sin(_barrelAngle);

	return firePos;
}
