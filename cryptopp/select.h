#pragma once

#include "hash.h"
#include "encrypt.h"

#define ALG1 GETSHA512      //128
#define ALG2 GETSHA256      //64
#define ALG3 GETSHA384      //96
#define ALG4 GETSHA224      //56
#define ALG5 GETBLAKE2s     //64
#define ALG6 GETBLAKE2b     //128
#define ALG7 GETMD5         //32
#define ALG8 GETSM3         //64
#define ALG9 GETTiger       //48
#define ALG0 GETRIPEMD320   //80
#define ALGA GETRIPEMD160   //40
#define ALGB GETRIPEMD128   //32
#define ALGC GETRIPEMD256   //64
#define ALGD GETWhirlpool   //128
#define ALGE GETCRC32       //8
#define ALGF GETKeccak_256  //64
#define ALGG GETKeccak_512  //128
#define ALGH GETSHA3_256    //64
#define ALGI GETSHA3_512    //128

string GetOperationSequence(string s,int level)
{
	switch (level)
	{
		case 0 :
			return GETCRC32(GETSHA256(s));                 //8
		case 1 :
			return GETMD5(GETKeccak_512(s)).erase(16,16);  //16
		case 2 :
			return GETRIPEMD128(GETBLAKE2b(s));            //32
		case 3 :
			return GETRIPEMD160(GETSHA3_256(s));           //40
		case 4 :
			return GETTiger(GETSM3(s));                    //48
		case 5 :
			return GETSHA224(GETKeccak_256(s));            //56
		case 6 :
			return GETBLAKE2s(GETSHA3_512(s));             //64
		case 7 :
			return GETRIPEMD320(GETWhirlpool(s));          //80
		case 8 :
			return GETSHA384(GETRIPEMD256(s));             //96
		case 9 :
			return GETSHA3_512(GETSHA512(s));              //128
	}
	return "";
}

string SelectAlgorithm(char t,string input,string& key)
{
	switch (t)
	{
		case '0' :
			key=GETSM3(key);
			return GETTiger(Kalyna256_CBC_Encrypt(input,key));
		case '1' :
			key=GETRIPEMD128(key);
			return GETBLAKE2b(AES_CBC_Encrypt(input,key));
		case '2' :
			key=GETMD5(key);
			return GETRIPEMD320(AES_CBC_Encrypt(input,key));
		case '3' :
			key=GETRIPEMD128(GETWhirlpool(key));
			return GETSHA512(Kalyna128_CBC_Encrypt(input,key));
		case '4' :
			key=GETMD5(GETBLAKE2s(key));
			return GETRIPEMD256(Kalyna128_CBC_Encrypt(input,key));
		case '5' :
			key=GETBLAKE2s(key);
			return GETSHA224(Kalyna256_CBC_Encrypt(input,key));
		case '6' :
			key=GETRIPEMD256(key);
			return GETSHA256(Kalyna256_CBC_Encrypt(input,key));
		case '7' :
			key=GETMD5(GETRIPEMD160(key));
			return GETSHA384(Kalyna128_CBC_Encrypt(input,key));
		case '8' :
			key=GETRIPEMD128(GETSHA256(key));
			return GETRIPEMD160(AES_CBC_Encrypt(input,key));
		case '9' :
			key=GETSHA256(key);
			return GETWhirlpool(Kalyna256_CBC_Encrypt(input,key));
		case 'A' :
			key=GETBLAKE2s(GETRIPEMD256(key));
			return GETRIPEMD160(GETSHA512(Kalyna256_CBC_Encrypt(input,key)));
		case 'B' :
			key=GETRIPEMD256(GETBLAKE2b(key));
			return GETSHA384(GETBLAKE2s(Kalyna256_CBC_Encrypt(input,key)));
		case 'C' :
			key=GETMD5(GETTiger(key));
			return GETRIPEMD320(AES_CBC_Encrypt(input,key));
		case 'D' :
			key=GETRIPEMD128(GETSM3(GETTiger(key)));
			return GETBLAKE2s(Kalyna128_CBC_Encrypt(input,key));
		case 'E' :
			key=GETKeccak_256(GETRIPEMD320(key));
			return GETRIPEMD256(Kalyna256_CBC_Encrypt(input,key));
		case 'F' :
			key=GETSHA3_256(GETSHA3_512(key));
			return GETKeccak_512(Kalyna256_CBC_Encrypt(input,key));
	}
	return "";
}