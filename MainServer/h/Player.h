#pragma once
#include "GameObject.h"

class GameObject;
class Player : public GameObject
{
	using Super = GameObject;
public:
	Player() = default;
	Player(unsigned long long id);
	virtual ~Player();

	void SetSession(GameSession* session);
	GameSession* GetSession() const { return m_session; }

	void BeginPlay() override;
	void Tick() override;

private:
	GameSession* m_session;
};