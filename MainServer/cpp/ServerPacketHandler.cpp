#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(Session* session, BYTE* buffer, int len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	return false;
}

bool Handle_REQ_ENTER(Session* session, Protocol::REQ_ENTER& pkt)
{
	if (auto gMap = GManager->Map()->Main())
		gMap->PushJob(&MapManager::HandleEnterMap, session, pkt);
	return false;
}

bool Handle_REQ_MOVE(Session* session, Protocol::REQ_MOVE& pkt)
{
	auto gameSession = static_cast<GameSession*>(session);
	if (auto map = gameSession->GetPlayer()->GetMap())
		map->PushJob(&Map::HandleMove, session, pkt);
	return false;
}

bool Handle_REQ_SAVE_INVENTORY(Session* session, Protocol::REQ_SAVE_INVENTORY& pkt)
{
	return false;
}

bool Handle_REQ_START_FISHING(Session* session, Protocol::REQ_START_FISHING& pkt)
{
	return false;
}
