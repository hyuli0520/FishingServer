#include "pch.h"
#include "Map.h"

Map::Map(int width, int height, int size)
	: m_width(width), m_height(height), m_regionSize(size)
{
	m_regionCountX = (width + size - 1) / size;
	m_regionCountY = (height + size - 1) / size;

	m_regions.resize(m_regionCountY);
	for (int y = 0; y < m_regionCountY; y++)
	{
		m_regions[y].resize(m_regionCountX);
		for (int x = 0; x < m_regionCountX; x++)
			m_regions[y][x] = make_shared<Region>(x, y);
	}
}

Map::~Map()
{
}

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
