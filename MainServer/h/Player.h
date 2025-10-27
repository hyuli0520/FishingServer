#pragma once
#include "GameObject.h"

class GameSession;
class Player : public GameObject
{
	using Super = GameObject;
public:
	Player() = default;
	Player(unsigned long long id);
	virtual ~Player();

	void SetSession(GameSession* session);
	GameSession* GetSession() const { return m_session; }
	void SetPosInfo(Protocol::PositionInfo position);
	Protocol::PositionInfo GetPosInfo() const { return m_position; }

	void BeginPlay() override;
	void Tick() override;

private:
	Protocol::PositionInfo m_position;
	GameSession* m_session;
};