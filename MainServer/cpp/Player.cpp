#include "pch.h"
#include "Player.h"
#include "GameObject.h"

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

void Player::BeginPlay()
{
	Super::BeginPlay();
}

void Player::Tick()
{
	Super::Tick();
}
