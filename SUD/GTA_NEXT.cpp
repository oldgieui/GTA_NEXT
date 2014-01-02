// SUD.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

//메인함수는 객체가 아니라 진입점함수. 저기다 뭘 많이 넣는 건 객체지향적이지 않음. 게임매니저가 전체 관리하는 객체. 메인함수는 게임매니저만 만들면 됨
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
	// 	printf("%s\n", helloWorld); //%s는 문자열 배열을 출력함. null문자(/0)를 만날 때까지 배열을 차례차례 출력하는 것. string은 문자열 배열이 아니라 객체이므로 출력이 안 된다.
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

