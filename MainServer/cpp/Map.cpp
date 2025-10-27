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

void Map::BroadCast(vector<char>& buffer, unsigned long long expectId)
{
	for (auto& row : m_regions)
	{
		for (auto& region : row)
		{
			for (auto& [id, player] : region->GetPlayers())
			{
				if (id == expectId)
					continue;

				if (auto session = player->GetSession())
					session->SendContext(buffer);
			}
		}
	}
}

void Map::BroadCastAround(vector<char>& buffer, unsigned long long expectId, int x, int y, bool enter)
{
	auto nearRegions = GetNearByRegions(x, y, 1);

	for (auto& region : nearRegions)
	{
		for (auto& [id, player] : region->GetPlayers())
		{
			if (id == expectId)
				continue;

			if (auto session = player->GetSession())
				session->SendContext(buffer);
		}
	}
}

void Map::BroadCastMove(shared_ptr<GameObject> object, int oldRx, int oldRy, int newRx, int newRy)
{
	auto oldRegions = GetNearByRegions(oldRx, oldRy, 1);
	auto newRegions = GetNearByRegions(newRx, newRy, 1);

	unordered_set<shared_ptr<Region>> oldSet(oldRegions.begin(), oldRegions.end());
	unordered_set<shared_ptr<Region>> newSet(newRegions.begin(), newRegions.end());

	auto player = static_pointer_cast<Player>(object);
	Protocol::NOTIFY_AOI_UPDATE appear;
	appear.set_id(player->GetId());
	appear.set_snapshot(false);
	{
		auto info = appear.add_appeared();
		info->set_objectid(player->GetId());
		Protocol::Vector2 pos = player->GetPosInfo().pos();
		info->mutable_posinfo()->set_allocated_pos(&pos);
		info->set_type(player->GetType());
	}
	auto appearBuffer = ServerPacketHandler::MakeSendBuffer(appear);

	Protocol::NOTIFY_AOI_UPDATE disappear;
	disappear.set_id(player->GetId());
	disappear.set_snapshot(false);
	disappear.add_disappeared_ids(player->GetId());
	auto disappearBuffer = ServerPacketHandler::MakeSendBuffer(disappear);

	const unsigned long long exceptId = player->GetId();
	for (auto& r : oldSet)
	{
		if (newSet.find(r) == newSet.end())
		{
			for (auto& [id, p] : r->GetPlayers())
			{
				if (id == exceptId)
					continue;

				if (auto s = p->GetSession())
					s->SendContext(*appearBuffer);
			}
		}
	}

	for (auto& r : newSet)
	{
		if (oldSet.find(r) == oldSet.end())
		{
			for (auto& [id, p] : r->GetPlayers())
			{
				if (id == exceptId)
					continue;

				if (auto s = p->GetSession())
					s->SendContext(*disappearBuffer);
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
