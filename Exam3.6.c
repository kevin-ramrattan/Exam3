/*

+ sorted all the varieble except team names 



+++++++++  To Do lists +++++++++++++

1. sort team names 




Shin

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define flush fflush(stdin)
#define cls system ("cls")
#define pause system ("pause")
#define SIZE 12

typedef struct{
	int teams;
	double win;
	double lose;
	double PCT;
	int total;
	int RunsScore;
	int RunsAgainst;
	int counter;

} major;//end of struct 


//function protytype
int mainMenu();
void game(major *team, major *temp,int *score,int *Pteam,int *flag);
void game2(major *team, major *temp,int *score2,int *Pteam2,int score, int Pteam);
void result(major *team,major *temp,int score,int score2,int Pteam,int Pteam2);
void putItBack(major *team,major *temp,int Pteam,int score);
void putItBack2(major *team,major *temp,int Pteam2,int score);
void display(major *team,int flag,char teamName[12][20]);
void reset(major *team,major *temp,int *flag);
void sort(major *team,major *temp, major swap,int score,int score2,int Pteam,int Pteam2);

FILE *fp;

main(){
	int read =0;
	int choice=0, flag=0;
	int score=0,score2=0,Pteam=0,Pteam2=0;
	int i=0;
	int position=0;

	char teamName[12][20]={"Atlanta","Orioles","Boston","Yankees","St.Louis","Dogers","White Sox","Mets","Giants",
		"Miami","Phillies","Tigers"};

	major team[SIZE];           major temp[SIZE];  major swap;



	/*for(i=0;i<12;i++){ 
	printf("%s\n\n",teamName[i]);

	}
	pause;*/

	for(i=0;i<12;i++){ //access to all 12 teams
		team[i].teams=0;           temp[i].teams=0;           //0
		team[i].win=0.0;           temp[i].win=0.0;
		team[i].lose=0.0;          temp[i].lose=0.0;
		team[i].PCT=0.0;           temp[i].PCT=0.0;
		team[i].total=0;           temp[i].total=0;
		team[i].RunsScore=0;       temp[i].RunsScore=0;
		team[i].RunsAgainst=0;     temp[i].RunsAgainst=0;
		team[i].counter=0;         temp[i].counter=0;


		swap.teams=0;           //0
		swap.win=0.0;
		swap.lose=0.0;
		swap.PCT=0.0;
		swap.total=0;
		swap.RunsScore=0;
		swap.RunsAgainst=0;
		swap.counter=0;
	}//end of for 

	fp = fopen("MLB.bin", "rb");
	fread(&read, sizeof(int), 1, fp);
	fclose(fp);

	flag = read;
	if(flag > 0){
		fp = fopen("MLB.bin", "rb");
		fseek(fp, sizeof(int), SEEK_SET);
		fread(&team,sizeof(major), SIZE, fp);
		fclose(fp);
	}//end of if 


	do{
		cls;
		choice = mainMenu();
		switch(choice){
		case 1:
			flush;
			game(team,temp,&score,&Pteam,&flag);
			game2(team,temp,&score2,&Pteam2,score,Pteam);
			result(team,temp,score,score2,Pteam,Pteam2);
			putItBack(team,temp,Pteam,score);
			putItBack2(team,temp,Pteam2,score2);
			sort(team,temp,swap,score,score2,Pteam,Pteam2);
			fp = fopen("MLB.bin", "wb");
			fwrite(&flag, sizeof(int), 1, fp);
			fwrite(&team,sizeof(major), SIZE, fp);
			fclose(fp);
			pause;
			break;
		case 2:
			display(team,flag,teamName);
			pause;
			break;
		case 3:
			reset(team,temp,&flag);
			break;
		case 4:
			printf("See you\n\n");
			pause;

		}//End of switch
	}while(choice!=4);

}//end of main

int mainMenu(){
	int i=0;
	printf("1) Enter the result of a game\n");
	printf("2) Display the league standings \n");
	printf("3) Restart the entire season \n");
	printf("4) Quit the program\n");
	scanf("%i",&i);
	flush;
	return i;
}//end of mainmenu

void game(major *team, major *temp,int *score,int *Pteam,int *flag){

	cls;
	printf("\t1\t Atlanta Braves\n");
	printf("\t2\t Baltimore Orioles\n");
	printf("\t3\t Boston Red Sox\n");
	printf("\t4\t New York Yankees\n");
	printf("\t5\t St.Louis Cardinals\n");
	printf("\t6\t Los Angeles Dogers\n");
	printf("\t7\t Chicago White Sox\n");
	printf("\t8\t New  York Mets\n");
	printf("\t9\t San Francisco Giants\n");
	printf("\t10\t Miami Marlins\n");
	printf("\t11\t Philadelphia Phillies\n");
	printf("\t12\t Detroit Tigers\n\n");
	printf("Game 1 pick team 1:");
	scanf("%i",Pteam);
	if(*Pteam>=13){
		do{
			printf("Selected team is invalid\n");
			printf("Game 1 pick team 1:");
			scanf("%i",Pteam);
		}while(*Pteam >= 13);

	}//end of if 

	printf("\nScore?");
	scanf("%i",score);//enter the score 


	//*(team + someNum).member ....
	(temp+*Pteam - 1)->win = (team + *Pteam - 1)->win; 
	(temp+*Pteam - 1)->lose = (team + *Pteam - 1)->lose;
	(temp+*Pteam - 1)->PCT = (team + *Pteam - 1)->PCT;
	//(temp+*Pteam - 1)->RunsScore = *score;                   //might cause the issue later on 
	(temp+*Pteam - 1)->RunsAgainst = (team + *Pteam - 1)->RunsAgainst;
	(temp+*Pteam - 1)->total = (team + *Pteam - 1)->total;
	(temp+*Pteam - 1)->counter = (team + *Pteam - 1)->counter;

	*flag= *flag + 1;
}///end of game 


void game2(major *team, major *temp,int *score2,int *Pteam2,int score, int Pteam){ //

	cls;
	printf("\t1\t Atlanta Braves\n");
	printf("\t2\t Baltimore Orioles\n");
	printf("\t3\t Boston Red Sox\n");
	printf("\t4\t New York Yankees\n");
	printf("\t5\t St.Louis Cardinals\n");
	printf("\t6\t Los Angeles Dogers\n");
	printf("\t7\t Chicago White Sox\n");
	printf("\t8\t New  York Mets\n");
	printf("\t9\t San Francisco Giants\n");
	printf("\t10\t Miami Marlins\n");
	printf("\t11\t Philadelphia Phillies\n");
	printf("\t12\t Detroit Tigers\n\n");
	printf("Game 1 pick team 2:");
	scanf("%i",Pteam2);
	if(*Pteam2>=13 || Pteam == *Pteam2){
		do{
			printf("Selected team is invalid\n");
			printf("Game 1 pick team 1:");
			scanf("%i",Pteam2);
		}while(*Pteam2 >= 13|| Pteam == *Pteam2);

	}//end of if 
	printf("\nScore?");// enter the score 
	scanf("%i",score2);

	if(score==*score2){

		do{
			printf("There Is No Tie Game In MLB");
			printf("\nScore?");
			scanf("%i",score2);
		}while(score==*score2);
	}//end of if

	//*(team + someNum).member ....
	(temp+*Pteam2 - 1)->win = (team + *Pteam2 - 1)->win; 
	(temp+*Pteam2 - 1)->lose = (team + *Pteam2 - 1)->lose;
	(temp+*Pteam2 - 1)->PCT = (team + *Pteam2 - 1)->PCT;
	//(temp+*Pteam2 - 1)->RunsScore = *score2;                   //might cause the issue later on 
	(temp+*Pteam2 - 1)->RunsAgainst = (team + *Pteam2 - 1)->RunsAgainst;
	(temp+*Pteam2 - 1)->total  =  (team + *Pteam2 - 1)->total;
	(temp+*Pteam2 - 1)->counter =  (team + *Pteam2 - 1)->counter;

}//end of game2

void result(major *team,major *temp,int score,int score2,int Pteam,int Pteam2){ 

	if(score>score2){
		(temp+Pteam - 1)->counter=(temp+Pteam - 1)->counter+1;
		(temp+Pteam2 - 1)->counter=(temp+Pteam2 - 1)->counter+1;
		(temp+Pteam - 1)->win=(temp+Pteam - 1)->win+1;
		(temp+Pteam2 - 1)->lose=(temp+Pteam2 - 1)->lose+1;
		(temp+Pteam - 1)->PCT=(temp+Pteam - 1)->win/(temp+Pteam - 1)->counter;
		(temp+Pteam2 - 1)->PCT=    (temp+Pteam2 - 1)->win/ (temp+Pteam2 - 1)->counter;
		(temp+Pteam - 1)->RunsScore =(temp+Pteam - 1)->RunsScore +score;
		(temp+Pteam2 - 1)->RunsScore=(temp+Pteam2 - 1)->RunsScore+score2;
		(temp+Pteam2 - 1)->RunsAgainst =(temp+Pteam2 - 1)->RunsAgainst +score;
		(temp+Pteam - 1)->RunsAgainst=(temp+Pteam - 1)->RunsAgainst+score2;
	}//end of if

	else{ // doesn't work with if(score<score2) 

		(temp+Pteam - 1)->counter=(temp+Pteam - 1)->counter+1;
		(temp+Pteam2 - 1)->counter=(temp+Pteam2 - 1)->counter+1;
		(temp+Pteam2 - 1)->win=(temp+Pteam2 - 1)->win+1;
		(temp+Pteam - 1)->lose=(temp+Pteam - 1)->lose+1;
		(temp+Pteam - 1)->PCT=(temp+Pteam - 1)->win/(temp+Pteam - 1)->counter;
		(temp+Pteam2 - 1)->PCT=(temp+Pteam2 - 1)->win/ (temp+Pteam2 - 1)->counter;
		(temp+Pteam - 1)->RunsScore =(temp+Pteam - 1)->RunsScore +score;
		(temp+Pteam2 - 1)->RunsScore=(temp+Pteam2 - 1)->RunsScore+score2;
		(temp+Pteam2 - 1)->RunsAgainst =(temp+Pteam2 - 1)->RunsAgainst +score;
		(temp+Pteam - 1)->RunsAgainst=(temp+Pteam - 1)->RunsAgainst+score2;
	}//end of else

}//end of result

void putItBack(major *team,major *temp,int Pteam,int score){

	(team + Pteam - 1)->win=(temp+Pteam - 1)->win; 
	(team + Pteam - 1)->lose=(temp+Pteam - 1)->lose;
	(team + Pteam - 1)->PCT=(temp+Pteam - 1)->PCT;
	(team + Pteam - 1)->total =(temp+Pteam - 1)->RunsScore;    //might cause the issue later on 
	(team + Pteam - 1)->RunsAgainst=(temp+Pteam - 1)->RunsAgainst;
	(team + Pteam - 1)->counter=(temp+Pteam - 1)->counter;

}//end of putItBack

void putItBack2(major *team, major *temp,int Pteam2,int score){

	(team + Pteam2 - 1)->win=(temp+Pteam2 - 1)->win; 
	(team + Pteam2 - 1)->lose=(temp+Pteam2 - 1)->lose;
	(team + Pteam2 - 1)->PCT=(temp+Pteam2 - 1)->PCT;
	(team + Pteam2 - 1)->total =(temp+Pteam2 - 1)->RunsScore ;    //might cause the issue later on 
	(team + Pteam2 - 1)->RunsAgainst=(temp+Pteam2 - 1)->RunsAgainst;
	(team + Pteam2 - 1)->counter=(temp+Pteam2 - 1)->counter;

}//end of putItBack2

void display(major *team,int flag,char teamName[12][20]){
	int i;
	int length=0;
	cls;
	if(flag >= 1){

		printf("Team\t\tWin\t\tLoses\tPCT\tRunscore\tRun Against\n");
		printf("----\t\t---\t\t-----\t---\t-------\t\t-----------\n");
		for(i=0; i<12; i ++){
			printf("%s\t",teamName[i]);
			length=strlen(teamName[i]); // if the letter is more than 8 remove \t
			if(length>=8){
				printf("%.0lf\t\t%.0lf\t%.3lf\t%i\t\t%i\n",team[i].win,team[i].lose,team[i].PCT,team[i].total,team[i].RunsAgainst);
			}//end of if

			else
				printf("\t%.0lf\t\t%.0lf\t%.3lf\t%i\t\t%i\n",team[i].win,team[i].lose,team[i].PCT,team[i].total,team[i].RunsAgainst);
		
		}// end of for
	}//end of if 

	else
		printf("\n\tXXX    Enter info first    XXX\n\n\n");

}//end of display

void reset(major *team,major *temp,int *flag){
	int i;
	for(i=0;i<12;i++){ //access to all 12 teams
		team[i].teams=0;           temp[i].teams=0; //0
		team[i].win=0.0;           temp[i].win=0.0;
		team[i].lose=0.0;          temp[i].lose=0.0;
		team[i].PCT=0.0;           temp[i].PCT=0.0;
		team[i].total=0;           temp[i].total=0;
		team[i].RunsScore=0;       temp[i].RunsScore=0;
		team[i].RunsAgainst=0;     temp[i].RunsAgainst=0;
		team[i].counter=0;         temp[i].counter=0;
	}//end of for 
	*flag=0;
	fp = fopen("MLB.bin","wb");
	fclose(fp);
	cls;
	printf("Now This is a new season!!\n\n");
	pause;
}// end of reset

void sort(major *team,major *temp,major swap,int score,int score2,int Pteam,int Pteam2){

	// it is kinda hard for folks to see whats happing in the actual display menu 
	//because the names stay where they are even though all the variables are changing  accrding to PCT

	int i=0,j=0;
	int counter=0; //keep track how many times PCT has been swapped 

	int a=0;
	int swa=0; //for swap

	for(i=0;i<12;i++){

		for(j=0;j<12;j++){

			if(team[j+1].PCT>team[j].PCT){ // compare team[].PCT

				int TEMP=0;//TEMP gets 0 every time if(team[j+1].PCT>team[j].PCT)

				swap.PCT = team[j+1].PCT;//thats the way this works 
				team[j+1].PCT = team[j].PCT;// i can't put these codes down below. when i tried it, code was messed up 
				team[j].PCT = swap.PCT;


				 //step 1 
	            swap.win         =  team[j+1].win;
	            swap.lose        =  team[j+1].lose;
                swap.lose        =  team[j+1].lose;
	            //swap[j].PCT         =  team[j+1].PCT;
	            swap.total       =  team[j+1].total;
	            swap.RunsScore   =  team[j+1].RunsScore;
	            swap.RunsAgainst =  team[j+1].RunsAgainst;
	            swap.counter     =  team[j+1].counter;

			   //step 2 
	           team[j+1].win         =  team[j].win;
	           team[j+1].lose        =  team[j].lose;
               team[j+1].lose        =  team[j].lose;
	           //team[j+1].PCT         =  team[j+1].PCT;
	           team[j+1].total       =  team[j].total;
	           team[j+1].RunsScore   =  team[j].RunsScore;
	           team[j+1].RunsAgainst =  team[j].RunsAgainst;
	           team[j+1].counter     =  team[j].counter;

			   //step 3
	           team[j].win         =  swap.win;
	           team[j].lose        =  swap.lose;
               team[j].lose        =  swap.lose;
	           //team[j].PCT         =  swap[j].PCT;
	           team[j].total       =  swap.total;
	           team[j].RunsScore   =  swap.RunsScore;
	           team[j].RunsAgainst =  swap.RunsAgainst;
	           team[j].counter     =  swap.counter;
			   


			}//end of if
		}//end of for inside
	}//end of for outside

	
	// just commented out in case 

	//swap[swa].teams       =  team[position].teams; //step 1 
	//swap[swa].win         =  team[position].win;
	//swap[swa].lose        =  team[position].lose;
	//swap[swa].lose        =  team[position].lose;
	////temp[i].PCT         =  team[position].PCT;
	//swap[swa].total       =  team[position].total;
	//swap[swa].RunsScore   =  team[position].RunsScore;
	//swap[swa].RunsAgainst =  team[position].RunsAgainst;
	//swap[swa].counter     =  team[position].counter;


	//team[position].teams       =  team[a].teams; //step 2 
	//team[position].win         =  team[a].win;
	//team[position].lose        =  team[a].lose;
	////team[position].PCT         =  team[a].PCT;
	//team[position].total       =  team[a].total;
	//team[position].RunsScore   =  team[a].RunsScore;
	//team[position].RunsAgainst =  team[a].RunsAgainst;
	//team[position].counter     =  team[a].counter;


	//team[a].teams       =  swap[swa].teams; //step 3 
	//team[a].win         =  swap[swa].win;
	//team[a].lose        =  swap[swa].lose;
	////team[a].PCT         =  temp[i].PCT;
	//team[a].total       =  swap[swa].total;
	//team[a].RunsScore   =  swap[swa].RunsScore;
	//team[a].RunsAgainst =  swap[swa].RunsAgainst;
	//team[a].counter     =  swap[swa].counter;

}//end of sort
