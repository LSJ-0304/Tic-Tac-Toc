#include<stdio.h>

int main(void){
	
	int number = 1;
	
	for(int i=0;i<3;i++){
		
		for(int j=0;j<3;j++){
			printf("  %d",number);
			
			if((j+1) % 3 == 0){
				printf("\n");
			}else{
				printf("  |");
			}
			
			number++;
		}
		
		if(i != 2)
			printf("-----------------\n");
		
	}
	
	int Onumber = 0;
	int Xnumber = 0;
	
	scanf("%d",&Onumber);
	
	
	return 0;
}
