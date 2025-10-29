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
	void BroadCast(vector<char>& buffer, unsigned long long expectId = 0);
	void BroadCastAround(vector<char>& buffer, unsigned long long expectId = 0, int x = 0, int y = 0, bool enter = false);
	void BroadCastMove(shared_ptr<GameObject> object, int oldRx = 0, int oldRy = 0, int newRx = 0, int newRy = 0);

	void HandleMove(Session* session, Protocol::REQ_MOVE pkt);

	void UpdateAOI(shared_ptr<GameObject> object, int newX, int newY);
	// Search AOI Region
	pair<int, int> GetRegionsPos(float x, float y);
	vector<shared_ptr<Region>> GetNearByRegions(int worldX, int worldY, int range);
	vector<shared_ptr<Player>> GetNearByPlayers(int worldX, int worldY, int range);
	vector<vector<shared_ptr<Region>>> GetAllRegions() const { return m_regions; }

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