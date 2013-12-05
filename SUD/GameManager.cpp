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
		printf("���ΰ��� �����Ͻʽÿ�\n1. ����\n2. ��������\n3. �ƺ�\n");
		getline(std::cin, playerClass);
		if (playerClass == "1")
		{
			printf("������ ���� ä����� �ʾҽ��ϴ�.\n\n");
			playerClass = "0";
		}
		if (playerClass == "2")
		{
			std::string name = "��������";
			m_PC->SetName(name);
		}
	}
	printf("\n������ �����մϴ�.\n\n");

	
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
	printf("W, A, S, DŰ�� �̵��� �� �ֽ��ϴ�.\nh�� �Է��Ͽ� ������ �� �� �ֽ��ϴ�.\n");
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
	printf("[������ ����!]\n");
	getchar();
}



bool CGameManager::InputProc(void)
{
	//Ű���� �Է��� �޾Ƽ�, Ŀ�ǵ带 �Ľ��ϰ� �°� ó���Ѵ�. Q�� �Է��ϸ� ����
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
		printf_s("������ �����մϴ�\n");
		return false;
	}
	else
		printf_s("�߸��� ����Դϴ�.\n");
	
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
		printf_s("%s���� �������ϴ�. ��� �Ͻðڽ��ϱ�?\n1. ������ �����.\n2. �ƺ��� ��ģ��.\n3. �ο��� �Ǵ�.\n",m_Map.GetMapInfo(m_PC->GetPosition())->pNPC->GetName().c_str());
		getline(std::cin, NPCKey);

		if (NPCKey == "1")
		{
			printf_s("%s : ���� %s �Դϴ�. \n", m_Map.GetMapInfo(m_PC->GetPosition())->pNPC->GetName().c_str(), m_Map.GetMapInfo(m_PC->GetPosition())->pNPC->GetJOB().c_str());
		}
		if (NPCKey == "2")
		{
			printf_s("�ƺ��� �̹� ������ �ֱ� ������ ��ĥ �ʿ䰡 �����ϴ�.\n");
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
			sprintf_s(buf, "�������� %04x", i * rand() % 65536);
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

	// agebreak : ������ define�̳� enum�� �̿��ϴ°� ����. 
	pNPC[0]->SetName("�ڹα�");
	pNPC[0]->SetJOB("����");
	pNPC[1]->SetName("������");
	pNPC[1]->SetJOB("�л�");
	pNPC[2]->SetName("������");
	pNPC[2]->SetJOB("����");
	pNPC[3]->SetName("������");
	pNPC[3]->SetJOB("�л�");
	pNPC[4]->SetName("���ͼ�");
	pNPC[4]->SetJOB("10Ƽ��");
	pNPC[5]->SetName("������");
	pNPC[5]->SetJOB("�л�");
	pNPC[6]->SetName("������");
	pNPC[6]->SetJOB("�л�");

	for (int k = 6; k >= 0; k--)
	{
		int mapX = rand()%MAP_SIZE;
		int mapY = rand()%MAP_SIZE;
		// agebreak : �ڵ带 ������ ��� ���°� ���� ������ �ƴ�. �Ʒ� ó�� ������ ���°� ���� ����
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
	printf_s("%s ��Ÿ���� ����. ����? (N/Y)\n", pMob->GetName().c_str());
	getline(std::cin, BattleKey);
	while (!(BattleKey  == "y" || BattleKey == "Y" || BattleKey == "n" || BattleKey == "N"))
	{
		printf_s("������ �� ������ �����Ͻʽÿ�\n");
		getline(std::cin, BattleKey);
	}

	if (BattleKey == "y" || BattleKey == "Y")
	{
		printf_s("�ɴ� %s����! �ο���! \n", pMob->GetName().c_str());
		while (m_PC->IsAlive() && pMob->IsAlive())
		{
			printf_s("������ :    %s ����!\n---->", pMob->GetName().c_str());

			damage = m_PC->GetATK()-(m_PC->GetATK()*0.1*(rand()%3)+(m_PC->GetATK()*0.1*(rand()%3)));
			pMob->DamageCheck(pMob->IsHit(), damage);
			if(pMob->IsAlive() == false)
			{
				printf_s("#### %s�� �¸�! #### \n", m_PC->GetName().c_str());
				break;
			}

			printf_s("���ݹ��� :  %s �κ���!\n---->", pMob->GetName().c_str());
			damage = pMob->GetATK()-(pMob->GetATK()*0.1*(rand()%3)+(pMob->GetATK()*0.1*(rand()%3)));
			m_PC->DamageCheck(m_PC->IsHit(), damage);
			if(m_PC->IsAlive() == false)
			{
				printf_s("\n  ��  ��  ��  \n");
				getchar();
				break;
			}
			Sleep(1000);
		}
	}

	else if (BattleKey == "n" || BattleKey == "N")
	{
		printf_s("����ϴ� ��ȭ ���! ���ǿ� �ǰ� �������� %s�� ����!\n", pMob->GetName().c_str());
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
			printf_s("%s �ִ� �� %d, %d ��.\n", mob->GetName().c_str(), i, j);
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
				printf_s("%s��(��) [%d, %d]�� �ֽ��ϴ�.\n", npc->GetName().c_str(), i, j);
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
		printf("�ƺ��� �̵��� �� �� �����ϴ�.\n");
	}
	else if (strInput == "f" || strInput == "F")
	{
		printf("�ƺ��� �ൿ�� �� �� �����ϴ�.\n");
	}
	else if (strInput == "h" || strInput == "H")
	{
		printf("�ƺϿ� ������ ��ġ�Ǿ� ���� �ʽ��ϴ�.\n");
	}
	else if (strInput == "q" || strInput == "Q")
	{
		printf_s("������ �����մϴ�.\n");
		return false;
	}
	else
		printf_s("�߸��� ����Դϴ�.\n");

	return true;
}

void CGameManager::OpenHelpMenu( void )
{
	printf("W, A, S, DŰ�� �̵��� �� �ֽ��ϴ�.\nFŰ�� ���� ã�� �� �ֽ��ϴ�.\nCŰ�� �ٸ� ������� ã�ƺ� �� �ֽ��ϴ�.\nHŰ�� ������ �� �� �ֽ��ϴ�.\n");
}
