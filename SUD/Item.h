#pragma once

enum ITEM_TYPE
{
	WEAPON,
	ARMOR,
	ACCESSORY,

	EQUIP_MAX
};
class CItem
{
public:
	CItem(void);
	~CItem(void);
	void SetItemName(std::string name){m_ItemName = name;}
	void SetATKBonus(int num){m_ATKbonus = num;}
	void SetHPBonus(int num){m_HPbonus = num;}
	void SetItemType(ITEM_TYPE type){m_ItemType = type;}
	std::string GetItemName(){return m_ItemName;}
	int GetATKBonus(){return m_ATKbonus;}
	int GetHPBonus(){return m_HPbonus;}
	ITEM_TYPE GetItemType(){return m_ItemType;}

private:
	std::string m_ItemName;
	int m_ATKbonus;
	int m_HPbonus;
	ITEM_TYPE m_ItemType;
};

