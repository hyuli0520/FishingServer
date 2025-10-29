#include "pch.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "MapManager.h"

Manager::Manager()
{
	Init();
}

Manager::~Manager()
{
}

void Manager::Init()
{
	m_object = MakeShared<ObjectManager>();
	m_map = MakeShared<MapManager>();

	m_object->Init();
}

Manager* GManager;