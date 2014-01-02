#include "stdafx.h"
#include "MapChip.h"
#include "NPC.h"
#include "Mob.h"
#include <string.h>


CMapChip::CMapChip(void)
{
}


CMapChip::~CMapChip(void)
{
}

void CMapChip::SetMapInfo( MapType mapType, std::string mapName, CMob* Mob, CNPC* NPC, CItem* hiddenItem )
{
	SetMapType(mapType);
	SetMapName(mapName);
	SetMob(Mob);
	SetNPC(NPC);
	SetHiddenItem(hiddenItem);
}

// void CMapChip::AddChildMapChip( int num, CMapChip* child1, CMapChip* child2 ... )
// {
// 	for(int i = 0; i < num; i++)
// 	{
// 		m_ChildrenMapChips.push_back(child1 + i);
// 	}
// }
