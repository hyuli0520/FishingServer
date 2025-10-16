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
