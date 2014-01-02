#include "stdafx.h"
#include "Mob.h"
#include "Character.h"


CMob::CMob(void)
{
	//printf_s("Mob Created\n");
}


CMob::~CMob(void)
{
	//printf_s("Mob deleted\n");
}

void CMob::PrintType()
{
	printf_s("My Type is CMob\n");
}
