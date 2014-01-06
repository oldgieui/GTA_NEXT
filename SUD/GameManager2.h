#pragma once
#include "Player.h"
#include "MapChip.h"

class CMob;

class Quest
{
public:
	Quest();
	~Quest();
	void setStart(){isStart = true;}
	bool GetIsStart(){return isStart;}
	void setClear(){isClear = true;}
	bool GetIsClear(){return isClear;}
private:
	bool isStart;
	bool isClear;
};

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
	std::string inputBuffer;
	CPlayer* m_PC;
	Quest* KillAllMobs;
	Quest* FindTA;
	CItem* BFT;
	CItem* URF;
	CMob* pMob[4];
	CNPC* pNPC[13];
};

