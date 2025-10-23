#include "pch.h"
#include "Region.h"
#include "GameObject.h"

Region::~Region()
{
}
void Region::Tick()
{
	for (auto& obj : m_players)
		obj.second->Tick();
}
