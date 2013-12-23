#pragma once
#include "character.h"
#include <vector>

class CPlayer :
	public CCharacter
{
public:
	CPlayer(void);
	~CPlayer(void);
	void PrintType();
};

