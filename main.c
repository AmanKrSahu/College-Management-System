//Header Files used in project
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structure datatype; named Student to manage data of Student
typedef struct Student{
    char Enrollment_Number[20];
    char Student_Name[30];
    char Address[50];
    int Mobile;
}Student;

//Structure datatype; named Course to manage the Courses available 
typedef struct Course{
    char Course_Code[10];
    char Course_Name[30];
}Course;

//Structure datatype; named Club to manage the Clubs available
typedef struct Club{
    char name[20];
}Club; 

//Structure datatype; named Academic_Performance to manage Academic Performance of Students
typedef struct Academic_Performance{
    char Enrollment_Number[20];
    char Student_Name[30];
    int Marks_Obtained;
    float CGPA;
}Academic_Performance;

//Structure datatype; named Lecture_Schedule to manage Lecture Schedule of Students
typedef struct Lecture_Schedule{
    char Timings[20];
    char Subject[30];
}Lecture_Schedule;

//Function to create a temporary file; to be used while removing records from csv files
void Temp_File(char filename[], char data[]){
    FILE *fptr = NULL, *temp_fptr = NULL;
    fptr = fopen(filename, "r+");
    temp_fptr = fopen("temp.txt","a+");
    char line[50], temp_line[50];
    while(fgets(line, sizeof(line), fptr)!=NULL){
        strcpy(temp_line,line);
        char *token = strtok(line, ",");
        if(strcmp(token,data)!=0){
            fprintf(temp_fptr,"%s",temp_line);
        }
    }
    fclose(fptr);
    fclose(temp_fptr);
}

//Function to create a temporary file; to be used while removing records from Clubs.csv file
void Temp_File_Club(char filename[], char data[]){
    FILE *fptr = NULL, *temp_fptr = NULL;
    fptr = fopen(filename, "r+");
    temp_fptr = fopen("temp.txt","a+");
    char line[50], temp_line[50];
    while(fgets(line, sizeof(line), fptr)!=NULL){
        strcpy(temp_line,line);
        char *token = strtok(line, "\n");
        if(strcmp(token,data)!=0){
            fprintf(temp_fptr,"%s",temp_line);
        }
    }
    fclose(fptr);
    fclose(temp_fptr);
}

//Function to display, add & remove data of Students in Students.csv
void func_Student(char var[]){
    if(strcmp(var,"Display")==0){ //Condition to display data in Students.csv
        FILE *fptr = NULL;
        fptr = fopen("Student.csv", "r");
        if (fptr==NULL){
            printf("The file doesn't exist!!\n");
        }
        else{
            char line[50];
            printf("The list of students are: \n");
            while(fgets(line, sizeof(line), fptr)!=NULL){
                char *token = strtok(line, ",");
                while(token!=NULL){
                    printf("%-15s", token);
                    token = strtok(NULL, ",");
                }
                printf("\n");
            }
        }
        fclose(fptr);
    }
    else if(strcmp(var,"Add")==0){ //Condition to add data in Students.csv
        FILE *fptr = NULL;
        fptr = fopen("Student.csv", "a");
        int num;
        printf("Enter the number of participants you want to enter: ");
        scanf("%d", &num);
        Student *ptr = NULL;
        ptr = (Student*)calloc(num,sizeof(Student));
        for(int i=0; i<num; i++){
            fflush(stdin);
            printf("Enter the Enrollment Number: ");
            gets((ptr+i)->Enrollment_Number);
            fflush(stdin);
            printf("Enter the Student's Name: ");
            gets((ptr+i)->Student_Name);
            fflush(stdin);
            printf("Enter the Student's Address: ");
            gets((ptr+i)->Address);
            fflush(stdin);
            printf("Enter the Student's Mobile Nos: ");
            scanf("%d", &(ptr+i)->Mobile);
            fprintf(fptr,"%s,%s,%s,%d\n", (ptr+i)->Enrollment_Number, (ptr+i)->Student_Name, (ptr+i)->Address, (ptr+i)->Mobile);
        }
        fflush(stdin);
        free(ptr);
        fclose(fptr);
    }
    else{ //Condition to remove a record a Student.csv
        char data[20];
        printf("Enter the Enrollment No of the Student: ");
        gets(data);
        Temp_File("Student.csv",data);
        FILE *fptr = NULL, *temp_fptr = NULL;
        fptr = fopen("Student.csv", "w");
        temp_fptr = fopen("temp.txt","r");
        char line[50];
        while(fgets(line, sizeof(line), temp_fptr)!=NULL){
            fprintf(fptr,"%s",line);
        }
        fclose(fptr);
        fclose(temp_fptr);
        remove("temp.txt");
    }
}

//Function to display, add & remove data of Course Lists in Course.csv
void func_Manage_Course(char var[]){
    if(strcmp(var,"Display")==0){ //Condition to display data in Course.csv
        FILE *fptr = NULL;
        fptr = fopen("Course.csv", "r");
        if (fptr==NULL){
            printf("The file doesn't exist!!\n");
        }
        else{
            char line[50];
            printf("The list of Courses are: \n");
            while(fgets(line, sizeof(line), fptr)!=NULL){
                char *token = strtok(line, ",");
                while(token!=NULL){
                    printf("%-15s", token);
                    token = strtok(NULL, ",");
                }
                printf("\n");
            }
        }
        fclose(fptr);
    }
    else if(strcmp(var,"Add")==0){ //Condition to add data in Course.csv
        FILE *fptr = NULL;
        fptr = fopen("Course.csv", "a");
        int num;
        printf("Enter the number of courses you want to enter: ");
        scanf("%d", &num);
        Course *ptr = NULL;
        ptr = (Course*)calloc(num,sizeof(Course));
        for(int i=0; i<num; i++){
            fflush(stdin);
            printf("Enter the course code: ");
            gets((ptr+i)->Course_Code);
            fflush(stdin);
            printf("Enter the course name: ");
            gets((ptr+i)->Course_Name);
            fprintf(fptr, "%s,%s\n", (ptr+i)->Course_Code, (ptr+i)->Course_Name);
        }
        free(ptr);
        fclose(fptr);
    }
    else{ //Condition to remove a record a Course.csv
        char data[20];
        printf("Enter the Course Code: ");
        gets(data);
        Temp_File("Course.csv",data);
        FILE *fptr = NULL, *temp_fptr = NULL;
        fptr = fopen("Course.csv", "w");
        temp_fptr = fopen("temp.txt","r");
        char line[50];
        while(fgets(line, sizeof(line), temp_fptr)!=NULL){
            fprintf(fptr,"%s",line);
        }
        fclose(fptr);
        fclose(temp_fptr);
        remove("temp.txt");
    }
}

//Function to display, add & remove data of Clubs in Clubs.csv
void func_Club_Management(char var[]){
    if(strcmp(var,"Display")==0){ //Condition to display data in Clubs.csv
        FILE *fptr = NULL;
        fptr = fopen("Clubs.csv", "r");
        if (fptr==NULL){
            printf("The file doesn't exist!!\n");
        }
        else{
            char line[20];
            printf("The list of Clubs are: \n");
            while(fgets(line, sizeof(line), fptr)){
                printf("%s", line);
            }
        }
        fclose(fptr);
    }
    else if(strcmp(var,"Add")==0){ //Condition to add data in Clubs.csv
        FILE *fptr = NULL;
        fptr = fopen("Clubs.csv", "a");
        int num;
        printf("Enter the number of clubs you want to enter: ");
        scanf("%d", &num);
        Club *ptr = NULL;
        ptr = (Club*)malloc(num*sizeof(Club));
        for(int i=0; i<num; i++){
            fflush(stdin);
            printf("Enter the name of the club: ");
            gets((ptr+i)->name);
            fprintf(fptr,"%s\n",(ptr+i)->name);
        }
        fflush(stdin);
        free(ptr);
        fclose(fptr);
    }
    else{ //Condition to remove a record a Clubs.csv
        char data[20];
        printf("Enter the name of the Club: ");
        gets(data);
        Temp_File_Club("Clubs.csv",data);
        FILE *fptr = NULL, *temp_fptr = NULL;
        fptr = fopen("Clubs.csv", "w");
        temp_fptr = fopen("temp.txt","r");
        char line[50];
        while(fgets(line, sizeof(line), temp_fptr)!=NULL){
            fprintf(fptr,"%s",line);
        }
        fclose(fptr);
        fclose(temp_fptr);
        remove("temp.txt");
    }
}

//Function to display, add & remove data of Student's Academic Performance in Academic_Performance.csv
void func_Academic_Performance(char var[]){
    if(strcmp(var,"Display")==0){ //Condition to display data in Academic_Performance.csv
        FILE *fptr = NULL;
        fptr = fopen("Academic_Performance.csv", "r");
        if (fptr==NULL){
            printf("The file doesn't exist!!\n");
        }
        else{
            char line[50];
            printf("The academic performances of students are: \n");
            while(fgets(line, sizeof(line), fptr)!=NULL){
                char *token = strtok(line, ",");
                while(token!=NULL){
                    printf("%-20s", token);
                    token = strtok(NULL, ",");
                }
                printf("\n");
            }
        }
        fclose(fptr);
    }
    else if(strcmp(var,"Add")==0){ //Condition to add data in Academic_Performance.csv
        FILE *fptr = NULL;
        fptr = fopen("Academic_Performance.csv", "a");
        int num;
        printf("Enter the number of participants you want to enter: ");
        scanf("%d", &num);
        Academic_Performance *ptr = NULL;
        ptr = (Academic_Performance*)calloc(num,sizeof(Academic_Performance));
        for(int i=0; i<num; i++){
            fflush(stdin);
            printf("Enter the Enrollment Number: ");
            gets((ptr+i)->Enrollment_Number);
            fflush(stdin);
            printf("Enter the Student's Name: ");
            gets((ptr+i)->Student_Name);
            fflush(stdin);
            printf("Enter the Total Marks Obtained by the Student: ");
            scanf("%d", &(ptr+i)->Marks_Obtained);
            printf("Enter the CGPA Obtained by the Student: ");
            scanf("%f", &(ptr+i)->CGPA);
            fprintf(fptr,"%s,%s,%d,%0.1f\n", (ptr+i)->Enrollment_Number, (ptr+i)->Student_Name, (ptr+i)->Marks_Obtained, (ptr+i)->CGPA);
        }
        fflush(stdin);
        free(ptr);
        fclose(fptr);
    }
    else{ //Condition to remove a record a Academic_Performance.csv
        char data[20];
        printf("Enter the Enrollment No of the Student: ");
        gets(data);
        Temp_File("Academic_Performance.csv",data);
        FILE *fptr = NULL, *temp_fptr = NULL;
        fptr = fopen("Academic_Performance.csv", "w");
        temp_fptr = fopen("temp.txt","r");
        char line[50];
        while(fgets(line, sizeof(line), temp_fptr)!=NULL){
            fprintf(fptr,"%s",line);
        }
        fclose(fptr);
        fclose(temp_fptr);
        remove("temp.txt");
    }
}

//Function to display, add & remove data of Lecture Schedules in Lecture_Schedule.csv
void func_Lecture_Schedule(char var[]){
    if(strcmp(var,"Display")==0){ //Condition to display data in Lecture_Schedule.csv
        FILE *fptr = NULL;
        fptr = fopen("Lecture_Schedule.csv", "r");
        if (fptr==NULL){
            printf("The file doesn't exist!!\n");
        }
        else{
            char line[50];
            printf("The Schedule of Lectures are: \n");
            while(fgets(line, sizeof(line), fptr)!=NULL){
                char *token = strtok(line, ",");
                while(token!=NULL){
                    printf("%-15s", token);
                    token = strtok(NULL, ",");
                }
                printf("\n");
            }
        }
        fclose(fptr);
    }
    else if(strcmp(var,"Add")==0){ //Condition to add data in Lecture_Schedule.csv
        FILE *fptr = NULL;
        fptr = fopen("Lecture_Schedule.csv", "a");
        int num;
        printf("Enter the number of Lectures you want to enter: ");
        scanf("%d", &num);
        Lecture_Schedule *ptr = NULL;
        ptr = (Lecture_Schedule*)calloc(num,sizeof(Lecture_Schedule));
        for(int i=0; i<num; i++){
            fflush(stdin);
            printf("Enter the timings: ");
            gets((ptr+i)->Timings);
            fflush(stdin);
            printf("Enter the subject: ");
            gets((ptr+i)->Subject);
            fprintf(fptr, "%s,%s\n", (ptr+i)->Timings, (ptr+i)->Subject);
        }
        fflush(stdin);
        free(ptr);
        fclose(fptr);
    }
    else{ //Condition to remove a record a Lecture_Schedule.csv
        char data[20];
        printf("Enter the Timings: ");
        gets(data);
        Temp_File("Lecture_Schedule.csv",data);
        FILE *fptr = NULL, *temp_fptr = NULL;
        fptr = fopen("Lecture_Schedule.csv", "w");
        temp_fptr = fopen("temp.txt","r");
        char line[50];
        while(fgets(line, sizeof(line), temp_fptr)!=NULL){
            fprintf(fptr,"%s",line);
        }
        fclose(fptr);
        fclose(temp_fptr);
        remove("temp.txt");
    }
}

//Main Function
int main(){
    //Welcome statement
    printf("===================================================================\n");
    printf("WELCOME TO COLLEGE MANAGEMENT SYSTEM\n");
    printf("===================================================================\n");

    //Module Label to navigate through Admin, Student & Exit Module
    Modules:
        printf("Select a module: \n 1.Admin \n 2.Student \n 3.Exit\n");
        printf("===================================================================\n");
        char Modules[10];
        printf("Enter the name of the Module: ");
        gets(Modules);
        if(strcmp(Modules,"Admin")==0){
            goto Admin;
        }
        else if(strcmp(Modules,"Student")==0){
            goto Student;
        }
        else{
            goto Exit;
        }

    //Admin Label to navigate Operations present in Admin Module
    //1.Manage Student 2.Manage Course 3.Club Management 4.Academic Performance 5.Lecture Schedule 6.Exit
    Admin:
        printf("Select a Operation: \n 1.Manage Student \n 2.Manage Course \n 3.Club Management \n 4.Academic Performance \n 5.Lecture Schedule \n 6.Exit\n");
        printf("===================================================================\n");
        char Admin[30];
        printf("Enter the name of the Operation: ");
        gets(Admin);

        if(strcmp(Admin,"Manage Student")==0){
            //Manage_Student Label to navigate Operations present in Manage Student Operation
            //1.Display 2.Add 3.Remove 4.Exit
            Manage_Student:
                printf("Select a Operation: \n 1.Display \n 2.Add \n 3.Remove\n 4.Exit\n");
                printf("===================================================================\n");
                char Manage_Student[10];
                printf("Enter the name of the Operation: ");
                gets(Manage_Student);
                if(strcmp(Manage_Student,"Display")==0){
                    func_Student(Manage_Student);
                    printf("===================================================================\n");
                    goto Manage_Student;
                }
                else if(strcmp(Manage_Student,"Add")==0){
                    func_Student(Manage_Student);
                    printf("===================================================================\n");
                    goto Manage_Student;
                }
                else if(strcmp(Manage_Student,"Remove")==0){
                    func_Student(Manage_Student);
                    goto Manage_Student;
                }
                else{
                    goto Admin; //To exit from Operation-->Manage Student
                }
        }

        else if(strcmp(Admin,"Manage Course")==0){
            //Manage_Course Label to navigate Operations present in Manage Course Operation
            //1.Display 2.Add 3.Remove 4.Exit
            Manage_Course:
                printf("Select a Operation: \n 1.Display \n 2.Add \n 3.Remove\n 4.Exit\n");
                printf("===================================================================\n");
                char Manage_Course[10];
                printf("Enter the name of the Operation: ");
                gets(Manage_Course);
                if(strcmp(Manage_Course,"Display")==0){
                    func_Manage_Course(Manage_Course);
                    printf("===================================================================\n");
                    goto Manage_Course;
                }
                else if(strcmp(Manage_Course,"Add")==0){
                    func_Manage_Course(Manage_Course);
                    printf("===================================================================\n");
                    goto Manage_Course;
                }
                else if(strcmp(Manage_Course,"Remove")==0){
                    func_Manage_Course(Manage_Course);
                    goto Manage_Course;
                }
                else{
                    goto Admin; //To exit from Operation-->Manage Course
                }
        }

        else if(strcmp(Admin,"Club Management")==0){
            //Club_Management Label to navigate Operations present in Club Management Operation
            //1.Display 2.Add 3.Remove 4.Exit
            Club_Management:
                printf("Select a Operation: \n 1.Display \n 2.Add \n 3.Remove\n 4.Exit\n");
                printf("===================================================================\n");
                char Club_Management[10];
                printf("Enter the name of the Operation: ");
                gets(Club_Management);
                if(strcmp(Club_Management,"Display")==0){
                    func_Club_Management(Club_Management);
                    printf("===================================================================\n");
                    goto Club_Management;
                }
                else if(strcmp(Club_Management,"Add")==0){
                    func_Club_Management(Club_Management);
                    printf("===================================================================\n");
                    goto Club_Management;
                }
                else if(strcmp(Club_Management,"Remove")==0){
                    func_Club_Management(Club_Management);
                    goto Club_Management;
                }
                else{
                    goto Admin; //To exit from Operation-->Club Management
                }
        }

        else if(strcmp(Admin,"Academic Performance")==0){
            //Academic_Performance Label to navigate Operations present in Academic Performance Operation
            //1.Display 2.Add 3.Remove 4.Exit
            Academic_Performance:
                printf("Select a Operation: \n 1.Display \n 2.Add \n 3.Remove\n 4.Exit\n");
                printf("===================================================================\n");
                char Academic_Performance[10];
                printf("Enter the name of the Operation: ");
                gets(Academic_Performance);
                if(strcmp(Academic_Performance,"Display")==0){
                    func_Academic_Performance(Academic_Performance);
                    printf("===================================================================\n");
                    goto Academic_Performance;
                }
                else if(strcmp(Academic_Performance,"Add")==0){
                    func_Academic_Performance(Academic_Performance);
                    printf("===================================================================\n");
                    goto Academic_Performance;
                }
                else if(strcmp(Academic_Performance,"Remove")==0){
                    func_Academic_Performance(Academic_Performance);
                    goto Academic_Performance;
                }
                else{
                    goto Admin; //To exit from Operation-->Academic Performance
                }
        }

        else if(strcmp(Admin,"Lecture Schedule")==0){
            //Lecture Label to navigate Operations present in Lecture Operation
            //1.Display 2.Add 3.Remove 4.Exit
            Lecture:
                printf("Select a Operation: \n 1.Display \n 2.Add \n 3.Remove\n 4.Exit\n");
                printf("===================================================================\n");
                char Schedule[10];
                printf("Enter the name of the Operation: ");
                gets(Schedule);
                if(strcmp(Schedule,"Display")==0){
                    func_Lecture_Schedule(Schedule);
                    printf("===================================================================\n");
                    goto Lecture;
                }
                else if(strcmp(Schedule,"Add")==0){
                    func_Lecture_Schedule(Schedule);
                    printf("===================================================================\n");
                    goto Lecture;
                }
                else if(strcmp(Schedule,"Remove")==0){
                    func_Lecture_Schedule(Schedule);
                    goto Lecture;
                }
                else{
                    goto Admin; //To exit from Operation-->Lecture Schedule
                }
        }

        else{
            goto Modules; //To exit from Admin Module
        }

    //Student Label to navigate Operations present in Student Module
    //1.Subject List 2.Lecture Schedule 3.Club List 4.Academic Performance 5.Exit
    Student:
        printf("Select a Operation: \n 1.Subject List \n 2.Lecture Schedule \n 3.Club List \n 4.Academic Performance \n 5.Exit\n");
        printf("===================================================================\n");
        char Student[30];
        printf("Enter the name of the Operation: ");
        gets(Student);

        if(strcmp(Student,"Subject List")==0){
            func_Manage_Course("Display");
            printf("===================================================================\n");
            goto Student;
        }

        else if(strcmp(Student,"Lecture Schedule")==0){
            func_Lecture_Schedule("Display");
            printf("===================================================================\n");
            goto Student;
        }

        else if(strcmp(Student,"Club List")==0){
            func_Club_Management("Display");
            printf("===================================================================\n");
            goto Student;
        }

        else if(strcmp(Student,"Academic Performance")==0){
            func_Academic_Performance("Display");
            printf("===================================================================\n");
            goto Student;
        }

        else{
            goto Modules; //To Exit from Student Module
        }
    
    //Exit Label to stop working
    Exit:
    return 0;
}
