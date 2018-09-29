#pragma once
#include "stdafx.h"
#include "encode.h"
#include "basic.h"

string AES_CBC_Encrypt(string input,string k)
{
	int length=k.size();
	if (length!=16 && length!=24 && length!=32)
	{
		LogError("The length of the AES key is NOT RIGHT");
		return input;
	}
	byte key[length];
	for (int i=0;i<length;i++)
		key[i]=k[i];
	string output;
	HexEncoder* hex_enc = new HexEncoder(new StringSink(output));
	CBC_Mode<AES>::Encryption aes(key, sizeof(key), AES_CBC_iv);
	StreamTransformationFilter* aes_enc = new StreamTransformationFilter(aes, hex_enc);
	StringSource source(input, true, aes_enc);
	return output;
}

string AES_CBC_Decrypt(string input,string k)
{
	int length=k.size();
	if (length!=16 && length!=24 && length!=32)
	{
		LogError("The length of the AES key is NOT RIGHT");
		return input;
	}
	byte key[length];
	for (int i=0;i<length;i++)
		key[i]=k[i];
	string output;
	input=DecodeHex(input);

	CryptoPP::AES::Decryption aesDecryption(key, length);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, AES_CBC_iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( output ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( input.c_str() ), input.size() );
	stfDecryptor.MessageEnd();
	return output;
}

string Kalyna128_CBC_Encrypt(string input,string k)
{
	int length=k.size();
	if (length!=16 && length!=32)
	{
		LogError("The length of the Kalyna128 key is NOT RIGHT");
		return input;
	}
	byte key[length];
	for (int i=0;i<length;i++)
		key[i]=k[i];
	string output;
	HexEncoder* hex_enc = new HexEncoder(new StringSink(output));
	CBC_Mode<Kalyna128>::Encryption kalyna128;
	kalyna128.SetKeyWithIV(key, length, Kalyna128_CBC_iv, 16);
	StreamTransformationFilter* kalyna128_enc = new StreamTransformationFilter(kalyna128, hex_enc);
	StringSource source(input, true, kalyna128_enc);
	return output;
}

string Kalyna128_CBC_Decrypt(string input,string k)
{
	int length=k.size();
	if (length!=16 && length!=32)
	{
		LogError("The length of the Kalyna128 key is NOT RIGHT");
		return input;
	}
	byte key[length];
	for (int i=0;i<length;i++)
		key[i]=k[i];
	string output;
	input=DecodeHex(input);

	CryptoPP::Kalyna128::Decryption kalyna128Decryption(key, length);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( kalyna128Decryption, Kalyna128_CBC_iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( output ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( input.c_str() ), input.size() );
	stfDecryptor.MessageEnd();
	return output;
}

string Kalyna256_CBC_Encrypt(string input,string k)
{
	int length=k.size();
	if (length!=32 && length!=64)
	{
		LogError("The length of the Kalyna256 key is NOT RIGHT");
		return input;
	}
	byte key[length];
	for (int i=0;i<length;i++)
		key[i]=k[i];
	string output;
	HexEncoder* hex_enc = new HexEncoder(new StringSink(output));
	CBC_Mode<Kalyna256>::Encryption kalyna256;
	kalyna256.SetKeyWithIV(key, length, Kalyna256_CBC_iv, 32);
	StreamTransformationFilter* kalyna256_enc = new StreamTransformationFilter(kalyna256, hex_enc);
	StringSource source(input, true, kalyna256_enc);
	return output;
}

string Kalyna256_CBC_Decrypt(string input,string k)
{
	int length=k.size();
	if (length!=32 && length!=64)
	{
		LogError("The length of the Kalyna256 key is NOT RIGHT");
		return input;
	}
	byte key[length];
	for (int i=0;i<length;i++)
		key[i]=k[i];
	string output;
	input=DecodeHex(input);

	CryptoPP::Kalyna256::Decryption kalyna256Decryption(key, length);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( kalyna256Decryption, Kalyna256_CBC_iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( output ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( input.c_str() ), input.size() );
	stfDecryptor.MessageEnd();
	return output;
}