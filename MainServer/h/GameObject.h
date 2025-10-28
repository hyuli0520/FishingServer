#pragma once

class Map;
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject();

	virtual void BeginPlay() {};
	virtual void Tick();

	unsigned long long GetId() const { return m_objectId; }
	Protocol::ObjectType GetType() const { return m_type; }
	shared_ptr<Map> GetMap() const { return m_map.lock(); }

	void SetMap(shared_ptr<Map> map);

protected:
	weak_ptr<Map> m_map;
private:
	unsigned long long m_objectId;
	unsigned long long m_delta = 0;
	unsigned long long m_lastTick = 0;
	Protocol::ObjectType m_type;
};