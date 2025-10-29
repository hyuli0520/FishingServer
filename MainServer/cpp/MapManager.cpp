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

void MapManager::HandleEnterMap(Session* session, Protocol::REQ_ENTER pkt)
{
    if (!session)
        return;

    auto gameSession = static_cast<GameSession*>(session);
    auto& map = m_maps[pkt.id()];
    auto myPlayer = gameSession->GetPlayer();

    Protocol::RES_ENTER enter;
    enter.set_success(map != nullptr && myPlayer->GetMap().get() == map.get());
    enter.set_id(pkt.id());
    auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enter);
    map->BroadCast(*sendBuffer);

    if (!enter.success())
        return;

    map->EnterObject(myPlayer);

    {
        Protocol::RES_SPAWN spawn;
        auto info = spawn.mutable_object();
        info->set_objectid(myPlayer->GetId());
        info->set_type(myPlayer->GetType());
        info->mutable_posinfo()->mutable_pos()->set_x(myPlayer->GetPosInfo().pos().x());
        info->mutable_posinfo()->mutable_pos()->set_y(myPlayer->GetPosInfo().pos().y());
        spawn.set_mine(true);

        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(spawn);
        session->SendContext(*sendBuffer);
    }

    {
        Protocol::NOTIFY_SPAWN notify;
        const auto& pos = myPlayer->GetPosInfo().pos();
        auto neighbors = map->GetNearByPlayers(pos.x(), pos.y(), 1);

        for (auto& p : neighbors)
        {
            if (p->GetId() == myPlayer->GetId())
                continue;

            auto info = notify.add_object();
            info->set_objectid(myPlayer->GetId());
            info->set_type(myPlayer->GetType());
            info->mutable_posinfo()->mutable_pos()->set_x(myPlayer->GetPosInfo().pos().x());
            info->mutable_posinfo()->mutable_pos()->set_y(myPlayer->GetPosInfo().pos().y());
        }

        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(notify);
        session->SendContext(*sendBuffer);
    }

    {
        Protocol::NOTIFY_SPAWN notify;
        auto info = notify.add_object();
        info->set_objectid(myPlayer->GetId());
        info->set_type(myPlayer->GetType());
        info->mutable_posinfo()->mutable_pos()->set_x(myPlayer->GetPosInfo().pos().x());
        info->mutable_posinfo()->mutable_pos()->set_y(myPlayer->GetPosInfo().pos().y());

        auto sendBuffer = ServerPacketHandler::MakeSendBuffer(notify);
        const auto& pos = myPlayer->GetPosInfo().pos();
        map->BroadCastAround(*sendBuffer, myPlayer->GetId(), pos.x(), pos.y(), true);
    }
}
