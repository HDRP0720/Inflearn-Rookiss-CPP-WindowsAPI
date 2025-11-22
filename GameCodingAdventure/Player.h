#pragma once
#include "Object.h"



class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	wstring GetMeshKey();

	void SetPlayerId(int32 playerId) { _playerId = playerId; }
	void SetPlayerType(PlayerType playerType) { _playerType = playerType; }
	void SetPlayerTurn(bool isPlayerTurn) { _isPlayerTurn = isPlayerTurn; }

	int32 GetPlayerId() { return _playerId; }
	PlayerType GetPlayerType() { return _playerType; }
	bool GetPlayerTurn() { return _isPlayerTurn; }

	void UpdateFireAngle();
	
public:
	int32 _playerId = 0;
	PlayerType _playerType = PlayerType::CannonTank;
	bool _isPlayerTurn = false;
	float _fireAngle = 0.f;
};

