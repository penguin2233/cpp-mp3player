#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <bass.h>
#include <bassflac.h>

void clearscreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void stats()
{
	BASS_INFO info;
	BASS_GetInfo(&info);
	std::cout << "current sample rate is ";
	std::cout << info.freq;
	std::cout << '\n';
	return;
}

void playflac()
{

	std::cout << "enter filename then press enter key \n";
	std::string filename;
	std::cin >> filename;
	std::cin.ignore();
	HSTREAM stream = BASS_FLAC_StreamCreateFile(FALSE, filename.c_str(), 0, 0, BASS_STREAM_PRESCAN);
	QWORD totaltimebyte = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
	int totaltime = BASS_ChannelBytes2Seconds(stream, totaltimebyte);
	BASS_ChannelPlay(stream, true);
	clearscreen();
	std::cout << "playing flac \n";
	std::cout << "0 / " << totaltime << '\n';

	while (BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		clearscreen();
		std::cout << "playing flac \n";
		QWORD currenttimebyte = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
		int currenttime = BASS_ChannelBytes2Seconds(stream, currenttimebyte);
		std::cout << currenttime << " / " << totaltime << '\n';
	}
	std::cout << "playback has finished use enter to exit";
	getchar();
}

void playmp3()
{

	std::cout << "enter filename then press enter key \n";
	std::string filename;
	std::cin >> filename;
	std::cin.ignore();
	HSTREAM stream = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, 0, BASS_STREAM_PRESCAN);
	QWORD totaltimebyte = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
	int totaltime = BASS_ChannelBytes2Seconds(stream, totaltimebyte);
	BASS_ChannelPlay(stream, true);
	clearscreen();
	std::cout << "playing mp3 \n";
	std::cout << "0 / " << totaltime << '\n';
	
	while( BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING )
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		clearscreen();
		std::cout << "playing mp3 \n";
		QWORD currenttimebyte = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
		int currenttime = BASS_ChannelBytes2Seconds(stream, currenttimebyte);
		std::cout << '\r' << currenttime << " / " << totaltime << '\n';
	}
	std::cout << "playback has finished use enter to exit";
	getchar();
}

int main()
{
	BASS_Free();
	BASS_Init(-1, 48000, 0, 0, 0);
	DWORD32 bassversion(BASS_GetVersion());
	std::cout << "running bass version ";
	std::cout << bassversion;
	std::cout << '\n';
	// shoutout to sami and shawnmb and peskypotato
	int sami;
	std::cout << "make your selection then press enter \n";
	std::cout << "1 for mp3, 2 for flac, 3 for information, anything else for exit \n";
	std::cin >> sami;
	std::cin.ignore();
	std::cout << '\n';
	switch (sami)
	{
		case 1:
			std::cout << '\n';
			playmp3();
			break;
		case 2:
			std::cout << '\n';
			playflac();
			break;
		case 3:
			stats();
			break;
		default:
			BASS_Free();
			return 0;
	}
	BASS_Free();
	return 0;
}