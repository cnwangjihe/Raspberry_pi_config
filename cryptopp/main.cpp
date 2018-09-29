#define LOGWARNING
#define LOGINFO
#define LOGDEBUG

#include "stdafx.h"
#include "hash.h"
#include "encrypt.h"
#include "basic.h"
#include "select.h"


int level,n,type;
string s,k,opt;

int main(int argc,char* argv[])
{
	/*
	string s,key;
	cin >> s >> key;
	string tmp=Kalyna256_CBC_Encrypt(s,key);
	cout << tmp << "|\n";
	cout << Kalyna256_CBC_Decrypt(tmp,key) << endl;
	*/
	if (argc<=1)
		cin >> s >> k >> level >> type;
	opt=GetOperationSequence(s+k,level);
	n=opt.size();
	for (int i=0;i<n;i++)
		s=SelectAlgorithm(s,k,opt[i]);
	cout << EncodeBase64(DecodeHex(s)) << endl;
	cout << ChangeBase64Alphabet(EncodeBase64(DecodeHex(s)),"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?") << endl;
//	cout << s << endl;
	/*
	string s,k,tmp;
	cin >> s >> k;
	for (char i='0';i<='F';i++)
	{
		s = SelectAlgorithm(s,k,i);
		cout << i << " : \n";
		cout << "  " << StringEraseEnter(Hex2Base64(s)) << endl;
		cout << "  " << s << endl;
	}
	return 0;
	*/
}
//Tr4zlfj3m9BaunsGI+Tx+aL1acmy5AJetsAYv8XgHg1b0o2auM0QZp0A42bHXrL4CrQNtIC5
//MMKHYmO++EcUxeLyRfRA79GNioYP4l23UDv+nx3DHCk=
//mN5yoMYZA/NSbSxuBibi046hVdB/CzMONyzcNdzqgQQ3qiQgoukZmAet79lElQPKHqUvUJuEClBjkzK+R8J+xQ==