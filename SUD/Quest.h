#pragma once
#include "Character.h"
class CQuest
{
public:
	CQuest(void);
	~CQuest(void);
	CCharacter GetClient(){return m_Client;}
	void SetClient(CCharacter client){m_Client = client;}

	void SetTitle(std::string title){m_title = title;}
	std::string GetTitle(){return m_title;}

	void SetContent(std::string content){m_content = content;}
	std::string GetContent(){return m_content;}

	void SetStart(){isStart = true;}
	bool GetIsStart(){return isStart;}

	void SetClear(){isClear = true;}
	bool GetIsClear(){return isClear;}

	void SetClearCondition(bool condition = false);


private:
	CCharacter m_Client;
	bool isClear;
	bool isStart;
	std::string m_title;
	std::string m_content;
};

