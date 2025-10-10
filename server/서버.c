#include<winsock2.h>
#include<time.h>
#include<stdio.h>

char isDraw(char number[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(number[i][j] != 'o' && number[i][j] != 'x')
				return 0;
		}
	}
	
	return 1;
}

char checkwinner(char number[3][3]){
	
	//가로
	for(int i=0;i<3;i++){
	    if(number[i][0] == number[i][1] && number[i][1] == number[i][2]){
	    	if(number[i][0] == 'o' || number[i][0] == 'x')
		        return number[i][0];
	    }
	}
	
	//세로 
	for(int i=0;i<3;i++){
	    if(number[0][i] == number[1][i] && number[1][i] == number[2][i]){
	        if(number[0][i] == 'o' || number[0][i] == 'x')
				return number[0][i];
	    }
	}
	
	//대각선 (version1)
	if(number[0][0] == number[1][1] && number[1][1] == number[2][2]){
	    if(number[0][0] == 'o' || number[0][0] == 'x')
			return number[0][0];
	}
	//대각선 (version2)
	if(number[0][2] == number[1][1] && number[1][1] == number[2][0]){
	    if(number[0][2] == 'o' || number[0][2] == 'x')
			return number[0][2];
	}
	
	return '0';

}

int main(void){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	int sk = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
    
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8099);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sk, (struct sockaddr*)&addr, sizeof(addr));
	
	listen(sk, 2);
	
	
	//client1
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int client_sk;
	client_sk = accept(sk, (struct sockaddr*)&client_addr, &client_len);
	
	//client2
	struct sockaddr_in client_addr2;
	int client_len2 = sizeof(client_addr);
	int client_sk2;
	client_sk2 = accept(sk, (struct sockaddr*)&client_addr2, &client_len2);
	
	//홀짝 주사위 코드
	char sniffling1[256];
	char sniffling2[256];
	
	recv(client_sk, sniffling1, sizeof(sniffling1), 0);
	printf("%s\n",sniffling1);
	recv(client_sk2, sniffling2, sizeof(sniffling2), 0);
	printf("%s\n",sniffling2);
	
	srand(time(NULL));
	
	int rnd = rand()%6+1;
	
	printf("%d\n",rnd);
	
	char rndresult[256] = {0,};
	
	if(rnd == 1 || rnd == 3 || rnd == 5){
		rndresult[0] = 'o'; //홀수
		printf("홀\n");
	}else{
		rndresult[0] = 'e'; //짝수
		printf("짝\n");
	}
	
	char Tnumber1;
	char Tnumber2;
	
	char check = 'o';
	
	char winner = '0';
	
	char number[3][3] = {
	    {' ',' ',' '},
	    {' ',' ',' '},
	    {' ',' ',' '}
	};
	
	char display[3][3] = {
	    {'7','8','9'},
	    {'4','5','6'},
	    {'1','2','3'}
	};
	
	char UrTurn[3] = {'Y','T'};
	int SEND;
	int SEND2;
	
	//클라1 이 맞았을 때  
	if(*sniffling1 == *rndresult){
		if(check == 'o'){
			send(client_sk, &check, sizeof(check) , 0);
			check = 'x';
			send(client_sk2, &check, sizeof(check) , 0);
		}else{
			send(client_sk2, &check, sizeof(check) , 0);
			check = 'o';
			send(client_sk, &check, sizeof(check) , 0);
		}
		while(1){
			if(check == 'o'){
				
				SEND = send(client_sk, UrTurn, sizeof(UrTurn) , 0);
				
				if(SEND > 0){
					printf("UrTurn 보냄 : %s\n",UrTurn);
				}
				
				printf("SEND : %d\n",SEND);
				
				recv(client_sk, &Tnumber1, sizeof(Tnumber1), 0);
				printf("Tnumber1 : %c\n",Tnumber1);
				
				for(int c=0;c<3;c++){
					for(int v=0;v<3;v++){
						
						if(Tnumber1 == display[c][v]){
							if(check == 'o'){
								number[c][v] = 'o';
								display[c][v] = 'o';
							}
						}
					}
				}
				
				winner = checkwinner(number);
	    		if(winner != '0' || isDraw(number)) break;
	    	}else{
				SEND2 = send(client_sk2, UrTurn, sizeof(UrTurn) , 0);
				
				if(SEND2 > 0){
					printf("UrTurn2 보냄 : %s\n",UrTurn);
				}
				
				printf("SEND2 : %d\n",SEND2);
				
				recv(client_sk2, &Tnumber2, sizeof(Tnumber2), 0);
				printf("Tnumber2 : %c\n",Tnumber2);
					
				for(int c=0;c<3;c++){
					for(int v=0;v<3;v++){
						
						if(Tnumber2 == display[c][v]){
							if(check == 'x'){
								number[c][v] = 'x';
								display[c][v] = 'x';
							}
						}
					}
				}
				
				winner = checkwinner(number);
	    		if(winner != '0' || isDraw(number)) break;
	    	}
			
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					printf("  \033[33m%c\033[0m",display[i][j]);
				
					if((j+1) % 3 == 0){
						printf("\n");
					}else{
						printf("  |");
					}
				}
				if(i != 2)
					printf("-----------------\n");
			}
	
			printf("------------------------\n");
			
			send(client_sk, display, sizeof(display), 0);
			send(client_sk2, display, sizeof(display), 0);
			
			//Tnumber1 비우기 
			Tnumber1 =  0;
			
			//Tnumber2 비우기 
			Tnumber2 =  0;
			
			winner = checkwinner(number);
    		if(winner != '-1' || isDraw(number)) break;
    		
    		SEND = 0;
    		SEND2 = 0;
    		
    		check = (check == 'o') ? 'x' : 'o';
		}
		
	//클라2 이 맞았을 때  
	}else if(*sniffling2 == *rndresult){
		if(check == 'o'){
			send(client_sk2, &check, sizeof(check) , 0);
			check = 'x';
			send(client_sk, &check, sizeof(check) , 0);
		}else{
			send(client_sk, &check, sizeof(check) , 0);
			check = 'o';
			send(client_sk2, &check, sizeof(check) , 0);
		}
		while(1){
			if(check == 'o'){
				
				SEND2 = send(client_sk2, UrTurn, sizeof(UrTurn) , 0);
				
				if(SEND2 > 0){
					printf("UrTurn2 보냄 : %s\n",UrTurn);
				}
				
				printf("SEND2 : %d\n",SEND2);
				
				recv(client_sk2, &Tnumber2, sizeof(Tnumber2), 0);
				printf("Tnumber2 : %c\n",Tnumber2);
				
				for(int c=0;c<3;c++){
					for(int v=0;v<3;v++){
						
						if(Tnumber2 == display[c][v]){
							if(check == 'o'){
								number[c][v] = 'o';
								display[c][v] = 'o';
							}
						}
					}
				}
				
				winner = checkwinner(number);
	    		if(winner != '0' || isDraw(number)) break;
	    	}else{
				SEND = send(client_sk, UrTurn, sizeof(UrTurn) , 0);
				
				if(SEND > 0){
					printf("UrTurn 보냄 : %s\n",UrTurn);
				}
				
				printf("SEND : %d\n",SEND);
				
				recv(client_sk, &Tnumber1, sizeof(Tnumber1), 0);
				printf("Tnumber1 : %c\n",Tnumber1);
				
				for(int c=0;c<3;c++){
					for(int v=0;v<3;v++){
						
						if(Tnumber1 == display[c][v]){
							if(check == 'x'){
								number[c][v] = 'x';
								display[c][v] = 'x';
							}
						}
					}
				}
				
				winner = checkwinner(number);
	    		if(winner != '0' || isDraw(number)) break;
	    	}
			
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					printf("  \033[33m%c\033[0m",display[i][j]);
				
					if((j+1) % 3 == 0){
						printf("\n");
					}else{
						printf("  |");
					}
				}
				if(i != 2)
					printf("-----------------\n");
			}
	
			printf("------------------------\n");
			
			send(client_sk2, display, sizeof(display), 0);
			send(client_sk, display, sizeof(display), 0);
			
			//Tnumber2 비우기 
			Tnumber2 =  0;

			
			//Tnumber1 비우기 
			Tnumber1 =  0;
			
			winner = checkwinner(number);
    		if(winner != '-1' || isDraw(number)) break;
    		
    		SEND = 0;
    		SEND2 = 0;
    		
    		check = (check == 'o') ? 'x' : 'o';
		}
	}	
	send(client_sk, display, sizeof(display), 0);
	send(client_sk2, display, sizeof(display), 0);
	
	send(client_sk, &winner, sizeof(winner) , 0);
	send(client_sk2, &winner, sizeof(winner) , 0);
	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("  \033[33m%c\033[0m",display[i][j]);
		
			if((j+1) % 3 == 0){
				printf("\n");
			}else{
				printf("  |");
			}
		}
		if(i != 2)
			printf("-----------------\n");
	}
	
	printf("------------------------\n");
	
	if(winner == 'o'){
	    printf("\033[32mo 승리!\033[0m\n");
	}else if(winner == 'x'){
	    printf("\033[32mx 승리!\033[0m\n");
	}else{
	    printf("\033[31m무승부!\033[0m\n");
	}
	
	scanf("%c", Tnumber1);
	
	return 0;
}
