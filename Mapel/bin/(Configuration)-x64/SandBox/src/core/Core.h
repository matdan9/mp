#pragma once

#ifdef MP_PLATFORM_WINDOWS
	#ifdef MP_BUILD_DLL
		#define MAPEL_API _declspec(dllexport)
	#else
		#define MAPLE_API _declspec(dllimport)
	#endif // HZ_BUILD_DLL
#else
		#error ONLY SUPPORT WINDOWS
#endif // HZ_PLATFORM_WINDOWS