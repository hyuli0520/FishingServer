#include "pch.h"
#include "GameSession.h"

void GameSession::OnConnected(endpoint ep)
{
	cout << "connected" << endl;
}

void GameSession::OnRecv(BYTE* buffer, int len)
{
	if (len < 3)
		return;

	int processLen = 0;
	PacketHeader header{};
	auto session = GetSession();

	while (true)
	{
		int dataSize = len - processLen;
		if (dataSize < sizeof(PacketHeader))
			break;

		header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		if (dataSize < header.size)
			break;

		ServerPacketHandler::HandlePacket(session, &buffer[processLen], header.size);

		processLen += header.size;
	}
}

void GameSession::OnSend(int len)
{
}

void GameSession::OnDisconnected()
{
	cout << "disconnected" << endl;
}

Session* GameSession::GetSession()
{
	return this;
}

void GameSession::SetPlayer(shared_ptr<Player> player)
{
	m_player = player;
}