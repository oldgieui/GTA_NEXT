#include "stdafx.h"
#include "Character.h"
#include "WorldMap.h"
#include <stdlib.h>



CCharacter::CCharacter(void)
{
	srand((unsigned)time(NULL));
	printf_s("Character created\n");
}

void CCharacter::SetPosition(int x, int y){
	m_Status.position.x = x;
	m_Status.position.y = y;
}

void CCharacter::PositionMove(DIRECTION dir)
{
	switch (dir)
	{
	case DIR_UP:
		m_Status.position.y = __max(m_Status.position.y -1, 0);
		break;
	case DIR_DOWN:
		m_Status.position.y = __min(m_Status.position.y +1, MAP_SIZE -1);
		break;
	case DIR_LEFT:
		m_Status.position.x = __max(m_Status.position.x -1, 0);
		break;
	case  DIR_RIGHT:
		m_Status.position.x = __min(m_Status.position.x +1, MAP_SIZE -1);
		break;
	}
}

CCharacter::~CCharacter(void)
{
	printf_s("Character deleted\n");
}

void CCharacter::PrintPosition()
{
	printf_s("현재 위치 : [%d, %d]\n", m_Status.position.x, m_Status.position.y);
}

ATTACK_RESULT CCharacter::IsHit()
{
	switch (rand()%3)
	{
	case 0:
		return HIT;
	case 1:
		return GUARD;
	case 2:
		return AVOID;
	default:
		return NONE;
	}
}

void CCharacter::DamageCheck( ATTACK_RESULT result, int damage )
{
	switch (result)
	{
	case HIT:
		m_Status.HP -= damage;
		printf("맞음 공격. 만큼의 피해 %d!\n", damage);
		break;
	case GUARD:
		m_Status.HP -= (int)(damage*0.5);
		printf("막음 공격. 만큼의 그침 피해. %0.f \n", (damage * 0.5));
		break;
	case AVOID:
		printf("피함!\n");
		break;
	default:
		break;
	}
} 

// void CCharacter::PrintType()
// {
// 	printf_s("My Type is CCharacter\n");
// }
