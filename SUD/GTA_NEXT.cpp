// SUD.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "GameManager.h"

//�����Լ��� ��ü ����. �������Լ�. ����� �� ���� �ִ� �� ��ü���������� ����. ���ӸŴ����� ��ü �����ϴ� ��ü. �����Լ��� ���ӸŴ����� ����� ��
int _tmain(int argc, _TCHAR* argv[])
{
// 	std::string helloWorld = "Hello World";
// 
// 	printf("%s\n", helloWorld); //%s�� ���ڿ� �迭�� �����. null����(/0)�� ���� ������ �迭�� �������� ����ϴ� ��. string�� ���ڿ� �迭�� �ƴ϶� ��ü�̹Ƿ� ����� �� �ȴ�.
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

