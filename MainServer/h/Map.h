#pragma once

class Region;
class Map : public JobSerializer
{
public:
	Map() = default;
	Map(int width, int height, int size);
	~Map();

	void EnterObject(shared_ptr<GameObject> object);
	void LeaveObject(shared_ptr<GameObject> object);

	void HandleMove(Session* session, Protocol::REQ_MOVE pkt);

	// Search AOI Region
	pair<int, int> GetRegionsPos(float x, float y);
	vector<shared_ptr<Region>> GetNearByRegions(int worldX, int worldY, int range);
	vector<shared_ptr<Player>> GetNearByPlayers(int worldX, int worldY, int range);

	void BeginPlay();
	void Tick();

private:
	int m_width;
	int m_height;
	int m_regionSize;
	int m_regionCountX;
	int m_regionCountY;
	vector<vector<shared_ptr<Region>>> m_regions;
};