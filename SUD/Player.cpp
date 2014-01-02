#include "stdafx.h"
#include "Player.h"
#include "MapChip.h"
#include "MapManager.h"


CPlayer::CPlayer(void)
{
	//printf_s("Player Created\n");
}


CPlayer::~CPlayer(void)
{
	//printf_s("Player deleted\n");
}

void CPlayer::PrintType()
{
	printf_s("My Type is CPlayer\n");
}

void CPlayer::SetName()
{
	bool complete = false;
	while (complete == false)
	{
		std::string inputBuffer;
		printf("당신의 이름을 입력해 주십시오.\n");
		getline(std::cin, inputBuffer);
		m_Status.name = inputBuffer;
		std::cout << "입력한 이름 : " << GetName() << std::endl;
		std::cout << "이 이름으로 결정하시겠습니까?(Y/N)" << std::endl;
		getline(std::cin, inputBuffer);
		if (inputBuffer == "y" || inputBuffer == "Y")
		{
			//printf("\n게임을 시작합니다.\n\n");
			complete = true;
		} 
		else if (inputBuffer == "n" || inputBuffer == "N")
		{
			printf("\n다른 이름을 입력합니다.\n\n");
		}
		else
		{
			printf("\n잘못된 응답입니다.\n\n");
		}
	}
}

void CPlayer::SetStartPosition()
{
	bool complete = false;
	while (complete == false)
	{
		std::string inputBuffer;
		printf("어느 리커버에서 시작하시겠습니까?\n1.리커버 2-3\n2.리커버 2-4\n3.리커버 2-6\n4.리커버 3-8\n5.리커버 3-9\n");
		getline(std::cin, inputBuffer);
		if (inputBuffer == "1")
		{
			m_StartPosition = &(CMapManager::GetInstance()->Recover2_3);
		}
		else if (inputBuffer == "2")
		{
			m_StartPosition = &(CMapManager::GetInstance()->Recover2_4);
		}
		else if (inputBuffer == "3")
		{
			m_StartPosition = &(CMapManager::GetInstance()->Recover2_6);
		}
		else if (inputBuffer == "4")
		{
			m_StartPosition = &(CMapManager::GetInstance()->Recover3_8);
		}
		else if (inputBuffer == "5")
		{
			m_StartPosition = &(CMapManager::GetInstance()->Recover3_9);
		}
		else
		{
			printf("입력이 잘못되었습니다.\n");
			continue;
		}

		std::cout << "시작 리커버 위치 : " << m_StartPosition->GetMapName() << std::endl;
		std::cout << "이곳에서 시작하시겠습니까?(Y/N)" << std::endl;
		getline(std::cin, inputBuffer);
		if (inputBuffer == "y" || inputBuffer == "Y")
		{
			printf("\n게임을 시작합니다.\n\n");
			CMapManager::GetInstance()->SetCurrentMap(m_StartPosition);
			complete = true;
		} 
		else if (inputBuffer == "n" || inputBuffer == "N")
		{
			printf("\n다른 리커버를 입력합니다.\n\n");
		}
		else
		{
			printf("\n잘못된 응답입니다.\n\n");
		}
	}
}
