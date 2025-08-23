#include<stdio.h>
#include<stdlib.h>

int main(void){
	
	int number[3][3] = {
	{7,8,9},
	{4,5,6},
	{1,2,3}
	};
	
	char imsi[4][4] = {0,};
	
	for(int i=0;i<3;i++){
		
		for(int j=0;j<3;j++){
			printf("  %d",number[i][j]);
		
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
	
	int Onumber = 0;
	int Xnumber = 0;
	
	while(1){
		
		scanf("%d",&Onumber);
		
		for(int c=0;c<3;c++){
			for(int v=0;v<3;v++){
				if(Onumber == number[c][v]){
					imsi[c][v] = 'o';
					printf("imsi[%d][%d] : %c\n",c,v,imsi[c][v]);
				}
			}
		}
		
		scanf("%d",&Xnumber);
		
		for(int c=0;c<3;c++){
			for(int v=0;v<3;v++){
				if(Xnumber == number[c][v]){
					imsi[c][v] = 'x';
					printf("imsi[%d][%d] : %c\n",c,v,imsi[c][v]);
				}
			}
		}
		
		for(int i=0;i<3;i++){
		
			for(int j=0;j<3;j++){
				printf("  %c",imsi[i][j]);
			
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
	
	
	//fflush(stdout);
	//system("cls");
	
	
	return 0;
}
