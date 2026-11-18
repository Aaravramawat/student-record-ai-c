#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define TOTAL_SEMESTERS 8
#define DATA_FILE "students.txt"

/* Structure to store student details */
typedef struct {
    long long sap_id;
    char roll_no[25];
    char name[50];
    char phone[15];
    char email[50];
    int year;
    int current_sem;
    float sgpa[TOTAL_SEMESTERS];
    float cgpa;
} Student;

/* Global variables */
Student students[MAX_STUDENTS];
int student_count = 0;

/* Function declarations */
void clearInputBuffer(void);
void readString(char *buffer, int size);
int stringsEqualIgnoreCase(const char *a, const char *b);
void calculateCGPA(Student *s);
void displayAdvisorRecommendation(float cgpa);
void initializeDefaultStudents(void);
void addStudent(void);
void displayAllStudents(void);
void searchStudent(void);
void calculateAllCGPA(void);
void calculateYearWiseAverage(void);
void sortBySapId(void);
void sortByName(void);
void deleteStudent(void);
void saveRecordsToFile(void);
void loadRecordsFromFile(void);
void printDivider(char ch, int length);

/* Clear input buffer */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Read strings safely */
void readString(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        int has_newline = strchr(buffer, '\n') != NULL;
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (!has_newline && !feof(stdin)) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
        }
    } else {
        buffer[0] = '\0';
    }
}

/* Compare strings without considering case */
int stringsEqualIgnoreCase(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) !=
            tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

/* Print divider */
void printDivider(char ch, int length) {
    for (int i = 0; i < length; i++) {
        putchar(ch);
    }
    putchar('\n');
}

/* Calculate CGPA */
void calculateCGPA(Student *s) {
    if (s->current_sem <= 0) {
        s->cgpa = 0.0f;
        return;
    }

    float sum = 0.0f;
    int valid_sems = 0;

    for (int i = 0;
         i < s->current_sem && i < TOTAL_SEMESTERS;
         i++) {
        sum += s->sgpa[i];
        valid_sems++;
    }

    if (valid_sems > 0) {
        s->cgpa = sum / (float)valid_sems;
    } else {
        s->cgpa = 0.0f;
    }
}

/* Rule-based AI Academic Advisor */
void displayAdvisorRecommendation(float cgpa) {

    printDivider('-', 65);

    printf(" [AI ACADEMIC ADVISOR ANALYSIS & RECOMMENDATION]\n");
    printDivider('-', 65);

    printf(" CGPA Calculated: %.2f / 10.00\n", cgpa);

    if (cgpa >= 8.5f) {

        printf(" Academic Category: EXCELLENT PERFORMANCE\n");
        printf(" Advisor Guidance:\n");
        printf("  * Outstanding academic track record!\n");
        printf("  * Maintain your academic performance.\n");
        printf("  * Explore research and internships.\n");
        printf("  * Participate in coding competitions.\n");

    } else if (cgpa >= 7.0f) {

        printf(" Academic Category: GOOD PERFORMANCE\n");
        printf(" Advisor Guidance:\n");
        printf("  * Strong foundational understanding.\n");
        printf("  * Identify subjects requiring improvement.\n");
        printf("  * Practice programming regularly.\n");
        printf("  * Participate in hackathons.\n");

    } else if (cgpa >= 5.5f) {

        printf(" Academic Category: NEEDS IMPROVEMENT\n");
        printf(" Advisor Guidance:\n");
        printf("  * Focus on improving academic performance.\n");
        printf("  * Review previous examination papers.\n");
        printf("  * Take guidance from faculty members.\n");
        printf("  * Study regularly with classmates.\n");

    } else {

        printf(" Academic Category: REQUIRES IMMEDIATE ATTENTION\n");
        printf(" Advisor Guidance:\n");
        printf("  * Immediate academic improvement is required.\n");
        printf("  * Contact your academic mentor.\n");
        printf("  * Attend remedial classes if required.\n");
        printf("  * Focus on understanding basic concepts.\n");
    }

    printDivider('-', 65);
}

/* Initialize default students */
void initializeDefaultStudents(void) {

    student_count = 5;

    /* Student 1 */
    students[0].sap_id = 590037088LL;
    strcpy(students[0].roll_no, "R214220001");
    strcpy(students[0].name, "Aarav Ramawat");
    strcpy(students[0].phone, "9876543210");
    strcpy(students[0].email, "aarav.590037088@stu.upes.ac.in");
    students[0].year = 1;
    students[0].current_sem = 2;
    students[0].sgpa[0] = 8.80f;
    students[0].sgpa[1] = 9.10f;

    for (int i = 2; i < TOTAL_SEMESTERS; i++)
        students[0].sgpa[i] = 0.0f;

    calculateCGPA(&students[0]);

    /* Student 2 */
    students[1].sap_id = 590037089LL;
    strcpy(students[1].roll_no, "R214220015");
    strcpy(students[1].name, "Diya Sharma");
    strcpy(students[1].phone, "9811223344");
    strcpy(students[1].email, "diya.sharma@stu.upes.ac.in");
    students[1].year = 2;
    students[1].current_sem = 4;

    students[1].sgpa[0] = 7.80f;
    students[1].sgpa[1] = 7.50f;
    students[1].sgpa[2] = 8.00f;
    students[1].sgpa[3] = 7.90f;

    for (int i = 4; i < TOTAL_SEMESTERS; i++)
        students[1].sgpa[i] = 0.0f;

    calculateCGPA(&students[1]);

    /* Student 3 */
    students[2].sap_id = 590037090LL;
    strcpy(students[2].roll_no, "R214220032");
    strcpy(students[2].name, "Rohan Verma");
    strcpy(students[2].phone, "9877001122");
    strcpy(students[2].email, "rohan.verma@stu.upes.ac.in");
    students[2].year = 3;
    students[2].current_sem = 6;

    students[2].sgpa[0] = 6.20f;
    students[2].sgpa[1] = 5.80f;
    students[2].sgpa[2] = 6.50f;
    students[2].sgpa[3] = 6.00f;
    students[2].sgpa[4] = 6.80f;
    students[2].sgpa[5] = 6.10f;

    for (int i = 6; i < TOTAL_SEMESTERS; i++)
        students[2].sgpa[i] = 0.0f;

    calculateCGPA(&students[2]);

    /* Student 4 */
    students[3].sap_id = 590037091LL;
    strcpy(students[3].roll_no, "R214220048");
    strcpy(students[3].name, "Ananya Patel");
    strcpy(students[3].phone, "9988776655");
    strcpy(students[3].email, "ananya.patel@stu.upes.ac.in");
    students[3].year = 1;
    students[3].current_sem = 2;

    students[3].sgpa[0] = 5.00f;
    students[3].sgpa[1] = 4.80f;

    for (int i = 2; i < TOTAL_SEMESTERS; i++)
        students[3].sgpa[i] = 0.0f;

    calculateCGPA(&students[3]);

    /* Student 5 */
    students[4].sap_id = 590037092LL;
    strcpy(students[4].roll_no, "R214220060");
    strcpy(students[4].name, "Kabir Mehta");
    strcpy(students[4].phone, "9765432109");
    strcpy(students[4].email, "kabir.mehta@stu.upes.ac.in");
    students[4].year = 4;
    students[4].current_sem = 8;

    students[4].sgpa[0] = 8.50f;
    students[4].sgpa[1] = 8.70f;
    students[4].sgpa[2] = 8.90f;
    students[4].sgpa[3] = 9.00f;
    students[4].sgpa[4] = 8.60f;
    students[4].sgpa[5] = 9.20f;
    students[4].sgpa[6] = 9.10f;
    students[4].sgpa[7] = 9.50f;

    calculateCGPA(&students[4]);
}

/* Add student */
void addStudent(void) {

    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student capacity reached.\n");
        return;
    }

    Student s;

    printf("\n--- ADD NEW STUDENT ---\n");

    printf("Enter SAP ID: ");

    if (scanf("%lld", &s.sap_id) != 1) {
        printf("Invalid SAP ID.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    for (int i = 0; i < student_count; i++) {
        if (students[i].sap_id == s.sap_id) {
            printf("Student already exists.\n");
            return;
        }
    }

    printf("Enter Roll Number: ");
    readString(s.roll_no, sizeof(s.roll_no));

    printf("Enter Name: ");
    readString(s.name, sizeof(s.name));

    printf("Enter Phone Number: ");
    readString(s.phone, sizeof(s.phone));

    printf("Enter Email: ");
    readString(s.email, sizeof(s.email));

    printf("Enter Academic Year (1-4): ");

    if (scanf("%d", &s.year) != 1 ||
        s.year < 1 || s.year > 4) {
        printf("Invalid academic year.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter Completed Semesters (1-8): ");

    if (scanf("%d", &s.current_sem) != 1 ||
        s.current_sem < 1 || s.current_sem > 8) {
        printf("Invalid semester count.\n");
        clearInputBuffer();
        return;
    }

    printf("\nEnter SGPA for completed semesters:\n");

    for (int i = 0; i < TOTAL_SEMESTERS; i++) {

        if (i < s.current_sem) {

            int valid = 0;

            while (!valid) {

                printf("Semester %d SGPA: ", i + 1);

                if (scanf("%f", &s.sgpa[i]) == 1 &&
                    s.sgpa[i] >= 0.0f &&
                    s.sgpa[i] <= 10.0f) {

                    valid = 1;

                } else {

                    printf("Enter a valid SGPA between 0 and 10.\n");
                }

                clearInputBuffer();
            }

        } else {
            s.sgpa[i] = 0.0f;
        }
    }

    calculateCGPA(&s);

    students[student_count] = s;
    student_count++;

    printf("\nStudent added successfully!\n");

    displayAdvisorRecommendation(s.cgpa);
}

/* Display all students */
void displayAllStudents(void) {

    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }

    printDivider('=', 110);

    printf("ALL REGISTERED STUDENT RECORDS (%d Total)\n",
           student_count);

    printDivider('=', 110);

    printf("%-4s | %-11s | %-12s | %-20s | %-4s | %-4s | %-6s | %-25s\n",
           "No.", "SAP ID", "Roll No", "Student Name",
           "Year", "Sem", "CGPA", "AI Performance Status");

    printDivider('-', 110);

    for (int i = 0; i < student_count; i++) {

        char status[30];

        if (students[i].cgpa >= 8.5f) {
            strcpy(status, "Excellent");
        } else if (students[i].cgpa >= 7.0f) {
            strcpy(status, "Good");
        } else if (students[i].cgpa >= 5.5f) {
            strcpy(status, "Needs Improvement");
        } else {
            strcpy(status, "Immediate Attention");
        }

        printf("%-4d | %-11lld | %-12s | %-20s | %-4d | %-4d | %-6.2f | %-25s\n",
               i + 1,
               students[i].sap_id,
               students[i].roll_no,
               students[i].name,
               students[i].year,
               students[i].current_sem,
               students[i].cgpa,
               status);
    }

    printDivider('=', 110);
}

/* Search student */
void searchStudent(void) {

    if (student_count == 0) {
        printf("No records available.\n");
        return;
    }

    int choice;

    printf("\n1. Search by SAP ID\n");
    printf("2. Search by Roll Number\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        printf("Invalid choice.\n");
        return;
    }

    clearInputBuffer();

    int found_index = -1;

    if (choice == 1) {

        long long search_sap;

        printf("Enter SAP ID: ");

        if (scanf("%lld", &search_sap) != 1) {
            clearInputBuffer();
            printf("Invalid SAP ID.\n");
            return;
        }

        clearInputBuffer();

        for (int i = 0; i < student_count; i++) {
            if (students[i].sap_id == search_sap) {
                found_index = i;
                break;
            }
        }

    } else if (choice == 2) {

        char search_roll[25];

        printf("Enter Roll Number: ");
        readString(search_roll, sizeof(search_roll));

        for (int i = 0; i < student_count; i++) {
            if (stringsEqualIgnoreCase(
                students[i].roll_no, search_roll)) {
                found_index = i;
                break;
            }
        }

    } else {
        printf("Invalid search option.\n");
        return;
    }

    if (found_index != -1) {

        Student s = students[found_index];

        printDivider('=', 65);

        printf("STUDENT DETAILS FOUND\n");
        printf("SAP ID: %lld\n", s.sap_id);
        printf("Roll Number: %s\n", s.roll_no);
        printf("Name: %s\n", s.name);
        printf("Phone: %s\n", s.phone);
        printf("Email: %s\n", s.email);
        printf("Academic Year: %d\n", s.year);
        printf("Current Semester: %d\n", s.current_sem);

        printDivider('-', 65);

        printf("SEMESTER-WISE SGPA:\n");

        for (int i = 0; i < TOTAL_SEMESTERS; i++) {

            if (i < s.current_sem) {
                printf("Semester %d: %.2f\n",
                       i + 1, s.sgpa[i]);
            } else {
                printf("Semester %d: N/A\n", i + 1);
            }
        }

        calculateCGPA(&students[found_index]);

        displayAdvisorRecommendation(
            students[found_index].cgpa);

    } else {
        printf("Student not found.\n");
    }
}

/* Calculate CGPA of all students */
void calculateAllCGPA(void) {

    if (student_count == 0) {
        printf("No records available.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {

        calculateCGPA(&students[i]);

        printf("\nStudent: %s\n", students[i].name);

        printf("SAP ID: %lld\n", students[i].sap_id);

        displayAdvisorRecommendation(students[i].cgpa);
    }
}

/* Calculate year-wise average */
void calculateYearWiseAverage(void) {

    if (student_count == 0) {
        printf("No records available.\n");
        return;
    }

    float year_sum[4] = {0};
    int year_count[4] = {0};

    for (int i = 0; i < student_count; i++) {

        calculateCGPA(&students[i]);

        if (students[i].year >= 1 &&
            students[i].year <= 4) {

            int y_idx = students[i].year - 1;

            year_sum[y_idx] += students[i].cgpa;
            year_count[y_idx]++;
        }
    }

    printf("\nYEAR-WISE AVERAGE CGPA\n");

    printDivider('-', 65);

    for (int y = 0; y < 4; y++) {

        if (year_count[y] > 0) {

            float avg =
                year_sum[y] / (float)year_count[y];

            printf("Year %d | Students: %d | Average CGPA: %.2f\n",
                   y + 1, year_count[y], avg);

        } else {

            printf("Year %d | No Students\n", y + 1);
        }
    }

    printDivider('-', 65);
}

/* Delete student */
void deleteStudent(void) {

    if (student_count == 0) {
        printf("No records available.\n");
        return;
    }

    long long delete_sap;

    printf("Enter SAP ID to delete: ");

    if (scanf("%lld", &delete_sap) != 1) {
        clearInputBuffer();
        printf("Invalid SAP ID.\n");
        return;
    }

    clearInputBuffer();

    int found_index = -1;

    for (int i = 0; i < student_count; i++) {

        if (students[i].sap_id == delete_sap) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Delete %s? (y/n): ",
           students[found_index].name);

    char confirm;
    scanf("%c", &confirm);
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {

        for (int i = found_index;
             i < student_count - 1; i++) {

            students[i] = students[i + 1];
        }

        student_count--;

        printf("Student deleted successfully.\n");

    } else {

        printf("Deletion cancelled.\n");
    }
}

/* Sort by SAP ID using Bubble Sort */
void sortBySapId(void) {

    if (student_count == 0) {
        printf("No records available.\n");
        return;
    }

    for (int i = 0; i < student_count - 1; i++) {

        for (int j = 0;
             j < student_count - 1 - i; j++) {

            if (students[j].sap_id >
                students[j + 1].sap_id) {

                Student temp = students[j];

                students[j] = students[j + 1];

                students[j + 1] = temp;
            }
        }
    }

    printf("Records sorted by SAP ID.\n");

    displayAllStudents();
}

/* Sort by Name */
void sortByName(void) {

    if (student_count == 0) {
        printf("No records available.\n");
        return;
    }

    for (int i = 0; i < student_count - 1; i++) {

        for (int j = 0;
             j < student_count - 1 - i; j++) {

            if (strcmp(students[j].name,
                       students[j + 1].name) > 0) {

                Student temp = students[j];

                students[j] = students[j + 1];

                students[j + 1] = temp;
            }
        }
    }

    printf("Records sorted by Name.\n");

    displayAllStudents();
}

/* Save records to file */
void saveRecordsToFile(void) {

    FILE *fp = fopen(DATA_FILE, "w");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(fp, "%d\n", student_count);

    for (int i = 0; i < student_count; i++) {

        fprintf(fp, "%lld\n", students[i].sap_id);
        fprintf(fp, "%s\n", students[i].roll_no);
        fprintf(fp, "%s\n", students[i].name);
        fprintf(fp, "%s\n", students[i].phone);
        fprintf(fp, "%s\n", students[i].email);

        fprintf(fp, "%d %d\n",
                students[i].year,
                students[i].current_sem);

        for (int j = 0; j < TOTAL_SEMESTERS; j++) {
            fprintf(fp, "%.2f ", students[i].sgpa[j]);
        }

        fprintf(fp, "\n%.2f\n", students[i].cgpa);
    }

    fclose(fp);

    printf("Records saved successfully to %s.\n",
           DATA_FILE);
}

/* Load records from file */
void loadRecordsFromFile(void) {

    FILE *fp = fopen(DATA_FILE, "r");

    if (fp == NULL) {
        initializeDefaultStudents();
        return;
    }

    int count = 0;

    if (fscanf(fp, "%d\n", &count) != 1 ||
        count < 0) {

        fclose(fp);
        initializeDefaultStudents();
        return;
    }

    student_count = 0;

    for (int i = 0;
         i < count && i < MAX_STUDENTS; i++) {

        Student s;

        if (fscanf(fp, "%lld\n", &s.sap_id) != 1)
            break;

        if (fgets(s.roll_no, sizeof(s.roll_no), fp) == NULL)
            break;

        s.roll_no[strcspn(s.roll_no, "\r\n")] = '\0';

        if (fgets(s.name, sizeof(s.name), fp) == NULL)
            break;

        s.name[strcspn(s.name, "\r\n")] = '\0';

        if (fgets(s.phone, sizeof(s.phone), fp) == NULL)
            break;

        s.phone[strcspn(s.phone, "\r\n")] = '\0';

        if (fgets(s.email, sizeof(s.email), fp) == NULL)
            break;

        s.email[strcspn(s.email, "\r\n")] = '\0';

        if (fscanf(fp, "%d %d\n",
                   &s.year, &s.current_sem) != 2)
            break;

        int valid_record = 1;

        for (int j = 0; j < TOTAL_SEMESTERS; j++) {

            if (fscanf(fp, "%f", &s.sgpa[j]) != 1) {
                valid_record = 0;
                break;
            }
        }

        if (!valid_record)
            break;

        if (fscanf(fp, "%f\n", &s.cgpa) != 1) {
            calculateCGPA(&s);
        }

        students[student_count++] = s;
    }

    fclose(fp);

    if (student_count == 0) {

        initializeDefaultStudents();

    } else {

        printf("Loaded %d student records successfully.\n",
               student_count);
    }
}

/* Main function */
int main(void) {

    loadRecordsFromFile();

    int choice;

    do {

        printf("\n");

        printDivider('=', 65);

        printf(" AI-ASSISTED STUDENT RECORD & RESULT MANAGEMENT SYSTEM\n");
        printf(" UPES Dehradun | SAP ID: 590037088\n");

        printDivider('=', 65);

        printf("1. Add Student Details\n");
        printf("2. Display All Student Records\n");
        printf("3. Search Student Record\n");
        printf("4. Calculate All Students' CGPA & AI Advisor\n");
        printf("5. Calculate Year-Wise Average CGPA\n");
        printf("6. Sort Records by SAP ID\n");
        printf("7. Sort Records by Name\n");
        printf("8. Delete Student Record\n");
        printf("9. Save Records to File\n");
        printf("10. Reset Records to Default Students\n");
        printf("0. Exit Application\n");

        printDivider('-', 65);

        printf("Enter your choice (0-10): ");

        if (scanf("%d", &choice) != 1) {

            printf("Invalid input. Enter a number.\n");

            clearInputBuffer();

            choice = -1;

            continue;
        }

        clearInputBuffer();

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                calculateAllCGPA();
                break;

            case 5:
                calculateYearWiseAverage();
                break;

            case 6:
                sortBySapId();
                break;

            case 7:
                sortByName();
                break;

            case 8:
                deleteStudent();
                break;

            case 9:
                saveRecordsToFile();
                break;

            case 10:
                initializeDefaultStudents();
                printf("Records reset successfully.\n");
                displayAllStudents();
                break;

            case 0: {

                printf("Save records before exiting? (y/n): ");

                char save_opt;

                if (scanf("%c", &save_opt) == 1 &&
                    (save_opt == 'y' || save_opt == 'Y')) {

                    saveRecordsToFile();
                }

                clearInputBuffer();

                printf("Thank you for using the system!\n");

                break;
            }

            default:
                printf("Invalid option. Choose between 0 and 10.\n");
        }

    } while (choice != 0);

    return 0;
}