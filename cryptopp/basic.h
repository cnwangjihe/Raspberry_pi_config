
#pragma once

#include "stdafx.h"

inline time_t SystemTime()
{
	return time(0);
}

string StringEraseEnter(const string& input)
{
	unsigned long long p;
	string output=input;
	while ((p=output.find('\n'))!=string::npos)
		output.erase(p,1);
	while ((p=output.find('\r'))!=string::npos)
		output.erase(p,1);
	return output;
}

inline void LogError(string message)
{
	cerr << SystemTime() << " : " << "error : " << message << '\n';
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
	cerr << SystemTime() << " : " << "info : " << message << '\n';
	return ;
}

inline void LogDebug(string message)
{
	#ifndef LOGDEBUG 
		return ;
	#endif
	cerr << SystemTime() << " : " << "debug : " << message << '\n';
	return ;
}
