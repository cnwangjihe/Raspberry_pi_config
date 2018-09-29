#include "stdafx.h"
#include "basic.h"

inline string DecodeBase64(string input)
{
	string output;
	StringSource(input,true,new Base64Decoder(new StringSink(output)));
	return output;
}

inline string EncodeBase64(string input)
{
	string output;
	StringSource(input,true,new Base64Encoder(new StringSink(output),false));
	return output;
}

inline string DecodeHex(string input)
{
	string output;
	StringSource(input,true,new HexDecoder(new StringSink(output)));
	return output;
}

inline string EncodeHex(string input)
{
	string output;
	StringSource(input,true,new HexEncoder(new StringSink(output)));
	return output;
}

inline string Hex2Base64(string input)
{
	return EncodeBase64(DecodeHex(input));
}

inline string Base642Hex(string input)
{
	return EncodeHex(DecodeBase64(input));
}

inline string ChangeBase64Alphabet(string input,string now,string old=Base64DefaultAlphabet)
{
	map<char,char> dictionary;
	bool flag=0;
	if (now.size()!=64)
	{
		LogError("The new length of Base64 Alphabet is not right");
		return input;
	}
	if (old.size()!=64)
	{
		LogError("The old length of Base64 Alphabet is not right");
		return input;
	}

	for (int i=0;i<64;i++)
	{
		if (dictionary.count(now[i]))
			flag=1;
		else
			dictionary[now[i]]=1;
	}
	if (flag)
		LogWarning("The new Base64 Alphabet may be wrong, some letters are duplicate");
	flag=0;
	dictionary.clear();
	for (int i=0;i<64;i++)
	{
		if (dictionary.count(old[i]))
			flag=1;
		else
			dictionary[old[i]]=now[i];
	}
	if (flag)
	{
		LogError("The old Base64 Alphabet is wrong, some letters are duplicate");
		return input;
	}

	flag=0;
	for (unsigned long long i=0;i<input.size();i++)
	{
		if (dictionary.count(input[i]))
			input[i]=dictionary[input[i]];
		else
			if (input[i]!='=')
				flag=1;
	}
	if (flag)
		LogWarning("The old Base64 Alphabet may be wrong, some letters are not included");
	return input;
}

string EraseBase64Enter(const string& input)
{
	unsigned long long p;
	string output=input;
	while ((p=output.find('\n'))!=string::npos)
		output.erase(p,1);
	while ((p=output.find('\r'))!=string::npos)
		output.erase(p,1);
	return output;
}

string EraseBase64Equalsign(string input)
{
	unsigned long long p=input.size();
	while (input[--p]=='=')
		input.erase(p,1);
	return input;
}