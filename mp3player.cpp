#include <iostream>
#include <string>
#include <bass.h>
#include <bassflac.h>

void cpuusage()
{
	float cpuusage(BASS_GetCPU());
	std::cout << "current cpu % used by bass is ";
	std::cout << cpuusage;
	std::cout << '\n';
	return;
}

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

int main()
{
	stats();
	BASS_Free();
	DWORD32 bassversion(BASS_GetVersion());
	std::cout << "running bass version ";
	std::cout << bassversion;
	std::cout << '\n';
	if (!BASS_Init(-1, 48000, 0, 0, 0))
		return 0;
	std::cout << "loading file \n";
	HSTREAM stream = BASS_FLAC_StreamCreateFile(FALSE, "test.FLAC", 0, 0, 0);
	BASS_ChannelPlay(stream, true);
	for (;;) 
	{
		cpuusage();
	}

	









	BASS_Free();
	return 0;
}