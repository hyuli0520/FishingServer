#pragma once

class Region : enable_shared_from_this<Region>
{
public:
	Region() = default;
	~Region();

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	unordered_map<unsigned long long, shared_ptr<GameObject>> GetObjects() const { return m_objects; }

	void Tick();

private:
	int m_x;
	int m_y;
	unordered_map<unsigned long long, shared_ptr<GameObject>> m_objects;
};