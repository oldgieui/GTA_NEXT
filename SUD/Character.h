#pragma once
#include <string>


struct Position
{
	int x;
	int y;
};

enum DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

enum ATTACK_RESULT
{
	HIT,
	GUARD,
	AVOID,
};

enum EQUIPMENT
{
	WEAPON,
	ARMOR,
	ACCESSORY
};

struct Status
{
	Position position;
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

	void SetPosition(Position pos){m_Status.position = pos;}
	void SetPosition(int x, int y);
	Position GetPosition(){return m_Status.position;}
	void PrintPosition();
	void PositionMove(DIRECTION dir);
	
	void SetName(std::string name){m_Status.name = name;}
	std::string GetName(){return m_Status.name;}
	
	void SetID(int ID){m_Status.ID = ID;}
	int GetID(){return m_Status.ID;}
	
	void SetHP(int HP){m_Status.HP = HP;}
	int GetHP(){return m_Status.HP;}
	
	void SetATK(int atk){m_Status.ATK = atk;}
	int GetATK(){return m_Status.ATK;}

	bool IsAlive(){return m_Status.HP > 0;}
	
	ATTACK_RESULT IsHit();
	void DamageCheck(ATTACK_RESULT result, int damage);

protected:
	Status m_Status;
};

