#include<stdio.h>
int main(){
	int Login;
	printf("Two Players-Enter 1");
	scanf("%d",&Login);
	printf("User Vs Computer-Enter 2");
	scanf("%d",&Login);
	printf("Multiple Players-Enter 3");
	scanf("%d",&Login);

	if(Login==1){
		printf("HI");
	}
	else if(Login==2){
		printf("Bye");
	}
	else if(Login==3){
		printf("go");
	}
	else
		printf("Invalid Index");
	return 0;
}
	

