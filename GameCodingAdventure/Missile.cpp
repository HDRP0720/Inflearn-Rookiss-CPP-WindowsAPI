#include "pch.h"
#include "Missile.h"
#include "TimeManager.h"
#include "ObjectManager.h"

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
	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
	{
		if (obj == this) continue;

		if (obj->GetObjectType() != ObjectType::Monster) continue;

		Pos p1 = GetPos();
		Pos p2 = obj->GetPos();

		const float dx = p1.x - p2.x;
		const float dy = p1.y - p2.y;
		float dist = sqrt(dx * dx + dy * dy);
		if (dist < 25)
		{
			GET_SINGLETON(ObjectManager)->Remove(obj);
			GET_SINGLETON(ObjectManager)->Remove(this);
			return;
		}
	}

	if (_pos.y < -200)
	{
		GET_SINGLETON(ObjectManager)->Remove(this);
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}