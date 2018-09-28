#include "stdafx.h"

inline string DecodeBase64(string input)
{
	string output;
	StringSource(input,true,new Base64Decoder(new StringSink(output)));
	return output;
}

inline string EncodeBase64(string input)
{
	string output;
	StringSource(input,true,new Base64Encoder(new StringSink(output)));
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