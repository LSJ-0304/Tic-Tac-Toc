#include<winsock2.h>

int main(void){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	int sk = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8099);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sk, (struct sockaddr*)&addr, sizeof(addr));
	
	printf("È¦Â¦ Áß ÇÏ³ª¸¦ ¼±ÅÃÇÏ½Ã¿À.\nÈ¦Àº 'o' Â¦Àº 'e'¸¦ ¾²½Ã¿À.");
	
	char lang[256];
	
	while(1){
		scanf("%s",lang);
	
		if(lang == "surrender"){
			send(sk, lang, strlen(lang) , 0);
			return 0;
		}
		
		send(sk, lang, 6 , 0);
		
		for(int i=0;i<strlen(lang);i++){
			lang[i] =  0;
		}
	}
}
