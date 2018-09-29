/*define*/

// 123456 ABC6DFB623AC2635 128
// noI32aUymrvqBbeD/TEeVQ== ABC6DFB623AC2635 128
#pragma once

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/kalyna.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <bits/stdc++.h>
#include <cryptopp/md5.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/sm3.h>
#include <cryptopp/blake2.h>
#include <cryptopp/tiger.h>
#include <cryptopp/ripemd.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/crc.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/keccak.h>
#include <cryptopp/sha3.h>
#include <cryptopp/adler32.h>
#include <time.h>

using namespace std;
using namespace CryptoPP;

const byte AES_CBC_iv[16]       = {0x15,0x04,0x12,0x11,0x09,0xA4,0x10,0x07,0x13,0x04,0x09,0x00,0x08,0x00,0x02,0x02};
const byte Kalyna128_CBC_iv[16] = {0xBB,0xC3,0x12,0x11,0x39,0xB4,0x09,0xA5,0x13,0xC4,0xCA,0x80,0x68,0x32,0x13,0xA8};
const byte Kalyna256_CBC_iv[32] = {0x11,0xBB,0x39,0xB4,0x09,0xA5,0x13,0x23,0xAB,0x7F,0x1A,0xBC,0xC3,0x12,0xC4,0xCA,
								   0x5C,0xD9,0x22,0x33,0x26,0xB2,0x2B,0x80,0x68,0x32,0x13,0xA8,0x37,0xAA,0xBB,0xFF};
const string EmptyString           = "",
			 Base64DefaultAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
			 Base64BetterAlphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?",
			 HexDefaultAlphabet    = "0123456789ABCDEF";
/*
system("bash -c \"read -rsp $'Press any key to continue...\n' -n 1 key\"");
*/