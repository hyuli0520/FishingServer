#pragma once

class ObjectManager;
class MapManager;
class Manager
{
public:
	Manager();
	virtual ~Manager();

	void Init();

	shared_ptr<ObjectManager> Object() { return m_object; }
	shared_ptr<MapManager> Map() { return m_map; }

private:
	shared_ptr<ObjectManager> m_object;
	shared_ptr<MapManager> m_map;
};

extern Manager* GManager;