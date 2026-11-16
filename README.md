# AI-Assisted Student Record and Result Management System

**Course:** Programming in C  
**Program:** B.Tech CSE, Semester I  
**University:** University of Petroleum and Energy Studies

## 1. Introduction
This is a simple, menu-driven C program for maintaining student records and viewing academic results. It is made using basic C programming concepts such as structures, arrays, functions, loops, conditional statements and strings.

## 2. Objectives
- Store details of students in one place.
- Search, display and delete student records.
- Calculate a student's CGPA from the available SGPA values.
- Find the average CGPA of students in each year.
- Display records in increasing order of SAP ID or name.
- Give simple academic suggestions based on CGPA.

## 3. Features
1. Add student details (SAP ID, roll number, name, phone, email, year, semester and SGPA for eight semesters).
2. Search using SAP ID.
3. Display all student records.
4. Calculate year-wise average CGPA.
5. Delete a student record.
6. Sort records by SAP ID.
7. Sort records by name.
8. Show an academic-advisor message based on CGPA.

The program can store up to 100 student records during one run. Records are held in an array while the program is running; they are not saved permanently after the program is closed. Permanent file storage was not listed as a required feature in the assignment instructions.

## 4. CGPA Calculation
The program adds the SGPA values greater than zero and divides the total by the number of available SGPA values. A value of `0` means that the semester has not been completed and is not included in the average.

## 5. Academic Advisor
The advisor uses simple `if-else` conditions. The categories used are:
- 8.50 and above: Excellent Performance
- 7.00 to 8.49: Good Performance
- 5.00 to 6.99: Needs Improvement
- Below 5.00: Requires Immediate Attention

These are simple project categories for demonstration, not official university grading rules.

## 6. C Concepts Used
- `struct` to group student details.
- Arrays to store multiple students and eight SGPA values.
- Functions to divide the program into smaller tasks.
- `if-else` and `switch` for decisions.
- `for` and `do-while` loops.
- String functions such as `strcmp()` and `strcspn()`.
- Basic input/output using `printf()` and `fgets()`.

## 7. How to Compile and Run
Using GCC:

```bash
gcc 590037088_ID.c -o student_record
./student_record
```

## 8. Limitations
- Up to 100 records can be stored in one run.
- Records are not retained after the program exits.
- The academic-advisor messages are basic suggestions based on CGPA and do not replace advice from teachers or academic counsellors.
