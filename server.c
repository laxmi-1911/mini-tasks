/* ================== TO-DO APP IN C ==================*/

#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN   100

/*Data Model*/
struct Task {
    int id;
    char text[MAX_LEN];
    int done; // 0 = pending, 1 = done
};

struct Task tasks[MAX_TASKS];
int taskCount = 0;
int nextId = 1;

/*Backend (CRUD)*/
void addTask(const char *text) {
    if (taskCount >= MAX_TASKS) {
        printf("⚠️ Task list is full!\n");
        return;
    }
    tasks[taskCount].id = nextId++;
    strcpy(tasks[taskCount].text, text);
    tasks[taskCount].done = 0;
    taskCount++;
    printf("✅ Task added!\n");
}

void listTasks() {
    if (taskCount == 0) {
        printf("No tasks yet!\n");
        return;
    }
    printf("\n---- TO-DO LIST ----\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%c] %s\n", 
               tasks[i].id, 
               tasks[i].done ? 'X' : ' ',
               tasks[i].text);
    }
    printf("---------------------\n");
}

void toggleTask(int id) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            tasks[i].done = !tasks[i].done;
            printf("🔄 Task %d marked as %s\n", id, tasks[i].done ? "done" : "pending");
            return;
        }
    }
    printf("⚠️ Task not found!\n");
}

void deleteTask(int id) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            taskCount--;
            printf("🗑️ Task %d deleted\n", id);
            return;
        }
    }
    printf("⚠️ Task not found!\n");
}

/*Frontend (Menu UI) */
void menu() {
    printf("\n====== TO-DO APP ======\n");
    printf("1. Add Task\n");
    printf("2. List Tasks\n");
    printf("3. Toggle Task (Done/Pending)\n");
    printf("4. Delete Task\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

/*  Main  */
int main() {
    int choice, id;
    char text[MAX_LEN];

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(text, MAX_LEN, stdin);
                text[strcspn(text, "\n")] = '\0'; // remove newline
                addTask(text);
                break;
            case 2:
                listTasks();
                break;
            case 3:
                printf("Enter task id to toggle: ");
                scanf("%d", &id);
                toggleTask(id);
                break;
            case 4:
                printf("Enter task id to delete: ");
                scanf("%d", &id);
                deleteTask(id);
                break;
            case 5:
                printf("👋 Exiting... Bye!\n");
                return 0;
            default:
                printf("⚠️ Invalid choice! Try again.\n");
        }
    }
}
