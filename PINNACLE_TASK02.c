#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100
#define CLEAR_SCREEN() printf("\033[H\033[J")

typedef struct {
    char description[MAX_LEN];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (!file) {
        printf("Warning: Could not open tasks file. Starting fresh.\n");
        return;
    }
    taskCount = 0;
    while (fscanf(file, "%d ", &tasks[taskCount].completed) == 1 && fgets(tasks[taskCount].description, MAX_LEN, file)) {
        tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = 0;
        taskCount++;
    }
    fclose(file);
}

void saveTasks() {
    FILE *file = fopen("tasks.txt", "w");
    if (!file) {
        printf("Error: Unable to save tasks.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d %s\n", tasks[i].completed, tasks[i].description);
    }
    fclose(file);
}

void displayTasks() {
    printf("\nTo-Do List:\n");
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%c] %s\n", i + 1, tasks[i].completed ? 'X' : ' ', tasks[i].description);
    }
}

void addTask() {
    CLEAR_SCREEN();
    if (taskCount >= MAX_TASKS) {
        printf("\nTask list is full!\n");
        return;
    }
    printf("Enter task description: ");
    getchar();
    if (!fgets(tasks[taskCount].description, MAX_LEN, stdin)) {
        printf("\nError reading input!\n");
        return;
    }
    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = 0;
    tasks[taskCount].completed = 0;
    taskCount++;
    saveTasks();
    printf("\nTask added successfully!\n");
}

void editTask() {
    CLEAR_SCREEN();
    displayTasks();
    if (taskCount == 0)
        return;
    int index;
    printf("\nEnter task number to edit: ");
    if (scanf("%d", &index) != 1 || index <= 0 || index > taskCount) {
        printf("\nInvalid task number!\n");
        return;
    }
    printf("Enter new description: ");
    getchar();
    if (!fgets(tasks[index - 1].description, MAX_LEN, stdin)) {
        printf("\nError reading input!\n");
        return;
    }
    tasks[index - 1].description[strcspn(tasks[index - 1].description, "\n")] = 0;
    saveTasks();
    printf("\nTask updated successfully!\n");
}

void markComplete() {
    CLEAR_SCREEN();
    displayTasks();
    if (taskCount == 0)
        return;
    int index;
    printf("\nEnter task number to mark complete: ");
    if (scanf("%d", &index) != 1 || index <= 0 || index > taskCount) {
        printf("\nInvalid task number!\n");
        return;
    }
    tasks[index - 1].completed = 1;
    saveTasks();
    printf("\nTask marked as complete!\n");
}

void deleteTask() {
    CLEAR_SCREEN();
    displayTasks();
    if (taskCount == 0) return;
    int index;
    printf("\nEnter task number to delete: ");
    if (scanf("%d", &index) != 1 || index <= 0 || index > taskCount) {
        printf("\nInvalid task number!\n");
        return;
    }
    for (int i = index - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--;
    saveTasks();
    printf("\nTask deleted successfully!\n");
}

void viewTasks() {
    CLEAR_SCREEN();
    displayTasks();
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

int main() {
    loadTasks();
    int choice;
    do {
        CLEAR_SCREEN();
        printf("To-Do List:\n\n");
        printf("1. Add Task\n2. Edit Task\n3. Mark Complete\n4. Delete Task\n5. View Tasks\n6. Exit\n");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
            case 1: addTask();
            break;
            case 2: editTask();
            break;
            case 3: markComplete();
            break;
            case 4: deleteTask();
            break;
            case 5: viewTasks();
            break;
            case 6:
            break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}
