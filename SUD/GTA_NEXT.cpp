// SUD.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "GameManager.h"
#include "GameManager2.h"
#include <iosfwd>
#include "MapManager.h"

std::string getAsciiArts(std::ifstream& File);
void PrintAsciiArts(std::string filePath);

//�����Լ��� ��ü�� �ƴ϶� �������Լ�. ����� �� ���� �ִ� �� ��ü���������� ����. ���ӸŴ����� ��ü �����ϴ� ��ü. �����Լ��� ���ӸŴ����� ����� ��
// void PrintMainTitle(void)
// {
// 	printf("");
// }

std::string getAsciiArts(std::ifstream& File)
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


void PrintAsciiArts( std::string filePath )
{
	std::ifstream File;
	File.open(filePath);
	printf_s("%s\n", getAsciiArts(File).c_str());
	File.close();
}


int _tmain(void)
{
	// 	std::string helloWorld = "Hello World";
	// 
	// 	printf("%s\n", helloWorld); //%s�� ���ڿ� �迭�� �����. null����(/0)�� ���� ������ �迭�� �������� ����ϴ� ��. string�� ���ڿ� �迭�� �ƴ϶� ��ü�̹Ƿ� ����� �� �ȴ�.
	// 	printf("%p\n", helloWorld);
	// 	printf_s("%s\n", helloWorld.c_str());
	// 
	// 	std::cout<<helloWorld<<std::endl;
	// 	

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

// 	std::ifstream mainTitle;
// 	mainTitle.open("AA/Title.txt");
// 
// 	printf_s("%s\n", getFileContents(mainTitle).c_str());
// 
// 	mainTitle.close();

	PrintAsciiArts("AA/Title.txt");
	/*std::cout << CMapManager::GetInstance()->NextHall.GetChildMapChips()[5]->GetMapName() << std::endl;*/
	CGameManager2 gameManager;

	gameManager.Init();
	gameManager.Run();
	gameManager.Release();

	getchar();
	return 0;
}

