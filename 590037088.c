#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

struct Student {
    long long sapId;
    int rollNo;
    char name[50];
    char phone[20];
    char email[60];
    int year;
    int semester;
    float sgpa[8];
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

void readLine(char message[], char value[], int size) {
    printf("%s", message);
    if (fgets(value, size, stdin) != NULL) {
        value[strcspn(value, "\n")] = '\0';
    }
}

int readInt(char message[]) {
    char line[100];
    int value;
    char extra;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue;
        }
        if (sscanf(line, "%d %c", &value, &extra) == 1) {
            return value;
        }
        printf("Please enter a valid whole number.\n");
    }
}

long long readLongLong(char message[]) {
    char line[100];
    long long value;
    char extra;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue;
        }
        if (sscanf(line, "%lld %c", &value, &extra) == 1) {
            return value;
        }
        printf("Please enter a valid number.\n");
    }
}

float readFloat(char message[]) {
    char line[100];
    float value;
    char extra;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue;
        }
        if (sscanf(line, "%f %c", &value, &extra) == 1) {
            return value;
        }
        printf("Please enter a valid number.\n");
    }
}

int findStudent(long long sapId) {
    int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].sapId == sapId) {
            return i;
        }
    }
    return -1;
}

float calculateCGPA(struct Student student) {
    float total = 0.0f;
    int count = 0;
    int i;

    for (i = 0; i < 8; i++) {
        if (student.sgpa[i] > 0.0f) {
            total = total + student.sgpa[i];
            count++;
        }
    }

    if (count == 0) {
        return 0.0f;
    }

    return total / count;
}

void addStudent(void) {
    struct Student s;
    int i;

    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    printf("\n--- Add Student Details ---\n");

    s.sapId = readLongLong("Enter SAP ID: ");
    if (findStudent(s.sapId) != -1) {
        printf("A student with this SAP ID already exists.\n");
        return;
    }

    s.rollNo = readInt("Enter Roll Number: ");
    readLine("Enter Name: ", s.name, sizeof(s.name));
    readLine("Enter Phone Number: ", s.phone, sizeof(s.phone));
    readLine("Enter Email ID: ", s.email, sizeof(s.email));

    do {
        s.year = readInt("Enter Year (1-4): ");
        if (s.year < 1 || s.year > 4) {
            printf("Year must be between 1 and 4.\n");
        }
    } while (s.year < 1 || s.year > 4);

    do {
        s.semester = readInt("Enter Current Semester (1-8): ");
        if (s.semester < 1 || s.semester > 8) {
            printf("Semester must be between 1 and 8.\n");
        }
    } while (s.semester < 1 || s.semester > 8);

    printf("Enter SGPA for each semester (enter 0 if not completed).\n");
    for (i = 0; i < 8; i++) {
        do {
            char prompt[80];
            snprintf(prompt, sizeof(prompt), "Semester %d SGPA: ", i + 1);
            s.sgpa[i] = readFloat(prompt);
            if (s.sgpa[i] < 0.0f || s.sgpa[i] > 10.0f) {
                printf("SGPA must be between 0 and 10.\n");
            }
        } while (s.sgpa[i] < 0.0f || s.sgpa[i] > 10.0f);
    }

    students[studentCount] = s;
    studentCount++;
    printf("Student record added successfully.\n");
}

void displayOneStudent(struct Student s) {
    int i;

    printf("\n----------------------------------------\n");
    printf("SAP ID       : %lld\n", s.sapId);
    printf("Roll Number  : %d\n", s.rollNo);
    printf("Name         : %s\n", s.name);
    printf("Phone Number : %s\n", s.phone);
    printf("Email ID     : %s\n", s.email);
    printf("Year         : %d\n", s.year);
    printf("Semester     : %d\n", s.semester);

    printf("SGPA         : ");
    for (i = 0; i < 8; i++) {
        if (s.sgpa[i] > 0.0f) {
            printf("%.2f ", s.sgpa[i]);
        } else {
            printf("- ");
        }
    }

    printf("\nCGPA         : %.2f\n", calculateCGPA(s));
    printf("----------------------------------------\n");
}

void searchStudent(void) {
    long long sapId = readLongLong("\nEnter SAP ID to search: ");
    int index = findStudent(sapId);

    if (index == -1) {
        printf("Student record not found.\n");
    } else {
        displayOneStudent(students[index]);
    }
}

void displayAllStudents(void) {
    int i;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    printf("\n===== All Student Records =====\n");
    for (i = 0; i < studentCount; i++) {
        displayOneStudent(students[i]);
    }
}

void averageCGPAByYear(void) {
    int year, i, count;
    float total;

    printf("\n===== Average CGPA Year-wise =====\n");

    for (year = 1; year <= 4; year++) {
        total = 0.0f;
        count = 0;

        for (i = 0; i < studentCount; i++) {
            if (students[i].year == year) {
                float cgpa = calculateCGPA(students[i]);
                if (cgpa > 0.0f) {
                    total = total + cgpa;
                    count++;
                }
            }
        }

        if (count > 0) {
            printf("Year %d Average CGPA: %.2f\n", year, total / count);
        } else {
            printf("Year %d: No CGPA records available.\n", year);
        }
    }
}

void deleteStudent(void) {
    long long sapId = readLongLong("\nEnter SAP ID to delete: ");
    int index = findStudent(sapId);
    int i;

    if (index == -1) {
        printf("Student record not found.\n");
        return;
    }

    for (i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    printf("Student record deleted successfully.\n");
}

void sortBySAP(void) {
    int i, j;
    struct Student temp;

    for (i = 0; i < studentCount - 1; i++) {
        for (j = 0; j < studentCount - i - 1; j++) {
            if (students[j].sapId > students[j + 1].sapId) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nRecords sorted by SAP ID in increasing order.\n");
    displayAllStudents();
}

void sortByName(void) {
    int i, j;
    struct Student temp;

    for (i = 0; i < studentCount - 1; i++) {
        for (j = 0; j < studentCount - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nRecords sorted by Name in increasing order.\n");
    displayAllStudents();
}

void academicAdvisor(void) {
    long long sapId = readLongLong("\nEnter SAP ID for academic advice: ");
    int index = findStudent(sapId);
    float cgpa;

    if (index == -1) {
        printf("Student record not found.\n");
        return;
    }

    cgpa = calculateCGPA(students[index]);

    if (cgpa == 0.0f) {
        printf("No SGPA details are available to give advice.\n");
    } else {
        printf("\nAcademic Advisor for %s\n", students[index].name);
        printf("Your CGPA is: %.2f\n", cgpa);

        if (cgpa >= 8.5f) {
            printf("Excellent performance - maintain your current study pattern.\n");
        } else if (cgpa >= 7.0f) {
            printf("Good performance - keep working consistently.\n");
        } else if (cgpa >= 5.0f) {
            printf("Needs improvement - focus more on subjects with lower SGPA.\n");
        } else {
            printf("Requires immediate attention - make a study plan and ask teachers for help.\n");
        }
    }
}

void showMenu(void) {
    printf("\n========== STUDENT RECORD AND RESULT MANAGEMENT ==========\n");
    printf("1. Add Student Details\n");
    printf("2. Search Student by SAP ID\n");
    printf("3. Display All Student Records\n");
    printf("4. Calculate Average CGPA of Each Year\n");
    printf("5. Delete Student Record\n");
    printf("6. Sort Records by SAP ID\n");
    printf("7. Sort Records by Name\n");
    printf("8. AI-Assisted Academic Advisor\n");
    printf("9. Exit\n");
    printf("==========================================================\n");
}

int main(void) {
    int choice;

    printf("Welcome to Student Record and Result Management System!\n");

    do {
        showMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                displayAllStudents();
                break;
            case 4:
                averageCGPAByYear();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                sortBySAP();
                break;
            case 7:
                sortByName();
                break;
            case 8:
                academicAdvisor();
                break;
            case 9:
                printf("Thank you for using the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select from 1 to 9.\n");
        }
    } while (choice != 9);

    return 0;
}
