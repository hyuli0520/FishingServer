#include "pch.h"
#include "Region.h"
#include "GameObject.h"

Region::~Region()
{
}

bool Region::AddObject(shared_ptr<GameObject> object)
{
	Protocol::ObjectType type = object->GetType();
	if (type == Protocol::PLAYER)
	{
		if (m_players.find(object->GetId()) != m_players.end())
			return false;

		m_players.insert({ object->GetId(), static_pointer_cast<Player>(object) });
	}

	return true;
}

bool Region::RemoveObject(shared_ptr<GameObject> object)
{
	auto objectId = object->GetId();
	Protocol::ObjectType type = object->GetType();
	if (type == Protocol::PLAYER)
	{
		if (m_players.find(objectId) == m_players.end())
			return false;

		m_players.erase(objectId);
	}

	return true;
}

void Region::Tick()
{
	for (auto& obj : m_players)
		obj.second->Tick();
}
