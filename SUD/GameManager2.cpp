#include "stdafx.h"
#include "GameManager2.h"
#include "Character.h"
#include <iostream>
#include <string>
#include "Mob.h"
#include <windows.h>
#include "MapManager.h"
#include "Item.h"

CGameManager2::CGameManager2(void)
{
	m_PC = new CPlayer;
	m_PC->SetATK(300);
	m_PC->SetHP(300);
	KillAllMobs = new Quest();
	FindTA = new Quest();
	BFT = new CItem();
	URF = new CItem();
	
}

CGameManager2::~CGameManager2(void)
{
	delete m_PC;
	delete KillAllMobs;
	delete FindTA;
	delete BFT;
	delete URF;
}

Quest::Quest(void): isStart(false), isClear(false)
{

}

Quest::~Quest(void)
{

}

void CGameManager2::Init(void)
{
	srand((unsigned)time(NULL));

	m_PC->SetName();
	m_PC->SetStartPosition();

 	CreateMobs();
 	CreateNPCs();
	CreateItems();
	
}

void CGameManager2::Run(void)
{
	while (InputProc())
	{
	}
}


void CGameManager2::Release(void)
{
	CMapManager::GetInstance()->ReleaseInstance();
	for (int i = 0; i < 4; ++i)
	{
		delete pMob[i];
	}
	for (int i = 0; i < 13; ++i)
	{
		delete pNPC[i];
	}
	printf("Thank you for playing\n");
}



bool CGameManager2::InputProc(void)
{
	//키보드 입력을 받아서, 커맨드를 파싱하고 맞게 처리한다. Q를 입력하면 종료
	// 	char ch = NULL;
	// 	scanf_s("%c", &ch, sizeof(ch));
	// 	printf_s("input:%c\n", ch);

	
	/*std::cin>>strInput;*/
	std::cout << "현재 위치 : " << CMapManager::GetInstance()->GetCurrentMap()->GetMapName() 
		<< std::endl;
	
	std::cout <<  "\n" << "원하는 행동을 선택해 주십시오.\n" << std::endl;
	std::cout <<
		"1. 이동하기\n" <<
		"2. 싸우기\n" <<
		"3. 대화하기\n" <<
		"4. 살펴보기\n" <<
		"5. 퀘스트\n" <<
		"6. 내 정보\n" <<
		"7. 도움말 보기\n" <<
		"8. 게임 종료\n" << std::endl;

	
	getline(std::cin, inputBuffer);

	if (inputBuffer == "1")
	{
		printf_s("어디로 이동하시겠습니까?\n");
		if (CMapManager::GetInstance()->GetCurrentMap()->GetParentMapChip() != nullptr)
		{
		std::cout << "1. " << 
			CMapManager::GetInstance()->GetCurrentMap()->GetParentMapChip()->GetMapName() << std::endl;
		}
		else
			printf_s("1. 개발 중 공간 - 출입불가\n");

		for (unsigned int i = 0; i < CMapManager::GetInstance()->GetCurrentMap()->GetChildMapChips().size(); ++i)
		{
			std::cout << i + 2 << ". " << CMapManager::GetInstance()->GetCurrentMap()->GetChildMapChips()[i]->GetMapName() << std::endl;
		}
		unsigned int key;
		scanf_s("%d", &key);
		if (key == 1)
			CMapManager::GetInstance()->GotoParentMap();
		if (key >= 2 && key < CMapManager::GetInstance()->GetCurrentMap()->GetChildMapChips().size() + 2)
			CMapManager::GetInstance()->GotoChildMap(key-2);
		
		if (CMapManager::GetInstance()->GetCurrentMap()->GetMapType() == PROF_OFFICE &&
			CMapManager::GetInstance()->GetCurrentMap()->GetNPC() != nullptr)
		{
			PrintProfImage(CMapManager::GetInstance()->GetCurrentMap()->GetMapName());
		}
		ShowMapMessage(CMapManager::GetInstance()->GetCurrentMap());
		return true;
	}
	else if (inputBuffer == "2")
	{
		if (CMapManager::GetInstance()->GetCurrentMap()->GetMob() != nullptr &&
			CMapManager::GetInstance()->GetCurrentMap()->GetNPC() == nullptr)
		{
			Battle(CMapManager::GetInstance()->GetCurrentMap()->GetMob());
			if (m_PC->IsAlive())
			{
				//delete CMapManager::GetInstance()->GetCurrentMap()->GetMob();
				CMapManager::GetInstance()->GetCurrentMap()->SetMob(nullptr);
			}
			else if (m_PC->IsAlive() == false)
			{
				return false;
			}
		}
		else if (CMapManager::GetInstance()->GetCurrentMap()->GetMob() == nullptr &&
			CMapManager::GetInstance()->GetCurrentMap()->GetNPC() != nullptr)
		{
			Battle(CMapManager::GetInstance()->GetCurrentMap()->GetNPC());
			if (m_PC->IsAlive())
			{
				//delete CMapManager::GetInstance()->GetCurrentMap()->GetNPC();
				CMapManager::GetInstance()->GetCurrentMap()->SetNPC(nullptr);
			}
			else if (m_PC->IsAlive() == false)
			{
				return false;
			}
		}
		else if (CMapManager::GetInstance()->GetCurrentMap()->GetMob() == nullptr &&
			CMapManager::GetInstance()->GetCurrentMap()->GetNPC() == nullptr)
		{
			printf_s("싸울 상대가 없습니다.\n");
		}


		if (KillAllMobs->GetIsStart() == true &&
			CMapManager::GetInstance()->Prompt2_4.GetMob() == nullptr &&
			CMapManager::GetInstance()->Prompt3_10.GetMob() == nullptr &&
			CMapManager::GetInstance()->Prompt4_11.GetMob() == nullptr &&
			CMapManager::GetInstance()->Prompt4_14.GetMob() == nullptr)
		{
			KillAllMobs->setClear();
		}

		return true;
	}
	else if (inputBuffer == "3")
	{
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC() != nullptr)
		{
			CMapManager::GetInstance()->GetCurrentMap()->GetNPC()->Speak();
		}
		else
			printf_s("대화를 나눌 상대가 없습니다.\n");
	}
	else if (inputBuffer == "4")
	{
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC()!= nullptr)
		{
			std::cout<<"이곳엔 " << 
				CMapManager::GetInstance()->GetCurrentMap()->GetNPC()->GetName() << 
				"이(가) 있습니다." << std::endl;
		}
		if (CMapManager::GetInstance()->GetCurrentMap()->GetMob()!= nullptr)
		{
			std::cout<<"이곳엔 " <<
				CMapManager::GetInstance()->GetCurrentMap()->GetMob()->GetName() << 
				"이(가) 있습니다." << std::endl;
		}
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC() == nullptr &&
			CMapManager::GetInstance()->GetCurrentMap()->GetMob() == nullptr)
		{
			std::cout<<"이곳엔 아무도 없습니다." << std::endl;
		}
		if (CMapManager::GetInstance()->GetCurrentMap()->GetItem() != nullptr)
		{
			std::cout<<"구석에서 " <<
				CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetItemName() << 
				"을 발견했습니다!\n" << "[system] 획득한 아이템은 즉시 장착됩니다.\n '내 정보 보기'를 통해 현재 장착한 아이템과 효과를 확인할 수 있습니다." << std::endl;
			if ( m_PC->GetEquippedItem
				(CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetItemType()) != nullptr)
			{
				m_PC->SetATK(m_PC->GetATK() -
					m_PC->GetEquippedItem(CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetItemType())->GetATKBonus() + 
					CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetATKBonus());
				m_PC->SetATK(m_PC->GetHP() - 
					m_PC->GetEquippedItem(CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetItemType())->GetHPBonus() + 
					CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetHPBonus());
			}
			else
			{
				m_PC->SetATK(m_PC->GetATK() + CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetATKBonus());
				m_PC->SetHP(m_PC->GetHP() + CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetHPBonus());
			}
			m_PC->EquipNewItem(CMapManager::GetInstance()->GetCurrentMap()->GetItem());
			CMapManager::GetInstance()->GetCurrentMap()->SetHiddenItem(nullptr);
		}
	}
	else if (inputBuffer == "5")
	{
		if (KillAllMobs->GetIsStart() == false && 
			CMapManager::GetInstance()->GetCurrentMap()->GetMapName() == 
			"교수 B의 사무실")
		{
			KillAllMobs->setStart();
			printf_s("\n\n\n\n Q  U  E  S  T\n\n모든 레지스터를 처치하라!\n\n\n");
		}
		else if (KillAllMobs->GetIsClear() == true &&
			CMapManager::GetInstance()->GetCurrentMap()->GetMapName() == 
			"교수 B의 사무실")
		{
			printf_s("교수 B : 오오 수고했네!\n");
		}
		

	}
	else if (inputBuffer == "6")
	{
		std::cout << "이름 : " << m_PC->GetName() << std::endl;
		std::cout << "HP : " << m_PC->GetHP() << std::endl;
		std::cout << "ATK : " << m_PC->GetATK() << std::endl; 
		std::cout << "현재 장착중인 아이템" << std::endl;
		if (m_PC->GetEquippedItem(WEAPON)!= nullptr)
		{
			std::cout << "무기 : " << m_PC->GetEquippedItem(WEAPON)->GetItemName() << std::endl;
		}
		if (m_PC->GetEquippedItem(ARMOR)!= nullptr)
		{
			std::cout << "방어장비 : " << m_PC->GetEquippedItem(ARMOR)->GetItemName() << std::endl;
		}
		if (m_PC->GetEquippedItem(ACCESSORY)!= nullptr)
		{
			std::cout << "악세사리 : " << m_PC->GetEquippedItem(ACCESSORY)->GetItemName() <<std::endl;
		}
		
	}
	else if (inputBuffer == "7")
	{
		OpenHelpMenu();
	}
	else if (inputBuffer == "8")
	{
		printf_s("게임을 종료합니다\n");
		return false;
	}
	else
		printf_s("잘못된 명령입니다.\n\n");

	//system("cls");
	return true;
}


void CGameManager2::CreateMobs(void)
{
	
	for (int i = 0; i < 4; ++i)
	{
		char buf[16];
		pMob[i] = new CMob();
		sprintf_s(buf, "레지스터 %04x", i * rand() % 65536);
		std::string mobName = buf;
		pMob[i]->SetName(mobName);
		pMob[i]->SetATK(300);
		pMob[i]->SetHP(2000);
	}
	CMapManager::GetInstance()->Prompt2_4.SetMob(pMob[0]);
	CMapManager::GetInstance()->Prompt3_10.SetMob(pMob[1]);
	CMapManager::GetInstance()->Prompt4_11.SetMob(pMob[2]);
	CMapManager::GetInstance()->Prompt4_14.SetMob(pMob[3]);
}

void CGameManager2::CreateNPCs(void)
{	
	
	for (int i = 0; i < 13; ++i)
	{
		pNPC[i] = new CNPC();
		pNPC[i]->SetATK(2000);
		pNPC[i]->SetHP(2000);
		pNPC[i]->SpeachInit();
	}
	pNPC[0]->SetName("교수 P");
	pNPC[0]->AddSpeach("일해라 닝겐");
	pNPC[0]->AddSpeach("공부해라 닝겐");
	pNPC[0]->AddSpeach("이 자식!");
	CMapManager::GetInstance()->Prof_PMK.SetNPC(pNPC[0]);
	pNPC[1]->SetName("교수 9");
	CMapManager::GetInstance()->Prof_SM9.SetNPC(pNPC[1]);
	pNPC[2]->SetName("교수 B");
	pNPC[2]->ClearSpeach();
	pNPC[2]->AddSpeach("퀘스트를 줄 테니 5번을 눌러 보세요.");
	CMapManager::GetInstance()->Prof_BYH.SetNPC(pNPC[2]);
	pNPC[3]->SetName("교수 H");
	CMapManager::GetInstance()->Prof_HSJ.SetNPC(pNPC[3]);
	pNPC[4]->SetName("교수 J");
	CMapManager::GetInstance()->Prof_JHY.SetNPC(pNPC[4]);
	pNPC[4]->AddSpeach("햐~ 생각만 해도 참 좋은데요");
	pNPC[5]->SetName("교수 K");
	CMapManager::GetInstance()->Prof_KDJ.SetNPC(pNPC[5]);
	pNPC[6]->SetName("교수 L");
	pNPC[6]->ClearSpeach();
	pNPC[6]->AddSpeach("퀘스트를 줄 테니 5번을 눌러 보세요.");
	CMapManager::GetInstance()->Prof_LSH.SetNPC(pNPC[6]);
	pNPC[7]->SetName("교수 Y");
	CMapManager::GetInstance()->Prof_YJS.SetNPC(pNPC[7]);
	pNPC[8]->SetName("최연규");
	CMapManager::GetInstance()->Recover2_3.SetNPC(pNPC[8]);
	pNPC[9]->SetName("김희재");
	CMapManager::GetInstance()->Recover2_4.SetNPC(pNPC[9]);
	pNPC[10]->SetName("이원효");
	CMapManager::GetInstance()->Recover2_6.SetNPC(pNPC[10]);
	pNPC[10]->AddSpeach("난 산타란다. 나이를 선물하러 왔지");
	pNPC[11]->SetName("정윤성");
	CMapManager::GetInstance()->Recover3_8.SetNPC(pNPC[11]);
	pNPC[12]->SetName("익성캐논");
	CMapManager::GetInstance()->Recover3_9.SetNPC(pNPC[12]);
}

void CGameManager2::CreateItems( void )
{
	BFT->SetATKBonus(99999);
	BFT->SetHPBonus(100);
	BFT->SetItemType(WEAPON);
	BFT->SetItemName("BIG FUCKING TEXTBOOK");
	CMapManager::GetInstance()->Office.SetHiddenItem(BFT);

	URF->SetATKBonus(100);
	URF->SetHPBonus(99999);
	URF->SetItemType(ACCESSORY);
	URF->SetItemName("ULTRA RARE FIGURE");
	CMapManager::GetInstance()->Prof_PMK.SetHiddenItem(URF);

}


void CGameManager2::Battle(CCharacter* pMob)
{
	
	printf_s("%s에게 싸움을 걸었습니다! \n", pMob->GetName().c_str());
	while (m_PC->IsAlive() && pMob->IsAlive())
	{
		printf_s("%s를 공격했습니다!\n---->", pMob->GetName().c_str());

		attackPower = static_cast<int>(m_PC->GetATK()-(m_PC->GetATK()*0.1*(rand()%3)+(m_PC->GetATK()*0.1*(rand()%3))));
		pMob->DamageCheck(pMob->IsHit(), attackPower);
		if(pMob->IsAlive() == false)
		{
			printf_s("#### %s의 승리! #### \n", m_PC->GetName().c_str());
			break;
		}

		printf_s("%s 로부터 공격당했습니다!\n---->", pMob->GetName().c_str());
		attackPower = static_cast<int>(pMob->GetATK()-(pMob->GetATK()*0.1*(rand()%3)+(pMob->GetATK()*0.1*(rand()%3))));
		m_PC->DamageCheck(m_PC->IsHit(), attackPower);
		if(m_PC->IsAlive() == false)
		{
			printf_s("\n  사망했습니다....  \n");
			getchar();
			break;
		}
		Sleep(1000);
	}
}


void CGameManager2::OpenHelpMenu( void )
{
	printf("이 게임은 도움말이 필요없을 정도로 쉽고 직관적입니다! :D\n");
}

void CGameManager2::ShowMapMessage(CMapChip* map )
{
	switch (map->GetMapType())
	{
	case HALL:
		printf("당신은 홀로 나왔습니다. 탁구대와 캔틴, 넓은 강의공간이 눈에 들어옵니다.\n");
		break;
	case PROMPT:
		printf("빈 프롬프트 안으로 들어왔습니다. 왠지 불길한 기분이 듭니다....\n");
		break;
	case LINK:
		break;
	case VILLAGE:
		printf("당신은 복도를 걷기 시작했습니다. 홀로 나가거나 근처의 개별 공간으로 들어갈 수 있습니다.\n");
		break;
	case RECOVER:
		printf("당신은 리커버에서 리커버되고 있습니다... 마음이 평안해지고 힘이 차오르는 것 같은 기분이 듭니다. 오로지 기분만.....\n");
		break;
	case PROF_OFFICE:
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC()!= nullptr)
		{
			printf("교        수\n\n\n\n출        현\n");
		}
		break;
	case TEACHER_OFFICE:
		printf("행정실을 방문했을 때는 계급과 이름을 큰 소리로 말하고 '용무가 있어 왔습니다!' 라고 밝힌 뒤 입실허가가 내려질 때까지 기다려야 합니다.\n");
		break;
	case LIBRARY:
		printf("당신은 라이브러리로 걸어갑니다... 하지만 아직 이 게임에는 도서 관련 기능이 구현되어 있지 않습니다.\n");
		break;
	default:
		break;
	}
	if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC()!= nullptr)
	{
		std::cout<<CMapManager::GetInstance()->GetCurrentMap()->GetNPC()->GetName() << "이(가) 나타났습니다." << std::endl;
	}
	if (CMapManager::GetInstance()->GetCurrentMap()->GetMob()!= nullptr)
	{
		std::cout<<CMapManager::GetInstance()->GetCurrentMap()->GetMob()->GetName() << "이(가) 나타났습니다." << std::endl;
	}
	if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC() == nullptr &&
		CMapManager::GetInstance()->GetCurrentMap()->GetMob() == nullptr)
	{
		std::cout<<"이곳엔 아무도 없습니다." << std::endl;
	}
}


std::string CGameManager2::getAsciiArts(std::ifstream& File)
{
	std::string Lines = "";

	if (File)
	{
		while (File.good())
		{
			std::string TempLine;
			std::getline(File, TempLine);
			TempLine += "\n";

			Lines += TempLine;
		}
		return Lines;
	}
	else
	{
		return "ERROR : Text File is not Exist";
	}
}


void CGameManager2::PrintAsciiArts( std::string filePath )
{
	std::ifstream File;
	File.open(filePath);
	printf_s("%s\n", getAsciiArts(File).c_str());
	File.close();
}

void CGameManager2::PrintProfImage( std::string mapName )
{
	if (mapName == "교수 P의 사무실")
	{
		PrintAsciiArts("AA/park.txt");
	}
	else if (mapName == "교수 H의 사무실")
	{
		PrintAsciiArts("AA/ham.txt");
	}
	else if (mapName == "교수 9의 사무실")
	{
		PrintAsciiArts("AA/sm9.txt");
	}
	else if (mapName == "교수 B의 사무실")
	{
		PrintAsciiArts("AA/bae.txt");
	}
	else if (mapName == "교수 J의 사무실")
	{
		PrintAsciiArts("AA/jhy.txt");
	}
	else if (mapName == "교수 K의 사무실")
	{
		PrintAsciiArts("AA/kdj.txt");
	}
	else if (mapName == "교수 L의 사무실")
	{
		PrintAsciiArts("AA/lsh.txt");
	}
	else if (mapName == "교수 Y의 사무실")
	{
		PrintAsciiArts("AA/yjs.txt");
	}
}


