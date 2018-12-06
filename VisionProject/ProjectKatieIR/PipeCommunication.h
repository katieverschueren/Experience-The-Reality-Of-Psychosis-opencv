#pragma once
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include "LedPair.h"


class PipeCommunication
{
public:
	PipeCommunication();
	void sendViaPipe(LedPair leds);
	void closeConnection();

private:
	HANDLE hPipe;
	char buffer[1024];
	DWORD dwRead;
	DWORD dwWritten;
};
