#include<winsock2.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	int sk = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8099);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sk, (struct sockaddr*)&addr, sizeof(addr));
	
	char UrTurn[3];
	
	printf("홀짝 중 하나를 선택하시오.\n홀은 'o' 짝은 'e'를 쓰시오.\n");
	
	char lang[256];
	
	scanf("%s",lang);
	send(sk, lang, 6 , 0);
	
	if(lang == "surrender"){
		send(sk, lang, strlen(lang) , 0);
		printf("You Lose");
		return 0;
	}
	
	for(int i=0;i<strlen(lang);i++){
		lang[i] =  0;
	}
	
	while(1){
		recv(sk, UrTurn, sizeof(UrTurn), 0);
				
		if(strcmp(UrTurn,"YT")==0)
			printf("Your Turn\n");
		
		scanf("%s",lang);
	
		if(lang == "surrender"){
			send(sk, lang, strlen(lang) , 0);
			printf("You Lose");
			return 0;
		}
		
		send(sk, lang, 6 , 0);
		
		for(int i=0;i<strlen(lang);i++){
			lang[i] =  0;
		}
	}
	
}
