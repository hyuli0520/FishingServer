#include "pch.h"
#include "Map.h"
#include <algorithm>

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
	for (auto& row : m_regions)
	{
		for (auto& region : row)
		{
			region->AddObject(object);
		}
	}
}

void Map::LeaveObject(shared_ptr<GameObject> object)
{
	for (auto& row : m_regions)
	{
		for (auto& region : row)
		{
			region->RemoveObject(object);
		}
	}
}

void Map::BroadCast(vector<char> buffer, unsigned long long expectId)
{
	for (auto& row : m_regions)
	{
		for (auto& region : row)
		{
			for (const auto& player : region->GetPlayers())
			{
				if (player.first == expectId)
					continue;

				if (auto session = player.second->GetSession())
					session->SendContext(buffer);
			}
		}
	}
}

void Map::BroadCastAround(vector<char> buffer, unsigned long long expectId, int x, int y, bool enter)
{
	auto nearRegions = GetNearByRegions(x, y, 1);

	for (auto& region : nearRegions)
	{
		for (auto& target : region->GetPlayers())
		{
			// TODO: target->Send(notify);
		}
	}
}

void Map::BroadCastMove(shared_ptr<GameObject> object, int oldRx, int oldRy, int newRx, int newRy)
{
	auto oldRegions = GetNearByRegions(oldRx, oldRy, 1);
	auto newRegions = GetNearByRegions(newRx, newRy, 1);

	unordered_set<shared_ptr<Region>> oldSet(oldRegions.begin(), oldRegions.end());
	unordered_set<shared_ptr<Region>> newSet(newRegions.begin(), newRegions.end());

	for (auto& r : oldSet)
	{
		if (newSet.find(r) == newSet.end())
		{
			for (auto& target : r->GetPlayers())
			{
				// TODO: target->Send(DisappearMsg);
			}
		}
	}

	for (auto& r : newSet)
	{
		if (oldSet.find(r) == oldSet.end())
		{
			for (auto& target : r->GetPlayers())
			{
				// TODO: target->Send(AppearMsg);
			}
		}
	}
}

void Map::HandleMove(Session* session, Protocol::REQ_MOVE pkt)
{
}

pair<int, int> Map::GetRegionsPos(float x, float y)
{
	int rx = (int)(x / m_regionSize);
	int ry = (int)(y / m_regionSize);

	rx = clamp(rx, 0, m_regionCountX - 1);
	ry = clamp(ry, 0, m_regionCountY - 1);

	return { rx, ry };
}

vector<shared_ptr<Region>> Map::GetNearByRegions(int worldX, int worldY, int range)
{
	vector<shared_ptr<Region>> result;

	int centerRx = worldX / m_regionSize;
	int centerRy = worldY / m_regionSize;

	for (int dy = -range; dy <= range; dy++)
	{
		for (int dx = -range; dx <= range; dx++)
		{
			int rx = centerRx + dx;
			int ry = centerRy + dy;

			if (rx < 0 || ry < 0 || rx >= m_regionCountX || ry >= m_regionCountY)
				continue;

			result.push_back(m_regions[ry][rx]);
		}
	}

	return result;
}

vector<shared_ptr<Player>> Map::GetNearByPlayers(int worldX, int worldY, int range)
{
	vector<shared_ptr<Player>> result;
	auto regions = GetNearByRegions(worldX, worldY, range);
	for (auto& region : regions)
	{
		for (auto& obj : region->GetPlayers())
			result.push_back(obj.second);
	}

	return result;
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
