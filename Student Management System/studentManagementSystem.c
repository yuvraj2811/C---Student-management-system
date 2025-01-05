#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

typedef struct Student
{
    int id;
    char name[20];
    int age;
    char course[30];
    char enrolledStatus[10];
} Student;

Student std;
int userCount=0;

void addStudent();
void allStudentDetails();
void searchById();
void updateById();
void deleteById();
void enrolledStatusById();

FILE *fp;


int main()
{

    int ch;

    while (1)
    {
        system("cls");
        printf("<== School Management System==>\n");
        printf("1. Add Student\n");
        printf("2.All Student Info\n");
        printf("3.Student Search by Id\n");
        printf("4.Update Student\n");
        printf("5.Delete Student\n");
        printf("6.Enrolled Status\n");
        printf("0.Exit\n");
        printf("Enter your choice\n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            exit(0);

        case 1:
            addStudent();
            break;

        case 2:
           allStudentDetails();
           break;
        case 3:
           searchById();
           break;
        case 4:
           updateById();
           break;
        case 5:
           deleteById();
           break;
        case 6:
           enrolledStatusById();
           break;
          default:
           printf("Enter a valid number\n");
        }
        printf("\nPress any key to continue\n");
        getch();
    }

    return 0;
}

void addStudent()
{
 
    fp = fopen("Student.txt", "a");
   
   printf("Enter the Student Id :\n");
   scanf("%d",&std.id);
    getchar();

    printf("Enter  Student  Name: \n");
    scanf("%[^\n]s",std.name);
    getchar();


    printf("Enter the Student Age :\n");
    scanf("%d",&std.age);
    getchar();

    printf("Enter the Student Course :\n");
    scanf("%[^\n]s",std.course);
    getchar();

    printf("Enter Enrollment Status\n");
    scanf("%[^\n]s",std.enrolledStatus);
    getchar();


   fprintf(fp, "%-10d%-30s%-10d%-30s%-20s\n", std.id, std.name, std.age, std.course, std.enrolledStatus);

    printf("Record Saved Successfully...");
    fclose(fp);
}

void allStudentDetails(){

fp = fopen("Student.txt", "r"); 

    if (fp == NULL) {
        printf("Error file not find\n");
        return;
    }

    char c[50]; 

    printf("                           <== All Student Details ==>\n\n");

    

    while (fgets(c, 50, fp)) {
        printf("%s", c); 
    }

    fclose(fp);
}

void searchById(){
    printf("Enter student id\n");
    int id ; 
    scanf("%d",&id);
    getchar(); 
    fp=fopen("Student.txt","r");
    char line[100];
    while (fgets(line, 100, fp)) {
        int studentId;
        sscanf(line, "%d", &studentId);
        if (studentId == id) {
            printf("%-10s%-30s%-10s%-30s%-20s\n", "Id", "Name", "Age", "Course", "Enrolled");
            printf("%s", line);
            fclose(fp);
            return;
        }
    }
    printf("Student id is not found\n");
    fclose(fp);
}


void updateById() {
    printf("Enter student id to update:\n");
    int id;
    scanf("%d", &id);
    getchar();  // Clear the newline character left by scanf

    FILE *fp = fopen("Student.txt", "r");  // Open file for reading
    if (fp == NULL) {
        printf("Error opening the file for reading.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");  // Open a temporary file for writing
    if (temp == NULL) {
        printf("Error opening the temporary file for writing.\n");
        fclose(fp);
        return;
    }

    char line[100];
    int found = 0;

    // Read each line from the original file
    while (fgets(line, sizeof(line), fp)) {
        int studentId;
        sscanf(line, "%d", &studentId);  

        if (studentId == id) {
            found = 1;

            
            printf("Enter new name: ");
            char name[30];
            fgets(name, sizeof(name), stdin);  
            name[strcspn(name, "\n")] = 0;  // Remove trailing newline

            printf("Enter new age: ");
            int age;
            scanf("%d", &age);
            getchar();  // Clear the newline character left by scanf

            printf("Enter new course: ");
            char course[50];
            fgets(course, sizeof(course), stdin);  
            course[strcspn(course, "\n")] = 0;  

            printf("Enter new enrollment status: ");
            char enrolledStatus[20];
            fgets(enrolledStatus, sizeof(enrolledStatus), stdin);  
            enrolledStatus[strcspn(enrolledStatus, "\n")] = 0;  

            
            fprintf(temp, "%-10d%-30s%-10d%-30s%-20s\n", id, name, age, course, enrolledStatus);
        } else {
            // If the record doesn't match the id, write the original line to the temp file
            fprintf(temp, "%s", line);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        
        remove("Student.txt");
        rename("temp.txt", "Student.txt");
        printf("Record updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("Student ID not found!\n");
    }
}

void deleteById() {
    printf("Enter student id to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();  

    fp = fopen("Student.txt", "r");  
    if (fp == NULL) {
        printf("Error opening the file for reading.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");  
    if (temp == NULL) {
        printf("Error opening the temporary file for writing.\n");
        fclose(fp);
        return;
    }

    char line[100];
    int found = 0;

    
    while (fgets(line, sizeof(line), fp)) {
        int studentId;
        sscanf(line, "%d", &studentId);  

        if (studentId == id) {
            
            found = 1;
            printf("Record with ID %d deleted successfully.\n", id);
        } else {
            // If the ID does not match, copy the line to the temporary file
            fprintf(temp, "%s", line);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        // Replace the original file with the updated one
        remove("Student.txt");
        rename("temp.txt", "Student.txt");
    } else {
        remove("temp.txt");
        printf("Student ID not found!\n");
    }
}

void enrolledStatusById() {
    printf("Enter student id to check enrollment status:\n");
    int id;
    scanf("%d", &id);
    getchar();  

     fp = fopen("Student.txt", "r");  
    if (fp == NULL) {
        printf("Error opening the file for reading.\n");
        return;
    }

    char line[100];
    int found = 0;

    
    while (fgets(line, sizeof(line), fp)) {
        int studentId;
        sscanf(line, "%d", &studentId);  

        if (studentId == id) {
            found = 1;

            
            char name[30], course[50], enrolledStatus[20];
            int age;

            
            sscanf(line, "%d %[^\n] %[^\n] %d %[^\n]", &studentId, name, course, &age, enrolledStatus);

            // Display the enrollment status
            printf("Student ID: %d\n", id);
            printf("Name: %s\n", name);
            printf("Enrollment Status: %s\n", enrolledStatus);
            fclose(fp);
            return;
        }
    }

    if (!found) {
        printf("Student ID %d not found!\n", id);
    }

    fclose(fp);
}