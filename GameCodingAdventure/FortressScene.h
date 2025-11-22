#pragma once
#include "Scene.h"
class FortressScene : public Scene
{
public:
	FortressScene();
	virtual ~FortressScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void ChangePlayerTurn();

private:
	// TODO: 할일 - Init 단계에서 ChangePlayerTurn 함수를 통해 0번부터 시작할 수 있게 임시 초기화
	int32 _playerTurn = 1;	
	float _sumTime = 0.0f;
};

