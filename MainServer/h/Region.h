#pragma once

class Region : enable_shared_from_this<Region>
{
public:
	Region() = default;
	~Region();

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	unordered_map<unsigned long long, shared_ptr<Player>> GetPlayers() const { return m_players; }

	bool AddObject(shared_ptr<GameObject> object);
	bool RemoveObject(shared_ptr<GameObject> object);

	void Tick();

private:
	int m_x;
	int m_y;
	unordered_map<unsigned long long, shared_ptr<Player>> m_players;
};