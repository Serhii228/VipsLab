
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMBER_OF_STUDENTS 8
#define BUFFER_SIZE SURNAME_SIZE+NAME_SIZE+MARKS_SIZE+10 + 6
#define SURNAME_SIZE 50
#define NAME_SIZE 50
#define MARKS_SIZE 50

struct student
{
    char surname[SURNAME_SIZE];
    char name[NAME_SIZE];
    char birthDate[10];
    int marks[MARKS_SIZE];
};
typedef struct student STUDENT;

void initializeStudents(char* filename);
void getStudents(STUDENT* studentArray, char* fileName);
void sortAndPrint(const STUDENT* studentArray);
void copyStudent(STUDENT* toStudent, const STUDENT fromStudent);
void changeStudents(STUDENT* student1, STUDENT* student2);

int main() {
    //initializeStudents("students.txt");
    printf("DISCLAIMER\n");
    printf("The story, all names, characters, and incidents portrayed in this production are fictitious.\n\
No identification with actual persons (living or deceased), places, buildings, and products is intended\n\
or should be inferred.\n");
    STUDENT poorStudents[NUMBER_OF_STUDENTS] = { 0 };
    getStudents(poorStudents, "students.txt");
    sortAndPrint(poorStudents);
    getchar();
    getchar();
    return 0;
}

void sortAndPrint(const STUDENT* studentArray) {
    STUDENT localStudents[NUMBER_OF_STUDENTS] = { 0 };
    int studentsCounter = 0;
    printf("|%-10s| |%-10s| |%-10s| |%-18s|\n", "Name",
        "Surname", "Birthday", "Marks");
    for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
        printf("|%-10s| |%-10s| |%-10s| |", studentArray[i].name, studentArray[i].surname, studentArray[i].birthDate);
        int numb;
        for (int j = 0; (numb = studentArray[i].marks[j]) != 0; ++j) {
            printf("%d ", numb);
        }
        printf("|");
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < NUMBER_OF_STUDENTS; ++i) {
        int numb;
        int flag = 0;
        for (int j = 0; (numb = studentArray[i].marks[j]) == 2 || numb == 3 || numb == 4 || numb == 5; ++j) {
            if (numb == 2) {
                flag = 1;
            }
        }
        if (flag == 0) {
            copyStudent(&localStudents[studentsCounter], studentArray[i]);
            ++studentsCounter;
        }
    }
    int maxIndex;
    for (int i = 0; i < studentsCounter; ++i) {
        maxIndex = i;
        for (int j = i + 1; j < studentsCounter; ++j) {
            if (strcmp(localStudents[maxIndex].surname, localStudents[j].surname) > 0) {
                maxIndex = j;
            }
        }
        changeStudents(&localStudents[i], &localStudents[maxIndex]);
    }
    printf("List after sotring:\n");
    printf("|%-10s| |%-10s| |%-10s| |%-18s|\n", "Name",
        "Surname", "Birthday", "Marks");
    for (int i = 0; i < studentsCounter; ++i) {
        printf("|%-10s| |%-10s| |%-10s| |", localStudents[i].name, localStudents[i].surname, localStudents[i].birthDate);
        int numb;
        for (int j = 0; (numb = localStudents[i].marks[j]) != 0; ++j) {
            printf("%d ", numb);
        }
        printf("|");
        printf("\n");
    }
    printf("\n");
    STUDENT oldestStudentOne = { 0 }, oldestStudentTwo = { 0 };
    copyStudent(&oldestStudentOne, localStudents[0]);
    copyStudent(&oldestStudentTwo, localStudents[1]);
    for (int i = 0; i < studentsCounter; ++i) {
        int days1 = 0, days2 = 0, days3 = 0;
        char temp[12] = { 0 };
        strcpy(temp, oldestStudentOne.birthDate);
        char* ptr = strtok(temp, ".");
        int counter = 0;
        while (ptr != NULL) {
            if (counter == 0) {
                days1 += atoi(ptr);
            }
            else if (counter == 1) {
                days1 += atoi(ptr) * 30;
            }
            else {
                days1 += atoi(ptr) * 365;
            }
            ptr = strtok(NULL, ".");
            ++counter;
        }
        strcpy(temp, oldestStudentTwo.birthDate);
        ptr = strtok(temp, ".");
        counter = 0;
        while (ptr != NULL) {
            if (counter == 0) {
                days2 += atoi(ptr);
            }
            else if (counter == 1) {
                days2 += atoi(ptr) * 30;
            }
            else {
                days2 += atoi(ptr) * 365;
            }
            ptr = strtok(NULL, ".");
            ++counter;
        }
        strcpy(temp, localStudents[i].birthDate);
        ptr = strtok(temp, ".");
        counter = 0;
        while (ptr != NULL) {
            if (counter == 0) {
                days3 += atoi(ptr);
            }
            else if (counter == 1) {
                days3 += atoi(ptr) * 30;
            }
            else {
                days3 += atoi(ptr) * 365;
            }
            ptr = strtok(NULL, ".");
            ++counter;
        }
        if (days1 > days3) {
            copyStudent(&oldestStudentOne, localStudents[i]);
        }
        else if (days2 > days3) {
            copyStudent(&oldestStudentTwo, localStudents[i]);
        }
    }
    printf("The oldest students in list:\n");
    printf("|%-10s| |%-10s| |%-10s| |", oldestStudentOne.name, oldestStudentOne.surname, oldestStudentOne.birthDate);
    int numb;
    for (int j = 0; (numb = oldestStudentOne.marks[j]) != 0; ++j) {
        printf("%d ", numb);
    }
    printf("|");
    printf("\n");
    printf("|%-10s| |%-10s| |%-10s| |", oldestStudentTwo.name, oldestStudentTwo.surname, oldestStudentTwo.birthDate);
    for (int j = 0; (numb = oldestStudentTwo.marks[j]) != 0; ++j) {
        printf("%d ", numb);
    }
    printf("|");
    printf("\n");
}
void changeStudents(STUDENT* student1, STUDENT* student2) {
    STUDENT tempStudent = *student1;
    *student1 = *student2;
    *student2 = tempStudent;
}
void copyStudent(STUDENT* toStudent, const STUDENT fromStudent) {
    *toStudent = fromStudent;
}
void getStudents(STUDENT* studentArray, char* fileName) {
    FILE* pFile;
    int studentCounter = 0;
    pFile = fopen("students.txt", "r");
    fseek(pFile, 0, SEEK_SET);
    while (!feof(pFile)) {
        char largeBuffer[BUFFER_SIZE] = { 0 };
        fgets(largeBuffer, BUFFER_SIZE, pFile);
        char* ptr;
        ptr = strtok(largeBuffer, "<,> \0\n");
        int posCount = 0;
        int markCount = 0;
        while (ptr != NULL) {
            if (posCount == 0) {
                strcpy(studentArray[studentCounter].name, ptr);
            }
            else if (posCount == 1) {
                strcpy(studentArray[studentCounter].surname, ptr);
            }
            else if (posCount == 2) {
                strcpy(studentArray[studentCounter].birthDate, ptr);
            }
            else {
                if (atoi(ptr) != 0) {
                    studentArray[studentCounter].marks[markCount] = atoi(ptr);
                    markCount++;
                }
            }
            ptr = strtok(NULL, "<,> \0\n");
            ++posCount;
        }
        ++studentCounter;
    }
    fclose(pFile);

}