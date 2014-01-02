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
		printf("����� �̸��� �Է��� �ֽʽÿ�.\n");
		getline(std::cin, inputBuffer);
		m_Status.name = inputBuffer;
		std::cout << "�Է��� �̸� : " << GetName() << std::endl;
		std::cout << "�� �̸����� �����Ͻðڽ��ϱ�?(Y/N)" << std::endl;
		getline(std::cin, inputBuffer);
		if (inputBuffer == "y" || inputBuffer == "Y")
		{
			//printf("\n������ �����մϴ�.\n\n");
			complete = true;
		} 
		else if (inputBuffer == "n" || inputBuffer == "N")
		{
			printf("\n�ٸ� �̸��� �Է��մϴ�.\n\n");
		}
		else
		{
			printf("\n�߸��� �����Դϴ�.\n\n");
		}
	}
}

void CPlayer::SetStartPosition()
{
	bool complete = false;
	while (complete == false)
	{
		std::string inputBuffer;
		printf("��� ��Ŀ������ �����Ͻðڽ��ϱ�?\n1.��Ŀ�� 2-3\n2.��Ŀ�� 2-4\n3.��Ŀ�� 2-6\n4.��Ŀ�� 3-8\n5.��Ŀ�� 3-9\n");
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
			printf("�Է��� �߸��Ǿ����ϴ�.\n");
			continue;
		}

		std::cout << "���� ��Ŀ�� ��ġ : " << m_StartPosition->GetMapName() << std::endl;
		std::cout << "�̰����� �����Ͻðڽ��ϱ�?(Y/N)" << std::endl;
		getline(std::cin, inputBuffer);
		if (inputBuffer == "y" || inputBuffer == "Y")
		{
			printf("\n������ �����մϴ�.\n\n");
			CMapManager::GetInstance()->SetCurrentMap(m_StartPosition);
			complete = true;
		} 
		else if (inputBuffer == "n" || inputBuffer == "N")
		{
			printf("\n�ٸ� ��Ŀ���� �Է��մϴ�.\n\n");
		}
		else
		{
			printf("\n�߸��� �����Դϴ�.\n\n");
		}
	}
}
