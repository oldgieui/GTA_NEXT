#include "stdafx.h"
#include "NPC.h"


CNPC::CNPC(void)
{
	printf_s("NPC created\n");
}


CNPC::~CNPC(void)
{
	printf_s("NPC deleted\n");
}

void CNPC::Respond( std::string question )
{
	if (question == "Á÷¾÷")
	{
		
	}
}

void CNPC::PrintType()
{
	printf_s("My Type is CNPC\n");
}

