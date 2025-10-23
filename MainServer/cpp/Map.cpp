#include "pch.h"
#include "Map.h"

void Map::EnterObject(shared_ptr<GameObject> object)
{
}

void Map::LeaveObject(shared_ptr<GameObject> object)
{
}

void Map::HandleMove(Session* session, Protocol::REQ_MOVE pkt)
{
}
void Map::BeginPlay()
{

}

void Map::Tick()
{
	TimerPushJob(33, &Map::Tick);
	for (auto& region : m_regions)
		for (auto& rg : region)
			rg->Tick();
}
