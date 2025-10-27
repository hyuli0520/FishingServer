#pragma once

class Session;
class GameSession : public Session
{
public:
	void OnConnected(endpoint ep) override;
	void OnRecv(BYTE* buffer, int len) override;
	void OnSend(int len) override;
	void OnDisconnected() override;

	Session* GetSession();
	shared_ptr<Player> GetPlayer() { return m_player; }
	void SetPlayer(shared_ptr<Player> player);

private:
	shared_ptr<Player> m_player;
};