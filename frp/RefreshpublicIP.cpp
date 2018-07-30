#include <fstream>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <string>
#if (defined _WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
#endif

using namespace std;

const int MAXLEN = 500;

string url = "https://gitlab.com/cnwangjihe/raspIP/raw/master/IP.txt";
string command,IP;
char sa[MAXLEN],sb[MAXLEN];
FILE *fa,*fb;
int systemd=2;

bool CompareFile(FILE *fa,FILE *fb)
{
	while(!feof(fa) && !feof(fb))
	{
		fgets(sa,MAXLEN,fa);
		fgets(sb,MAXLEN,fb);
		if(strcmp(sa,sb))
			return 0;
	}
	return !(feof(fa)^feof(fb));
}

int main()
{
	#if (defined __linux__)
		cout << "GetLinux\n";
		system("ps -eaf | grep [s]ystemd > ctemp");
		system("touch empty");
		systemd=!CompareFile(fopen("ctemp","rt"),fopen("empty","rt"));
		system("rm ctemp empty");
		cout << (systemd?"with systemd\n":"with init.d\n");
	#else
		cout << "GetWindows ";
		#if (defined PSv5)
			cout << "with powershell v5\n";
		#else
			cout << "with GNU_Win32\n";
		#endif
	#endif
	while (1)
	{
		#if (defined __linux__)
			system("rm IP.txt");
		#else
			system("del /f /q IP.txt");
		#endif
		#if (defined __linux__) || ((defined _WIN32) && (!defined PSv5))
			command = "wget "+ url;
			system(command.c_str());
			ifstream fin("IP.txt");
			fin >> IP;
			fin.close();
			command = "sed \"s/\\[IP\\]/ "+ IP + "/g\" frpc.ini.template > frpc.ini.new";
			system(command.c_str());
		#else
			command = "powershell wget " + url + " -out IP.txt";
			system(command.c_str());
			ifstream fin("IP.txt");
			fin >> IP;
			fin.close();
			command = "powershell  \"Get-Content \'frpc.ini.template\' | %{Write-Host $_.Replace(\'[IP]\',\'" + IP + "\')}\" > frpc.ini.new";
			system(command.c_str());
		#endif
		fa = fopen("frpc.ini","rt");
		fb = fopen("frpc.ini.new","rt");
		if (fa==NULL || !CompareFile(fa,fb))
		{
			if (fa!=NULL)
				fclose(fa);
			fclose(fb);
			#if (defined __linux__)
				system(systemd?"systemctl stop frpc":"/etc/init.d/frpc stop");
				system("mv frpc.ini.new frpc.ini");
				system("chmod 777 frpc.ini");
				system(systemd?"systemctl start frpc":"/etc/init.d/frpc start");
			#else
				system("net stop frpc");
				system("copy /Y frpc.ini.new frpc.ini");
				system("del /f /q frpc.ini.new");
				system("net start frpc");
			#endif
		}
		else
			fclose(fa),fclose(fb);
		#if (defined __linux__)
			sleep(30);
		#else
			Sleep(30000);
		#endif
	}
	return 0;
}