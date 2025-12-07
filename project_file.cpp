#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------- FILE NAMES ------------------- */
#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

/* ------------------- STRUCTURE ------------------- */
struct Student
{
    
    int roll;
    char name[50];
    float marks;
};

/* ------------------- FUNCTION DECLARATIONS ------------------- */
void addStudent();
void displayStudents();
void SearchStudent();
void SearchStudentByName();
void DeleteStudent();
void UpdateStudent();
int rollExists(int);

int loginSystem(char role[]);
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

/* ------------------- MAIN FUNCTION ------------------- */
int main()
{
    char role[20];

    if (!loginSystem(role))
    {
        printf("\nLogin Failed. Exiting...\n");
        return 0;
    }

    if (strcmp(role, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(role, "STAFF") == 0)
        staffMenu();
    else if (strcmp(role, "USER") == 0)
        userMenu();
    else if (strcmp(role, "GUEST") == 0)
        guestMenu();

    return 0;
}

/* ------------------- LOGIN SYSTEM ------------------- */
int loginSystem(char role[])
{
    FILE *file = fopen(CREDENTIAL_FILE, "r");
    if (file == NULL)
    {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    char savedUser[50], savedPass[50], savedRole[20];
    char user[50], pass[50];

    int attempts = 3;

    while (attempts--)
    {
        printf("\n======== LOGIN SCREEN ========\n");
        printf("Username: ");
        scanf("%s", user);

        printf("Password: ");
        scanf("%s", pass);

        rewind(file);

        while (fscanf(file, "%s %s %s", savedUser, savedPass, savedRole) != EOF)
        {
            if (strcmp(user, savedUser) == 0 && strcmp(pass, savedPass) == 0)
            {
                printf("\nLogin Successful!\n");
                printf("Role: %s\n", savedRole);

                strcpy(role, savedRole);
                fclose(file);
                return 1;
            }
        }

        printf("\nInvalid username or password! Attempts left: %d\n", attempts);
    }

    fclose(file);
    printf("\nToo many failed attempts. Access Denied.\n");
    return 0;
}

/* ------------------- ADMIN MENU ------------------- */
void adminMenu()
{
    int choice;
    do
    {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by Roll\n");
        printf("4. Search Student by Name\n");
        printf("5. Update Student\n");
        printf("6. Delete Student\n");
        printf("7. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: SearchStudent(); break;
        case 4: SearchStudentByName(); break;
        case 5: UpdateStudent(); break;
        case 6: DeleteStudent(); break;
        case 7: printf("Logging out...\n"); break;
        default: printf("Invalid Choice!\n");
        }
    } while (choice != 7);
}

/* ------------------- STAFF MENU ------------------- */
void staffMenu()
{
    int choice;
    do
    {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by Roll\n");
        printf("4. Search Student by Name\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: SearchStudent(); break;
        case 4: SearchStudentByName(); break;
        case 5: printf("Logging out...\n"); break;
        default: printf("Invalid Choice!\n");
        }
    } while (choice != 5);
}

/* ------------------- USER MENU ------------------- */
void userMenu()
{
    int choice;
    do
    {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: displayStudents(); break;
        case 2: printf("Logging out...\n"); break;
        default: printf("Invalid Choice!\n");
        }
    } while (choice != 2);
}

/* ------------------- GUEST MENU ------------------- */
void guestMenu()
{
    printf("\n===== GUEST MENU =====\n");

    FILE *file = fopen(STUDENT_FILE, "r");
    if (!file)
    {
        printf("No student records found.\n");
        return;
    }

    int count = 0;
    struct Student s;

    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
        count++;

    fclose(file);

    printf("Total Students Registered: %d\n", count);
    printf("(Guest users cannot view detailed records.)\n");
}

/* ------------------- CHECK ROLL NUMBER ------------------- */
int rollExists(int roll)
{
    struct Student s;
    FILE *file = fopen(STUDENT_FILE, "r");
    if (!file) return 0;

    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
    {
        if (s.roll == roll)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

/* ------------------- ADD STUDENT ------------------- */
void addStudent()
{
    struct Student s;
    FILE *file = fopen(STUDENT_FILE, "a");

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);

    if (rollExists(s.roll))
    {
        printf("\nError: Roll number already exists!\n");
        return;
    }

    printf("Enter Name: ");
    getchar();
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(file, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(file);

    printf("\nStudent Added Successfully!\n");
}

/* ------------------- DISPLAY STUDENTS ------------------- */
void displayStudents()
{
    struct Student s;
    FILE *file = fopen(STUDENT_FILE, "r");

    if (file == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n----- STUDENT RECORDS -----\n");
    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);

    fclose(file);
}

/* ------------------- SEARCH BY ROLL ------------------- */
void SearchStudent()
{
    struct Student s;
    int roll;
    FILE *file = fopen(STUDENT_FILE, "r");

    if (!file)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("Enter Roll No to Search: ");
    scanf("%d", &roll);

    int found = 0;

    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
    {
        if (s.roll == roll)
        {
            printf("\nStudent Found:\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
        printf("\nStudent Not Found!\n");
}

/* ------------------- SEARCH BY NAME ------------------- */
void SearchStudentByName()
{
    struct Student s;
    char searchName[50];
    FILE *file = fopen(STUDENT_FILE, "r");

    if (!file)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("Enter Name to Search: ");
    getchar();
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;

    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
    {
        if (strcasecmp(s.name, searchName) == 0)
        {
            printf("\nStudent Found:\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n",
                   s.roll, s.name, s.marks);
            found = 1;
        }
    }

    fclose(file);

    if (!found)
        printf("\nNo student found with that name.\n");
}

/* ------------------- DELETE STUDENT ------------------- */
void DeleteStudent()
{
    struct Student s;
    int roll;

    FILE *file = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("Enter Roll No to Delete: ");
    scanf("%d", &roll);

    int found = 0;

    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
    {
        if (s.roll == roll)
            found = 1;
        else
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(file);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("\nStudent Deleted Successfully.\n");
    else
        printf("\nRoll No Not Found.\n");
}

/* ------------------- UPDATE STUDENT ------------------- */
void UpdateStudent()
{
    struct Student s;
    int roll;

    FILE *file = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file)
    {
        printf("\nNo student records found.\n");
        return;
    }

    printf("Enter Roll No to Update: ");
    scanf("%d", &roll);

    int found = 0;

    while (fscanf(file, "%d %s %f", &s.roll, s.name, &s.marks) != EOF)
    {
        if (s.roll == roll)
        {
            found = 1;
            printf("Enter New Name: ");
            getchar();
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }

        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(file);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("\nStudent Updated Successfully.\n");
    else
        printf("\nRoll No Not Found.\n");
}