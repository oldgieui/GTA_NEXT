#include "stdafx.h"
#include "WorldMap.h"
#include "GameManager.h"
#include "Character.h"
#include <iostream>
#include <string>
#include "Mob.h"
#include <windows.h>

CGameManager::CGameManager(void)
{
	m_PC = new CPlayer;
	m_PC->SetATK(300);
	m_PC->SetHP(200000);
}


CGameManager::~CGameManager(void)
{
	delete m_PC;
}

void CGameManager::Init(void)
{
	printf_s(" Great\t\tN\n TDD\t\tEX\n Awesome\t T\n\t\tFeat. Waldo\n\n");
	srand((unsigned)time(NULL));
	
	playerClass;
	while (playerClass != "2" && playerClass != "3")
	{
		printf("주인공을 선택하십시오\n1. 교수\n2. 비전공자\n3. 맥북\n");
		getline(std::cin, playerClass);
		if (playerClass == "1")
		{
			printf("교수는 아직 채용되지 않았습니다.\n\n");
			playerClass = "0";
		}
		if (playerClass == "2")
		{
			std::string name = "비전공자";
			m_PC->SetName(name);
		}
	}
	printf("\n게임을 시작합니다.\n\n");

	
	Position pos;
	pos.x = 5;
	pos.y = 5;
	m_PC->SetPosition(pos);
	m_PC->PrintPosition();
	
	CreateMobs();
	CreateNPCs();

	/*CMob* pMob = m_Map.GetMapInfo(2,3)->pMob;*/
	/*printf("MOB Name : %s\n", pMob->GetName().c_str());*/
	
}


void CGameManager::Run(void)
{
	printf("W, A, S, D키로 이동할 수 있습니다.\nh를 입력하여 도움말을 볼 수 있습니다.\n");
	if (playerClass == "3")
	{
		while ( MacInputProc()){}
		return;
	}
	while (InputProc())
	{
	}
}


void CGameManager::Release(void)
{
	printf("[오베르 가메!]\n");
	getchar();
}



bool CGameManager::InputProc(void)
{
	//키보드 입력을 받아서, 커맨드를 파싱하고 맞게 처리한다. Q를 입력하면 종료
// 	char ch = NULL;
// 	scanf_s("%c", &ch, sizeof(ch));
// 	printf_s("input:%c\n", ch);
	
	std::string strInput;
	/*std::cin>>strInput;*/
	getline(std::cin, strInput);

	if (strInput == "w" || strInput == "W")
	{
		m_PC->PositionMove(DIR_UP);
	}
	else if (strInput == "s" || strInput == "S")
	{
		m_PC->PositionMove(DIR_DOWN);
	}
	else if (strInput == "a" || strInput == "A")
	{
		m_PC->PositionMove(DIR_LEFT);
	}
	else if (strInput == "d" || strInput == "D")
	{
		m_PC->PositionMove(DIR_RIGHT);
	}
	else if (strInput == "f" || strInput == "F")
	{
		FindAllMobs();
	}
	else if (strInput == "c" || strInput == "c")
	{
		FindAllNPCs();
	}
	else if (strInput == "h" || strInput == "H")
	{
		OpenHelpMenu();
	}
 	else if (strInput == "q" || strInput == "Q")
	{
		printf_s("게임을 종료합니다\n");
		return false;
	}
	else
		printf_s("잘못된 명령입니다.\n");
	
	m_PC->PrintPosition();

	if (m_Map.GetMapInfo(m_PC->GetPosition())->pMob != nullptr)
	{
		Battle(m_Map.GetMapInfo(m_PC->GetPosition())->pMob);
		if (m_PC->IsAlive())
		{
			delete m_Map.GetMapInfo(m_PC->GetPosition())->pMob;
			m_Map.GetMapInfo(m_PC->GetPosition())->pMob = nullptr;
		}
		else if (m_PC->IsAlive() == false)
		{
			return false;
		}
	}


	if (m_Map.GetMapInfo(m_PC->GetPosition())->pNPC != nullptr)
	{
		std::string NPCKey;
		printf_s("%s님을 만났습니다. 어떻게 하시겠습니까?\n1. 직업을 물어본다.\n2. 맥북을 훔친다.\n3. 싸움을 건다.\n",m_Map.GetMapInfo(m_PC->GetPosition())->pNPC->GetName().c_str());
		getline(std::cin, NPCKey);

		if (NPCKey == "1")
		{
			printf_s("%s : 나는 %s 입니다. \n", m_Map.GetMapInfo(m_PC->GetPosition())->pNPC->GetName().c_str(), m_Map.GetMapInfo(m_PC->GetPosition())->pNPC->GetJOB().c_str());
		}
		if (NPCKey == "2")
		{
			printf_s("맥북은 이미 가지고 있기 때문에 훔칠 필요가 없습니다.\n");
		}
		if (NPCKey == "3")
		{
			Battle(m_Map.GetMapInfo(m_PC->GetPosition())->pNPC);
			if (m_PC->IsAlive())
			{
				delete m_Map.GetMapInfo(m_PC->GetPosition())->pNPC;
				m_Map.GetMapInfo(m_PC->GetPosition())->pNPC = nullptr;
			}
			else if (m_PC->IsAlive() == false)
			{
				return false;
			}
		}
	}

	
	//printf_s("%s\n", strInput.c_str());
	
	return true;
}


void CGameManager::CreateMobs(void)
{
	int numberOfMobs = (int)(MAP_SIZE * MAP_SIZE * 0.25);

	for (int i = numberOfMobs; i > 0; --i)
	{
		int mapX = rand() % MAP_SIZE;
		int mapY = rand() % MAP_SIZE;
		char buf[16];
		if ((mapX != m_PC->GetPosition().x || 
			mapY != m_PC->GetPosition().y) &&
			m_Map.GetMapInfo(mapX, mapY)->pMob == nullptr &&
			m_Map.GetMapInfo(mapX, mapY)->pNPC == nullptr)
		{
			CMob* pMob = new CMob();
			sprintf_s(buf, "레지스터 %04x", i * rand() % 65536);
			std::string mobName = buf;
			pMob->SetName(mobName);
			pMob->SetATK(300);
			pMob->SetHP(2000);
			m_Map.GetMapInfo(mapX, mapY)->pMob = pMob;
		}
		else
		{
			++i;
		}
	}
}

void CGameManager::CreateNPCs(void)
{	
	CNPC* pNPC[7];
	for (int i = 0; i < 7; ++i)
	{
		pNPC[i] = new CNPC();
	}

	// agebreak : 직업은 define이나 enum을 이용하는게 편함. 
	pNPC[0]->SetName("박민근");
	pNPC[0]->SetJOB("교수");
	pNPC[1]->SetName("김진우");
	pNPC[1]->SetJOB("학생");
	pNPC[2]->SetName("문진상");
	pNPC[2]->SetJOB("교수");
	pNPC[3]->SetName("정윤성");
	pNPC[3]->SetJOB("학생");
	pNPC[4]->SetName("조익성");
	pNPC[4]->SetJOB("10티어");
	pNPC[5]->SetName("최종찬");
	pNPC[5]->SetJOB("학생");
	pNPC[6]->SetName("김희재");
	pNPC[6]->SetJOB("학생");

	for (int k = 6; k >= 0; k--)
	{
		int mapX = rand()%MAP_SIZE;
		int mapY = rand()%MAP_SIZE;
		// agebreak : 코드를 옆으로 길게 쓰는건 좋은 습관이 아님. 아래 처럼 밑으로 쓰는게 보기 편함
		if ((mapX != m_PC->GetPosition().x || 
			mapY != m_PC->GetPosition().y) && 
			m_Map.GetMapInfo(mapX, mapY)->pMob == nullptr && 
			m_Map.GetMapInfo(mapX, mapY)->pNPC == nullptr)
		{
			pNPC[k]->SetATK(300);
			pNPC[k]->SetHP(2000);
			m_Map.GetMapInfo(mapX, mapY)->pNPC = pNPC[k];
		}
		else
			k++;
	}
	
}



void CGameManager::Battle(CCharacter* pMob)
{
	std::string BattleKey;
	printf_s("%s 나타났다 여기. 전투? (N/Y)\n", pMob->GetName().c_str());
	getline(std::cin, BattleKey);
	while (!(BattleKey  == "y" || BattleKey == "Y" || BattleKey == "n" || BattleKey == "N"))
	{
		printf_s("전투를 할 것인지 선택하십시오\n");
		getline(std::cin, BattleKey);
	}

	if (BattleKey == "y" || BattleKey == "Y")
	{
		printf_s("걸다 %s에게! 싸움을! \n", pMob->GetName().c_str());
		while (m_PC->IsAlive() && pMob->IsAlive())
		{
			printf_s("공격함 :    %s 에게!\n---->", pMob->GetName().c_str());

			damage = m_PC->GetATK()-(m_PC->GetATK()*0.1*(rand()%3)+(m_PC->GetATK()*0.1*(rand()%3)));
			pMob->DamageCheck(pMob->IsHit(), damage);
			if(pMob->IsAlive() == false)
			{
				printf_s("#### %s의 승리! #### \n", m_PC->GetName().c_str());
				break;
			}

			printf_s("공격받음 :  %s 로부터!\n---->", pMob->GetName().c_str());
			damage = pMob->GetATK()-(pMob->GetATK()*0.1*(rand()%3)+(pMob->GetATK()*0.1*(rand()%3)));
			m_PC->DamageCheck(m_PC->IsHit(), damage);
			if(m_PC->IsAlive() == false)
			{
				printf_s("\n  사  망  함  \n");
				getchar();
				break;
			}
			Sleep(1000);
		}
	}

	else if (BattleKey == "n" || BattleKey == "N")
	{
		printf_s("사랑하는 평화 사람! 주의에 의거 지나가다 %s를 무시!\n", pMob->GetName().c_str());
	}
}

void CGameManager::FindAllMobs(void){
	
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			if (m_Map.GetMapInfo(i,j)->pMob != nullptr)
			{
			CMob* mob = m_Map.GetMapInfo(i, j)->pMob;
			printf_s("%s 있다 에 %d, %d 곳.\n", mob->GetName().c_str(), i, j);
			}
		}
	}
}

void CGameManager::FindAllNPCs(void){

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			if (m_Map.GetMapInfo(i,j)->pNPC != nullptr)
			{
				CNPC* npc = m_Map.GetMapInfo(i, j)->pNPC;
				printf_s("%s이(가) [%d, %d]에 있습니다.\n", npc->GetName().c_str(), i, j);
			}
		}
	}
}

bool CGameManager::MacInputProc( void )
{

	std::string strInput;
	/*std::cin>>strInput;*/
	getline(std::cin, strInput);

	if (strInput == "w" || strInput == "W" || strInput == "s" || strInput == "S" || strInput == "a" || strInput == "A" || strInput == "d" || strInput == "D")
	{
		printf("맥북은 이동을 할 수 없습니다.\n");
	}
	else if (strInput == "f" || strInput == "F")
	{
		printf("맥북은 행동을 할 수 없습니다.\n");
	}
	else if (strInput == "h" || strInput == "H")
	{
		printf("맥북에 도움말이 설치되어 있지 않습니다.\n");
	}
	else if (strInput == "q" || strInput == "Q")
	{
		printf_s("게임을 종료합니다.\n");
		return false;
	}
	else
		printf_s("잘못된 명령입니다.\n");

	return true;
}

void CGameManager::OpenHelpMenu( void )
{
	printf("W, A, S, D키로 이동할 수 있습니다.\nF키로 적을 찾을 수 있습니다.\nC키로 다른 사람들을 찾아볼 수 있습니다.\nH키로 도움말을 열 수 있습니다.\n");
}
