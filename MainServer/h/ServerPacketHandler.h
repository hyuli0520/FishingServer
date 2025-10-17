#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = function<bool(Session*, BYTE*, int)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : unsigned short
{
	PKT_REQ_ENTER = 1000,
	PKT_RES_ENTER = 1001,
	PKT_REQ_MOVE = 1002,
	PKT_RES_MOVE = 1003,
	PKT_REQ_SAVE_INVENTORY = 1004,
	PKT_RES_SAVE_INVENTORY = 1005,
	PKT_REQ_START_FISHING = 1006,
	PKT_RES_BITE_BAIT = 1007,
	PKT_RES_SPAWN = 1008,
	PKT_NOTIFY_SPAWN = 1009,
};

bool Handle_INVALID(Session* session, BYTE* buffer, int len);
bool Handle_REQ_ENTER(Session* session, Protocol::REQ_ENTER& pkt);
bool Handle_REQ_MOVE(Session* session, Protocol::REQ_MOVE& pkt);
bool Handle_REQ_SAVE_INVENTORY(Session* session, Protocol::REQ_SAVE_INVENTORY& pkt);
bool Handle_REQ_START_FISHING(Session* session, Protocol::REQ_START_FISHING& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_REQ_ENTER] = [](Session* session, BYTE* buffer, int len) {return HandlePacket<Protocol::REQ_ENTER>(Handle_REQ_ENTER, session, buffer, len); };
		GPacketHandler[PKT_REQ_MOVE] = [](Session* session, BYTE* buffer, int len) {return HandlePacket<Protocol::REQ_MOVE>(Handle_REQ_MOVE, session, buffer, len); };
		GPacketHandler[PKT_REQ_SAVE_INVENTORY] = [](Session* session, BYTE* buffer, int len) {return HandlePacket<Protocol::REQ_SAVE_INVENTORY>(Handle_REQ_SAVE_INVENTORY, session, buffer, len); };
		GPacketHandler[PKT_REQ_START_FISHING] = [](Session* session, BYTE* buffer, int len) {return HandlePacket<Protocol::REQ_START_FISHING>(Handle_REQ_START_FISHING, session, buffer, len); };
	}
	static shared_ptr<vector<char>> MakeSendBuffer(Protocol::RES_ENTER& pkt) { return MakeSendBuffer(pkt, PKT_RES_ENTER); }
	static shared_ptr<vector<char>> MakeSendBuffer(Protocol::RES_MOVE& pkt) { return MakeSendBuffer(pkt, PKT_RES_MOVE); }
	static shared_ptr<vector<char>> MakeSendBuffer(Protocol::RES_SAVE_INVENTORY& pkt) { return MakeSendBuffer(pkt, PKT_RES_SAVE_INVENTORY); }
	static shared_ptr<vector<char>> MakeSendBuffer(Protocol::RES_BITE_BAIT& pkt) { return MakeSendBuffer(pkt, PKT_RES_BITE_BAIT); }
	static shared_ptr<vector<char>> MakeSendBuffer(Protocol::RES_SPAWN& pkt) { return MakeSendBuffer(pkt, PKT_RES_SPAWN); }
	static shared_ptr<vector<char>> MakeSendBuffer(Protocol::NOTIFY_SPAWN& pkt) { return MakeSendBuffer(pkt, PKT_NOTIFY_SPAWN); }

	static bool HandlePacket(Session* session, BYTE* buffer, int len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}

	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, Session* session, BYTE* buffer, int len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	template<typename T>
	static shared_ptr<vector<char>> MakeSendBuffer(T& pkt, unsigned short id)
	{
		const unsigned short dataSize = static_cast<unsigned short>(pkt.ByteSizeLong());
		const unsigned short packetSize = dataSize + sizeof(PacketHeader);

		shared_ptr<vector<char>> sendBuffer = MakeShared<vector<char>>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->data());
		header->size = packetSize;
		header->id = id;
		assert(pkt.SerializeToArray(sendBuffer->data() + 4, dataSize));

		return sendBuffer;
	}
};
