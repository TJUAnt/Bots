#ifndef __DAILOG_H__
#define __DAILOG_H__
#include <stdio.h>

class ChatBot
{

public:
	unsigned int InitBot(char* filePath);  // this work mostly only happens on first startup, not on a restart
	
	void CloseBot();

	int ReadLine(char* buffer, FILE* in, unsigned int limit = 0);

	int Chat(char* user, char* incoming, char* output); // returns volleycount or 0 if command done or -1 PENDING_RESTART
	
	void ProcessInput();

	void SetParameters(char* user,char* loginID, char* computerID, char* ourMainInputBuffer);

	char* ProcessOutput(char* bufferfrom); // ��������ı�

	char* HandleOOB(char* buffer);

	void NewDialog(); // ��ʼ�µĶԻ�
};

#endif // !__DAILOG_H__