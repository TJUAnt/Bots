#ifndef __DAILOG_H__
#define __DAILOG_H__
#include <stdio.h>

struct ParameterList {
	char ourMainInputBuffer[80000];
	char loginID[500];
	char computerID[500];
};

class ChatBot
{

public:
	unsigned int InitBot(int argcx, char * argvx[]);  // this work mostly only happens on first startup, not on a restart
	void CloseBot();
	int ReadLine(char* buffer, FILE* in, unsigned int limit = 0);
	int Chat(char* user, char* incoming, char* output); // returns volleycount or 0 if command done or -1 PENDING_RESTART
	void ProcessInput();

	ParameterList* GetParameters();
	void SetParameters(char* user,char* loginID, char* computerID, char* ourMainInputBuffer);

	char* ProcessOutput(char* bufferfrom); // ��������ı�

	void ResetInput(); // ��������

	char* HandleOOB(char* buffer);

	void NewDialog(); // ��ʼ�µĶԻ�

	void Reboot(); // ����
	
};

#endif // !__DAILOG_H__