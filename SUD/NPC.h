#pragma once
#include "character.h"
#include <vector>

enum JOB
{
	PROFESSOR,
	STUDENT
};
class CNPC :
	public CCharacter
{
public:

	CNPC(void);
	~CNPC(void);
	
	
	void Speak(int n);
	void Speak();
	void AddSpeach(std::string speach);
	void PrintType();
	void SpeachInit();
	void SetJob(JOB job){m_Job = job;}
	JOB GetJob(){return m_Job;}

private:
	std::vector<std::string> m_Conversation;
	JOB m_Job;
};

