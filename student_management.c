#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
void sortStudents();

// Add a new student
void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "a");

    if (!fp) {
        printf("❌ Error opening file!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    fclose(fp);

    printf("✅ Student added successfully!\n");
}

// Display all students
void displayStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r");

    if (!fp) {
        printf("❌ No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        printf("ID: %d | Name: %s | Age: %d | Marks: %.2f\n", 
               s.id, s.name, s.age, s.marks);
    }
    fclose(fp);
    printf("------------------------\n");
}

// Search a student by ID
void searchStudent() {
    int id, found = 0;
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r");

    if (!fp) {
        printf("❌ No records found!\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        if (s.id == id) {
            printf("\n✅ Student Found:\n");
            printf("ID: %d | Name: %s | Age: %d | Marks: %.2f\n", 
                   s.id, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("❌ Student not found!\n");
    }

    fclose(fp);
}

// Delete a student by ID
void deleteStudent() {
    int id, found = 0;
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp) {
        printf("❌ No records found!\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        if (s.id != id) {
            fprintf(temp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("🗑️ Student deleted successfully!\n");
    } else {
        printf("❌ Student not found!\n");
    }
}

// Update/Edit student record
void updateStudent() {
    int id, found = 0;
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp) {
        printf("❌ No records found!\n");
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        if (s.id == id) {
            printf("Editing student (ID %d)\n", id);
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Age: ");
            scanf("%d", &s.age);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fprintf(temp, "%d %s %d %.2f\n", s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("✏️ Student record updated successfully!\n");
    } else {
        printf("❌ Student not found!\n");
    }
}

// Sort students by marks or name
void sortStudents() {
    struct Student arr[100], s;
    int count = 0, i, j, choice;
    FILE *fp = fopen(FILE_NAME, "r");

    if (!fp) {
        printf("❌ No records found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %d %f", &s.id, s.name, &s.age, &s.marks) != EOF) {
        arr[count++] = s;
    }
    fclose(fp);

    if (count == 0) {
        printf("❌ No students to sort!\n");
        return;
    }

    printf("Sort by:\n1. Name\n2. Marks\nChoose: ");
    scanf("%d", &choice);

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            int cmp = 0;
            if (choice == 1) {
                cmp = strcmp(arr[i].name, arr[j].name);
            } else if (choice == 2) {
                cmp = (arr[i].marks > arr[j].marks);
            }
            if (cmp > 0) {
                struct Student temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    printf("\n--- Sorted Students ---\n");
    for (i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Age: %d | Marks: %.2f\n",
               arr[i].id, arr[i].name, arr[i].age, arr[i].marks);
    }
    printf("------------------------\n");
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Sort Students\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: sortStudents(); break;
            case 7: printf("👋 Exiting...\n"); exit(0);
            default: printf("❌ Invalid option!\n");
        }
    }

    return 0;
}
