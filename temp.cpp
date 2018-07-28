#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

#define BUF_SIZE 512
string publicIP,usedIP;
struct sockaddr_in pin;
struct hostent *nlp_host;
int sd;
int len;
char buf[BUF_SIZE],GET[100],header[240],tIP[20],myurl[100];
char url[] = "www.3322.org/dyndns/getip";
string command,tmp;

bool getPublicIP()
{

    sd = 0;
    len = 0;
    memset(buf,0,sizeof buf);
    memset(header,0,sizeof header);
    memset(GET,0,sizeof GET);
    memset(myurl,0,sizeof myurl);
    memset(tIP,0,sizeof tIP);
    char *pHost = 0;

    strcpy(myurl,url);
    ///get the host name and the relative address from url name!!!
	for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost) ;
		if ((unsigned int)(pHost - myurl) == strlen(myurl))
			strcpy(GET, "/");
		else
			strcpy(GET, pHost);
	*pHost = '\0';


    ///setting socket param
	if ((nlp_host = gethostbyname(myurl)) == 0)
	{
		perror("error get host\n");
		return 0;
	}

	bzero(&pin, sizeof(pin));
	pin.sin_family = AF_INET;
	pin.sin_addr.s_addr = htonl(INADDR_ANY);
	pin.sin_addr.s_addr = ((struct in_addr *)(nlp_host->h_addr))->s_addr;
	pin.sin_port = htons(80);

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Error opening socket!!!\n");
		return 0;
	}


    ///together the request info that will be sent to web server
    ///Note: the blank and enter key byte is necessary,please remember!!!
	strcat(header, "GET");
	strcat(header, " ");
	strcat(header, GET);
	strcat(header, " ");
	strcat(header, "HTTP/1.1\r\n");
	strcat(header, "HOST:");
	strcat(header, myurl);
	strcat(header, "\r\n");
    strcat(header, "ACCEPT:*/*");
	strcat(header, "\r\nConnection: close\r\n\r\n\r\n");


    ///connect to the webserver,send the header,and receive the web sourcecode
//    if (::connect(sd, (void *)&pin, sizeof(pin)) == -1)
	if (::connect(sd, (sockaddr *)&pin, sizeof(pin)) == -1)
	{
		::close(sd);
		printf("error connect to socket\n");
		return 0;
	}

	if (send(sd, header, strlen(header), 0) == -1)
	{
		::close(sd);
		perror("error in send \n");
		return 0;
	}


    ///send the message and wait the response!!!
	len = recv(sd, buf, BUF_SIZE, 0);
	if (len < 0)
	{
		::close(sd);
		printf("receive data error!!!\n");
		return 0;
	}
	else
	{
		sscanf(strstr(buf,"utf-8")+9,"%*[^\n]\n%[^\n]",tIP);
		publicIP=tIP;
		printf("ip = %s\n",tIP);
		cerr << publicIP << endl;
		::close(sd);
		return 1;
	}
}

int main(int argc, char *argv[])
{
	getPublicIP();
}