#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{

}

void Missile::Init()
{
	// TODO: 할일 - 스탯 임시 처리 (Data sheet 필요)
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	_pos.y -= _stat.speed * deltaTime;

	// TODO: 할일 - 충돌 처리 및 기타
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 50);
}