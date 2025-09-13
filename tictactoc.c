#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

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
	
	return ' ';

}

int main(void){
	
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

	
	for(int i=0;i<3;i++){
		
		for(int j=0;j<3;j++){
			printf("  %c",display[i][j]);
		
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
	
	char Tnumber;
	char check = 'o';
	char wrongnumber = 0;
	int PreviousN[3][3] = {0,};
	int valid = 0;
	
	while(1){
		
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
		
		for(int c=0;c<3;c++){
			for(int v=0;v<3;v++){
				
				if(Tnumber == display[c][v]){
					if(check == 'o'){
						number[c][v] = 'o';
						display[c][v] = 'o';
						check = 'x';
					}else{
						number[c][v] = 'x';
						display[c][v] = 'x';
						check = 'o';
					}
				}
			}
		}
		
		clearScreen();
		
		for(int i=0;i<3;i++){
		
			for(int j=0;j<3;j++){
				printf("  %c",display[i][j]);
			
				if((j+1) % 3 == 0){
					printf("\n");
				}else{
					printf("  |");
				}
		}
			if(i != 2)
				printf("-----------------\n");
		}
		
		char winner = checkwinner(number);
		
		if(winner == 'o'){
			clearScreen();
			printf("o 승리!");
			break;
		}else if(winner == 'x'){
			clearScreen();
			printf("x 승리!");
			break;
		}else if(isDraw(number)){
			clearScreen();
			printf("무승부!");
			break;
		}
		
	}
	
	return 0;
}
