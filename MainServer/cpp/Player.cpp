#include "pch.h"
#include "Player.h"
#include "GameSession.h"

Player::Player(unsigned long long id)
{
}

Player::~Player()
{
}

void Player::SetSession(GameSession* session)
{
	m_session = session;
}

void Player::SetPosInfo(Protocol::PositionInfo position)
{
	m_position = position;
}

void Player::BeginPlay()
{
	Super::BeginPlay();
}

void Player::Tick()
{
	Super::Tick();
}
