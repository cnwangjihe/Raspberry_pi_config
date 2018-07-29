#include <fstream>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <string>
#ifdef WIN32
	#include <windows.h>
#endif
#ifdef linux
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
//		printf("%s\n\n%s\n\n",sa,sb);
		if(strcmp(sa,sb))
			return 0;
	}
//	cerr << "sds";
	return !(feof(fa)^feof(fb));
}

void test()
{
	fa = fopen("frpc.ini","rt");
	fb = fopen("frpc.ini.new","rt");
	cerr << CompareFile(fa,fb);
	exit(0);
}

int main()
{
	#ifdef linux
		cerr << "GetLinux\n";
		system("ps -eaf | grep [s]ystemd > ctemp");
		system("touch empty");
		systemd=!CompareFile(fopen("ctemp","rt"),fopen("empty","rt"));
		system("rm ctemp empty");
		cerr << (systemd?"with systemd\n":"with init.d\n");
	#endif
	#ifdef WIN32
		cerr << "GetWindows\n";
	#endif
	while (1)
	{
	//	cerr << "pass \n";
		#ifdef linux
			system("rm IP.txt");
			command = "wget "+ url;
		#endif
		#ifdef WIN32
			command = "powershell wget " + url + " -out IP.txt";
		#endif
		system(command.c_str());
		ifstream fin("IP.txt");
		fin >> IP;
		#ifdef linux
			command = "sed \'s/\\[IP\\]/ "+ IP + "/g\' frpc.ini.template > frpc.ini.new";
			system(command.c_str());
		#endif
		#ifdef WIN32
			command = "powershell  \"Get-Content \'frpc.ini.template\' | %{Write-Host $_.Replace(\'[IP]\',\'" + IP + "\')}\" > frpc.ini.new";
			system(command.c_str());
		#endif
		fa = fopen("frpc.ini","rt");
		fb = fopen("frpc.ini.new","rt");
		if (!CompareFile(fa,fb))
		{
			fclose(fa),fclose(fb);
			#ifdef linux
				system(systemd?"systemctl stop frpc":"/etc/init.d/frpc stop");
				system("mv frpc.ini.new frpc.ini");
				system("chmod 777 frpc.ini");
				system(systemd?"systemctl start frpc":"/etc/init.d/frpc start");
			#endif
			#ifdef WIN32
				system("net stop frpc");
				system("copy /Y frpc.ini.new frpc.ini");
				system("del /f /q frpc.ini.new");
				system("net start frpc");
			#endif
		}
		fclose(fa),fclose(fb);
		#ifdef linux
			sleep(30);
		#endif
		#ifdef WIN32
			Sleep(30000);
		#endif
	}
	return 0;
}