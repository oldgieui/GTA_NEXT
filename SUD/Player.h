#pragma once
#include "character.h"
#include <vector>

class CMapChip;


class CPlayer :
	public CCharacter
{
public:
	CPlayer(void);
	~CPlayer(void);
	void PrintType();
	void SetName();
	void SetStartPosition();

private:
	CMapChip*	m_StartPosition;
};

