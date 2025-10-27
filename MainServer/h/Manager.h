#pragma once

class Manager
{
public:
	Manager();
	virtual ~Manager();

	void Init();
};

extern Manager* GManager;