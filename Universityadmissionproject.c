#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data Structures 
struct Student {
    char name[50];
    char password[50];
    char department[50];
    float totalGPA;
    int age;
    char fatherName[50];
    char motherName[50];
    char city[50];
    char email[100];
    char phoneNumber[15];
    char bloodGroup[5];
    char transactionID[20];
};

struct AdmissionForm {
    char name[50];
    // Additional fields can be added if needed
};

// Doubly Linked List Node for Student
typedef struct StudentNode {

    struct Student data;
    struct StudentNode *prev;
    struct StudentNode *next;
}
 StudentNode;

// Doubly Linked List Node for AdmissionForm
typedef struct FormNode {

    struct AdmissionForm data;
    struct FormNode *prev;
    struct FormNode *next;
}
 FormNode;

// Global linked list heads
StudentNode *studentHead = NULL;

FormNode *formHead = NULL;

// Global university data arrays
int size = 0;
char *departments[100];
int faculty[100];
int students[100];
int alumni[100];
int fees[100];
float gpa[100];

// Linked List Utilities 
// Student list operations (doubly linked, supports stack & queue)
void insertStudentAtEnd(struct Student s) {

    StudentNode *newNode = (StudentNode*)malloc(sizeof(StudentNode));

    newNode->data = s;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (studentHead == NULL)
     {
        studentHead = newNode;
    } 
    else
     {
        StudentNode *temp = studentHead;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

StudentNode* findStudentByNamePass(char *name, char *pass) {
    StudentNode *temp = studentHead;

    while (temp) {
        if (strcmp(temp->data.name, name) == 0 && strcmp(temp->data.password, pass) == 0)

            return temp;

        temp = temp->next;
    }
    return NULL;
}

// AdmissionForm list operations
void insertFormAtEnd(struct AdmissionForm f) {
    FormNode *newNode = (FormNode*)malloc(sizeof(FormNode));

    newNode->data = f;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (formHead == NULL)
     {
        formHead = newNode;
    } 
    else
     {
        FormNode *temp = formHead;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

int countForms() {

    int cnt = 0;
    FormNode *temp = formHead;
    while (temp){
         cnt++;
          temp = temp->next; 
        }
    return cnt;
}

FormNode* findFormByName(char *name) {
    FormNode *temp = formHead;

    while (temp) {
        if (strcmp(temp->data.name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

void deleteFormByName(char *name) {
    FormNode *node = findFormByName(name);

    if (!node) return;
    if (node->prev) node->prev->next = node->next;

    else formHead = node->next;
    if (node->next) node->next->prev = node->prev;
    free(node);
}

// Stack and Queue demonstration (using Student list)
void pushStudentFront(struct Student s) {
    StudentNode *newNode = (StudentNode*)malloc(sizeof(StudentNode));

    newNode->data = s;
    newNode->prev = NULL;
    newNode->next = studentHead;

    if (studentHead) studentHead->prev = newNode;
    studentHead = newNode;
}

StudentNode* popStudentFront() {

    if (!studentHead) return NULL;
    StudentNode *removed = studentHead;
    studentHead = studentHead->next;
    if (studentHead) studentHead->prev = NULL;

    return removed;
}

void enqueueStudentBack(struct Student s) { insertStudentAtEnd(s); }

StudentNode* dequeueStudentFront() { return popStudentFront(); }

//Original Functions Adapted 
struct Student createStudentAccount() {
    struct Student newStudent;
    printf("\nEnter Name: ");
    scanf(" %[^\n]", newStudent.name);
    printf("Enter Password: ");
    scanf(" %[^\n]", newStudent.password);

    // other fields will be filled during application
    strcpy(newStudent.department, "");
    newStudent.totalGPA = 0;
    newStudent.age = 0;
    return newStudent;
}

void displayStudentDetails(struct Student student) {
    printf("\nStudent Details:\n");
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Department: %s\n", student.department);
    printf("Father: %s\n", student.fatherName);
    printf("Mother: %s\n", student.motherName);
    printf("City: %s\n", student.city);
    printf("Email: %s\n", student.email);
    printf("Phone: %s\n", student.phoneNumber);
    printf("Blood Group: %s\n", student.bloodGroup);
    printf("Transaction ID: %s\n", student.transactionID);
}

void displayAdmissionFormDetails(struct AdmissionForm form) {
    printf("\nAdmission Form Details:\n");
    printf("Name: %s\n", form.name);
}

void updateUniversityData() {
    int updateChoice;
    printf("\nUpdate University Data:\n");
    printf("1. Faculty Details\n2. Students & Alumni Details\n3. Tuition Fees\n4. GPA Requirement\n5. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &updateChoice);
    switch (updateChoice) {
        case 1: printf("\n--- Faculty Details ---\nCSE:20, SWE:25, NEF:20, JMC:22, Pharmacy:20\n"); 
        break;
        case 2: printf("\n--- Students & Alumni ---\nCSE:2000/1500, SWE:1800/1000, NEF:1000/800, JMC:500/500, Pharmacy:150/400\n");
         break;
        case 3: printf("\n--- Tuition Fees (4 years) ---\nCSE:800,000, SWE:750,000, NEF:500,000, JMC:700,000, Pharmacy:960,000\n");
         break;
        case 4: printf("\n--- GPA Requirement ---\nCSE:9.0, SWE:8.75, NEF:8.5, JMC:8.5, Pharmacy:8.0\n");
         break;
        case 5: printf("Exiting update.\n");
         break;
        default: printf("Invalid choice.\n");
    }
}

void manageAppliedStudents() {
    int manageChoice;

    printf("\nManage Applied Student Information:\n");
    printf("1. Count\n2. Add\n3. Delete\n4. Search\n5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &manageChoice);
    
    switch (manageChoice) {
        case 1:
         printf("\nNumber of Applied Students: %d\n", countForms());
          break;
        case 2: {
            struct AdmissionForm newForm;
            printf("Enter student name to add: ");
            scanf(" %[^\n]", newForm.name);

            insertFormAtEnd(newForm);
            printf("Student added to applied list.\n");
            break;
        }
        case 3: {
            char delName[50];
            printf("Enter name to delete: ");
            scanf(" %[^\n]", delName);

            if (findFormByName(delName)) {
                deleteFormByName(delName);
                printf("Deleted successfully.\n");
            }
             else 
             printf("Not found.\n");
            break;
        }
        case 4: {
            char searchName[50];
            printf("Enter name to search: ");
            scanf(" %[^\n]", searchName);

            FormNode *found = findFormByName(searchName);
            if (found) {
                displayAdmissionFormDetails(found->data);
            } else {
                printf("Not found.\n");
            }
            break;
        }
        case 5: printf("Exiting.\n");
         break;
        default: printf("Invalid choice.\n");
    }
}

void user() {
    int userChoice;
    StudentNode *loggedInStudent = NULL;
    do {
        printf("\n--- Student Dashboard ---\n1. Create Account\n2. Log In\n3. Exit\nChoice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {

            case 1: {
                struct Student newSt = createStudentAccount();
                insertStudentAtEnd(newSt);
                printf("Account created!\n");
                break;
            }

            case 2: {
                char uname[50], upass[50];

                printf("Username: "); 
                scanf(" %[^\n]", uname);
                printf("Password: ");
                 scanf(" %[^\n]", upass);

                loggedInStudent = findStudentByNamePass(uname, upass);

                if (!loggedInStudent) {
                    printf("Login failed.\n");
                    break;
                }

                printf("Login successful!\n");

                int studentChoice;

                do {
                     printf("\n--- MENU ---\n");
                    printf("1. About University\n");
                    printf("2. Departments Info\n");
                    printf("3. Apply for Registration\n");
                    printf("4. Log Out\n");
                    printf("Choice: ");

                    scanf("%d", &studentChoice);

                    switch (studentChoice) {

                        case 1:
                            printf("\nDaffodil International University (DIU)\n");
                            printf("Established: 2002\nLocation: Dhaka, Bangladesh\n");
                            break;

                        case 2: {
                            int deptChoice;
                            printf("\n1.Faculty 2.Students & Alumni 3.GPA Requirement 4.Tuition Fees\nChoice: ");
                            scanf("%d", &deptChoice);

                            if (deptChoice == 1)
                                printf("CSE:20,SWE:25, NEF:20, JMC:22, Pharmacy:20\n");
                            else if (deptChoice == 2)
                                printf("CSE:2000/1500, SWE:1800/1000, NEF:1000/800, JMC:500/500, Pharmacy:150/400\n");
                            else if (deptChoice == 3)
                                printf("CSE:9.0, SWE:8.75, NEF:8.5, JMC:8.5, Pharmacy:8.0\n");
                            else if (deptChoice == 4)
                                printf("CSE:800k, SWE:750k, NEF:500k, JMC:700k, Pharmacy:960k Taka\n");
                            else
                                printf("Invalid.\n");
                
                            break;
                        }
                        case 3: {
                            float gpa;
                            printf("Enter your total GPA (out of 10): ");
                            scanf("%f", &gpa);

                            if (gpa >= 9.0) strcpy(loggedInStudent->data.department, "CSE");
                            else if (gpa >= 8.75) strcpy(loggedInStudent->data.department, "SWE");
                            else if (gpa >= 8.5) strcpy(loggedInStudent->data.department, "NEF");
                            else if (gpa >= 8.0) strcpy(loggedInStudent->data.department, "JMC");
                            else {
                                printf("GPA too low for any department.\n");
                                break;
                            }
                           printf("Enter Age: ");
                            scanf("%d", &loggedInStudent->data.age);

                            printf("Father's Name: ");
                            scanf(" %[^\n]", loggedInStudent->data.fatherName);

                            printf("Mother's Name: ");
                            scanf(" %[^\n]", loggedInStudent->data.motherName);

                            printf("City: ");
                            scanf(" %[^\n]", loggedInStudent->data.city);

                            printf("Email: ");
                            scanf(" %[^\n]", loggedInStudent->data.email);

                            printf("Phone: ");
                            scanf(" %[^\n]", loggedInStudent->data.phoneNumber);

                            printf("Blood Group: ");
                            scanf(" %[^\n]", loggedInStudent->data.bloodGroup);

                            printf("Transaction ID: ");
                            scanf(" %[^\n]", loggedInStudent->data.transactionID);

                            // Add to applied students list
                            struct AdmissionForm appForm;
                            strcpy(appForm.name, loggedInStudent->data.name);
                            insertFormAtEnd(appForm);

                            printf("\nAdmission form submitted! Exam: 2 May 2026, Daffodil Smart City, Dhaka.\n");
                            displayStudentDetails(loggedInStudent->data);
                            break;
                        }
                        case 4: 
                        printf("Logged out.\n"); 
                        break;

                        default: 
                        printf("Invalid choice.\n");
                    }
                } while (studentChoice != 4);
                break;
            }
            case 3: 
            printf("Exiting user mode.\n"); 
            break;

            default: 
            printf("Invalid.\n");
        }
    } while (userChoice != 3);
}

void admin() {
  char adminPass[50], entered[50];
    strcpy(adminPass, "admin123");

    printf("Enter Admin Password: ");
    scanf(" %[^\n]", entered);

    if (strcmp(adminPass, entered) != 0) {
        printf("Access denied.\n");
        return;
    }
    printf("Admin Login Successful!\n");

    int adminChoice;

    do {
        printf("\n--- ADMIN PANEL ---\n");
        printf("1. Update University Data\n");
        printf("2. Manage Applied Students\n");
        printf("3. Exit\n");
        printf("Choice: ");

        scanf("%d", &adminChoice);

        switch (adminChoice) {

            case 1:
             updateUniversityData(); 
             break;

            case 2:
             manageAppliedStudents(); 
             break;

            case 3: 
            printf("Exiting admin.\n"); 
            break;

            default: 
            printf("Invalid choice.\n");
        }
    } while (adminChoice != 3);
}

//  Main 
int main() {
    system("COLOR 60");

    int choice;

     printf("\n\n");
        printf("                  =====================================================\n");
        printf("                         University Admission Management System\n");
        printf("                  =====================================================\n\n");

printf("                   1. User                                    2. Admin\n\n");
    printf("                                 3.Exit\n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: 
        user();
         break;

        case 2: 
        admin(); 
        break;

        case 3:
         printf("Exiting program. Goodbye!\n"); 
        break;
       
        default:
         printf("Invalid choice.\n");
    }
    // Free memory (optional, OS reclaims)
    return 0;
}