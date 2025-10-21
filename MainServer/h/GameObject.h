#pragma once

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject();

	virtual void BeginPlay() {};
	virtual void Tick();

protected:

private:
	unsigned long long m_objectId;
	unsigned long long m_delta = 0;
	unsigned long long m_lastTick = 0;
};