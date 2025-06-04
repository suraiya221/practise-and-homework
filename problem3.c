#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 10
#define MAX_NAME_LEN 50
#define MAX_ALLERGY_LEN 100
#define DAYS_IN_WEEK 7

typedef struct {
    char name[MAX_NAME_LEN];
    int is_vegan;
    char allergies[MAX_ALLERGY_LEN];
    int daily_calories;
} Member;

typedef struct {
    char day[10];
    char breakfast[50];
    char lunch[50];
    char dinner[50];
    int calories;
} DayMenu;

Member members[MAX_MEMBERS];
DayMenu weekly_menu[DAYS_IN_WEEK];
int member_count = 0;
char days[][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

void init_sample_data() {
    strcpy(members[0].name, "Alice");
    members[0].is_vegan = 1;
    strcpy(members[0].allergies, "nuts");
    members[0].daily_calories = 1800;
    
    strcpy(members[1].name, "Bob");
    members[1].is_vegan = 0;
    strcpy(members[1].allergies, "none");
    members[1].daily_calories = 2200;
    
    strcpy(members[2].name, "Carol");
    members[2].is_vegan = 1;
    strcpy(members[2].allergies, "dairy");
    members[2].daily_calories = 1900;
    
    member_count = 3;
    
    for(int i = 0; i < DAYS_IN_WEEK; i++) {
        strcpy(weekly_menu[i].day, days[i]);
        strcpy(weekly_menu[i].breakfast, "Oatmeal");
        strcpy(weekly_menu[i].lunch, "Salad");
        strcpy(weekly_menu[i].dinner, "Rice Bowl");
        weekly_menu[i].calories = 1500;
    }
}

void display_members() {
    printf("\n=== Millieway's Members ===\n");
    for(int i = 0; i < member_count; i++) {
        printf("%d. %s (Vegan: %s, Allergies: %s, Cal: %d)\n", 
               i+1, members[i].name, 
               members[i].is_vegan ? "Yes" : "No",
               members[i].allergies, members[i].daily_calories);
    }
}

void check_vegans() {
    int vegan_count = 0;
    printf("\n=== Vegan Members ===\n");
    for(int i = 0; i < member_count; i++) {
        if(members[i].is_vegan) {
            printf("- %s\n", members[i].name);
            vegan_count++;
        }
    }
    printf("Total vegans: %d\n", vegan_count);
}

void display_weekly_menu() {
    printf("\n=== Weekly Menu ===\n");
    for(int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s: %s | %s | %s (%d cal)\n",
               weekly_menu[i].day, weekly_menu[i].breakfast,
               weekly_menu[i].lunch, weekly_menu[i].dinner,
               weekly_menu[i].calories);
    }
}

void add_member() {
    if(member_count >= MAX_MEMBERS) {
        printf("Maximum members reached!\n");
        return;
    }
    
    printf("Name: ");
    scanf("%s", members[member_count].name);
    printf("Vegan (1/0): ");
    scanf("%d", &members[member_count].is_vegan);
    printf("Allergies: ");
    scanf("%s", members[member_count].allergies);
    printf("Daily calories: ");
    scanf("%d", &members[member_count].daily_calories);
    
    member_count++;
    printf("Member added!\n");
}

void update_menu() {
    int day_idx;
    printf("Select day (0-6, Mon-Sun): ");
    scanf("%d", &day_idx);
    
    if(day_idx < 0 || day_idx >= DAYS_IN_WEEK) {
        printf("Invalid day!\n");
        return;
    }
    
    printf("Breakfast: ");
    scanf("%s", weekly_menu[day_idx].breakfast);
    printf("Lunch: ");
    scanf("%s", weekly_menu[day_idx].lunch);
    printf("Dinner: ");
    scanf("%s", weekly_menu[day_idx].dinner);
    printf("Total calories: ");
    scanf("%d", &weekly_menu[day_idx].calories);
    
    printf("Menu updated for %s!\n", weekly_menu[day_idx].day);
}

int main() {
    init_sample_data();
    int choice;
    
    printf("=== Magratea Diet Management System ===\n");
    
    while(1) {
        printf("\n1. View Members\n2. Check Vegans\n3. View Weekly Menu\n");
        printf("4. Add Member\n5. Update Menu\n6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: display_members(); break;
            case 2: check_vegans(); break;
            case 3: display_weekly_menu(); break;
            case 4: add_member(); break;
            case 5: update_menu(); break;
            case 6: return 0;
            default: printf("Invalid choice!\n");
        }
    }
    
    return 0;
}