//Payroll Program 
//
//
//  I can take out previous info but not whole thing 
//
//
//
// Shin Nagai 
// With Happy Teammates 

/*Things I needto work on: 

+ Binary file

+ Loading previous infomation*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define flush fflush(stdin)
#define cls system ("cls")
#define pause system ("pause")
#define SIZE 20

// struct
typedef struct {
	char name[20];
	int day;
	int month;
	int year;
	int hourlyRate;
	int workedHour;
	int overTime;
	int regularPay;
	int grossPay;
} PAYROLL;

//function prototype
int mainMenu();
void getPaid(PAYROLL *payday[],int *flag,int *counter);//pass by pointer
void display(PAYROLL *payday,int flag,int counter);//passing the copy of getPaid
void payDate(PAYROLL payday[],int counter);
void payDateRange(PAYROLL payday[], int counter);


main(){
	FILE *filePointer;
	int choice=0,flag=0,counter=0;

	PAYROLL payday[SIZE];

	payday[0].name[20]='\0';
	payday[0].day=0;
	payday[0].month=0;
	payday[0].year=0;
	payday[0].hourlyRate=0;
	payday[0].workedHour=0;
	payday[0].overTime=0;
	payday[0].regularPay=0;
	payday[0].grossPay=0;
	
   
	
	filePointer = fopen("c:\\payroll.bin", "rb");
	fread(&payday,sizeof(PAYROLL), 1, filePointer);
    fclose(filePointer);



	do{
		cls;
		choice=mainMenu();
		switch(choice){
		case 1:
			cls;
			getPaid(&payday[0],&flag,&counter);
			break;
		case 2:
			payDate(&payday[0],counter);
			break;
		case 3:
			cls;
			display(&payday[0],flag,counter);// dont know why i cant pass just copy of getPaid. have to use pointer 
			pause;
			break;
		case 4:
			payDateRange(&payday[0],counter);
			break;
		case 5:
			printf("see you\n\n");
			pause;
		}//end of switch

	}while (choice!=5);
}//End of main

int  mainMenu(){
	int i =0;
	printf("1) Add payroll info\n");
	printf("2) Display payroll for a pay date  \n");
	printf("3) Dispaly payroll info for all emloyees on a pay date \n");
	printf("4) Display totalpayroll for a companyy by a pay date range\n");
	printf("5) Quit\n");
	scanf("%i",&i);
	flush;
	return i;
}//End of mainMenu

void getPaid(PAYROLL *payday,int *flag,int *counter){
	int i;
	
  FILE *filePointer;
  filePointer= fopen("c:\\payroll.bin", "wb");

   if(filePointer ==NULL){
      printf("couldn't create a file\n");
      pause;
     }//end of if

	for(i=0;i<1;i++){

		printf("\tEnter your name:");
		scanf("%s",payday[*counter].name);
		flush;
		printf("\tEnter your day of Payday :");
		scanf("%i",&payday[*counter].day);
		flush;
		printf("\tEnter your month of Payday :");
		scanf("%i",&payday[*counter].month);
		flush;
		printf("\tEnter your year of Payday :");
		scanf("%i",&payday[*counter].year);
		flush;
		printf("\tEnter your Hourly rate :");
		scanf("%i",&payday[*counter].hourlyRate);
		flush;
		printf("\tEnter your Worked hours :");
		scanf("%i",&payday[*counter].workedHour);
		flush;
		if(41 <= payday[*counter].workedHour){
			payday[*counter].overTime=(payday[*counter].workedHour-40)*(1.5*payday[*counter].hourlyRate);
			payday[*counter].regularPay= 40*payday[*counter].hourlyRate;//calucurate gross pay 
			payday[*counter].grossPay=payday[*counter].regularPay+payday[*counter].overTime;//calucurate grosspay
			//Asumming that Overtime paymanet is 1.5 of hourlyrate
		}//end of if 
		if(40 >= payday[*counter].workedHour){
			payday[*counter].overTime=0;
			payday[*counter].regularPay=payday[*counter].workedHour*payday[*counter].hourlyRate;//calucurate gross pay 
			payday[*counter].grossPay=payday[*counter].regularPay+payday[*counter].overTime;//calucurate grosspay
		}
	}//end of for
	fwrite(payday,sizeof(PAYROLL), 1, filePointer);
	fclose(filePointer);
	*flag=1;
	*counter=*counter+1;
}//End of gerPaid

void display(PAYROLL *payday,int flag,int counter){
	int i;
	cls;
	//if(flag ==1){
		for(i=0;i<counter;i++){
			printf("++++++++++++++++++++++++++++++++++++++++\n");
			printf("\t%s\n",payday[i].name);
			printf("\tPayday         %i/%i/%i\n",payday[i].month,payday[i].day,payday[i].year);
			printf("\tHours worked   :%ihr\n",payday[i].workedHour);
			printf("\tHourly rate    $%i\n",payday[i].hourlyRate);
			printf("\tregular pay    $%i\n",payday[i].regularPay); 
			printf("\tOver time pay  $%i\n",payday[i].overTime);
			printf("\tGross pay      $%i\n",payday[i].grossPay);
			printf("++++++++++++++++++++++++++++++++++++++++\n\n\n");
		}//End of for 
	//}//End of flag

	//else
		//printf("Enter infor first\n\n");

}//end of display


void payDate(PAYROLL payday[],int counter){
	int a=0,b=0,c=0,i=0,FLAG=0;

	cls;
	printf("Enter a date that you want to check\n");
	printf("\tEnter your day of Payday :");
	scanf("%i",&a);
	flush;
	printf("\tEnter your month of Payday :");
	scanf("%i",&b);
	flush;
	printf("\tEnter your year of Payday :");
	scanf("%i",&c);

	for(i=0;i<=counter;i++){

		if((a == payday[i].day) && (b == payday[i].month) && (c ==payday[i].year)){

			printf("++++++++++++++++++++++++++++++++++++++++\n");
			printf("\t%s\n",payday[i].name);
			printf("\tPayday         %i/%i/%i\n",payday[i].month,payday[i].day,payday[i].year);
			printf("\tHours worked   :%ihr\n",payday[i].workedHour);
			printf("\tHourly rate    $%i\n",payday[i].hourlyRate);
			printf("\tregular pay    $%i\n",payday[i].regularPay); 
			printf("\tOver time pay  $%i\n",payday[i].overTime);
			printf("\tGross pay      $%i\n\n",payday[i].grossPay);
			printf("++++++++++++++++++++++++++++++++++++++++\n\n");
			FLAG=1;//FLAG gets 1 for the if statement down below
		}//end of if

	}//endo of for

	if(FLAG==0){
		cls;
		printf("\tNo Date on %i/%i/%i\n\n",b,a,c);
	}//end of FLAG


	pause;
}//End of payDate

void payDateRange(PAYROLL payday[], int counter){

	int a=0,b=0,c=0,i=0,FLAG=0;
	int total=0,flag=0;
	cls;
	printf("Enter a date that you want to check\n");
	printf("\tEnter your day of Payday :");
	scanf("%i",&a);
	flush;
	printf("\tEnter your month of Payday :");
	scanf("%i",&b);
	flush;
	printf("\tEnter your year of Payday :");
	scanf("%i",&c);
	for(i=0;i<=counter;i++){

		if((a == payday[i].day) && (b == payday[i].month) && (c ==payday[i].year)){

			total=total+payday[i].grossPay;
			flag=1;
		}//end of if 
	}//End of payDateRange

	if(flag==1){
		cls;
		printf("\t++++++++++++++++++++++++++++++++++++++++\n");
		printf("\t   Total Gross pay on %i/%i/%i is $%i\n",b,a,c,total);
		printf("\t++++++++++++++++++++++++++++++++++++++++\n");
		pause;
	}//end of if 
	else{
		cls;
		printf("\tNo date on %i/%i/%i\n\n",b,a,c);
		pause;
	}//end of else

}//End of payDateRange
