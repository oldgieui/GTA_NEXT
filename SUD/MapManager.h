#pragma once
#include "MapChip.h"

class CMapManager
{
public:
	static CMapManager* GetInstance();
	static void ReleaseInstance();

	void GotoParentMap();
	void GotoChildMap(unsigned int mapNum);
	
	void Init();
	void SetCurrentMap(CMapChip* map){m_currentMap = map;}
	CMapChip* GetCurrentMap(void){return m_currentMap;}

	CMapChip NextHall, Library, Office, Village1, Village2, Village3, Village4, Recover3_9, Recover3_8, Recover2_3, Recover2_4, Recover2_6,	Prof_PMK, Prof_SM9, Prof_BYH, Prof_HSJ, Prof_JHY, Prof_KDJ, Prof_LSH, Prof_YJS, Prompt3_10, Prompt2_4, Prompt4_11, Prompt4_14;

private:
	CMapManager(void);
	~CMapManager(void);

	static CMapManager* m_pInstance;
	CMapChip* m_currentMap;
};

