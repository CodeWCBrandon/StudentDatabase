#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "data.cpp"

//--------------------- ALL THE FUNCTION DECLARATION --------------------
void AddStudent();
void CheckStudentRecord();
bool CheckValidityInt(const char* value);
bool CheckValidityGPA(const char* value);
void DeleteRecord();
void SearchStudent();
void Menu();
//--------------------- END OF THE FUNCTION DECLARATION -------------------



void Menu()
{
    //clear everything at the start of the program
    system("cls");

    int choice = 0;
    while(choice != 5)
    {
        printf("\t\t\t====STUDENT DATABASE====\n");
        printf("\n\n\n\t\t\t 1. Add Student Record\n");
        printf("\t\t\t 2. Student Record\n");
        printf("\t\t\t 3. Search Student\n");
        printf("\t\t\t 4. Delete Record\n");
        printf("\t\t\t 5. Exit\n");
        printf("\t\t\t ------------------------\n\n");
        printf("Choose Option: ");
        scanf("%d", &choice); getchar();   

        
        switch(choice)
        {
            case 1:
                system("cls");
                AddStudent();
                system("cls");
                break;
            case 2:
                system("cls");
                CheckStudentRecord();
                system("cls");
                break;
            case 3:
                system("cls");
                SearchStudent();
                system("cls");
                break;
            case 4:
                system("cls");
                DeleteRecord();
                system("cls");
                break;
            case 5:
                system("cls");
                exit(0);
                break;
            default:
                system("cls");
                break;
        }
        
    }
}

void CheckStudentRecord()
{
    PrintHashTable();

    //delay between the next loop
    printf("\n\nClick Any button to Continue...");
    getch();
}

void DeleteRecord()
{
    char name[100];

    printf("Enter the name: ");
    scanf("%[^\n]", &name); getchar();
    DeleteKey(name);

    //Delat between the next loop
    printf("\n\nClick Any button to Continue...");
    getch();
}


void AddStudent()
{
    char name[100];
    char studentID[100];
    char age[10];
    char GPA[10];

    bool isValid = false;

    do
    {
        printf("Enter Name: "); scanf("%[^\n]", name); getchar();
        printf("Enter Student ID: "); scanf("%[^\n]", studentID); getchar();
        printf("Enter Age: "); scanf("%[^\n]", age); getchar();
        printf("Enter GPA: "); scanf("%[^\n]", GPA); getchar();

        isValid = CheckValidityInt(studentID);
        isValid = isValid == true ? CheckValidityInt(age) : false;
        isValid = isValid == true ? CheckValidityGPA(GPA) : false;

        if(isValid == false)
        {
            printf("Your Input is not Valid!\n");
            printf("Try again!\n");
            printf("Click any button to try again...");
            getch();
            system("cls");
        }  
    }while(isValid == false);


    Insert(name, studentID, age, GPA);
}

bool CheckValidityGPA(const char* value)
{
    for(int i = 0; i < strlen(value); i++)
    {
        if((value[i] >= 48 && value[i] <= 52) || value[1] == '.')
        {
            //valid
        }else
        {
            return false;
        }
    }
    return true;
}

bool CheckValidityInt(const char* value)
{
    for(int i = 0; i < strlen(value); i++)
    {
        if(value[i] >= 48 && value[i] <= 57)
        {
            //valid
        }else
        {
            return false;
        }
    }
    return true;
}

void SearchStudent()
{
    char name[100];

    //Search by name
    printf("Enter the student name: ");
    scanf("%[^\n]", &name); getchar();

    PrintKey(name);

    // Wait for useer input
    printf("\n\nClick any button to continue...");
    getch();
}