#include<winsock2.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <windows.h>

void clearScreen() {
    printf("\033[2J");
    printf("\033[H");
    fflush(stdout);
}

char isDraw(char number[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(number[i][j] != 'o' && number[i][j] != 'x')
				return 0;
		}
	}
	
	return 1;
}

int main(void){
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	
	int sk = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8099);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(sk, (struct sockaddr*)&addr, sizeof(addr));
	
	char UrTurn[3] = {0,};
	
	printf("홀짝 중 하나를 선택하시오.\n홀은 'o' 짝은 'e'를 쓰시오.\n");
	
	char lang[256];
	
	scanf("%s",lang);
	send(sk, lang, 6 , 0);
	
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
	
	
	char Tnumber;
	char check;
	char wrongnumber = 0;
	int PreviousN[3][3] = {0,};
	int valid = 0;
	char winner;
	
	int RECV;
	
	for(int i=0;i<strlen(lang);i++){
		lang[i] =  0;
	}
	
	clearScreen();
	
	recv(sk, &check, sizeof(check) , 0);
	
	char myMark;
	if(check == 'o') myMark = 'o';
	else myMark = 'x';
	
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

	while(1){
		RECV = recv(sk, UrTurn, 3, 0);
				
		if(RECV > 0){
			printf("%s\n",UrTurn);
		
			do{
				valid = 0;
				Tnumber = _getch();
				if(check == 'o'){
					for(int c=0;c<3;c++){
						for(int v=0;v<3;v++){
							
							if(Tnumber == display[c][v]){
								PreviousN[c][v] = 1;
								valid = 1;
							}
						}
					}
				}else{
					for(int c=0;c<3;c++){
						for(int v=0;v<3;v++){
							
							if(Tnumber == display[c][v]){
								PreviousN[c][v] = 1;
								valid = 1;
							}
						}
					}
				}
					
				if(!valid) printf("Wrong Number\n");
			}while(!valid);
			
			send(sk, &Tnumber, 1 , 0);
			
			int recv_len = recv(sk, display, sizeof(display), 0);
			
			clearScreen();
			
			if(recv_len > 0){
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
			}
			printf("------------------------\n");
			
			recv(sk, &winner, sizeof(winner), 0);
			
			printf("winner의 값 : %c\n",winner);
			
			if(winner == myMark){
			    printf("\033[32m%c 승리!\033[0m", myMark);
			    break;
			}else if(winner == 'o' || winner == 'x'){
			    printf("\033[31m%c 패배!\033[0m", myMark);
			    break;
			}else if(isDraw(number)){
			    printf("\033[35m무승부!\033[0m");
			    break;
			}
		}
	}
	
	Sleep(5000);
}
