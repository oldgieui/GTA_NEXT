#pragma once
#include "Mob.h"
#include "NPC.h"
#define MAP_SIZE 10


struct MapInfo{
	CMob* pMob;
	CNPC* pNPC;
};
class CWorldMap
{
public:
	CWorldMap(void);
	~CWorldMap(void);

	MapInfo* GetMapInfo(int x, int y);
	//MapInfo* GetMapInfo(Position pos);

protected:
	MapInfo m_mapInfo[MAP_SIZE][MAP_SIZE];
};

