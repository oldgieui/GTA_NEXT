#include "stdafx.h"
#include "MapManager.h"

CMapManager* CMapManager::m_pInstance = nullptr;

CMapManager::CMapManager(void)
{
	Init();
}


CMapManager::~CMapManager(void)
{
}

CMapManager * CMapManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CMapManager();
	}
	return m_pInstance;
}

void CMapManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}


void CMapManager::Init()
{
	NextHall.SetMapInfo(HALL, "NEXT HALL", nullptr, nullptr, nullptr);
	Library.SetMapInfo(LIBRARY, "NEXT LIBRARY", nullptr, nullptr, nullptr);
	Office.SetMapInfo(TEACHER_OFFICE, "OFFICE", nullptr, nullptr, nullptr);
	Village1.SetMapInfo(VILLAGE, "1마을 복도", nullptr, nullptr, nullptr);
	Village2.SetMapInfo(VILLAGE, "2마을 복도", nullptr, nullptr, nullptr);
	Village3.SetMapInfo(VILLAGE, "3마을 복도", nullptr, nullptr, nullptr);
	Village4.SetMapInfo(VILLAGE, "4마을 복도", nullptr, nullptr, nullptr);
	Recover2_3.SetMapInfo(RECOVER, "리커버 2-3", nullptr, nullptr, nullptr);
	Recover2_4.SetMapInfo(RECOVER, "리커버 2-4", nullptr, nullptr, nullptr);
	Recover2_6.SetMapInfo(RECOVER, "리커버 2-6", nullptr, nullptr, nullptr);
	Recover3_8.SetMapInfo(RECOVER, "리커버 3-8", nullptr, nullptr, nullptr);
	Recover3_9.SetMapInfo(RECOVER, "리커버 3-9", nullptr, nullptr, nullptr);
	Prof_PMK.SetMapInfo(PROF_OFFICE, "교수 P의 사무실", nullptr, nullptr, nullptr);
	Prof_SM9.SetMapInfo(PROF_OFFICE, "교수 9의 사무실", nullptr, nullptr, nullptr);
	Prof_BYH.SetMapInfo(PROF_OFFICE, "교수 B의 사무실", nullptr, nullptr, nullptr);
	Prof_HSJ.SetMapInfo(PROF_OFFICE, "교수 H의 사무실", nullptr, nullptr, nullptr);
	Prof_JHY.SetMapInfo(PROF_OFFICE, "교수 J의 사무실", nullptr, nullptr, nullptr);
	Prof_KDJ.SetMapInfo(PROF_OFFICE, "교수 K의 사무실", nullptr, nullptr, nullptr);
	Prof_LSH.SetMapInfo(PROF_OFFICE, "교수 L의 사무실", nullptr, nullptr, nullptr);
	Prof_YJS.SetMapInfo(PROF_OFFICE, "교수 Y의 사무실", nullptr, nullptr, nullptr);
	Prompt2_4.SetMapInfo(PROMPT, "프롬프트 2-4", nullptr, nullptr, nullptr);
	Prompt3_10.SetMapInfo(PROMPT, "프롬프트 3-10", nullptr, nullptr, nullptr);
	Prompt4_11.SetMapInfo(PROMPT, "프롬프트 4-11", nullptr, nullptr, nullptr);
	Prompt4_14.SetMapInfo(PROMPT, "프롬프트 4-14", nullptr, nullptr, nullptr);


	NextHall.SetParentMapChip(nullptr);
//	NextHall.AddChildMapChip(6, &Office, &Library, &Village1, &Village2, &Village3, &Village4);
	NextHall.AddChildMapChip(&Library);
	NextHall.AddChildMapChip(&Office);
	NextHall.AddChildMapChip(&Village1);
	NextHall.AddChildMapChip(&Village2);
	NextHall.AddChildMapChip(&Village3);
	NextHall.AddChildMapChip(&Village4);

	Library.SetParentMapChip(&NextHall);
	Office.SetParentMapChip(&NextHall);

	Village1.SetParentMapChip(&NextHall);
	Village1.AddChildMapChip(&Prof_HSJ);
	Village1.AddChildMapChip(&Prof_BYH);
	Village1.AddChildMapChip(&Prof_JHY);

	Prof_HSJ.SetParentMapChip(&Village1);
	Prof_BYH.SetParentMapChip(&Village1);
	Prof_JHY.SetParentMapChip(&Village1);
	
	Village2.SetParentMapChip(&NextHall);
	Village2.AddChildMapChip(&Recover2_3);
	Village2.AddChildMapChip(&Recover2_4);
	Village2.AddChildMapChip(&Recover2_6);
	Village2.AddChildMapChip(&Prof_LSH);
	Village2.AddChildMapChip(&Prompt2_4);

	Recover2_3.SetParentMapChip(&Village2);
	Recover2_4.SetParentMapChip(&Village2);
	Recover2_6.SetParentMapChip(&Village2);
	Prof_LSH.SetParentMapChip(&Village2);
	Prompt2_4.SetParentMapChip(&Village2);
	
	Village3.SetParentMapChip(&NextHall);
	Village3.AddChildMapChip(&Prompt3_10);
	Village3.AddChildMapChip(&Prof_PMK);
	Village3.AddChildMapChip(&Prof_SM9);
	Village3.AddChildMapChip(&Recover3_8);
	Village3.AddChildMapChip(&Recover3_9);

	Prompt3_10.SetParentMapChip(&Village3);
	Prof_PMK.SetParentMapChip(&Village3);
	Prof_SM9.SetParentMapChip(&Village3);
	Recover3_8.SetParentMapChip(&Village3);
	Recover3_9.SetParentMapChip(&Village3);

	Village4.SetParentMapChip(&NextHall);
	Village4.AddChildMapChip(&Prompt4_11);
	Village4.AddChildMapChip(&Prompt4_14);
	Village4.AddChildMapChip(&Prof_KDJ);
	Village4.AddChildMapChip(&Prof_YJS);

	Prompt4_11.SetParentMapChip(&Village4);
	Prompt4_14.SetParentMapChip(&Village4);
	Prof_KDJ.SetParentMapChip(&Village4);
	Prof_YJS.SetParentMapChip(&Village4);
}

void CMapManager::GotoParentMap()
{
	if (m_currentMap->GetParentMapChip() != nullptr)
	{
		SetCurrentMap(m_currentMap->GetParentMapChip());
	}
	else
	{
		printf("잘못된 선택입니다.\n");
	}
}

void CMapManager::GotoChildMap( unsigned int mapNum )
{
	if (m_currentMap->GetChildMapChips().empty() == false && 
		mapNum >= 0 &&
		mapNum < m_currentMap->GetChildMapChips().size())
	{
		SetCurrentMap(m_currentMap->GetChildMapChips()[mapNum]);
	} 
	else
	{
		printf("잘못된 선택입니다.\n");
	}
}





