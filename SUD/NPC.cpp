#include "stdafx.h"
#include "NPC.h"


CNPC::CNPC(void)
{
	
//	printf_s("NPC created\n");
	
}


CNPC::~CNPC(void)
{
//	printf_s("NPC deleted\n");
}


void CNPC::PrintType()
{
//	printf_s("My Type is CNPC\n");
}

void CNPC::AddSpeach( std::string speach )
{
	m_Conversation.push_back(speach);
}

void CNPC::SpeachInit()
{
	char buf[90];
	sprintf_s(buf, "안녕하신가! 힘세고 강한 아침, 만일 내게 물어보면 나는 %s", GetName());
	std::string dialog = buf;
	AddSpeach(dialog);
	AddSpeach("좋다 아침!");
	AddSpeach("All Your Grade Are belong to us");
}

void CNPC::Speak()
{
	std::cout << GetName() << " : " <<  m_Conversation[rand() % m_Conversation.size()] << std::endl;
}

