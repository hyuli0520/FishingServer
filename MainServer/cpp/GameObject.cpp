#include "pch.h"
#include "GameObject.h"

GameObject::~GameObject()
{
}

void GameObject::Tick()
{
	uint64_t now = GetTickCount64();
	m_delta = static_cast<float>(now - m_lastTick);
	m_lastTick = GetTickCount64();
}