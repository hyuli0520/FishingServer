#include "pch.h"
#include "Manager.h"

Manager::Manager()
{
	Init();
}

Manager::~Manager()
{
}

void Manager::Init()
{
	m_object->Init();
}

Manager* GManager;