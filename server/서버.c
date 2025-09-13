#include<winsock2.h>
#include<time.h>
#include<stdio.h>

int main(void){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	int sk = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
    
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8099);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sk, (struct sockaddr*)&addr, sizeof(addr));
	
	listen(sk, 5);
	
	
	//client1
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int client_sk;
	client_sk = accept(sk, (struct sockaddr*)&client_addr, &client_len);
	
	//client2
	struct sockaddr_in client_addr2;
	int client_len2 = sizeof(client_addr);
	int client_sk2;
	client_sk2 = accept(sk, (struct sockaddr*)&client_addr, &client_len2);
	
	//홀짝 주사위 코드
	char sniffling1[256];
	char sniffling2[256];
	
	recv(client_sk, sniffling1, sizeof(sniffling1), 0);
	printf("%s\n",sniffling1);
	recv(client_sk2, sniffling2, sizeof(sniffling2), 0);
	printf("%s\n",sniffling2);
	
	srand(time(NULL));
	
	int rnd = rand()%6+1;
	
	printf("%d",rnd);
	
	char rndresult[256] = {0,};
	
	if(rnd == 1 || rnd == 3 || rnd == 5){
		rndresult[0] = 'o'; //홀수
		printf("홀");
	}else{
		rndresult[0] = 'e'; //짝수
		printf("짝");
	}
	
	char buffer1[256];
	char buffer2[256];
	
	char UrTurn[3] = "YT";
	
	//클라1 이 맞았을 때  
	if(*sniffling1 == *rndresult){
		while(1){
			send(client_sk, UrTurn, strlen(UrTurn) , 0);
			
			recv(client_sk, buffer1, sizeof(buffer1), 0);
				printf("%s\n",buffer1);
				
			send(client_sk2, UrTurn, strlen(UrTurn) , 0);
			
			recv(client_sk2, buffer2, sizeof(buffer2), 0);
				printf("%s\n",buffer2);
			
			if(buffer1 == "surrender" || buffer2 == "surrender"){
				return 0;
			}
			
			//buffer1 비우기 
			for(int i=0;i<strlen(buffer1);i++){
				buffer1[i] =  0;
			}
			
			//buffer2 비우기 
			for(int i=0;i<strlen(buffer2);i++){
				buffer2[i] =  0;
			}
		}
		
	//클라2 이 맞았을 때  
	}else if(*sniffling2 == *rndresult){
		while(1){
			send(client_sk2, UrTurn, strlen(UrTurn) , 0);
			
			recv(client_sk2, buffer2, sizeof(buffer2), 0);
				printf("%s\n",buffer1);
				
			send(client_sk, UrTurn, strlen(UrTurn) , 0);
			
			recv(client_sk, buffer1, sizeof(buffer1), 0);
				printf("%s\n",buffer2);
			
			if(buffer1 == "surrender1" || buffer2 == "surrender2"){
				return 0;
			}
			
			//buffer2 비우기 
			for(int i=0;i<strlen(buffer2);i++){
				buffer2[i] =  0;
			}
			
			//buffer1 비우기 
			for(int i=0;i<strlen(buffer1);i++){
				buffer1[i] =  0;
			}
		}
	}
	
	
	
	scanf("%s", buffer1);
	
	return 0;
}
