#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "FortressScene.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{

}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	_radius = 20.0f;
}

void Bullet::Update()
{
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	// TODO: 且老 - Wind, Gravity
	float windPercent = GET_SINGLETON(UIManager)->GetWindPercent();
	_velocity.x += 20 * deltaTime * windPercent;
	_velocity.y += 1000 * deltaTime;

	_pos += _velocity * deltaTime;

	const vector<Object*>& objects = GET_SINGLETON(ObjectManager)->GetObjects();
	for (Object* obj : objects)
	{
		if (obj->GetObjectType() != ObjectType::Player) continue;

		if (obj == _owner) continue;

		Vector dir = _pos - obj->GetPos();
		if (dir.Length() < _radius + obj->GetRadius())
		{

			// TODO: 且老 - damage 贸府 殿

			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLETON(SceneManager)->GetCurrentScene());
			if (scene)
				scene->ChangePlayerTurn();	

			GET_SINGLETON(ObjectManager)->Remove(this);
			return;
		}
	}


	if (_pos.y > GWinSizeY * 1.5 || _pos.y < -GWinSizeY * 1.5)
	{
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLETON(SceneManager)->GetCurrentScene());
		if (scene)
			scene->ChangePlayerTurn();

		GET_SINGLETON(ObjectManager)->Remove(this);
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
