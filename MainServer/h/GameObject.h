#pragma once

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject();

	virtual void BeginPlay() {};
	virtual void Tick();

	unsigned long long GetId() const { return m_objectId; }
	Protocol::ObjectType GetType() const { return m_type; }

protected:

private:
	unsigned long long m_objectId;
	unsigned long long m_delta = 0;
	unsigned long long m_lastTick = 0;
	Protocol::ObjectType m_type;
};