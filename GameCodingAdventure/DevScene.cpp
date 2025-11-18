#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
}

void DevScene::Update()
{
	float deltaTime = GET_SINGLETON(TimeManager)->GetDeltaTime();

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::A))
		_playerPos.x -= _speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::D))
		_playerPos.x += _speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::W))
		_playerPos.y -= _speed * deltaTime;

	if (GET_SINGLETON(InputManager)->GetButton(KeyType::S))
		_playerPos.y += _speed * deltaTime;
}

void DevScene::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _playerPos, 50);
}
