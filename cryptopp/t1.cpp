#include "stdafx.h"
#include "hash.h"
#include "encrypt.h"
#include "basic.h"
#include "select.h"

int main()
{
	/*
	string s,key;
	cin >> s >> key;
	string tmp=Kalyna256_CBC_Encrypt(s,key);
	cout << tmp << "|\n";
	cout << Kalyna256_CBC_Decrypt(tmp,key) << endl;
	*/
	string s,k;
	cin >> s >> k;
	for (char i='0';i<='F';i++)
		cout << i << " : " << SelectAlgorithm(i,s,k) << endl;
	return 0;
}
