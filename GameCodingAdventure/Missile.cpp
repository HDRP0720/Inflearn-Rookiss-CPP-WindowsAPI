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

	if (_target == nullptr)
	{
		_pos.x += _stat.speed * deltaTime * ::cos(_angle);
		_pos.y -= _stat.speed * deltaTime * ::sin(_angle);

		_beginHommingTime += deltaTime;
		if (_beginHommingTime >= 0.2f)
		{
			const vector<Object*>& objects = GET_SINGLETON(ObjectManager)->GetObjects();
			for (Object* obj : objects)
			{
				if (obj->GetObjectType() == ObjectType::Monster)
				{
					_target = obj;
					break;
				}
			}
		}
	}
	else
	{
		Vector dir = _target->GetPos() - GetPos();
		dir.Normalize();

		Vector moveDir = dir * _stat.speed * deltaTime;
		_pos += moveDir;
	}

	// TODO: 할일 - 충돌 처리 및 기타
	const vector<Object*> objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
	{
		if (obj == this) continue;

		if (obj->GetObjectType() != ObjectType::Monster) continue;

		Vector p1 = GetPos();
		Vector p2 = obj->GetPos();

		Vector dir = p2 - p1;
		float dist = dir.Length();
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