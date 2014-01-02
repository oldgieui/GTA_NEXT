#pragma once
#include <vector>
#include "Mob.h"
#include "NPC.h"
#include "Item.h"

enum MapType
{
	HALL,
	PROMPT,
	LINK,
	VILLAGE,
	RECOVER,
	PROF_OFFICE,
	TEACHER_OFFICE,
	LIBRARY,
};

class CMapChip
{
public:
	CMapChip(void);
	~CMapChip(void);

	void SetMapInfo
		(MapType mapType, std::string mapName, 
		CMob* pMob, CNPC* pNPC, CItem* pHiddenItem);

	void SetMapType(MapType mapType){m_MapType = mapType;}
	void SetMapName(std::string mapName){m_MapName = mapName;}
	void SetMob(CMob* mob){pMob = mob;}
	void SetNPC(CNPC* npc){pNPC = npc;}
	void SetHiddenItem(CItem* item){pHiddenItem = item;}

	MapType GetMapType(void){return m_MapType;}
	std::string GetMapName(void){return m_MapName;}
	CMob* GetMob(void){return pMob;}
	CNPC* GetNPC(){return pNPC;}
	CItem* GetItem(){return pHiddenItem;}

	void SetParentMapChip(CMapChip* parent){m_ParentMapChip = parent;}
	CMapChip* GetParentMapChip(void){return m_ParentMapChip;}

	//void AddChildMapChip(int num, CMapChip* child1, CMapChip* child2 ...);
	void AddChildMapChip(CMapChip* child)
		{m_ChildrenMapChips.push_back(child);}
	std::vector<CMapChip*> GetChildMapChips(void)
		{return m_ChildrenMapChips;}

protected:
	

private:
	MapType		m_MapType;
	std::string	m_MapName;
	CMob*		pMob;
	CNPC*		pNPC;
	CItem*		pHiddenItem;
	CMapChip* m_ParentMapChip;
	std::vector<CMapChip*> m_ChildrenMapChips;
};

