#pragma once
#include "Player.h"
#include "MapChip.h"


class CMob;

class CGameManager2
{
public:
	CGameManager2(void);
	~CGameManager2(void);
	//���α׷����� �ʱ�ȭ, ����, ���ᰡ �ִ�. (����� �� �޸� �� ������ ��� ��)

	void Init(void);
	void Run(void);
	void Release(void);

protected:
	bool InputProc(void);
	void OpenHelpMenu(void);
	void CreateMobs(void);
	void CreateNPCs(void);
	void CreateItems(void);
	void Battle(CCharacter* pMob);
	void GetOrder();
	void ShowMapMessage(CMapChip* map);
	void PrintProfImage(std::string mapName);
	void PrintAsciiArts( std::string filePath );
	std::string getAsciiArts(std::ifstream& File);

protected:
	int attackPower;
	CPlayer* m_PC;
};

