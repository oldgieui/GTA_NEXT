#pragma once
#include <string>
#include "Item.h"


enum ATTACK_RESULT
{
	NONE,
	HIT,
	GUARD,
	AVOID,
};



struct Status
{
	
	std::string name;
	int ID;
	int HP;
	int ATK;
	double damageReduction;
};

class CCharacter
{
public:
	

	CCharacter(void);
	virtual ~CCharacter(void);
	
	void SetName(std::string name){m_Status.name = name;}
	std::string GetName(){return m_Status.name;}
	
	void SetID(int ID){m_Status.ID = ID;}
	int GetID(){return m_Status.ID;}
	
	void SetHP(int HP){m_Status.HP = HP;}
	int GetHP(){return m_Status.HP;}
	
	void SetATK(int atk){m_Status.ATK = atk;}
	int GetATK(){return m_Status.ATK;}

	CItem* GetEquippedItem(ITEM_TYPE type);
	void EquipNewItem(CItem* newItem);

	bool IsAlive(){return m_Status.HP > 0;}
	
	ATTACK_RESULT IsHit();
	void DamageCheck(ATTACK_RESULT result, int damage);


protected:
	Status m_Status;
	CItem* m_Equipment[EQUIP_MAX] ;
};

