#pragma once

#include "stdafx.h"
#include "WorldMap.h"
#include <string.h>

#define ZeroMemory(mem, size) memset(mem, 0, size))


CWorldMap::CWorldMap(void)
{
	memset(m_mapInfo, 0, sizeof(m_mapInfo));
}

MapInfo* CWorldMap::GetMapInfo(int x, int y){
	if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE)
	{
		return &m_mapInfo[x][y];
	}
	return nullptr;
}

MapInfo* CWorldMap::GetMapInfo( Position pos )
{
	return GetMapInfo(pos.x, pos.y);
}



CWorldMap::~CWorldMap(void)
{
	for (int i = 0; i <MAP_SIZE ; ++i)
	{
		for (int j = 0; j< MAP_SIZE; ++j)
		{
			delete m_mapInfo[i][j].pMob;
			m_mapInfo[i][j].pMob = nullptr;

			delete m_mapInfo[i][j].pNPC;
			m_mapInfo[i][j].pNPC = nullptr;
		}
	}
}
