#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 10
#define MAX_NAME_LENGTH 50
#define FITNESS_TESTS 7
#define DAYS_PER_WEEK 6

struct Member {
    char name[MAX_NAME_LENGTH];
    char nickname[MAX_NAME_LENGTH];
};

/* Global arrays */
struct Member milliways_members[MAX_MEMBERS];
float health_scores[MAX_MEMBERS][FITNESS_TESTS];
int member_routine[MAX_MEMBERS][DAYS_PER_WEEK][3]; /* Max 3 exercises per day */
int total_members = 0;

/* Exercise types: 15 exercises total (3 per category) */
char exercises[15][20] = {
    "Running", "Cycling", "Fast Walking",           /* Cardio: 0-2 */
    "Push-ups", "Squats", "Burpees",               /* Full-body: 3-5 */
    "Leg Press", "Leg Curl", "Lunges",             /* Lower-body: 6-8 */
    "Pull-ups", "Chin-ups", "Bench Press",         /* Upper-body: 9-11 */
    "Plank", "Crunches", "Russian Twists"          /* Core: 12-14 */
};

char exercise_categories[5][20] = {"Cardio", "Full-body", "Lower-body", "Upper-body", "Core"};
char days[6][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/* Helper functions */
int findMember(char nickname[]) {
    int i;
    for (i = 0; i < total_members; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0) return i;
    }
    return -1;
}

int getExerciseType(int exercise_id) {
    return exercise_id / 3; /* 0=Cardio, 1=Full-body, 2=Lower-body, 3=Upper-body, 4=Core */
}

void displayMemberList() {
    int i;
    printf("\n=== MEMBER LIST ===\n");
    for (i = 0; i < total_members; i++) {
        printf("%d. %s (%s)\n", i+1, milliways_members[i].name, milliways_members[i].nickname);
    }
}

void displayExerciseMenu() {
    int i;
    printf("\n=== AVAILABLE EXERCISES ===\n");
    for (i = 0; i < 15; i++) {
        printf("%2d. %-15s (%s)\n", i+1, exercises[i], exercise_categories[getExerciseType(i)]);
    }
}

/* Core Functions */
int addMember(char name[], char nickname[]) {
    if (total_members >= MAX_MEMBERS) {
        printf("Maximum members reached!\n");
        return 0;
    }
    
    strcpy(milliways_members[total_members].name, name);
    strcpy(milliways_members[total_members].nickname, nickname);
    
    /* Initialize arrays */
    int i, j, k;
    for (i = 0; i < FITNESS_TESTS; i++) health_scores[total_members][i] = -1.0;
    for (j = 0; j < DAYS_PER_WEEK; j++) {
        for (k = 0; k < 3; k++) member_routine[total_members][j][k] = -1;
    }
    
    total_members++;
    printf("Member added: %s (%s)\n", name, nickname);
    return 1;
}

int setHealth(char nickname[], char csv_data[]) {
    int member_index = findMember(nickname);
    if (member_index == -1) {
        printf("Member '%s' not found!\n", nickname);
        return 0;
    }
    
    char temp[200];
    strcpy(temp, csv_data);
    char *token = strtok(temp, ",");
    int count = 0;
    
    while (token != NULL && count < FITNESS_TESTS) {
        health_scores[member_index][count] = atof(token);
        token = strtok(NULL, ",");
        count++;
    }
    
    if (count != FITNESS_TESTS) {
        printf("Error: Need exactly %d values, got %d\n", FITNESS_TESTS, count);
        return 0;
    }
    
    printf("Fitness data saved for %s!\n", nickname);
    return 1;
}

void getHealth(int mode, char nickname[], int test_number) {
    if (mode == 0) { /* Show all data */
        printf("\n=== ALL FITNESS DATA ===\n");
        printf("%-15s %-10s Run  Sprint Push Squat Arm  Swim Weight\n", "Name", "Nickname");
        int i, j;
        for (i = 0; i < total_members; i++) {
            printf("%-15s %-10s", milliways_members[i].name, milliways_members[i].nickname);
            for (j = 0; j < FITNESS_TESTS; j++) {
                if (health_scores[i][j] >= 0) printf("%-5.1f", health_scores[i][j]);
                else printf("%-5s", "N/A");
            }
            printf("\n");
        }
    } else {
        int member_index = findMember(nickname);
        if (member_index == -1) {
            printf("Member '%s' not found!\n", nickname);
            return;
        }
        
        if (mode == 1) { /* Show member data */
            printf("\n=== FITNESS DATA FOR %s (%s) ===\n", 
                   milliways_members[member_index].name, nickname);
            char tests[7][15] = {"1-Mile Run", "Speed Sprint", "Push-ups", "Squats", 
                               "Arm Strength", "Swimming", "Weightlifting"};
            int i;
            for (i = 0; i < FITNESS_TESTS; i++) {
                printf("%-15s: ", tests[i]);
                if (health_scores[member_index][i] >= 0) printf("%.1f\n", health_scores[member_index][i]);
                else printf("No data\n");
            }
        }
    }
}

int setExerciseRoutine(char nickname[]) {
    int member_index = findMember(nickname);
    if (member_index == -1) {
        printf("Member '%s' not found!\n", nickname);
        return 0;
    }
    
    printf("\nSetting routine for %s (%s)\n", milliways_members[member_index].name, nickname);
    printf("Rules: Each day needs 1+ cardio (1-3) + 1+ strength/core (4-15)\n");
    printf("Core exercises (13-15) allowed only once per week!\n");
    
    displayExerciseMenu();
    
    int day, slot, exercise, core_used = 0;
    for (day = 0; day < DAYS_PER_WEEK; day++) {
        printf("\n=== %s ===\n", days[day]);
        
        int has_cardio = 0, has_strength = 0;
        for (slot = 0; slot < 3; slot++) {
            printf("Exercise %d (0 to finish day): ", slot + 1);
            scanf("%d", &exercise);
            
            if (exercise == 0) break;
            if (exercise < 1 || exercise > 15) {
                printf("Invalid exercise! Choose 1-15\n");
                slot--; continue;
            }
            
            exercise--; /* Convert to 0-based index */
            int type = getExerciseType(exercise);
            
            if (type == 4) { /* Core exercise */
                if (core_used) {
                    printf("Core exercise already used this week!\n");
                    slot--; continue;
                }
                core_used = 1;
            }
            
            member_routine[member_index][day][slot] = exercise;
            printf("Added: %s\n", exercises[exercise]);
            
            if (type == 0) has_cardio = 1;
            if (type >= 1) has_strength = 1;
        }
        
        if (!has_cardio || !has_strength) {
            printf("Warning: %s needs cardio + strength/core!\n", days[day]);
        }
    }
    
    printf("Routine set for %s!\n", nickname);
    return 1;
}

void getExerciseRoutine(char nickname[]) {
    int member_index = findMember(nickname);
    if (member_index == -1) {
        printf("Member '%s' not found!\n", nickname);
        return;
    }
    
    printf("\n=== WORKOUT ROUTINE FOR %s (%s) ===\n", 
           milliways_members[member_index].name, nickname);
    
    int day, slot;
    for (day = 0; day < DAYS_PER_WEEK; day++) {
        printf("\n%s:\n", days[day]);
        int has_exercises = 0;
        
        for (slot = 0; slot < 3; slot++) {
            if (member_routine[member_index][day][slot] != -1) {
                int ex_id = member_routine[member_index][day][slot];
                printf("  - %s (%s)\n", exercises[ex_id], exercise_categories[getExerciseType(ex_id)]);
                has_exercises = 1;
            }
        }
        
        if (!has_exercises) printf("  No exercises assigned\n");
    }
}

void showMenu() {
    printf("\n=== MILLIWAYS FITNESS TRACKER ===\n");
    printf("1. Add Member\n2. Enter Fitness Data\n3. View All Fitness Data\n");
    printf("4. View Member Fitness Data\n5. Set Exercise Routine\n");
    printf("6. View Exercise Routine\n7. Show Member List\n8. Exit\n");
    printf("Choose (1-8): ");
}

int main() {
    int choice;
    char name[MAX_NAME_LENGTH], nickname[MAX_NAME_LENGTH], fitness_data[200];
    
    printf("Welcome to Milliways Fitness Tracker!\n");
    
    while (1) {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf(" %[^\n]", name);
                printf("Enter nickname: ");
                scanf(" %[^\n]", nickname);
                addMember(name, nickname);
                break;
                
            case 2:
                printf("Enter nickname: ");
                scanf(" %[^\n]", nickname);
                printf("Enter 7 scores (comma-separated): ");
                scanf(" %[^\n]", fitness_data);
                setHealth(nickname, fitness_data);
                break;
                
            case 3:
                getHealth(0, "", 0);
                break;
                
            case 4:
                printf("Enter nickname: ");
                scanf(" %[^\n]", nickname);
                getHealth(1, nickname, 0);
                break;
                
            case 5:
                printf("Enter nickname: ");
                scanf(" %[^\n]", nickname);
                setExerciseRoutine(nickname);
                break;
                
            case 6:
                printf("Enter nickname: ");
                scanf(" %[^\n]", nickname);
                getExerciseRoutine(nickname);
                break;
                
            case 7:
                displayMemberList();
                break;
                
            case 8:
                printf("Thank you!\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}