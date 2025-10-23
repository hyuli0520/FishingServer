#pragma once

class Region;
class Map : public JobSerializer
{
public:
	Map() = default;
	~Map();

	void EnterObject(shared_ptr<GameObject> object);
	void LeaveObject(shared_ptr<GameObject> object);

	void HandleMove(Session* session, Protocol::REQ_MOVE pkt);

	void BeginPlay();
	void Tick();

private:
	vector<vector<shared_ptr<Region>>> m_regions;
};