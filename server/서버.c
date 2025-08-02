#include<winsock2.h>

int main(void){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	int sk = socket(AF_INET, SOCK_STREAM, 0);
	closesocket(sk);
	
	struct sockaddr_in addr;
    
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8099);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sk, (struct sockaddr*)&addr, sizeof(addr));
	
	listen(sk, 5);
	
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int client_sk;
	client_sk = accept(sk, (struct sockaddr*)&client_addr, &client_len);
	
	return 0;
}
