#include<stdio.h>
#include<string.h>
#include "color.h"

#define MAX_STUDENTS 100

typedef struct ca_evaluation{
    char first_name[20];
    char last_name[20];
    int reg_no;
    float total_marks;
    float marks;
}CA;

void login(int *Verify);
void create(CA *Stud, int *numstud);
void display(CA *Stud, int numstud);
void search(CA *Stud, int numstud);
void modify(CA *Stud, int numstud);
void del(CA *Stud, int *numstud);

int main() {
    int numStud=0; //Variable to count the entries of the Student in the database
    int choice; //To perform the operation
    int Verify=0; // variable to check if the password entered is correct or not
    CA Stud[MAX_STUDENTS];
    login(&Verify); // Login/Authentication
    if(Verify==1){
    do { 
    cyan();
        printf("\n\n");
        printf("------------------------------------\n");
        printf("\tCA Evalutor System\n");
        printf("------------------------------------\n");
        printf("\n1. Create Record\n");
        printf("2. Search Record\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Display Record\n");
        printf("6. Exit\n");
        purple();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        system("cls");
        switch(choice) {
            case 1:
                create(Stud, &numStud);
                break;
            case 2:
                search(Stud, numStud);
                break;
            case 3:
                modify(Stud, numStud);
                break;
            case 4:
                del(Stud, &numStud);
                break;
            case 5:
                display(Stud, numStud);
                break;
            case 6:
            	green();
                printf("Exiting Program. Thank You!\n");
                reset();
                break; 
            default:
                printf("Invalid Choice!\n");
                break;
        }
    }while(choice!=6);
}
	red();
    printf("You have successfully exited the program...\n\n");
    reset();
    return 0;
}

void login(int *Verify) {
    char password[15];
    blue();
    printf("\nEnter Password: ");
    scanf("%s",&password);
    system("cls");
    FILE *pass;
    pass=fopen("Password.txt","r");
    char myString[15];
    fgets(myString,15,pass); 
    fclose(pass);
    if (strcmp(password, myString) == 0) {
    	green();
        printf("Login Successful!\n\n");
        *Verify=1; //Value changed as pass is true
    } 
	else {
		red();
        printf("Wrong Password, Login Failed. Try Again!.\n");
		reset(); //else program is closed
    }
}

void create(CA *Stud, int *numstud) {
	if(*numstud >=100){
		system("cls");
		red();
		printf("Maximum number of students reached\n");
		reset();
		return;
	}
    CA new_student; // We are creating a new Struct to take all the details and will store the details at the end in the araay created
    char first[50];
	char last[50];
	yellow();
    printf("Enter First name : ");
    scanf("%s",first);
    printf("Enter Last name : ");
    scanf("%s",last);
    strcpy(new_student.first_name,first);
    strcpy(new_student.last_name,last);
    printf("Enter Registeration Number: ");
    scanf("%d",&new_student.reg_no);
    int z;
    for(z=0;z<*numstud;z++){ //Loop to verify if entered roll_no is not duplicate
    	if(Stud[z].reg_no==new_student.reg_no){
    		system("cls");
    		red();
    		printf("Sorry, Entered Registeration No. is already in existance!\nPlease Try Again.\n\n");
    		reset();
    		return;
		}
	}
	
    printf("Enter the Total Marks: ");
    scanf("%f",&new_student.total_marks);
    printf("Enter the Marks Obtained: ");
    scanf("%f",&new_student.marks);
    reset();
    if(new_student.marks>new_student.total_marks){
    	system("cls");
    	red();
    	printf("Sorry, Marks Obtained cannot be greater than Total Marks!\n");
    	reset();
	}
	else if(new_student.marks<0) {
		system("cls");
		red();
    	printf("Sorry, Marks Obtained cannot be negative!\n");
    	reset();
	}
	else{
    Stud[*numstud] = new_student;
    *numstud=*numstud+1;
    system("cls");
    green();
    printf("\nRecord added successfully!\n");
    reset();
}
}

void display(CA *Stud, int numstud) {
    if (numstud==0){ //Checking if there is a value or not
    	red();
        printf("Record List is Empty!\n");
        reset();
    }
    else{
    	green();
    printf("\nFull Name\t\tRegisteration No:\t\tTotal Marks\t\tMarks Obtained\n");
    // Loop for printing all the details of the Students
    reset();
    int i;
    for(i=0; i<numstud; i++) {
    	white();
        printf("%s %s\t\t%d\t\t\t%.2f\t\t\t%.2f\n", Stud[i].first_name,Stud[i].last_name, Stud[i].reg_no, Stud[i].total_marks,Stud[i].marks);
        reset();
    }
    }
    reset();
}

void search(CA *Stud, int numstud) {
	if (numstud==0){ 
		red();
        printf("Record List is Empty!\n");
        return;
        reset();
    }
int reg_no;
yellow();
int found = 0; // Variable to check if the name exists or not
printf("\nPlease Enter the Registeration No. of the Student to search: ");
scanf("%d", &reg_no);
int i;
reset();
system("cls");
green();
    for(i=0; i<numstud; i++) {
    if(Stud[i].reg_no==reg_no) {
        printf("\nRecord Found!\n");
        reset();
        white();
		printf("Full Name: %s %s\nRegisteration No.: %d\nTotal Marks: %.2f\nMarks Obtained: %.2f\n", Stud[i].first_name,Stud[i].last_name, Stud[i].reg_no, Stud[i].total_marks, Stud[i].marks);
        reset();
		found = 1;
        break;
    }
}
reset();
if(found==0) {
	red();
    printf("\nRecord not found!\n");
    reset();
}
}

void modify(CA *Stud, int numstud) {
	if (numstud==0){ 
	red();
        printf("Record List is Empty!\n");
        reset();
        return;
    }
int reg_no;
int found = 0; // Variable to check if the name exists or not
yellow();
printf("\nPlease Enter the Registeration No. of the Student to modify: ");
scanf("%d", &reg_no);
reset();
int i;
float new_marks;
system("cls");
for(i=0; i<numstud; i++) {
    if(Stud[i].reg_no==reg_no) {
    	green();
        printf("\nRecord Found!\n");
        reset();
        white();
		printf("Full Name: %s %s\nRegisteration No.: %d\nTotal Marks: %.2f\nMarks Obtained: %.2f\n", Stud[i].first_name,Stud[i].last_name, Stud[i].reg_no, Stud[i].total_marks, Stud[i].marks);
        reset();
        blue();
		printf("\nEnter Marks to edit: ");
        scanf("%f", &new_marks);
        reset();
        if(new_marks>Stud[i].total_marks){
    	system("cls");
    	red();
    	printf("Sorry, Marks Obtained cannot be greater than Total Marks!\n");
    	reset();
    	return;
	}
	else if(new_marks<0) {
		system("cls");
		red();
    	printf("Sorry, Marks Obtained cannot be negative!\n");
    	reset();
    	return;
	}
	else{
		Stud[i].marks=new_marks;
		system("cls");
		green();
        printf("\nRecord updated successfully!\n");
        reset();
        found = 1;
        break;
    }
}
}
if(found==0) {
	red();
    printf("\nRecord not found!\n");
    reset();
}
}

void del(CA *Stud, int *numstud) {
	if (*numstud==0){ 
		red();
        printf("Record List is Empty!\n");
        reset();
        return;
    }
int reg_no,found=0;
yellow();
printf("\nPlease Enter the Registeration No. of the Student to delete: ");
scanf("%d", &reg_no);
int i;
reset();
system("cls");
for(i=0; i<*numstud; i++) {
    if(Stud[i].reg_no==reg_no) {
    	green();
        printf("\nRecord Found!");
        white();
		printf("\nFull Name: %s %s\nRegisteration No.: %d\nTotal Marks: %.2f\nMarks Obtained: %.2f\n", Stud[i].first_name,Stud[i].last_name, Stud[i].reg_no, Stud[i].total_marks, Stud[i].marks);
        reset();
		int j;
        reset();
        for(j=i; j<(*numstud)-1; j++) {
            Stud[j] = Stud[j+1];
        }
        *numstud=*numstud-1;
        green();
        printf("\nRecord deleted successfully!\n");
        reset();
        found = 1;
        break;
    }
}
if(found==0) {
	system("cls");
	red();
    printf("\nRecord not found!\n");
    reset();
}
}

