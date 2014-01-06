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
	//Ű���� �Է��� �޾Ƽ�, Ŀ�ǵ带 �Ľ��ϰ� �°� ó���Ѵ�. Q�� �Է��ϸ� ����
	// 	char ch = NULL;
	// 	scanf_s("%c", &ch, sizeof(ch));
	// 	printf_s("input:%c\n", ch);

	
	/*std::cin>>strInput;*/
	std::cout << "���� ��ġ : " << CMapManager::GetInstance()->GetCurrentMap()->GetMapName() 
		<< std::endl;
	
	std::cout <<  "\n" << "���ϴ� �ൿ�� ������ �ֽʽÿ�.\n" << std::endl;
	std::cout <<
		"1. �̵��ϱ�\n" <<
		"2. �ο��\n" <<
		"3. ��ȭ�ϱ�\n" <<
		"4. ���캸��\n" <<
		"5. ����Ʈ\n" <<
		"6. �� ����\n" <<
		"7. ���� ����\n" <<
		"8. ���� ����\n" << std::endl;

	
	getline(std::cin, inputBuffer);

	if (inputBuffer == "1")
	{
		printf_s("���� �̵��Ͻðڽ��ϱ�?\n");
		if (CMapManager::GetInstance()->GetCurrentMap()->GetParentMapChip() != nullptr)
		{
		std::cout << "1. " << 
			CMapManager::GetInstance()->GetCurrentMap()->GetParentMapChip()->GetMapName() << std::endl;
		}
		else
			printf_s("1. ���� �� ���� - ���ԺҰ�\n");

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
			printf_s("�ο� ��밡 �����ϴ�.\n");
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
			printf_s("��ȭ�� ���� ��밡 �����ϴ�.\n");
	}
	else if (inputBuffer == "4")
	{
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC()!= nullptr)
		{
			std::cout<<"�̰��� " << 
				CMapManager::GetInstance()->GetCurrentMap()->GetNPC()->GetName() << 
				"��(��) �ֽ��ϴ�." << std::endl;
		}
		if (CMapManager::GetInstance()->GetCurrentMap()->GetMob()!= nullptr)
		{
			std::cout<<"�̰��� " <<
				CMapManager::GetInstance()->GetCurrentMap()->GetMob()->GetName() << 
				"��(��) �ֽ��ϴ�." << std::endl;
		}
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC() == nullptr &&
			CMapManager::GetInstance()->GetCurrentMap()->GetMob() == nullptr)
		{
			std::cout<<"�̰��� �ƹ��� �����ϴ�." << std::endl;
		}
		if (CMapManager::GetInstance()->GetCurrentMap()->GetItem() != nullptr)
		{
			std::cout<<"�������� " <<
				CMapManager::GetInstance()->GetCurrentMap()->GetItem()->GetItemName() << 
				"�� �߰��߽��ϴ�!\n" << "[system] ȹ���� �������� ��� �����˴ϴ�.\n '�� ���� ����'�� ���� ���� ������ �����۰� ȿ���� Ȯ���� �� �ֽ��ϴ�." << std::endl;
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
			"���� B�� �繫��")
		{
			KillAllMobs->setStart();
			printf_s("\n\n\n\n Q  U  E  S  T\n\n��� �������͸� óġ�϶�!\n\n\n");
		}
		else if (KillAllMobs->GetIsClear() == true &&
			CMapManager::GetInstance()->GetCurrentMap()->GetMapName() == 
			"���� B�� �繫��")
		{
			printf_s("���� B : ���� �����߳�!\n");
		}
		

	}
	else if (inputBuffer == "6")
	{
		std::cout << "�̸� : " << m_PC->GetName() << std::endl;
		std::cout << "HP : " << m_PC->GetHP() << std::endl;
		std::cout << "ATK : " << m_PC->GetATK() << std::endl; 
		std::cout << "���� �������� ������" << std::endl;
		if (m_PC->GetEquippedItem(WEAPON)!= nullptr)
		{
			std::cout << "���� : " << m_PC->GetEquippedItem(WEAPON)->GetItemName() << std::endl;
		}
		if (m_PC->GetEquippedItem(ARMOR)!= nullptr)
		{
			std::cout << "������ : " << m_PC->GetEquippedItem(ARMOR)->GetItemName() << std::endl;
		}
		if (m_PC->GetEquippedItem(ACCESSORY)!= nullptr)
		{
			std::cout << "�Ǽ��縮 : " << m_PC->GetEquippedItem(ACCESSORY)->GetItemName() <<std::endl;
		}
		
	}
	else if (inputBuffer == "7")
	{
		OpenHelpMenu();
	}
	else if (inputBuffer == "8")
	{
		printf_s("������ �����մϴ�\n");
		return false;
	}
	else
		printf_s("�߸��� ����Դϴ�.\n\n");

	//system("cls");
	return true;
}


void CGameManager2::CreateMobs(void)
{
	
	for (int i = 0; i < 4; ++i)
	{
		char buf[16];
		pMob[i] = new CMob();
		sprintf_s(buf, "�������� %04x", i * rand() % 65536);
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
	pNPC[0]->SetName("���� P");
	pNPC[0]->AddSpeach("���ض� �װ�");
	pNPC[0]->AddSpeach("�����ض� �װ�");
	pNPC[0]->AddSpeach("�� �ڽ�!");
	CMapManager::GetInstance()->Prof_PMK.SetNPC(pNPC[0]);
	pNPC[1]->SetName("���� 9");
	CMapManager::GetInstance()->Prof_SM9.SetNPC(pNPC[1]);
	pNPC[2]->SetName("���� B");
	pNPC[2]->ClearSpeach();
	pNPC[2]->AddSpeach("����Ʈ�� �� �״� 5���� ���� ������.");
	CMapManager::GetInstance()->Prof_BYH.SetNPC(pNPC[2]);
	pNPC[3]->SetName("���� H");
	CMapManager::GetInstance()->Prof_HSJ.SetNPC(pNPC[3]);
	pNPC[4]->SetName("���� J");
	CMapManager::GetInstance()->Prof_JHY.SetNPC(pNPC[4]);
	pNPC[4]->AddSpeach("��~ ������ �ص� �� ��������");
	pNPC[5]->SetName("���� K");
	CMapManager::GetInstance()->Prof_KDJ.SetNPC(pNPC[5]);
	pNPC[6]->SetName("���� L");
	pNPC[6]->ClearSpeach();
	pNPC[6]->AddSpeach("����Ʈ�� �� �״� 5���� ���� ������.");
	CMapManager::GetInstance()->Prof_LSH.SetNPC(pNPC[6]);
	pNPC[7]->SetName("���� Y");
	CMapManager::GetInstance()->Prof_YJS.SetNPC(pNPC[7]);
	pNPC[8]->SetName("�ֿ���");
	CMapManager::GetInstance()->Recover2_3.SetNPC(pNPC[8]);
	pNPC[9]->SetName("������");
	CMapManager::GetInstance()->Recover2_4.SetNPC(pNPC[9]);
	pNPC[10]->SetName("�̿�ȿ");
	CMapManager::GetInstance()->Recover2_6.SetNPC(pNPC[10]);
	pNPC[10]->AddSpeach("�� ��Ÿ����. ���̸� �����Ϸ� ����");
	pNPC[11]->SetName("������");
	CMapManager::GetInstance()->Recover3_8.SetNPC(pNPC[11]);
	pNPC[12]->SetName("�ͼ�ĳ��");
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
	
	printf_s("%s���� �ο��� �ɾ����ϴ�! \n", pMob->GetName().c_str());
	while (m_PC->IsAlive() && pMob->IsAlive())
	{
		printf_s("%s�� �����߽��ϴ�!\n---->", pMob->GetName().c_str());

		attackPower = static_cast<int>(m_PC->GetATK()-(m_PC->GetATK()*0.1*(rand()%3)+(m_PC->GetATK()*0.1*(rand()%3))));
		pMob->DamageCheck(pMob->IsHit(), attackPower);
		if(pMob->IsAlive() == false)
		{
			printf_s("#### %s�� �¸�! #### \n", m_PC->GetName().c_str());
			break;
		}

		printf_s("%s �κ��� ���ݴ��߽��ϴ�!\n---->", pMob->GetName().c_str());
		attackPower = static_cast<int>(pMob->GetATK()-(pMob->GetATK()*0.1*(rand()%3)+(pMob->GetATK()*0.1*(rand()%3))));
		m_PC->DamageCheck(m_PC->IsHit(), attackPower);
		if(m_PC->IsAlive() == false)
		{
			printf_s("\n  ����߽��ϴ�....  \n");
			getchar();
			break;
		}
		Sleep(1000);
	}
}


void CGameManager2::OpenHelpMenu( void )
{
	printf("�� ������ ������ �ʿ���� ������ ���� �������Դϴ�! :D\n");
}

void CGameManager2::ShowMapMessage(CMapChip* map )
{
	switch (map->GetMapType())
	{
	case HALL:
		printf("����� Ȧ�� ���Խ��ϴ�. Ź����� ĵƾ, ���� ���ǰ����� ���� ���ɴϴ�.\n");
		break;
	case PROMPT:
		printf("�� ������Ʈ ������ ���Խ��ϴ�. ���� �ұ��� ����� ��ϴ�....\n");
		break;
	case LINK:
		break;
	case VILLAGE:
		printf("����� ������ �ȱ� �����߽��ϴ�. Ȧ�� �����ų� ��ó�� ���� �������� �� �� �ֽ��ϴ�.\n");
		break;
	case RECOVER:
		printf("����� ��Ŀ������ ��Ŀ���ǰ� �ֽ��ϴ�... ������ ��������� ���� �������� �� ���� ����� ��ϴ�. ������ ��и�.....\n");
		break;
	case PROF_OFFICE:
		if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC()!= nullptr)
		{
			printf("��        ��\n\n\n\n��        ��\n");
		}
		break;
	case TEACHER_OFFICE:
		printf("�������� �湮���� ���� ��ް� �̸��� ū �Ҹ��� ���ϰ� '�빫�� �־� �Խ��ϴ�!' ��� ���� �� �Խ��㰡�� ������ ������ ��ٷ��� �մϴ�.\n");
		break;
	case LIBRARY:
		printf("����� ���̺귯���� �ɾ�ϴ�... ������ ���� �� ���ӿ��� ���� ���� ����� �����Ǿ� ���� �ʽ��ϴ�.\n");
		break;
	default:
		break;
	}
	if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC()!= nullptr)
	{
		std::cout<<CMapManager::GetInstance()->GetCurrentMap()->GetNPC()->GetName() << "��(��) ��Ÿ�����ϴ�." << std::endl;
	}
	if (CMapManager::GetInstance()->GetCurrentMap()->GetMob()!= nullptr)
	{
		std::cout<<CMapManager::GetInstance()->GetCurrentMap()->GetMob()->GetName() << "��(��) ��Ÿ�����ϴ�." << std::endl;
	}
	if (CMapManager::GetInstance()->GetCurrentMap()->GetNPC() == nullptr &&
		CMapManager::GetInstance()->GetCurrentMap()->GetMob() == nullptr)
	{
		std::cout<<"�̰��� �ƹ��� �����ϴ�." << std::endl;
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
	if (mapName == "���� P�� �繫��")
	{
		PrintAsciiArts("AA/park.txt");
	}
	else if (mapName == "���� H�� �繫��")
	{
		PrintAsciiArts("AA/ham.txt");
	}
	else if (mapName == "���� 9�� �繫��")
	{
		PrintAsciiArts("AA/sm9.txt");
	}
	else if (mapName == "���� B�� �繫��")
	{
		PrintAsciiArts("AA/bae.txt");
	}
	else if (mapName == "���� J�� �繫��")
	{
		PrintAsciiArts("AA/jhy.txt");
	}
	else if (mapName == "���� K�� �繫��")
	{
		PrintAsciiArts("AA/kdj.txt");
	}
	else if (mapName == "���� L�� �繫��")
	{
		PrintAsciiArts("AA/lsh.txt");
	}
	else if (mapName == "���� Y�� �繫��")
	{
		PrintAsciiArts("AA/yjs.txt");
	}
}


