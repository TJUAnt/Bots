#include "common.h" 
#include "evserver.h"

#include "Dialog.h"

unsigned int ChatBot::InitBot(char* filePath)
{
	/*
	int argcx = 8;
	char * argvx[] = { "ChatScript_Main", "root=./data", "users=USERS", "logs=LOGS", "topic=TOPIC", "login=user", "buildfiles=filesTest.txt", "local" };
	
	for (int i = 1; i < argc; ++i)
	{
		if (!strnicmp(argv[i],"root=",5)) 
		{
			chdir((char*)argv[i]+5);
		}
	}
	*/

	int argcx = 0;
	char * argvx[] = {};
	char unchangedPath[100];
	char readablePath[100];
	char writeablePath[100];

	strcpy(unchangedPath, filePath);
	strcpy(readablePath, filePath);
	strcpy(writeablePath, filePath);

	InitSystem(argcx, argvx, unchangedPath, readablePath, writeablePath);
}

void ChatBot::CloseBot()
{
	CloseSystem();
}

int ChatBot::Chat(char* _user, char* incoming, char* output)
{
	int turn = 0;
	strcpy(ourMainInputBuffer + 1, incoming);
	turn = PerformChat(_user, computerID, ourMainInputBuffer, NULL, ourMainOutputBuffer);

	strcpy(output, ourMainOutputBuffer);

	if (turn == PENDING_RESTART)
	{
		ourMainInputBuffer[0] = ourMainInputBuffer[1] = 0;
		Restart();
	}

	*ourMainInputBuffer = 0;
	ourMainInputBuffer[1] = 0;

	return turn;
}

void ChatBot::ProcessInput()
{
	ProcessInputFile();
}

int ChatBot::ReadLine(char* buffer, FILE* in, unsigned int limit)
{
	if (limit == 0)
		ReadALine(buffer, in);
	else
		ReadALine(buffer, in, limit);
}

void ChatBot::SetParameters(char* _user, char* _loginID, char* _computerID, char* _ourMainInputBuffer)
{
	char user[MAX_WORD_SIZE];
	strcpy(user, _user); // array
	strcpy(loginID, _loginID);
	strcpy(computerID, _computerID);
	strcpy(ourMainInputBuffer, _ourMainInputBuffer);
}

char* ChatBot::ProcessOutput(char* bufferfrom)
{
	if ((!silent) && (bufferfrom != NULL) && (bufferfrom[0] == '\0'))
		return UTF2ExtendedAscii(bufferfrom);
	else
		return (char*)"";
}


char* ChatBot::HandleOOB(char* buffer)
{
	if ((!silent) && (buffer != NULL) && (buffer[0] == '\0'))
	{
		ProcessOOB(buffer);
	}
	callBackDelay = 0; // now turned off after an output
	return buffer;
}

void ChatBot::NewDialog() // ��ʼ�µĶԻ�
{
	*ourMainInputBuffer = ' '; // leave space at start to confirm NOT a null init message, even if user does only a cr
	ourMainInputBuffer[1] = 0;

	if (loopBackDelay)
		loopBackTime = ElapsedMilliseconds() + loopBackDelay; // resets every output
}
