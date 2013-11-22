// SUD.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "GameManager.h"

//메인함수는 객체 ㄴㄴ. 진입점함수. 저기다 뭘 많이 넣는 건 객체지향적이지 않음. 게임매니저가 전체 관리하는 객체. 메인함수는 게임매니저만 만들면 됨
int _tmain(int argc, _TCHAR* argv[])
{
// 	std::string helloWorld = "Hello World";
// 
// 	printf("%s\n", helloWorld); //%s는 문자열 배열을 출력함. null문자(/0)를 만날 때까지 배열을 차례차례 출력하는 것. string은 문자열 배열이 아니라 객체이므로 출력이 안 된다.
// 	printf("%p\n", helloWorld);
// 	printf_s("%s\n", helloWorld.c_str());
// 
// 	std::cout<<helloWorld<<std::endl;
// 	

	CGameManager gameManager;

	gameManager.Init();
	gameManager.Run();
	gameManager.Release();


//	getchar();
	return 0;
}

