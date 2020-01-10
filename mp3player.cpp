#include <iostream>
#include <string>
#include <bass.h>

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
	float cpuusage(BASS_GetCPU());
	std::cout << "current cpu % used by bass is ";
	std::cout << cpuusage;
	std::cout << '\n';
	return;
}

int main()
{
	BASS_Free();
	DWORD32 bassversion(BASS_GetVersion());
	std::cout << "running bass version ";
	std::cout << bassversion;
	std::cout << '\n';
	BASS_Init(-1, 48000, 0, 0, NULL);
	stats();










	BASS_Free();
	return 0;
}