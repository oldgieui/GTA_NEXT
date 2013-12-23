#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer(void)
{
	printf_s("Player Created\n");
}


CPlayer::~CPlayer(void)
{
	printf_s("Player deleted\n");
}

void CPlayer::PrintType()
{
	printf_s("My Type is CPlayer\n");
}
