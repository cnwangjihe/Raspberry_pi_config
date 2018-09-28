#include "stdafx.h"
#include "hash.h"
#include "encrypt.h"
#include "basic.h"
#include "select.h"

int main(int argc,char* argv[])
{
	/*
	string s,key;
	cin >> s >> key;
	string tmp=Kalyna256_CBC_Encrypt(s,key);
	cout << tmp << "|\n";
	cout << Kalyna256_CBC_Decrypt(tmp,key) << endl;
	*/
	int level,n;
	string s,k,opt;
	cin >> s >> k >> level;
	opt=GetOperationSequence(s+k,level);
	n=opt.size();
	for (int i=0;i<n;i++)
		s=SelectAlgorithm(opt[i],s,k);
	cout << EncodeBase64(DecodeHex(s)) << endl;
	return 0;
}