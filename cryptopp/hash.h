#pragma once
#include "stdafx.h"

string GETSHA512(string input)
{
	CryptoPP::SHA512 hash;
	byte digest[ CryptoPP::SHA512::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETSHA256(string input)
{
	CryptoPP::SHA256 hash;
	byte digest[ CryptoPP::SHA256::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETSHA384(string input)
{
	CryptoPP::SHA384 hash;
	byte digest[ CryptoPP::SHA384::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETSHA224(string input)
{
	CryptoPP::SHA224 hash;
	byte digest[ CryptoPP::SHA224::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETBLAKE2s(string input)
{
	CryptoPP::BLAKE2s hash;
	byte digest[ CryptoPP::BLAKE2s::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETBLAKE2b(string input)
{
	CryptoPP::BLAKE2b hash;
	byte digest[ CryptoPP::BLAKE2b::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETMD5(string input)
{
	CryptoPP::Weak::MD5 hash;
	byte digest[ CryptoPP::Weak::MD5::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETSM3(string input)
{
	CryptoPP::SM3 hash;
	byte digest[ CryptoPP::SM3::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETTiger(string input)
{
	CryptoPP::Tiger hash;
	byte digest[ CryptoPP::Tiger::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETRIPEMD320(string input)
{
	CryptoPP::RIPEMD320 hash;
	byte digest[ CryptoPP::RIPEMD320::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETRIPEMD160(string input)
{
	CryptoPP::RIPEMD160 hash;
	byte digest[ CryptoPP::RIPEMD160::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETRIPEMD256(string input)
{
	CryptoPP::RIPEMD256 hash;
	byte digest[ CryptoPP::RIPEMD256::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETRIPEMD128(string input)
{
	CryptoPP::RIPEMD128 hash;
	byte digest[ CryptoPP::RIPEMD128::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETCRC32(string input)
{
	CryptoPP::CRC32 hash;
	byte digest[ CryptoPP::CRC32::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETWhirlpool(string input)
{
	CryptoPP::Whirlpool hash;
	byte digest[ CryptoPP::Whirlpool::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETKeccak_256(string input)
{
	CryptoPP::Keccak_256 hash;
	byte digest[ CryptoPP::Keccak_256::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETKeccak_512(string input)
{
	CryptoPP::Keccak_512 hash;
	byte digest[ CryptoPP::Keccak_512::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETSHA3_256(string input)
{
	CryptoPP::SHA3_256 hash;
	byte digest[ CryptoPP::SHA3_256::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}

string GETSHA3_512(string input)
{
	CryptoPP::SHA3_512 hash;
	byte digest[ CryptoPP::SHA3_512::DIGESTSIZE ];

	hash.CalculateDigest( digest, (byte*) input.c_str(), input.length() );

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	return output;
}