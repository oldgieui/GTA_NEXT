#include "stdafx.h"
#include "Character.h"
#include "WorldMap.h"
#include <stdlib.h>



CCharacter::CCharacter(void)
{
	srand((unsigned)time(NULL));
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
}

void CCharacter::PrintPosition()
{
	printf_s("���� ��ġ : [%d, %d]\n", m_Status.position.x, m_Status.position.y);
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
	}
}

void CCharacter::DamageCheck( ATTACK_RESULT result, int damage )
{
	switch (result)
	{
	case HIT:
		m_Status.HP -= damage;
		printf("���� ����. ��ŭ�� ���� %d!\n", damage);
		break;
	case GUARD:
		m_Status.HP -= (int)(damage*0.5);
		printf("���� ����. ��ŭ�� ��ħ ����. %0.f \n", (damage * 0.5));
		break;
	case AVOID:
		printf("����!\n");
		break;
	default:
		break;
	}
} 
