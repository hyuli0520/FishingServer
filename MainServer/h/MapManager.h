#pragma once
using MapId = unsigned long long;

class Map;
class MapManager
{
public:
	MapManager();
	virtual ~MapManager();

	shared_ptr<Map> CreateMap(MapId id, int w, int h, int size);
	shared_ptr<Map> GetMap(MapId id) const;

	void SetMain(MapId id);
	shared_ptr<Map> Main() const { GetMap(m_mainId); }

private:
	concurrent_unordered_map<MapId, shared_ptr<Map>> m_maps;
	MapId m_mainId = 1;
};