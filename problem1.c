#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Constants - make the code easier to understand and change */
#define MAX_MEMBERS 10          /* Maximum number of members */
#define MAX_NAME_LENGTH 50      /* Maximum length for names */
#define FITNESS_TESTS 7         /* Number of fitness tests */

/* 
 * Structure to store member information
 * This groups related data together
 */
struct Member {
    char name[MAX_NAME_LENGTH];
    char nickname[MAX_NAME_LENGTH];
};

/* Global variables - accessible throughout the program */
struct Member milliways_members[MAX_MEMBERS];  /* Array to store all members */
float health_scores[MAX_MEMBERS][FITNESS_TESTS]; /* 2D array for fitness scores */
int total_members = 0;  /* Keep track of how many members we have */

/* 
 * Function to add a new member to our system
 * Takes: member's full name and nickname
 * Returns: 1 if successful, 0 if failed
 */
int addMember(char name[], char nickname[]) {
    /* Check if we have space for more members */
    if (total_members >= MAX_MEMBERS) {
        printf("Sorry! Cannot add more members. Maximum limit reached.\n");
        return 0;
    }
    
    /* Copy the name and nickname to our member array */
    strcpy(milliways_members[total_members].name, name);
    strcpy(milliways_members[total_members].nickname, nickname);
    
    /* Initialize all fitness scores to -1 (means no data yet) */
    int i;
    for (i = 0; i < FITNESS_TESTS; i++) {
        health_scores[total_members][i] = -1.0;
    }
    
    total_members++;  /* Increase our member count */
    printf("Member added successfully: %s (%s)\n", name, nickname);
    return 1;
}

/* 
 * Function to find a member by their nickname
 * Takes: nickname to search for
 * Returns: member's position in array, or -1 if not found
 */
int findMember(char nickname[]) {
    int i;
    for (i = 0; i < total_members; i++) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0) {
            return i;  /* Found the member! */
        }
    }
    return -1;  /* Member not found */
}

/* 
 * Function to parse comma-separated fitness data
 * Takes: input string with comma-separated values, array to store results
 * Returns: number of values parsed
 */
int parseCSVData(char input[], float results[]) {
    char temp_input[200];  /* Temporary copy of input */
    char *token;           /* Pointer for string parsing */
    int count = 0;
    
    strcpy(temp_input, input);  /* Make a copy so we don't change original */
    
    /* Use strtok to split the string by commas */
    token = strtok(temp_input, ",");
    
    while (token != NULL && count < FITNESS_TESTS) {
        results[count] = atof(token);  /* Convert string to float */
        token = strtok(NULL, ",");     /* Get next token */
        count++;
    }
    
    return count;  /* Return how many values we found */
}

/* 
 * setHealth() - Main function to enter fitness data
 * Takes: member's nickname and comma-separated fitness scores
 * Returns: 1 if successful, 0 if failed
 */
int setHealth(char nickname[], char csv_data[]) {
    int member_index;
    float fitness_values[FITNESS_TESTS];
    int values_count;
    int i;
    
    /* First, find the member */
    member_index = findMember(nickname);
    if (member_index == -1) {
        printf("Error: Member '%s' not found!\n", nickname);
        return 0;
    }
    
    /* Parse the comma-separated data */
    values_count = parseCSVData(csv_data, fitness_values);
    
    /* Check if we got the right number of values */
    if (values_count != FITNESS_TESTS) {
        printf("Error: Need exactly %d fitness scores, but got %d\n", 
               FITNESS_TESTS, values_count);
        return 0;
    }
    
    /* Store all the fitness scores */
    for (i = 0; i < FITNESS_TESTS; i++) {
        health_scores[member_index][i] = fitness_values[i];
    }
    
    printf("Fitness data saved for %s!\n", nickname);
    return 1;
}

/* 
 * Function to display all fitness data in a nice table
 */
void showAllFitnessData() {
    /* Names of our fitness tests */
    char test_names[FITNESS_TESTS][20] = {
        "1-Mile Run", "Speed Sprint", "Push-ups", "Squats", 
        "Arm Strength", "Swimming", "Weightlifting"
    };
    
    int i, j;
    
    printf("\n=== ALL MEMBERS FITNESS DATA ===\n");
    printf("%-15s %-15s", "Name", "Nickname");
    
    /* Print header with test names */
    for (j = 0; j < FITNESS_TESTS; j++) {
        printf("%-12s ", test_names[j]);
    }
    printf("\n");
    
    /* Print a line separator */
    for (i = 0; i < 80; i++) {
        printf("-");
    }
    printf("\n");
    
    /* Print data for each member */
    for (i = 0; i < total_members; i++) {
        printf("%-15s %-15s", 
               milliways_members[i].name, 
               milliways_members[i].nickname);
        
        /* Print fitness scores */
        for (j = 0; j < FITNESS_TESTS; j++) {
            if (health_scores[i][j] >= 0) {
                printf("%-12.1f ", health_scores[i][j]);
            } else {
                printf("%-12s ", "No Data");
            }
        }
        printf("\n");
    }
}

/* 
 * Function to show fitness data for one specific member
 */
void showMemberFitnessData(char nickname[]) {
    int member_index;
    char test_names[FITNESS_TESTS][20] = {
        "1-Mile Run", "Speed Sprint", "Push-ups", "Squats", 
        "Arm Strength", "Swimming", "Weightlifting"
    };
    int i;
    
    member_index = findMember(nickname);
    if (member_index == -1) {
        printf("Error: Member '%s' not found!\n", nickname);
        return;
    }
    
    printf("\n=== FITNESS DATA FOR %s (%s) ===\n", 
           milliways_members[member_index].name, nickname);
    
    for (i = 0; i < FITNESS_TESTS; i++) {
        printf("%-15s: ", test_names[i]);
        if (health_scores[member_index][i] >= 0) {
            printf("%.1f\n", health_scores[member_index][i]);
        } else {
            printf("No data entered\n");
        }
    }
}

/* 
 * Function to show a specific test result for a member
 */
void showSpecificTestResult(char nickname[], int test_number) {
    int member_index;
    char test_names[FITNESS_TESTS][20] = {
        "1-Mile Run", "Speed Sprint", "Push-ups", "Squats", 
        "Arm Strength", "Swimming", "Weightlifting"
    };
    
    member_index = findMember(nickname);
    if (member_index == -1) {
        printf("Error: Member '%s' not found!\n", nickname);
        return;
    }
    
    if (test_number < 0 || test_number >= FITNESS_TESTS) {
        printf("Error: Test number must be between 0 and %d\n", FITNESS_TESTS-1);
        return;
    }
    
    printf("\n%s's %s result: ", nickname, test_names[test_number]);
    if (health_scores[member_index][test_number] >= 0) {
        printf("%.1f\n", health_scores[member_index][test_number]);
    } else {
        printf("No data entered\n");
    }
}

/* 
 * getHealth() - Main function to view fitness data
 * mode: 0 = show all data, 1 = show one member's data, 2 = show specific test
 */
void getHealth(int mode, char nickname[], int test_number) {
    switch (mode) {
        case 0:
            showAllFitnessData();
            break;
        case 1:
            showMemberFitnessData(nickname);
            break;
        case 2:
            showSpecificTestResult(nickname, test_number);
            break;
        default:
            printf("Invalid mode! Use 0, 1, or 2.\n");
    }
}

/* 
 * Simple menu system for testing our functions
 */
void showMenu() {
    printf("\n=== MILLIWAYS FITNESS TRACKER ===\n");
    printf("1. Add Member\n");
    printf("2. Enter Fitness Data\n");
    printf("3. View All Fitness Data\n");
    printf("4. View Member Fitness Data\n");
    printf("5. View Specific Test Result\n");
    printf("6. Exit\n");
    printf("Choose an option (1-6): ");
}

/* 
 * Main function - where our program starts
 */
int main() {
    int choice;
    char name[MAX_NAME_LENGTH];
    char nickname[MAX_NAME_LENGTH];
    char fitness_data[200];
    int test_num;
    
    printf("Welcome to Milliways Fitness Tracker!\n");
    
    /* Main program loop */
    while (1) {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  /* Add Member */
                printf("Enter member's full name: ");
                scanf(" %[^\n]", name);  /* Read line with spaces */
                printf("Enter member's nickname: ");
                scanf(" %[^\n]", nickname);
                addMember(name, nickname);
                break;
                
            case 2:  /* Enter Fitness Data */
                printf("Enter member's nickname: ");
                scanf(" %[^\n]", nickname);
                printf("Enter 7 fitness scores (comma-separated):\n");
                printf("Format: run,sprint,pushups,squats,armstrength,swimming,weightlifting\n");
                printf("Example: 8.5,12.3,25,30,20,45.2,150\n");
                printf("Your input: ");
                scanf(" %[^\n]", fitness_data);
                setHealth(nickname, fitness_data);
                break;
                
            case 3:  /* View All Data */
                getHealth(0, "", 0);
                break;
                
            case 4:  /* View Member Data */
                printf("Enter member's nickname: ");
                scanf(" %[^\n]", nickname);
                getHealth(1, nickname, 0);
                break;
                
            case 5:  /* View Specific Test */
                printf("Enter member's nickname: ");
                scanf(" %[^\n]", nickname);
                printf("Enter test number (0-6): ");
                scanf("%d", &test_num);
                getHealth(2, nickname, test_num);
                break;
                
            case 6:  /* Exit */
                printf("Thank you for using Milliways Fitness Tracker!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please choose 1-6.\n");
        }
    }
    
    return 0;
}