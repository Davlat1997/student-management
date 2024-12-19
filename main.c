#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char phone[15];
    char email[50];
} Contact;

typedef struct {
    char name[50];
    Contact contact;
} Parent;

typedef struct {
    char first_name[50];
    char last_name[50];
    int age;
    Contact contact;
    Parent parent;
} Student;

typedef struct {
    int id;
    char name[50];
} Lesson;

typedef struct {
    int score;
    Lesson lesson;
    Student student;
} Score;


Student* students = NULL;
Lesson* lessons = NULL;
Score* scores = NULL;

int student_count = 0;
int lesson_count = 0;
int score_count = 0;


void menu();
void add_student();
void add_lesson();
void add_score();
void view_students();
void view_student_details();
void find_student_by_name();
void view_lesson_statistics();
void list_lessons();
void list_scores();

void allocate_student();
void allocate_lesson();
void allocate_score();

int main() {
    menu();
   
    free(students);
    free(lessons);
    free(scores);
    return 0;
}



void menu() {
    int choice;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Add Student\n");
        printf("2. Add Lesson\n");
        printf("3. Add Score\n");
        printf("4. View Students\n");
        printf("5. View Student Details\n");
        printf("6. Find Student by Name\n");
        printf("7. View Lesson Statistics\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: add_lesson(); break;
            case 3: add_score(); break;
            case 4: view_students(); break;
            case 5: view_student_details(); break;
            case 6: find_student_by_name(); break;
            case 7: view_lesson_statistics(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 8);
}

void allocate_student() {
    students = realloc(students, (student_count + 1) * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed for students!\n");
        exit(1);
    }
}

void allocate_lesson() {
    lessons = realloc(lessons, (lesson_count + 1) * sizeof(Lesson));
    if (!lessons) {
        printf("Memory allocation failed for lessons!\n");
        exit(1);
    }
}

void allocate_score() {
    scores = realloc(scores, (score_count + 1) * sizeof(Score));
    if (!scores) {
        printf("Memory allocation failed for scores!\n");
        exit(1);
    }
}

void add_student() {
    allocate_student();
    printf("Enter first name: ");
    scanf("%s", students[student_count].first_name);

    printf("Enter last name: ");
    scanf("%s", students[student_count].last_name);

    printf("Enter age: ");
    scanf("%d", &students[student_count].age);

    printf("Enter phone: ");
    scanf("%s", students[student_count].contact.phone);

    printf("Enter email: ");
    scanf("%s", students[student_count].contact.email);

    printf("Enter parent's name: ");
    scanf("%s", students[student_count].parent.name);

    printf("Enter parent's phone: ");
    scanf("%s", students[student_count].parent.contact.phone);

    printf("Enter parent's email: ");
    scanf("%s", students[student_count].parent.contact.email);

    student_count++;
    printf("Student added successfully!\n");
}

void add_lesson() {
    allocate_lesson();
    printf("Enter lesson name: ");
    getchar(); // Clear newline buffer
    fgets(lessons[lesson_count].name, sizeof(lessons[lesson_count].name), stdin);
    lessons[lesson_count].name[strcspn(lessons[lesson_count].name, "\n")] = '\0'; // Remove newline character
    lessons[lesson_count].id = lesson_count;
    lesson_count++;
    printf("Lesson added successfully!\n");
}

void add_score() {
    if (student_count == 0 || lesson_count == 0) {
        printf("Please add students and lessons first.\n");
        return;
    }

    allocate_score();
    view_students();
    printf("Enter student ID: ");
    int student_id;
    scanf("%d", &student_id);

    list_lessons();
    printf("Enter lesson ID: ");
    int lesson_id;
    scanf("%d", &lesson_id);

    scores[score_count].student = students[student_id];
    scores[score_count].lesson = lessons[lesson_id];

    printf("Enter score: ");
    scanf("%d", &scores[score_count].score);

    score_count++;
    printf("Score added successfully!\n");
}

void view_students() {
    printf("\n%-3s | %-15s | %-15s | %-3s | %-15s\n", "ID", "First Name", "Last Name", "Age", "Parent's Name");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%-3d | %-15s | %-15s | %-3d | %-15s\n",
               i, students[i].first_name, students[i].last_name,
               students[i].age, students[i].parent.name);
    }
}

void view_student_details() {
    view_students();
    printf("Enter student ID: ");
    int id;
    scanf("%d", &id);

    if (id < 0 || id >= student_count) {
        printf("Invalid ID!\n");
        return;
    }

    printf("\nFirst Name: %s\n", students[id].first_name);
    printf("Last Name: %s\n", students[id].last_name);
    printf("Age: %d\n", students[id].age);
    printf("Phone: %s\n", students[id].contact.phone);
    printf("Email: %s\n", students[id].contact.email);
    printf("Parent's Name: %s\n", students[id].parent.name);
    printf("Parent's Phone: %s\n", students[id].parent.contact.phone);
    printf("Parent's Email: %s\n", students[id].parent.contact.email);
}

void find_student_by_name() {
    char name[50];
    printf("Enter first name: ");
    scanf("%s", name);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].first_name, name) == 0) {
            printf("Found student with ID: %d\n", i);
            view_student_details();
            return;
        }
    }
    printf("Student not found.\n");
}

void view_lesson_statistics() {
    list_lessons();
    printf("Enter lesson ID: ");
    int id;
    scanf("%d", &id);

    if (id < 0 || id >= lesson_count) {
        printf("Invalid ID!\n");
        return;
    }

    printf("\nScores for lesson: %s\n", lessons[id].name);
    printf("%-3s | %-15s | %-15s | %-5s\n", "ID", "First Name", "Last Name", "Score");
    printf("----------------------------------------\n");

    for (int i = 0; i < score_count; i++) {
        if (strcmp(scores[i].lesson.name, lessons[id].name) == 0) {
            printf("%-3d | %-15s | %-15s | %-5d\n",
                   i, scores[i].student.first_name,
                   scores[i].student.last_name,
                   scores[i].score);
        }
    }
}

void list_lessons() {
    printf("\n%-3s | %-15s\n", "ID", "Lesson Name");
    printf("------------------------\n");
    for (int i = 0; i < lesson_count; i++) {
        printf("%-3d | %-15s\n", i, lessons[i].name);
    }
}

void list_scores() {
    printf("\n%-3s | %-15s | %-15s | %-5s | %-15s\n",
           "ID", "First Name", "Last Name", "Score", "Lesson");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < score_count; i++) {
        printf("%-3d | %-15s | %-15s | %-5d | %-15s\n",
               i, scores[i].student.first_name,
               scores[i].student.last_name,
               scores[i].score,
               scores[i].lesson.name);
    }
}