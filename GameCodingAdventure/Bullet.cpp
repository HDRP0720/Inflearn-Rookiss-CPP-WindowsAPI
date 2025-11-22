#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
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

	// TODO: ÇÒÀÏ - Wind, Gravity

	_pos += _velocity * deltaTime;

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
