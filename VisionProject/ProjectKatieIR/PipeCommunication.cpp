#include "PipeCommunication.h"
#include "LedPair.h"
#include <string> 

PipeCommunication::PipeCommunication()
{
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\KatiePipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	std::cout << "###---- Waiting for Unity to connect-----####" << std::endl;
	std::cout << "###---- Dont forget to change webcam focus!!!!!!-----####" << std::endl;
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // wait for someone to connect to the pipe
		{

			std::cout << "###---- Unity connected -----####" << std::endl;

			break;
		}
	}
}


void PipeCommunication::sendViaPipe(LedPair leds)
{
		std::string message = "{ \"Leds\": [";
		message += "{\"X\": " + std::to_string(leds.LED1.x) + ",";
		message += "\"Y\": " + std::to_string(leds.LED1.y) + "},";
		message += "{\"X\": " + std::to_string(leds.LED2.x) + ",";
		message += "\"Y\": " + std::to_string(leds.LED2.y) + "},";
		message += "{\"X\": " + std::to_string(leds.LED3.x) + ",";
		message += "\"Y\": " + std::to_string(leds.LED3.y) + "}]}\n";


		//message = "Hello\n";

		WriteFile(hPipe,
			message.c_str(),
			message.size(),   // = length of string + terminating '\0' !!!
			&dwWritten,
			NULL);

}

void PipeCommunication::closeConnection()
{
	DisconnectNamedPipe(hPipe);
}
