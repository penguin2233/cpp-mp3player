#include <iostream>
#include <fstream>
#include <string>
#include <bass.h>
#include <bassflac.h>

void stats()
{
	BASS_INFO info;
	BASS_GetInfo(&info);
	std::cout << "current sample rate is ";
	std::cout << info.freq;
	std::cout << '\n';
	float volume(BASS_GetVolume());
	std::cout << "current volume is ";
	std::cout << volume;
	std::cout << '\n';
	return;
}

void cpuusage()
{
	float cpuusage(BASS_GetCPU());
	std::cout << "current cpu % used by bass is ";
	std::cout << cpuusage;
	std::cout << '\n';
	return;
}

void playflac()
{
	std::cout << "loading file \n";
	HSTREAM stream = BASS_FLAC_StreamCreateFile(FALSE, "test.FLAC", 0, 0, 0);
	BASS_ChannelPlay(stream, true);
	for (;;)
	{
		cpuusage();
	}
}

void playmp3()
{
	std::cout << "loading file \n";
	HSTREAM stream = BASS_StreamCreateFile(FALSE, "test.mp3", 0, 0, 0);
	BASS_ChannelPlay(stream, true);
	for (;;)
	{
		cpuusage();
	}
}

int main()
{
	BASS_Free();
	BASS_Init(-1, 48000, 0, 0, 0);
	DWORD32 bassversion(BASS_GetVersion());
	std::cout << "running bass version ";
	std::cout << bassversion;
	std::cout << '\n';
	int sami;
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
			std::cout << 'n';
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