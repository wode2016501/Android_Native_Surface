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

FILE *fp;
char flag=1;
int sfd,cfd,ret;
struct sockaddr_in src,cli;
ssize_t recv_bytes,send_bytes;



void callback(char* buf,int size){
	fwrite(buf, 1, size, fp);
}


int main(int argc, char *argv[]){
	fp = fopen("/sdcard/test.h264", "w");

		flag=1;
		// 初始化录屏，帧率设置无用待解决
		_Z10initRecordPKcfjj("8M", 60.0F, 720, 1080);
		// 开始录屏
		_Z9runRecordPbPFvPhmE(&flag, callback);
		// stop录屏
		return 0;

}


