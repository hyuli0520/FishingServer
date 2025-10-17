#include "pch.h"
#include "ServerPacketHandler.h"

bool Handle_INVALID(Session* session, BYTE* buffer, int len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	return false;
}

bool Handle_REQ_ENTER(Session* session, Protocol::REQ_ENTER& pkt)
{
	return false;
}

bool Handle_REQ_MOVE(Session* session, Protocol::REQ_MOVE& pkt)
{
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
