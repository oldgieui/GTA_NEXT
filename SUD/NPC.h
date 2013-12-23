#pragma once
#include "character.h"
class CNPC :
	public CCharacter
{
public:
// 	enum JOB
// 	{
// 		POLICE,
// 		PROFESSOR,
// 		TEACHER,
// 		STUDENT,
// 		CODE,
// 		GAMECONSOLE,
// 		PINGPONG_RACKET
// 	};

	enum NAME
	{

	};

	CNPC(void);
	~CNPC(void);
	
	void SetJOB(std::string job){m_job = job;}
	std::string GetJOB(){return m_job;}

	void Respond(std::string question);

	void PrintType();
private:
	std::string m_job;
};

