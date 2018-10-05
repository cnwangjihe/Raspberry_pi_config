#define LOGWARNING
#define LOGINFO
#define LOGDEBUG

#include "stdafx.h"
#include "hash.h"
#include "encrypt.h"
#include "basic.h"
#include "select.h"


int level,n,type,len;
string s,k,opt;

int main(int argc,char* argv[])
{
	if (argc==1)
		cin >> s >> k >> level >> len >> type;
	else
	{
		if (argc!=6)
		{
			LogError("The number of parameters is wrong");
			return 0;
		}
		else
		{
			s=argv[1];
			k=argv[2];
			level=atoi(argv[3]);
			len=atoi(argv[4]);
			type=atoi(argv[5]);
			LogDebug(s);
			LogDebug(k);
			LogDebug(to_string(level));
			LogDebug(to_string(len));
			LogDebug(to_string(type));
		}
	}

	opt=GetOperationSequence(s+k,level);
	n=opt.size();
	for (int i=0;i<n;i++)
		s=SelectAlgorithm(s,k,opt[i]);
	s=CorrectLength(s,len);
	if (type)
		s=ChangeBase64Alphabet(EraseBase64Equalsign(Hex2Base64(s)),Base64BetterAlphabet);
	cout << s << endl;
}

// g++ -std=c++11 main.cpp -o main -Wall -Wextra -Wparentheses -O2 -DNDEBUG -I/usr/include/cryptopp -lcryptopp -lpthread

/*

0:6:2OYOmA
1:11:a4fZi?BPtjw
2:22:ag6cpuplkZrn?Xa9YX6Kpw
3:27:kGnxV1nBvgOsWY8TmpFCr47l58g
4:32:WSaPf2ZfPnbUjaTE?uiBnT2Hymtf?MqE
5:38:U7JMaLRY5!VkM5KYhSJNHOHanKXo7u468gEQLA
6:43:BLH7P38?l3MDO2G6LUtNyAnM8WKQ27GFlQihlF9B2e0
7:54:B6evwJHKzO4PCC1HP96nASIg7Ft73u6iX2lcIYdRJz!VrQsGs8ET8g
8:64:bAWZBO4PW9U5uW8ZBNL8oWE5iqmOfgm44Vi95jmXyUqxDNPJwjkuvHLL1FxkSLRs
9:86:RyQ8LuxxoVEZCNNNik0W8JVrKWr4B9ciqQqGwoEaClLVXFvJ?T9FJHaAfif6fiqVxQrcqRUxGdPx!xXzEbq9xg

*/