#include<stdio.h>
#include<sys/types.h>           
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void _Z10initRecordPKcfjj(const char* bitRate,float fps,int  videoWidth, int  videoHeight);
void  _Z9runRecordPbPFvPhmE(char *runFlag,void callback(char *,size_t));
void _Z10stopRecordv();

//FILE *fp;
char flag=1;
int sfd,cfd,ret;
struct sockaddr_in src,cli;
ssize_t recv_bytes,send_bytes;



void callback(char* buf,int size){
	//fwrite(buf, 1, size, fp);
	send_bytes = send(cfd,buf,size,0);
	if (send_bytes<1){
		printf("Failed to send buffer\n");
		flag=0;
	}

}


int main(int argc, char *argv[]){
//	fp = fopen("/sdcard/test.h264", "w");

	int port=6656;
	socklen_t len = sizeof(src);
	socklen_t addrlen = sizeof(cli);
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket fail");
		return -1;
	}
	if(argc>=2)
		port=atoi(argv[1]);
	src.sin_family = AF_INET;
	src.sin_port = htons(port);
	src.sin_addr.s_addr = inet_addr("0.0.0.0");
	ret = bind(sfd,(const struct sockaddr *)&src,len);
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	ret = listen(sfd,10);
	if(ret == -1)
	{
		perror("listen");
		return -1;
	}
	while(1){
		cfd = accept(sfd,(struct sockaddr *)&cli,&addrlen);
		if(cfd == -1)
		{
			perror("accept");
			return -1;
		}
		printf("cfd:%d\n",cfd);
		printf("client ip : %s\nport %d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
		char * str="HTTP/1.1 200 OK\r\n\r\n";
		send_bytes = send(cfd,str,strlen(str),0);

		flag=1;
		// 初始化录屏，帧率设置无用待解决
		_Z10initRecordPKcfjj("12M", 60.0F, 1080,2280);
		// 开始录屏
		_Z9runRecordPbPFvPhmE(&flag, callback);
		// stop录屏
		_Z10stopRecordv();
		close(cfd);
	}
	close(sfd);
	return 0;

}


