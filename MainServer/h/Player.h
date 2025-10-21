#pragma once

class GameObject;
class Player : public GameObject
{
	using Super = GameObject;
public:
	void BeginPlay() override;
	void Tick() override;
};