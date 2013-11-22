#pragma once
#include "Player.h"
#include "WorldMap.h"

class CMob;

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);
	//프로그램에는 초기화, 실행, 종료가 있다. (종료될 때 메모리 등 관리해 줘야 함)

	void Init(void);
	void Run(void);
	void Release(void);

protected:
	bool InputProc(void);
	CPlayer* m_PC;
	CWorldMap m_Map;
	std::string playerClass;
	bool MacInputProc(void);
	void OpenHelpMenu(void);
	int damage;
public:
	void CreateMobs(void);
	void FindAllMobs(CWorldMap* map);
	void FindAllMobs(void);
	void FindAllMobs(CWorldMap map);
	void Battle(CCharacter* pMob);
	void GetOrder();
	void CreateNPCs(void);
	void FindAllNPCs(void);
};

