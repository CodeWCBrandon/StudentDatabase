#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define DATA_FILE "Database.txt"

FILE* databaseRead = fopen(DATA_FILE, "r");
FILE* databaseWrite = fopen(DATA_FILE, "a");

struct StudentData
{
    const char* name;
    const char* studentID;
    const char* age;
    const char* GPA;

    StudentData* next = NULL;
};

StudentData* hashTable[TABLE_SIZE];

//------------------- ALL THE FUNCTION DECLARATION ----------------------
unsigned int Hash(const char* key);
void Insert(const char* name, const char* studentID, const char* age, const char* GPA);
void ReadFile(const char* filename);
void WriteFile();
void PrintHashTable();
void ResetFile();
//------------------- END OF THE FUNCTION DECLARATION  ----------------------

unsigned int Hash(const char* key)
{
    // get the string lemgth
    int length = strlen(key);

    // hash value 
    unsigned int hashValue = 0;

    // create a random hash value
    for(int i = 0; i < length; i++)
    {
        hashValue += key[i];
        hashValue = (hashValue * key[i]) % TABLE_SIZE;
    }
    
    return hashValue;
}

void Insert(const char* name, const char* studentID, const char* age, const char* GPA)
{
    // Check if the input is not empty
    if(name == NULL || studentID == NULL || age == NULL || GPA == NULL)
    {
        printf("Cannot insert NULL");
        return;
    }

    // creating the index
    int index = Hash(strdup(name));

    // Allocate memory for new data
    StudentData* newData = (StudentData*)malloc(sizeof(StudentData));
    newData->name = strdup(name);
    newData->studentID = strdup(studentID);
    newData->age = strdup(age);
    newData->GPA = strdup(GPA);
    newData->next = NULL;

    //if there's an empty place
    if(hashTable[index] == NULL)
    {
        hashTable[index] = newData;   
        return; 
    }

    //traverse to the end of the list
    StudentData* tail = hashTable[index];
    while(tail->next != NULL)
    {
        tail = tail->next;
    }

    //if the tail is in the end of the hashtable
    tail->next = newData;

}

void ReadFile()
{
    // Create a buffer and a var to store the value
    char buffer[256];
    char name[100], studentID[100], age[10], GPA[10];


    while (fgets(buffer, sizeof(buffer), databaseRead))
    {
        if (sscanf(buffer, "Name: %99[^\n]", name) == 1)
        {
            fgets(buffer, sizeof(buffer), databaseRead);
            sscanf(buffer, "Student ID: %99[^\n]", studentID);
            fgets(buffer, sizeof(buffer), databaseRead);
            sscanf(buffer, "Age: %9[^\n]", age);
            fgets(buffer, sizeof(buffer), databaseRead);
            sscanf(buffer, "GPA: %9[^\n]", GPA);

            Insert(name, studentID, age, GPA);
        }
    }

    // Clear all the value from the file so there's no duplication
    ResetFile();
}

void WriteFile()
{
    //placing to the file
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        while(hashTable[i] != NULL)
        {         
            fputs("\n\n------------------\n", databaseWrite);
            fputs("\nName: ", databaseWrite); fputs(hashTable[i]->name, databaseWrite);
            fputs("\nStudent ID: ", databaseWrite); fputs(hashTable[i]->studentID, databaseWrite);
            fputs("\nAge: ", databaseWrite); fputs(hashTable[i]->age, databaseWrite);
            fputs("\nGPA: ", databaseWrite); fputs(hashTable[i]->GPA, databaseWrite);

            hashTable[i] = hashTable[i]->next;
        }     
    }

    //close the file to avoid any duplication
    fclose(databaseWrite);
}

void PrintHashTable() 
{
    // Print all the value from the hashTable
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("\n-----------------------------\n");

        //Travese the linked lists
        StudentData* temp = hashTable[i];
        while(temp != NULL)
        {
            printf("%d", i);
            printf("\tName: %s\n", temp->name);
            printf("\tStudent ID: %s\n", temp->studentID);
            printf("\tAge: %s\n", temp->age);
            printf("\tGPA: %s\n\n", temp->GPA);

            temp = temp->next;
        }
        
        //if not found
        printf("%d. -\n", i);
        
    }
}

void DeleteKey(const char* key)
{
    int index = Hash(key);

    StudentData* temp = hashTable[index];
    StudentData* prev = NULL;

    //traverse from the index
    while(temp != NULL)
    {
        if(strcmp(temp->name, key) == 0)
        {   
            if(prev == NULL) // if deleting the head
            {
                hashTable[index] = temp->next;
            }
            else // if deleting the body
            {
                prev->next = temp->next;
            }

            //free all of the allocated memory
            free((void*)temp->name);
            free((void*)temp->age);
            free((void*)temp->studentID);
            free((void*)temp->GPA);
            free(temp);

            printf("%s Deleted!", key);
            return;
        }else
        {
            prev = temp;
            temp = temp->next;
        }
    }

    //if not found
    printf("%s is not found", key);
}

void PrintKey(const char* key)
{
    int index = Hash(key);

    StudentData* temp = hashTable[index];

    //traverse from the index
    while(temp != NULL)
    {
        if(strcmp(temp->name, key) == 0)
        {
            printf("\tName: %s\n", temp->name);
            printf("\tStudent ID: %s\n", temp->studentID);
            printf("\tAge: %s\n", temp->age);
            printf("\tGPA: %s\n", temp->GPA);    
            return;
        }else
        {
            temp = temp->next;
        }
    }

    free(temp);
    
    //if not found
    printf("%s is not found", key);

}

void ResetFile()
{
    FILE* reset = fopen(DATA_FILE, "w");
    fclose(reset);
}