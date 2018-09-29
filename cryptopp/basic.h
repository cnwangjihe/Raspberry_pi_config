
#pragma once

#include "stdafx.h"

inline time_t SystemTime()
{
	return time(0);
}

inline void LogError(string message)
{
	cerr << SystemTime() << " : " << "error   : " << message << '\n';
	return ;
}

inline void LogWarning(string message)
{
	#ifndef LOGWARNING
		return ;
	#endif
	cerr << SystemTime() << " : " << "warning : " << message << '\n';
	return ;
}

inline void LogInfo(string message)
{
	#ifndef LOGINFO 
		return ;
	#endif
	cerr << SystemTime() << " : " << "info    : " << message << '\n';
	return ;
}

inline void LogDebug(string message)
{
	#ifndef LOGDEBUG 
		return ;
	#endif
	cerr << SystemTime() << " : " << "debug   : " << message << '\n';
	return ;
}
