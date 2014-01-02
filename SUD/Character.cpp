#include "stdafx.h"
#include "Character.h"
#include "WorldMap.h"
#include <stdlib.h>



CCharacter::CCharacter(void)
{
	srand((unsigned)time(NULL));
	//printf_s("Character created\n");
	for (int i = 0; i<EQUIP_MAX; ++i)
	{
		m_Equipment[i] = nullptr;
	}
}



CCharacter::~CCharacter(void)
{
	//printf_s("Character deleted\n");
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
		printf("공격이 명중, %d만큼의 피해!\n", damage);
		break;
	case GUARD:
		m_Status.HP -= (int)(damage*0.5);
		printf("방어 발동,  %0.f만큼의 피해에 그침. \n", (damage * 0.5));
		break;
	case AVOID:
		printf("회피함!\n");
		break;
	default:
		break;
	}
} 

CItem* CCharacter::GetEquippedItem( ITEM_TYPE type )
{
	switch (type)
	{
	case WEAPON:
		return m_Equipment[WEAPON];
		break;
	case ARMOR:
		return m_Equipment[ARMOR];
		break;
	case ACCESSORY:
		return m_Equipment[ACCESSORY];
		break;
	case EQUIP_MAX:
		break;
	default:
		break;
	}
}

void CCharacter::EquipNewItem( CItem* newItem )
{
	switch (newItem->GetItemType())
	{
	case WEAPON:
		m_Equipment[WEAPON] = newItem;
		break;
	case ARMOR:
		m_Equipment[ARMOR] = newItem;
		break;
	case ACCESSORY:
		m_Equipment[ACCESSORY] = newItem;
		break;
	default:
		break;
	}
}
