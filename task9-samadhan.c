/* ================== STUDENT DIRECTORY=========================================
   Frontend  : Console menu (UI)
   Backend   : CRUD operations (Add, Search, Update, Delete, List)
   Storage   : In-memory only (local state, no files)
   =========================================================================== */

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_LEN 50

/* ------------------------------ Data Model -------------------------------- */
struct Student {
    int  roll;
    char name[MAX_LEN];
    char dept[MAX_LEN];
    char phone[MAX_LEN];
};

/* ---------------------------- Global Storage ------------------------------ */
struct Student students[MAX_STUDENTS];
int studentCount = 0;

/* ------------------------------ Prototypes -------------------------------- */
int  findStudentIndex(int roll);
int  addStudent(struct Student s);
int  updateStudent(int roll, struct Student s);
int  deleteStudent(int roll);
void listStudents(void);

int  readInt(const char *label);
void readLine(const char *label, char *buf, int maxlen);
void pauseScreen(void);

/* ------------------------------- Backend ---------------------------------- */
int findStudentIndex(int roll) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].roll == roll) return i;
    }
    return -1;
}

int addStudent(struct Student s) {
    if (studentCount >= MAX_STUDENTS) return 0;          
    if (findStudentIndex(s.roll) != -1) return -1;     
    students[studentCount++] = s;
    return 1;
}

int updateStudent(int roll, struct Student s) {
    int idx = findStudentIndex(roll);
    if (idx == -1) return 0;
    students[idx] = s;  // overwrite with new details
    return 1;
}

int deleteStudent(int roll) {
    int idx = findStudentIndex(roll);
    if (idx == -1) return 0;
    for (int i = idx; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    return 1;
}

void listStudents(void) {
    if (studentCount == 0) {
        printf("\nNo records found.\n");
        return;
    }
    printf("\n%-6s %-20s %-12s %-12s\n", "Roll", "Name", "Dept", "Phone");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-6d %-20s %-12s %-12s\n",
               students[i].roll,
               students[i].name,
               students[i].dept,
               students[i].phone);
    }
}

/* ----------------------------- Frontend/UI -------------------------------- */
int readInt(const char *label) {
    int x;
    printf("%s", label);
    scanf("%d", &x);
    getchar(); // clear newline left by scanf
    return x;
}

void readLine(const char *label, char *buf, int maxlen) {
    printf("%s", label);
    fgets(buf, maxlen, stdin);
    buf[strcspn(buf, "\n")] = 0; // remove newline
}

void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    getchar();
}

/* --------------------------------- MAIN ----------------------------------- */
int main(void) {
    int choice, roll;
    struct Student s;
    int status, idx;

    do {
        printf("\n================= STUDENT DIRECTORY =================\n");
        printf("1. Add Student\n");
        printf("2. List All Students\n");
        printf("3. Search Student by Roll\n");
        printf("4. Update Student by Roll\n");
        printf("5. Delete Student by Roll\n");
        printf("6. Exit\n");
        printf("=====================================================\n");
        choice = readInt("Enter choice: ");

        if (choice == 1) {
            s.roll = readInt("Enter Roll: ");
            readLine("Enter Name : ",  s.name,  MAX_LEN);
            readLine("Enter Dept : ",  s.dept,  MAX_LEN);
            readLine("Enter Phone: ",  s.phone, MAX_LEN);

            status = addStudent(s);
            if (status == 1)       printf("\nStudent added successfully.\n");
            else if (status == -1) printf("\nRoll already exists. Add failed.\n");
            else                   printf("\nDirectory full. Add failed.\n");
            pauseScreen();
        }
        else if (choice == 2) {
            listStudents();
            pauseScreen();
        }
        else if (choice == 3) {
            roll = readInt("Enter Roll to search: ");
            idx = findStudentIndex(roll);
            if (idx == -1) {
                printf("\nNot found.\n");
            } else {
                printf("\nFound:\n");
                printf("Roll : %d\nName : %s\nDept : %s\nPhone: %s\n",
                       students[idx].roll, students[idx].name,
                       students[idx].dept, students[idx].phone);
            }
            pauseScreen();
        }
        else if (choice == 4) {
            roll = readInt("Enter Roll to update: ");
            idx  = findStudentIndex(roll);
            if (idx == -1) {
                printf("\nNot found.\n");
            } else {
                printf("\nEnter new details (roll will remain %d):\n", roll);
                s.roll = roll;
                readLine("New Name : ",  s.name,  MAX_LEN);
                readLine("New Dept : ",  s.dept,  MAX_LEN);
                readLine("New Phone: ",  s.phone, MAX_LEN);
                if (updateStudent(roll, s))
                    printf("\nUpdated.\n");
                else
                    printf("\nUpdate failed.\n");
            }
            pauseScreen();
        }
        else if (choice == 5) {
            roll = readInt("Enter Roll to delete: ");
            if (deleteStudent(roll)) printf("\nDeleted.\n");
            else                     printf("\nNot found.\n");
            pauseScreen();
        }
        else if (choice == 6) {
            printf("\nExiting... (data is in memory only; not saved)\n");
        }
        else {
            printf("\nInvalid choice.\n");
            pauseScreen();
        }
    } while (choice != 6);

    return 0;
}
