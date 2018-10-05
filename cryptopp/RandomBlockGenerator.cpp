#include <bits/stdc++.h>

using namespace std;

char charset[20];
int m=0,n;

int main()
{
	srand(time(0));
	for (int i=0;i<10;i++)
		charset[m++]=i+48;
	for (int i='A';i<'G';i++)
		charset[m++]=i;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		printf("0x%c%c%c",charset[rand()%16],charset[rand()%16],i==n?'\n':',');
	return 0;
}