#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STAGES 8

// Global array to hold training results, 0: not attempted, 'P': pass, 'F': fail
char trainingResults[MAX_STAGES] = {0};

// Function prototypes
void mainMenu();
void auditionManagement();
void trainingMenu();
void debut();

void enterEvaluation(int stage);
int canAccessStage(int stage);
void displayTrainingStatus();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Audition Management\n");
        printf("2. Training\n");
        printf("3. Debut\n");
        printf("Q. Quit\n");
        printf("Select an option: ");

        char choice[10];
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            auditionManagement();
        } else if (strcmp(choice, "2") == 0) {
            trainingMenu();
        } else if (strcmp(choice, "3") == 0) {
            debut();
        } else if (strcmp(choice, "Q") == 0 || strcmp(choice, "q") == 0 || strcmp(choice, "0") == 0 || choice[0] == '\0') {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void auditionManagement() {
    printf("\n-- Audition Management --\n");
    printf("Functionality not implemented.\n");
    // Placeholder for actual implementation
}

void debut() {
    printf("\n-- Debut --\n");
    printf("Functionality not implemented.\n");
    // Placeholder for actual implementation
}

// Display current training progress
void displayTrainingStatus() {
    printf("\nCurrent Training Status:\n");
    for (int i = 0; i < MAX_STAGES; i++) {
        printf("%d. %s : ", i + 1, 
               (i == 0) ? "Physical Strength & Knowledge" :
               (i == 1) ? "Self-Management & Teamwork" :
               (i == 2) ? "Language & Pronunciation" :
               (i == 3) ? "Vocal" :
               (i == 4) ? "Dance" :
               (i == 5) ? "Visual & Image" :
               (i == 6) ? "Acting & Stage Performance" :
                        "Fan Communication");
        if (trainingResults[i] == 'P') printf("Passed\n");
        else if (trainingResults[i] == 'F') printf("Failed\n");
        else printf("Not attempted\n");
    }
}

int canAccessStage(int stage) {
    // Stage is 0-based index
    if (stage == 0) return 1; // First stage can always be accessed
    if (stage == 1) {
        // Second stage depends on first
        if (trainingResults[0] == 'P') return 1;
        else return 0;
    }
    // For stages 3-7, check if previous stages 0 and 1 are passed
    if (trainingResults[0] == 'P' && trainingResults[1] == 'P') {
        // Also ensure this stage not already passed
        if (trainingResults[stage] != 'P') return 1;
    }
    return 0;
}

void enterEvaluation(int stage) {
    // stage is 0-based index
    if (!canAccessStage(stage)) {
        printf("You cannot access this stage yet.\n");
        return;
    }

    if (trainingResults[stage] == 'P') {
        printf("This stage has already been passed.\n");
        return;
    }

    printf("\n-- %s --\n", 
        (stage == 0) ? "Physical Strength & Knowledge" :
        (stage == 1) ? "Self-Management & Teamwork" :
        (stage == 2) ? "Language & Pronunciation" :
        (stage == 3) ? "Vocal" :
        (stage == 4) ? "Dance" :
        (stage == 5) ? "Visual & Image" :
        (stage == 6) ? "Acting & Stage Performance" :