#pragma once
#include "Player.h"
#include "WorldMap.h"

class CMob;

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);
	//���α׷����� �ʱ�ȭ, ����, ���ᰡ �ִ�. (����� �� �޸� �� ������ ��� ��)

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

