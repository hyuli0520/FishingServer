#include "pch.h"
#include "MapManager.h"

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}

shared_ptr<Map> MapManager::CreateMap(MapId id, int w, int h, int size)
{
    auto it = m_maps.find(id);
    if (it != m_maps.end())
        return it->second;

    auto m = make_shared<Map>(w, h, size);
    m_maps.emplace(id, m);
    return m;
}

shared_ptr<Map> MapManager::GetMap(MapId id) const
{
	auto it = m_maps.find(id);
	return (it != m_maps.end()) ? it->second : nullptr;
}

void MapManager::SetMain(MapId id)
{
    m_mainId = id;
}
